#include "main.h"
#include "settings.h"

#include "viewfinder.h"

// Temporary storage while displaying ISO at viewfinder
int viewfinder_iso_CfNotEmitFlash, viewfinder_iso_TvVal;

void viewfinder_iso_inc() {
	const int iso = iso_inc(cameraMode.ISO);

	if (settings.iso_in_viewfinder) {
		if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
			viewfinder_iso_CfNotEmitFlash = cameraMode.CfNotEmitFlash;
			SendToIntercom(0x30, 1, 1);

			viewfinder_iso_TvVal = cameraMode.TvVal;
			SendToIntercom(0x08, 1, iso + 0x25);
		}

		eventproc_SetIsoValue(&iso);
	}
}

void viewfinder_iso_dec() {
	const int iso = iso_dec(cameraMode.ISO);

	if (settings.iso_in_viewfinder) {
		if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
			viewfinder_iso_CfNotEmitFlash = cameraMode.CfNotEmitFlash;
			SendToIntercom(0x30, 1, 1);

			viewfinder_iso_TvVal = cameraMode.TvVal;
			SendToIntercom(0x08, 1, iso + 0x25);
		}

		eventproc_SetIsoValue(&iso);
	}
}

void viewfinder_iso_end() {
	if (settings.iso_in_viewfinder) {
		if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
			SendToIntercom(0x30, 1, viewfinder_iso_CfNotEmitFlash);
			SendToIntercom(0x08, 1, viewfinder_iso_TvVal);
		}
	}
}
