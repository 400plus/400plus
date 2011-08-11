#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu_shortcuts.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"
#include "debug.h"
#include "memspy.h"

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

	// We are no longer booting up
	status.booting = FALSE;
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
	if (cameraMode->ae < AE_MODE_AUTO) {
		send_to_intercom(IC_SET_ISO, 2, iso_roll(cameraMode->iso));
		print_icu_info();
		display_refresh();
	}
}

void toggle_img_format() {
	static int first_call = TRUE;

	if (!first_call && cameraMode->ae >= AE_MODE_AUTO) {
		switch(cameraMode->img_format) {
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

	first_call = FALSE;
}

void toggle_CfMLU() {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, cameraMode->cf_mirror_up_lock ^ 0x01);
}

void toggle_CfFlashSyncRear() {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, cameraMode->cf_flash_sync_rear ^ 0x01);
}

void restore_iso() {
	send_to_intercom(IC_SET_ISO, 2, cameraMode->iso & 0xF8);
}

void restore_wb() {
	if (cameraMode->wb == WB_MODE_COLORTEMP)
		send_to_intercom(IC_SET_WB, 1, WB_MODE_AUTO);
}

void restore_metering() {
	if (cameraMode->metering == METERING_MODE_SPOT)
		send_to_intercom(IC_SET_METERING, 1, METERING_MODE_EVAL);
}

void autoiso() {
	int mintv = ((settings.autoiso_mintv - 5) << 3) + 0x10;

	switch(cameraMode->ae) {
	case AE_MODE_AV:
		if (status.measured_tv < mintv - 5 && cameraMode->iso < 0x68) {
			send_to_intercom(IC_SET_ISO, 2, iso_inc(cameraMode->iso));
			print_icu_info();
			display_refresh();
		} else if (status.measured_tv - 0x08 > mintv - 5 && cameraMode->iso > 0x48) {
			send_to_intercom(IC_SET_ISO, 2, iso_dec(cameraMode->iso));
			print_icu_info();
			display_refresh();
		}
	default:
		break;
	}
}
