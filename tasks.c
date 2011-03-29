#include "main.h"
#include "utils.h"
#include "display.h"
#include "shortcuts.h"
#include "settings.h"
#include "firmware.h"

#include "tasks.h"

void restore_iso();
void restore_wb();
void restore_metering();

void switch_raw_jpeg();
void set_intermediate_iso();

void show_factory_menu();
void start_debug_mode();

void start_up() {
	// Wait for camera to settle down
	SleepTask(1000);

	// Enable (hidden) CFn.8 for ISO H
	if (!cameraMode.CfExtendIso)
		SendToIntercom(0x31, 1, 1);

	// Enable realtime ISO change
	SendToIntercom(0xF0, 0, 0);
	SendToIntercom(0xF1, 0, 0);

	// Read (and apply) settings from file
	settings_read();
	settings_apply();
}

void set_metering_spot() {
	int metering_spot = METERING_MODE_SPOT;

	pressButton_(BUTTON_SET);
	eventproc_SetMesMode(&metering_spot);
	eventproc_PrintICUInfo();

	beep();
}

void set_whitebalance_colortemp() {
	pressButton_(BUTTON_SET);
	SendToIntercom(0x05, 1, WB_MODE_COLORTEMP);
	SendToIntercom(0x10, 2, settings.color_temp);
	eventproc_PrintICUInfo();

	beep();
}

void set_iso_high() {
	int iso_high = 0x6F;

	pressButton_(BUTTON_SET);
	eventproc_SetIsoValue(&iso_high);
	eventproc_PrintICUInfo();

	beep();
}

void switch_raw_jpeg() {
	if (cameraMode.AEMode > 6) {
		// Only for non-creative modes
		SendToIntercom(0x22, 1, cameraMode.QualityRaw ^ 0x03);
	}
}

void set_intermediate_iso() {
	if (cameraMode.AEMode < 6) {
		int iso = iso_next(cameraMode.ISO);
		eventproc_SetIsoValue(&iso);
		SleepTask(50);
	}
}

void restore_iso() {
	int iso;

	if (cameraMode.ISO >= 0x68) {
		iso = 0x68;
	} else if (cameraMode.ISO >= 0x60) {
		iso = 0x60;
	} else if (cameraMode.ISO >= 0x58) {
		iso = 0x58;
	} else if (cameraMode.ISO >= 0x50) {
		iso = 0x50;
	} else {
		iso = 0x48;
	}

	eventproc_SetIsoValue(&iso);
}

void restore_wb() {
	if (cameraMode.WB == WB_MODE_COLORTEMP) {
		SendToIntercom(0x5, 1, WB_MODE_AUTO);
	}
}

void restore_metering() {
	const int metering_evaluative = METERING_MODE_EVAL;

	if (cameraMode.MeteringMode == METERING_MODE_SPOT)
		eventproc_SetMesMode(&metering_evaluative);
}

void factory_or_debug() {
	if (! status.factory_menu) {
		status.factory_menu = TRUE;
		show_factory_menu();
	} else if (! status.debug_mode) {
		status.debug_mode = TRUE;
		start_debug_mode();
	}
}

void show_factory_menu() {
	EnterFactoryMode();
	SleepTask(25);
	ExitFactoryMode();
}

void start_debug_mode() {
	int file;

	if((file = FIO_CreateFile("A:/STDOUT.TXT")) > 0)
		ioGlobalStdSet(1, file);

	if((file = FIO_CreateFile("A:/STDERR.TXT")) > 0)
		ioGlobalStdSet(2, file);

	beep();
}

