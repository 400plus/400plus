/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>
#include <stdio.h>

#include "macros.h"
#include "main.h"
#include "firmware.h"

#include "bmp.h"
#include "cmodes.h"
#include "debug.h"
#include "display.h"
#include "exposure.h"
#include "languages.h"
#include "memspy.h"
#include "menu_main.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"

#include "actions.h"

void set_intermediate_iso();
void repeat_last_script();

void button_action(type_BUTTON_ACTION action);

void start_up() {
	// Read settings from file
	settings_read();

	// If configured, start debug mode
	if (settings.debug_on_poweron)
		start_debug_mode();

	// Set current language
	lang_pack_init();

	// Read custom modes configuration from file
	cmodes_read();

#if 0
	// vram testing
	SleepTask(1000);
	beep();

	int i;
	for (i=0; i<vram_size; i+=4) {
		MEM(vram_start+i)= 0x88888888;
	}
	beep();

	//bmp_draw_palette();
	bmp_printf(FONT_LARGE, 0, 50, "Hello World!");
	SleepTask(5000);

	// vram testing - end
#endif

#ifdef MEMSPY
	debug_log("starting memspy task");
	CreateTask("memspy", 0x1e, 0x1000, memspy_task, 0);
#endif

	// enable IR remote
	// i'm not sure where to call this? perhaps this isnt the right place.
	if (settings.remote_enable) {
		remote_on();
	}

	// Enable (hidden) CFn.8 for ISO H
	send_to_intercom(IC_SET_CF_EXTEND_ISO, 1);

	// Enable realtime ISO change
	send_to_intercom(IC_SET_REALTIME_ISO_0, 0);
	send_to_intercom(IC_SET_REALTIME_ISO_1, 0);

	// turn off the blue led after it was lighten by our my_task_MainCtrl()
	eventproc_EdLedOff();

#if 0
	debug_log("=== DUMPING DDD ===");
	printf_DDD_log( (void*)(int)(0x00007604+0x38) );

	debug_log("maindlg @ 0x%08X, handler @ 0x%08X", hMainDialog, hMainDialog->event_handler);

	debug_log("dumping");
	long *addr   = (long*) 0x7F0000;

	int file = FIO_OpenFile("A:/dump.bin", O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, addr, 0xFFFF);
		FIO_CloseFile(file);
		beep();
	}
#endif
}

void set_metering_spot() {
	press_button(IC_BUTTON_SET);
	send_to_intercom(IC_SET_METERING, METERING_MODE_SPOT);
	print_icu_info();

	beep();
}

void set_whitebalance_colortemp() {
	press_button(IC_BUTTON_SET);
	send_to_intercom(IC_SET_WB, WB_MODE_COLORTEMP);
	print_icu_info();

	beep();
}

void set_intermediate_iso() {
	if (AE_IS_CREATIVE(DPData.ae)) {
		send_to_intercom(IC_SET_ISO, iso_roll(DPData.iso));
		print_icu_info();
		display_refresh();
	}
}

void toggle_img_format() {
	static int first_call = true;

	if (!first_call && AE_IS_AUTO(DPData.ae)) {
		switch(DPData.img_format) {
		case IMG_FORMAT_JPG:
			send_to_intercom(IC_SET_IMG_FORMAT, IMG_FORMAT_RAW);
			break;
		case IMG_FORMAT_RAW:
			send_to_intercom(IC_SET_IMG_FORMAT, IMG_FORMAT_JPG | IMG_FORMAT_RAW);
			break;
		case IMG_FORMAT_JPG | IMG_FORMAT_RAW:
			send_to_intercom(IC_SET_IMG_FORMAT, IMG_FORMAT_JPG);
			break;
		}

		send_to_intercom(IC_SET_IMG_QUALITY, IMG_QUALITY_HIGH);
		send_to_intercom(IC_SET_IMG_SIZE,    IMG_SIZE_L);
	}

	first_call = false;
}

void toggle_CfMLU() {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, DPData.cf_mirror_up_lock ^ 0x01);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, DPData.cf_flash_sync_rear ^ 0x01);
}

void toggle_AEB() {
	send_to_intercom(IC_SET_AE_BKT, (EV_TRUNC(DPData.ae_bkt) + 0010) % 0030);
}

void restore_iso() {
	send_to_intercom(IC_SET_ISO, EV_TRUNC(DPData.iso));
}

