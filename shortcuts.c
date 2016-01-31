#include "firmware.h"

#include "main.h"

#include "display.h"
#include "persist.h"
#include "settings.h"
#include "scripts.h"
#include "utils.h"
#include "intercom.h"

#include "shortcuts.h"

void toggle_CfMLU           (void);
void toggle_CfEmitFlash     (void);
void toggle_CfFlashSyncRear (void);
void toggle_AEB             (void);

void cycle_intermediate_iso (void);
void repeat_last_script     (void);

void shortcut_down(shortcut_action_t action);
void shortcut_up  (shortcut_action_t action);

#ifdef DEV_BTN_ACTION
void dev_btn_action() {
	// quick shortcut for developers to test stuff
	beep();
	ptp_dump_info();
}
#endif

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

void cycle_intermediate_iso() {
	if (AE_IS_CREATIVE(DPData.ae)) {
		send_to_intercom(IC_SET_ISO, iso_roll(DPData.iso));

		// No need to set a proper value here,
		// we hacked this function at hack_item_set_label_int()
		dialog_set_property_str(hMainDialog, 0x04, "0000");

		print_icu_info();
		display_refresh();
	}
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

void shortcut_jump_down() {
	shortcut_down(settings.button_jump);
}

void shortcut_jump_up() {
	shortcut_up(settings.button_jump);
}

void shortcut_trash_down() {
	shortcut_down(settings.button_trash);
}

void shortcut_trash_up() {
	shortcut_up(settings.button_trash);
}

void shortcut_down(shortcut_action_t action) {
	switch (action) {
	case SHORTCUT_ACTION_ISO:
		cycle_intermediate_iso();
		break;
	case SHORTCUT_ACTION_SCRIPT:
		repeat_last_script();
		break;
	case SHORTCUT_ACTION_MLU:
		toggle_CfMLU();
		break;
	case SHORTCUT_ACTION_AEB:
		toggle_AEB();
		break;
	case SHORTCUT_ACTION_HACK_MENU:
		menu_main_start();
		break;
	case SHORTCUT_ACTION_TOGGLE_FLASH:
		toggle_CfEmitFlash();
		break;
#ifdef DEV_BTN_ACTION
	case SHORTCUT_ACTION_DEV_BTN:
		dev_btn_action();
		break;
#endif
	default:
		break;
	}
}

void shortcut_up(shortcut_action_t action) {
}
