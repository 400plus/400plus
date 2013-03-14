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
#include "persist.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"

#include "actions.h"

void set_intermediate_iso();
void repeat_last_script();

void button_action(button_action_t action);

void start_up() {

#if 0
	debug_log("AF: Creating directories (%#x)", GetErrorNum());

	if (FIO_CreateDirectory(PathBase))
		printf_log(8,8,"Error[%#x]: CreateDir(" PathBase ")", GetErrorNum());
	if (FIO_CreateDirectory(PathLogs))
		printf_log(8,8,"Error[%#x]: CreateDir(" PathLogs ")", GetErrorNum());
	if (FIO_CreateDirectory(PathLang))
		printf_log(8,8,"Error[%#x]: CreateDir(" PathLang ")", GetErrorNum());
	if (FIO_CreateDirectory(PathPresets))
		printf_log(8,8,"Error[%#x]: CreateDir(" PathPresets ")", GetErrorNum());
#endif

	// Recover persisting information
	persist_read();

	// Read settings from file
	settings_read();

	// If configured, start debug mode
	if (settings.debug_on_poweron)
		start_debug_mode();

	// If configured, restore AEB
	if (settings.persist_aeb)
		send_to_intercom(IC_SET_AE_BKT, persist.aeb);

	// Enable IR remote
	// i'm not sure where to call this? perhaps this isn't the right place.
	if (settings.remote_enable)
		remote_on();

	// Enable extended ISOs
	// Enable (hidden) CFn.8 for ISO H
	send_to_intercom(IC_SET_CF_EXTEND_ISO, 1);

	// Enable realtime ISO change
	send_to_intercom(IC_SET_REALTIME_ISO_0, 0);
	send_to_intercom(IC_SET_REALTIME_ISO_1, 0);

	// turn off the blue led after it was lighten by our my_task_MainCtrl()
	eventproc_EdLedOff();

	// Set current language
	enqueue_action(lang_pack_init);

	// Read custom modes configuration from file
	enqueue_action(cmodes_read);

	// And optionally apply a custom mode
	enqueue_action(cmode_recall);

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

void drivemode_set() {
	if (settings.remote_enable) {
		printf_log(8,8, "[400Plus-DRIVE]: re-setting IR remote enable");
		remote_on();
	}

	if (settings.remote_delay) {
		printf_log(8,8, "[400Plus-DRIVE]: re-setting IR remote delay");
		remote_delay(true);
	}
}

void toggle_img_format() {
	static int first_call = true;

	if (!first_call && AE_IS_AUTO(DPData.ae)) {
		switch (DPData.img_format) {
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
	char message[LP_MAX_WORD];

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, !DPData.cf_mirror_up_lock);

	sprintf(message, "%s: %s", LP_WORD(L_A_MIRROR_LOCKUP), DPData.cf_mirror_up_lock ? LP_WORD(L_A_YES) : LP_WORD(L_A_NO));
	display_message_set(message, ACTION_MSG_TIMEOUT);
}

void toggle_CfEmitFlash() {
	char message[LP_MAX_WORD];

	send_to_intercom(IC_SET_CF_EMIT_FLASH, !DPData.cf_emit_flash);

	sprintf(message, "%s: %s",LP_WORD(L_A_FLASH),(DPData.cf_emit_flash ? LP_WORD(L_A_NO) : LP_WORD(L_A_YES)));
	display_message_set(message, ACTION_MSG_TIMEOUT);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, !DPData.cf_flash_sync_rear);
}

void toggle_AEB() {
	int aeb;
	char message[LP_MAX_WORD];

	static int last_toggle = 0;

	if (timestamp() - last_toggle < ACTION_AEB_TIMEOUT)
		// Button was pressed recently: roll over all range
		aeb = (EV_TRUNC(DPData.ae_bkt) + EV_CODE(1, 0)) % EV_CODE(6, 0);
	else if (DPData.ae_bkt)
		// Button was pressed long ago, and AEB is on: switch it off
		aeb = EC_ZERO;
	else
		// Button was pressed long ago, and AEB is off: switch it on
		aeb = persist.last_aeb;

	send_to_intercom(IC_SET_AE_BKT, aeb);

	persist.aeb = aeb;

	if (persist.aeb)
		persist.last_aeb = persist.aeb;

	enqueue_action(persist_write);
	last_toggle = timestamp();
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

void repeat_last_script() {
	switch (persist.last_script) {
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

void button_action(button_action_t action) {
	switch (action) {
	case BUTTON_ACTION_ISO:
		set_intermediate_iso();
		break;
	case BUTTON_ACTION_SCRIPT:
		repeat_last_script();
		break;
	case BUTTON_ACTION_MLU:
		toggle_CfMLU();
		break;
	case BUTTON_ACTION_AEB:
		toggle_AEB();
		break;
	case BUTTON_ACTION_HACK_MENU:
		menu_main_start();
		break;
	case BUTTON_ACTION_TOGGLE_FLASH:
		toggle_CfEmitFlash();
		break;
	default:
		break;
	}
}
