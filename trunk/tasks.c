/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "macros.h"
#include "main.h"
#include "firmware.h"

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "exposure.h"
#include "languages.h"
#include "memspy.h"
#include "menu_main.h"
#include "presets.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"

#include "tasks.h"

void set_intermediate_iso();
void repeat_last_script();

void button_task(type_BUTTON_ACTION action);

void start_up() {
	// Wait for camera to settle down
	SleepTask(1000);

	// Read settings from file
	settings_read();

	if (settings.debug_on_poweron)
		start_debug_mode();

	SleepTask(100);

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

	// Set current language
	lang_pack_init();

	// Enable (hidden) CFn.8 for ISO H
	send_to_intercom(IC_SET_CF_EXTEND_ISO, 1, 1);

	// Enable realtime ISO change
	send_to_intercom(IC_SET_REALTIME_ISO_0, 0, 0);
	send_to_intercom(IC_SET_REALTIME_ISO_1, 0, 0);

	// Read presets from file
	presets_read();

	// turn off the blue led after it was lighten by our my_task_MainCtrl()
	eventproc_EdLedOff();

	// We are no longer booting up
	status.booting = false;

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
	send_to_intercom(IC_SET_METERING, 1, METERING_MODE_SPOT);
	print_icu_info();

	beep();
}

void set_whitebalance_colortemp() {
	press_button(IC_BUTTON_SET);
	send_to_intercom(IC_SET_WB, 1, WB_MODE_COLORTEMP);
	print_icu_info();

	beep();
}

void set_intermediate_iso() {
	if (DPData.ae < AE_MODE_AUTO) {
		send_to_intercom(IC_SET_ISO, 2, iso_roll(DPData.iso));
		print_icu_info();
		display_refresh();
	}
}

void toggle_img_format() {
	static int first_call = true;

	if (!first_call && DPData.ae >= AE_MODE_AUTO) {
		switch(DPData.img_format) {
		case IMG_FORMAT_JPG:
			send_to_intercom(IC_SET_IMG_FORMAT, 1, IMG_FORMAT_RAW);
			break;
		case IMG_FORMAT_RAW:
			send_to_intercom(IC_SET_IMG_FORMAT, 1, IMG_FORMAT_JPG | IMG_FORMAT_RAW);
			break;
		case IMG_FORMAT_JPG | IMG_FORMAT_RAW:
			send_to_intercom(IC_SET_IMG_FORMAT, 1, IMG_FORMAT_JPG);
			break;
		}

		send_to_intercom(IC_SET_IMG_QUALITY, 1, IMG_QUALITY_HIGH);
		send_to_intercom(IC_SET_IMG_SIZE,    1, IMG_SIZE_L);
	}

	first_call = false;
}

void toggle_CfMLU() {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, DPData.cf_mirror_up_lock ^ 0x01);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, DPData.cf_flash_sync_rear ^ 0x01);
}

void toggle_AEB() {
	send_to_intercom(IC_SET_AE_BKT, 1, (EV_TRUNC(DPData.ae_bkt) + 0010) % 0030);
}

void restore_iso() {
	send_to_intercom(IC_SET_ISO, 2, EV_TRUNC(DPData.iso));
}

void restore_wb() {
	if (DPData.wb == WB_MODE_COLORTEMP)
		send_to_intercom(IC_SET_WB, 1, WB_MODE_AUTO);
}

void restore_metering() {
	if (DPData.metering == METERING_MODE_SPOT)
		send_to_intercom(IC_SET_METERING, 1, METERING_MODE_EVAL);
}

void autoiso() {
	ev_t limit;

	ec_t ev      = EC_ZERO;
	ec_t measure = EC_ZERO;

	iso_t newiso = DPData.iso;

	switch(DPData.ae) {
	case AE_MODE_M:
		ev = status.measured_ev - status.ev_comp;

		if (ev != EC_ZERO) {
			newiso = (DPData.iso - ev);
			newiso = MIN(newiso, ISO_EXT);
			newiso = MAX(newiso, ISO_MIN);

			send_to_intercom(IC_SET_ISO, 2, newiso);
			ENQUEUE_TASK(restore_display);
		}

		return;
	case AE_MODE_P:
	case AE_MODE_AV:
		measure = status.measured_tv;
		limit   = settings.autoiso_mintv;
		break;
	case AE_MODE_TV:
		measure = status.measured_av;
		limit   = settings.autoiso_maxav;
		break;
	default:
		break;
	}

	if (measure != EC_ZERO) {
		if (measure < limit)
			ev = (limit - measure) + 0010;
		else if (measure >= limit + 0010)
			ev = (limit - measure);
	}

	if (ev != EC_ZERO) {
		newiso = (DPData.iso + ev);

		newiso = MIN(newiso, settings.autoiso_maxiso);
		newiso = MAX(newiso, settings.autoiso_miniso);

		send_to_intercom(IC_SET_ISO, 2, EV_TRUNC(newiso));
		ENQUEUE_TASK(restore_display);
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

void button_jump_task() {
	button_task(settings.button_jump);
}

void button_trash_task() {
	button_task(settings.button_trash);
}

void button_task(type_BUTTON_ACTION action) {
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
	default:
		break;
	}
}
