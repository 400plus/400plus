#include <vxworks.h>
#include <dirent.h>
#include <stdio.h>

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
#include "persist.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"
#include "intercom.h"

#include "actions.h"

void set_intermediate_iso(void);
void repeat_last_script  (void);

void button_action_down(button_action_t action);
void button_action_up  (button_action_t action);

#ifdef DEV_BTN_ACTION
void dev_btn_action() {
	// quick shortcut for developers to test stuff
	beep();
	ptp_dump_info();
}
#endif

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

		// No need to set a proper value here,
		// we hacked this function at hack_item_set_label_int()
		dialog_set_property_str(hMainDialog, 0x04, "0000");

		print_icu_info();
		display_refresh();
	}
}

void drivemode_set() {
	if (settings.remote_enable) {
		debug_log("Re-setting IR remote => enable");
		remote_on();
	}

	if (settings.remote_delay) {
		debug_log("Re-setting IR remote => delay");
		remote_delay(TRUE);
	}
}

void toggle_img_format() {
	static int first_call = TRUE;

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

	first_call = FALSE;
}

void toggle_CfMLU() {
	char message[LP_MAX_WORD];

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, !DPData.cf_mirror_up_lock);

	sprintf(message, "%s: %s", LP_WORD(L_A_MIRROR_LOCKUP), DPData.cf_mirror_up_lock ? LP_WORD(L_A_YES) : LP_WORD(L_A_NO));
	display_message_set(message, ACTION_MSG_TIMEOUT);
}

void toggle_CfEmitFlash(void) {
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

void repeat_last_script(void) {
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

void button_jump_down() {
	button_action_down(settings.button_jump);
}

void button_jump_up() {
	button_action_up(settings.button_jump);
}

void button_trash_down() {
	button_action_down(settings.button_trash);
}

void button_trash_up() {
	button_action_up(settings.button_trash);
}

void button_action_down(button_action_t action) {
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
#ifdef DEV_BTN_ACTION
	case BUTTON_ACTION_DEV_BTN:
		dev_btn_action();
		break;
#endif
	default:
		break;
	}
}

void button_action_up(button_action_t action) {
}