void restore_wb() {
	if (DPData.wb == WB_MODE_COLORTEMP)
		send_to_intercom(IC_SET_WB, WB_MODE_AUTO);
}

void restore_metering() {
	if (DPData.metering == METERING_MODE_SPOT)
		send_to_intercom(IC_SET_METERING, METERING_MODE_EVAL);
}

void autoiso() {
	ev_t limit;

	ec_t ec = EC_ZERO;
	ev_t ev = EV_ZERO;

	iso_t newiso;

	switch(DPData.ae) {
	case AE_MODE_M:
		if (DPData.tv_val == TV_VAL_BULB) {
			// BULB mode: disable AutoISO and set ISO100
			settings.autoiso_enable = false;

			send_to_intercom(IC_SET_ISO, ISO_MIN);
			enqueue_action(restore_display);
		} else {
			// M mode: set ISO to match exposure
			ec = - (status.measured_ec - status.ev_comp);

			// Normalize an apply new ISO
			if (ec != EC_ZERO) {
				newiso = DPData.iso + ec;
				newiso = CLAMP(newiso, settings.autoiso_miniso, settings.autoiso_maxiso);
				newiso = EV_ROUND(newiso);

				send_to_intercom(IC_SET_ISO, newiso);
				enqueue_action(restore_display);
			}
		}

		return;
	case AE_MODE_P:
	case AE_MODE_AV:
		// P / Av mode: raise ISO if shutter time is lower than limit
		ev    = status.measured_tv;
		limit = settings.autoiso_mintv;
		break;
	case AE_MODE_TV:
		// Tv mode: raise ISO if apperture is larger than lens' max plus offset
		ev    = status.measured_av;
		limit = DPData.avo + settings.autoiso_maxav;
		break;
	default:
		return;
	}

	// Decide whether we need to change current ISO
	if (ev != EC_ZERO) {
		if (ev < limit)
			ec = (limit - ev) + EV_CODE(1, 0);
		else if (ev >= limit + EV_CODE(1, 0))
			ec = (limit - ev);
	}

	// Normalize an apply new ISO
	if (ec != EC_ZERO) {
		newiso = DPData.iso + ec;
		newiso = CLAMP(newiso, settings.autoiso_miniso, settings.autoiso_maxiso);
		newiso = EV_TRUNC(newiso);

		send_to_intercom(IC_SET_ISO, newiso);
		enqueue_action(restore_display);
	}
}

void autoiso_enable() {
	press_button(IC_BUTTON_SET);

	if (!settings.autoiso_enable) {
		settings.autoiso_enable = true;
		settings_write();
	}

	print_icu_info();
	beep();
}

void autoiso_disable() {
	if (settings.autoiso_enable) {
		settings.autoiso_enable = false;
		settings_write();
	}
}

void repeat_last_script() {
	switch (status.last_script) {
	case SCRIPT_EXT_AEB:
		script_ext_aeb();
		break;
	case SCRIPT_EFL_AEB:
		script_efl_aeb();
		break;
	case SCRIPT_ISO_AEB:
		script_iso_aeb();
		break;
	case SCRIPT_INTERVAL:
		script_interval();
		break;
	case SCRIPT_WAVE:
		script_wave();
		break;
	case SCRIPT_TIMER:
		script_self_timer();
		break;
	default:
		break;
	}
}

void button_jump_action() {
	button_action(settings.button_jump);
}

void button_trash_action() {
	button_action(settings.button_trash);
}

void button_action(type_BUTTON_ACTION action) {
	switch (action) {
	case BUTTON_ACTION_ISO:
		set_intermediate_iso();
		break;
	case BUTTON_ACTION_SCRIPT:
		repeat_last_script();
		break;
	case BUTTON_ACTION_MLU:
		toggle_CfMLU();
		beep();
		break;
	case BUTTON_ACTION_AEB:
		toggle_AEB();
		beep();
		break;
	case BUTTON_ACTION_HACK_MENU:
		menu_main_start();
		break;
	case BUTTON_ACTION_TOGGLE_FLASH:
		send_to_intercom(IC_SET_CF_EMIT_FLASH, !DPData.cf_emit_flash);
		char buf[20];
		sprintf(buf, "%-11s: %-5s",LP_WORD(L_S_FLASH),(DPData.cf_emit_flash ? LP_WORD(L_V_NO) : LP_WORD(L_V_YES)));
		bmp_printf_timed(250, FONT_LARGE, 0, 0, buf);
		break;
	default:
		break;
	}
}
