#include "main.h"
#include "utils.h"
#include "display.h"
#include "settings.h"
#include "menu_shortcuts.h"
#include "firmware.h"
#include "languages.h"

#include "tasks.h"

void set_intermediate_iso();

void start_up() {
	// Wait for camera to settle down
	SleepTask(1000);

	start_debug_mode();

	LangPlus_lang_packs_init(); // initialize lang pack strings
	change_lang_pack();

	// Enable (hidden) CFn.8 for ISO H
	if (!cameraMode.cf_extend_iso)
		send_to_intercom(EVENT_SET_CF_EXTEND_ISO, 1, 1);

	// Enable realtime ISO change
	send_to_intercom(EVENT_SET_REALTIME_ISO_0, 0, 0);
	send_to_intercom(EVENT_SET_REALTIME_ISO_1, 0, 0);

	// Read (and apply) settings from file
	if (settings_read())
		settings_apply();

}

void dp_action() {
	if (settings.shortcuts_menu || cameraMode.ae > 6) {
		menu_shortcuts_start();
	} else {
		set_intermediate_iso();
		display_refresh();
	}
}

void set_metering_spot() {
	int metering_spot = METERING_MODE_SPOT;

	press_button(BUTTON_SET);
	send_to_intercom(EVENT_SET_METERING, 1, metering_spot);
	print_icu_info();

	beep();
}

void set_whitebalance_colortemp() {
	press_button(BUTTON_SET);
	send_to_intercom(EVENT_SET_WB,         1, WB_MODE_COLORTEMP);
	send_to_intercom(EVENT_SET_COLOR_TEMP, 2, settings.color_temp);
	print_icu_info();

	beep();
}

void set_iso_high() {
	press_button(BUTTON_SET);
	send_to_intercom(EVENT_SET_ISO, 2, 0x6F);
	print_icu_info();

	beep();
}

void toggle_raw_jpeg() {
	if (cameraMode.ae > 6) {
		// Only for non-creative modes
		send_to_intercom(EVENT_SET_IMG_FORMAT, 1, cameraMode.img_format ^ 0x03);
	}
}

void toggle_CfMLU() {
	send_to_intercom(EVENT_SET_CF_MIRROR_UP_LOCK, 1, cameraMode.cf_mirror_up_lock ^ 0x01);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(EVENT_SET_CF_FLASH_SYNC_REAR, 1, cameraMode.cf_flash_sync_rear ^ 0x01);
}

void set_intermediate_iso() {
	if (cameraMode.ae < 6) {
		int iso = iso_roll(cameraMode.iso);
		send_to_intercom(EVENT_SET_ISO, 2, iso);
	}

	SleepTask(50);
}

void restore_iso() {
	int iso;

	if (cameraMode.iso >= 0x68) {
		iso = 0x68;
	} else if (cameraMode.iso >= 0x60) {
		iso = 0x60;
	} else if (cameraMode.iso >= 0x58) {
		iso = 0x58;
	} else if (cameraMode.iso >= 0x50) {
		iso = 0x50;
	} else {
		iso = 0x48;
	}

	send_to_intercom(EVENT_SET_ISO, 2, iso);
}

void restore_wb() {
	if (cameraMode.wb == WB_MODE_COLORTEMP) {
		send_to_intercom(EVENT_SET_WB, 1, WB_MODE_AUTO);
	}
}

void restore_metering() {
	if (cameraMode.metering == METERING_MODE_SPOT)
		send_to_intercom(EVENT_SET_METERING, 1, METERING_MODE_EVAL);
}
