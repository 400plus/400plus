#include "main.h"

#include "tasks.h"

// Temporary storage while displaying ISO at viewfinder
int viewfinder_iso_CfNotEmitFlash, viewfinder_iso_TvVal;

void set_intermediate_iso() {
	if (cameraMode.AEMode < 6) {
		int iso = iso_next(cameraMode.ISO);

		eventproc_SetIsoValue(&iso);

		SleepTask(10);
		display_refresh();
	}
}

void viewfinder_iso_inc() {
	int iso = iso_inc(cameraMode.ISO);

	if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
		viewfinder_iso_CfNotEmitFlash = cameraMode.CfNotEmitFlash;
		SendToIntercom(0x30, 1, 1);

		viewfinder_iso_TvVal = cameraMode.TvVal;
		SendToIntercom(0x08, 1, iso + 0x25);
	}

	eventproc_SetIsoValue(&iso);
}

void viewfinder_iso_dec() {
	int iso = iso_dec(cameraMode.ISO);

	if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
		viewfinder_iso_CfNotEmitFlash = cameraMode.CfNotEmitFlash;
		SendToIntercom(0x30, 1, 1);

		viewfinder_iso_TvVal = cameraMode.TvVal;
		SendToIntercom(0x08, 1, iso + 0x25);
	}

	eventproc_SetIsoValue(&iso);
}

void viewfinder_iso_end() {
	if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
		SendToIntercom(0x30, 1, viewfinder_iso_CfNotEmitFlash);
		SendToIntercom(0x08, 1, viewfinder_iso_TvVal);
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

void show_factory_menu() {
	EnterFactoryMode();
	SleepTask(25);
	ExitFactoryMode();
}

void start_debug_mode() {
	int file;

  while ((file = FIO_CreateFile("A:/STDOUT.TXT")) < 0)
		SleepTask(100);

  ioGlobalStdSet(1, file);

  while ((file = FIO_CreateFile("A:/STDERR.TXT")) < 0)
		SleepTask(100);

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
