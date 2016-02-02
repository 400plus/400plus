#include <vxworks.h>
#include <dirent.h>
#include <stdio.h>

#include "firmware.h"

#include "macros.h"
#include "main.h"

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
