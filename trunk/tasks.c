#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "presets.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"
#include "debug.h"
#include "memspy.h"

#include "tasks.h"

void set_intermediate_iso();
void repeat_last_script();

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
	status.booting = FALSE;

	debug_log("maindlg @ 0x%08X, handler @ 0x%08X", hMainDialog, hMainDialog->event_handler);

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
	int mask = 0xF8, ev = 0x00, measure = 0x00, limit = 0x00;
	int miniso = settings.autoiso_miniso;
	int maxiso = settings.autoiso_maxiso;

	int newiso = cameraMode->iso;

	switch(cameraMode->ae) {
	case AE_MODE_P:
	case AE_MODE_AV:
		measure = status.measured_tv;
		limit   = settings.autoiso_mintv;
		break;
	case AE_MODE_TV:
		measure = status.measured_av;
		limit   = settings.autoiso_maxav;
		break;
	case AE_MODE_M:
		mask   = 0xFF;
		miniso = 0x48;
		maxiso = 0x6F;

		ev = (status.measured_ev & 0x80) ? (0x100 - status.measured_ev) : -status.measured_ev;
		ev = ev_add(ev, status.ev_comp);
		break;
	default:
		break;
	}

	if (measure != 0x00) {
		if (measure < limit)
			ev = (limit - measure) + 0x08;
		else if (measure >= limit + 0x08)
			ev = (limit - measure);
	}

	if (ev != 0x00) {
		newiso = (cameraMode->iso + ev) & mask;

		newiso = MIN(newiso, maxiso);
		newiso = MAX(newiso, miniso);

		send_to_intercom(IC_SET_ISO, 2, newiso);
		ENQUEUE_TASK(restore_display);
	}
}

void autoiso_enable() {
	press_button(IC_BUTTON_SET);

	if (!settings.autoiso_enable) {
		settings.autoiso_enable = TRUE;
		settings_write();
	}

	print_icu_info();
	beep();
}

void autoiso_disable() {
	if (settings.autoiso_enable) {
		settings.autoiso_enable = FALSE;
		settings_write();
	}
}

void repeat_last_script() {
	switch (status.last_script) {
	case SCRIPT_EAEB:
		script_extended_aeb();
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
	switch (settings.button_jump) {
	case BUTTON_ACTION_ISO:
		set_intermediate_iso();
		break;
	case BUTTON_ACTION_SCRIPT:
		repeat_last_script();
		break;
	default:
		break;
	}
}
