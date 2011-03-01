#include "main.h"
#include "scripts.h"
#include "settings.h"

#include "tasks.h"

void restore_iso();
void restore_wb();
void restore_metering();

void switch_raw_jpeg();
void set_intermediate_iso();

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

void dp_action() {
	if (cameraMode.AEMode > 6) { // Non-creative modes
		switch_raw_jpeg();
	} else {
		switch (settings.dp_action) {
		case DP_ACTION_INTERMEDIATE_ISO:
			// Set intermediate ISO
			set_intermediate_iso();
			break;
		case DP_ACTION_EXTENDED_AEB:
			// Start extended AEB script
			script_extended_aeb();
			break;
		case DP_ACTION_INTERVAL:
			// Start interval script
			script_interval();
			break;
		}
	}
}

void set_metering_spot() {
	int metering_spot = METERING_MODE_SPOT;

	pressButton_(BUTTON_SET);
	eventproc_SetMesMode(&metering_spot);
	eventproc_PrintICUInfo();

	if (cameraMode.Beep)
		eventproc_RiseEvent("RequestBuzzer");
}

void switch_raw_jpeg() {
	SendToIntercom(0x22, 1, cameraMode.QualityRaw ^ 0x03);
}

void set_intermediate_iso() {
	if (cameraMode.AEMode < 6) {
		int iso = iso_next(cameraMode.ISO);

		eventproc_SetIsoValue(&iso);

		SleepTask(10);
		display_refresh();
	}
}

void show_factory_menu() {
	start_debug_mode();

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
}

void restore_iso() {
	int iso;

	if (cameraMode.ISO > 0x68) {
		iso = 0x68;
	} else if (cameraMode.ISO > 0x60) {
		iso = 0x60;
	} else if (cameraMode.ISO > 0x58) {
		iso = 0x58;
	} else if (cameraMode.ISO > 0x50) {
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
	int metering_evaluative = METERING_MODE_EVAL;

	if (cameraMode.MeteringMode == METERING_MODE_SPOT)
		eventproc_SetMesMode(&metering_evaluative);
}
