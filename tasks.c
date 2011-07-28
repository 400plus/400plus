#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu_shortcuts.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "tasks.h"

void set_intermediate_iso();
int img_setting;

void start_up() {
	// Wait for camera to settle down
	SleepTask(1000);

	// Read settings from file
	settings_read();

	if (settings.debug_on_poweron)
		start_debug_mode();

	SleepTask(100);

	// enable IR remote
	// i'm not sure where to call this? perhaps this isnt the right place.
	if (settings.remote_enable) {
		eventproc_RemOn();
	}

	// Set current language
	lang_pack_config();

	// Enable (hidden) CFn.8 for ISO H
	send_to_intercom(IC_SET_CF_EXTEND_ISO, 1, 1);

	// Enable realtime ISO change
	send_to_intercom(IC_SET_REALTIME_ISO_0, 0, 0);
	send_to_intercom(IC_SET_REALTIME_ISO_1, 0, 0);

	// Read presets from file
	presets_read();

	// turn off the blue led after it was lighten by our my_task_MainCtrl()
	eventproc_EdLedOff();

	// set img_setting
	set_img_setting();

	// We are no longer booting up
	status.booting = FALSE;
}

void dp_action() {
	if (settings.shortcuts_menu || cameraMode->ae > 6) {
		menu_shortcuts_start();
	} else {
		set_intermediate_iso();
		display_refresh();
	}
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

void set_iso_high() {
	press_button(IC_BUTTON_SET);
	send_to_intercom(IC_SET_ISO, 2, 0x70);
	print_icu_info();

	beep();
}

void set_img_setting() {
	img_setting = IMG_SETTING_RAW;

	if (cameraMode->img_format == IMG_FORMAT_RAW) {
		img_setting = IMG_SETTING_RAW;
	} else if (cameraMode->img_format == IMG_FORMAT_RAW_JPG) {
		img_setting = IMG_SETTING_RAW_JPEG_L;
	} else if (cameraMode->img_format == IMG_FORMAT_JPG) {
		switch (cameraMode->img_size) {
			case IMG_SIZE_JPEG_L:
				switch (cameraMode->img_quality) {
					case IMG_QUALITY_HIGH:
						img_setting = IMG_SETTING_JPEG_L_HIGH;
						break;
					case IMG_QUALITY_LOW:
						img_setting = IMG_SETTING_JPEG_L_LOW;
						break;
				}
				break;
			case IMG_SIZE_JPEG_M:
				switch (cameraMode->img_quality) {
					case IMG_QUALITY_HIGH:
						img_setting = IMG_SETTING_JPEG_M_HIGH;
						break;
					case IMG_QUALITY_LOW:
						img_setting = IMG_SETTING_JPEG_M_LOW;
						break;
				}
				break;
			case IMG_SIZE_JPEG_S:
				switch (cameraMode->img_quality) {
					case IMG_QUALITY_HIGH:
						img_setting = IMG_SETTING_JPEG_S_HIGH;
						break;
					case IMG_QUALITY_LOW:
						img_setting = IMG_SETTING_JPEG_S_LOW;
						break;
				}
				break;
		}
	}

	toggle_img_setting();
}

void toggle_img_setting() {
	switch (img_setting) {
		case IMG_SETTING_RAW:
			cameraMode->img_format = IMG_FORMAT_RAW;
			cameraMode->img_quality = IMG_QUALITY_HIGH;
			cameraMode->img_size = IMG_SIZE_JPEG_L;
			img_setting = IMG_SETTING_RAW_JPEG_L;
			break;
		case IMG_SETTING_RAW_JPEG_L:
			cameraMode->img_format = IMG_FORMAT_RAW_JPG;
			cameraMode->img_quality = IMG_QUALITY_HIGH;
			cameraMode->img_size = IMG_SIZE_JPEG_L;
			img_setting = IMG_SETTING_JPEG_L_HIGH;
			break;
		case IMG_SETTING_JPEG_L_HIGH:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_HIGH;
			cameraMode->img_size = IMG_SIZE_JPEG_L;
			img_setting = IMG_SETTING_JPEG_L_LOW;
			break;
		case IMG_SETTING_JPEG_L_LOW:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_LOW;
			cameraMode->img_size = IMG_SIZE_JPEG_L;
			img_setting = IMG_SETTING_JPEG_M_HIGH;
			break;
		case IMG_SETTING_JPEG_M_HIGH:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_HIGH;
			cameraMode->img_size = IMG_SIZE_JPEG_M;
			img_setting = IMG_SETTING_JPEG_M_LOW;
			break;
		case IMG_SETTING_JPEG_M_LOW:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_LOW;
			cameraMode->img_size = IMG_SIZE_JPEG_M;
			img_setting = IMG_SETTING_JPEG_S_HIGH;
			break;
		case IMG_SETTING_JPEG_S_HIGH:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_HIGH;
			cameraMode->img_size = IMG_SIZE_JPEG_S;
			img_setting = IMG_SETTING_JPEG_S_LOW;
			break;
		case IMG_SETTING_JPEG_S_LOW:
			cameraMode->img_format = IMG_FORMAT_JPG;
			cameraMode->img_quality = IMG_QUALITY_LOW;
			cameraMode->img_size = IMG_SIZE_JPEG_S;
			img_setting = IMG_SETTING_RAW;
			break;
	}
	send_to_intercom(IC_SET_IMG_FORMAT, 1, cameraMode->img_format);
	send_to_intercom(IC_SET_IMG_QUALITY, 1, cameraMode->img_quality);
	send_to_intercom(IC_SET_IMG_SIZE, 1, cameraMode->img_size);
}

void toggle_CfMLU() {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, cameraMode->cf_mirror_up_lock ^ 0x01);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, cameraMode->cf_flash_sync_rear ^ 0x01);
}

void set_intermediate_iso() {
	if (cameraMode->ae < 6) {
		send_to_intercom(IC_SET_ISO, 2, iso_roll(cameraMode->iso));
		print_icu_info();
	}
}

void restore_iso() {
	int iso = cameraMode->iso & 0xF8;

	send_to_intercom(IC_SET_ISO, 2, MIN(iso, 0x68));
}

void restore_wb() {
	if (cameraMode->wb == WB_MODE_COLORTEMP)
		send_to_intercom(IC_SET_WB, 1, WB_MODE_AUTO);
}

void restore_metering() {
	if (cameraMode->metering == METERING_MODE_SPOT)
		send_to_intercom(IC_SET_METERING, 1, METERING_MODE_EVAL);
}
