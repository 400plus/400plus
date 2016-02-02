#include "firmware.h"

#include "main.h"
#include "macros.h"

#include "autoiso.h"
#include "display.h"
#include "persist.h"
#include "settings.h"
#include "scripts.h"
#include "utils.h"
#include "intercom.h"

#include "shortcuts.h"

void repeat_last_script     (void);

void shortcut_start(shortcut_action_t action);

void shortcut_iso_toggle (void);
void shortcut_aeb_toggle (void);

void shortcut_iso_set    (iso_t iso);
void shortcut_mlu_set    (int status);
void shortcut_efl_set    (int status);
void shortcut_f2c_set    (int status);
void shortcut_aeb_set    (int aeb);
void shortcut_disp_set   (int brightness);

void shortcut_jump() {
	shortcut_start(settings.shortcut_jump);
}

void shortcut_trash() {
	shortcut_start(settings.shortcut_trash);
}

void shortcut_disp() {
	if (settings.button_disp) {
		status.shortcut_running = SHORTCUT_ACTION_DISPLAY;

		if (FLAG_GUI_MODE == GUIMODE_OFF)
			press_button(IC_BUTTON_DISP);
	} else
		press_button(IC_BUTTON_DISP);
}

void shortcut_start(shortcut_action_t action) {
	status.shortcut_running = action;

	switch (action) {
	case SHORTCUT_ACTION_SCRIPT:
		repeat_last_script();
		break;
	case SHORTCUT_ACTION_HACK_MENU:
		menu_main_start();
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

void shortcut_event_disp() {
	press_button(IC_BUTTON_DISP);
	enqueue_action(beep);
	shortcut_event_end();
}

void shortcut_event_end() {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_AEB:
		enqueue_action(persist_write);
		break;
	default:
		break;
	}

	status.shortcut_running = SHORTCUT_ACTION_NONE;
}

void shortcut_event_set(void) {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_ISO:
		shortcut_iso_toggle();
		break;
	case SHORTCUT_ACTION_AEB:
		shortcut_aeb_toggle();
		break;
	case SHORTCUT_ACTION_DISPLAY:
		enqueue_action(beep);
		shortcut_event_end();
		break;
	default:
		break;
	}
}

void shortcut_event_up(void) {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_ISO:
		shortcut_iso_set(iso_next(DPData.iso));
		break;
	case SHORTCUT_ACTION_MLU:
		shortcut_mlu_set(TRUE);
		break;
	case SHORTCUT_ACTION_AEB:
		shortcut_aeb_set(MIN((EV_TRUNC(DPData.ae_bkt) + EV_CODE(1, 0)), EC_MAX));
		break;
	case SHORTCUT_ACTION_TOGGLE_FLASH:
		shortcut_efl_set(FALSE);
		break;
	case SHORTCUT_ACTION_DISPLAY:
		shortcut_disp_set(7);
		break;
	default:
		break;
	}
}

void shortcut_event_down(void) {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_ISO:
		shortcut_iso_set(iso_prev(DPData.iso));
		break;
	case SHORTCUT_ACTION_MLU:
		shortcut_mlu_set(FALSE);
		break;
	case SHORTCUT_ACTION_AEB:
		shortcut_aeb_set(MAX((EV_TRUNC(DPData.ae_bkt) - EV_CODE(1, 0)), EC_ZERO));
		break;
	case SHORTCUT_ACTION_TOGGLE_FLASH:
		shortcut_efl_set(TRUE);
		break;
	case SHORTCUT_ACTION_DISPLAY:
		shortcut_disp_set(1);
		break;
	default:
		break;
	}
}

void shortcut_event_right(void) {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_ISO:
		shortcut_iso_set(iso_inc(DPData.iso));
		break;
	case SHORTCUT_ACTION_AEB:
		shortcut_aeb_set(MIN(ec_inc(DPData.ae_bkt), EC_MAX));
		break;
	case SHORTCUT_ACTION_TOGGLE_FLASH:
		shortcut_f2c_set(TRUE);
		break;
	case SHORTCUT_ACTION_DISPLAY:
		shortcut_disp_set(MIN(DPData.lcd_brightness + 1, 7));
		break;
	default:
		break;
	}
}

void shortcut_event_left(void) {
	switch (status.shortcut_running) {
	case SHORTCUT_ACTION_ISO:
		shortcut_iso_set(iso_dec(DPData.iso));
		break;
	case SHORTCUT_ACTION_AEB:
		shortcut_aeb_set(MAX(ec_dec(DPData.ae_bkt), EV_ZERO));
		break;
	case SHORTCUT_ACTION_TOGGLE_FLASH:
		shortcut_f2c_set(FALSE);
		break;
	case SHORTCUT_ACTION_DISPLAY:
		shortcut_disp_set(MAX(DPData.lcd_brightness - 1, 1));
		break;
	default:
		break;
	}
}

void shortcut_iso_toggle() {
	char label[8] = "AUTO";

	settings.autoiso_enable = ! settings.autoiso_enable;
	enqueue_action(settings_write);

	if (!settings.autoiso_enable)
		iso_print(label, DPData.iso);

	dialog_item_set_label(hMainDialog, 0x08, label, 4, 0x04);
	display_refresh();
}

void shortcut_aeb_toggle() {
	shortcut_aeb_set(DPData.ae_bkt ? EC_ZERO : persist.last_aeb);
}

void shortcut_iso_set(iso_t iso) {
	char label[8] = "AUTO";

	if (settings.autoiso_enable) {
		settings.autoiso_enable = FALSE;
		enqueue_action(settings_write);
		enqueue_action(beep);
	}

	send_to_intercom(IC_SET_ISO, iso);
	iso_print(label, iso);

	dialog_item_set_label(hMainDialog, 0x08, label, 4, 0x04);
	display_refresh();
}

void shortcut_mlu_set(int status) {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, status);
	enqueue_action(beep);
}

void shortcut_efl_set(int status) {
	send_to_intercom(IC_SET_CF_EMIT_FLASH, status);
	enqueue_action(beep);
}

void shortcut_f2c_set(int status) {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, status);
	enqueue_action(beep);
}

void shortcut_aeb_set(int aeb) {
	send_to_intercom(IC_SET_AE_BKT, aeb);

	persist.aeb = aeb;

	if (persist.aeb)
		persist.last_aeb = persist.aeb;
}

void shortcut_disp_set(int brightness) {
	send_to_intercom(IC_SET_LCD_BRIGHTNESS, brightness);
}

#ifdef DEV_BTN_ACTION
void dev_btn_action() {
	// quick shortcut for developers to test stuff
	beep();
	ptp_dump_info();
}
#endif

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
