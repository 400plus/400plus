#include "main.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "viewfinder.h"

// Temporary storage while displaying ISO at viewfinder
struct {
	int TvVal;
	int CfNotEmitFlash;
} storage;

void viewfinder_change_iso(const int iso);

void viewfinder_right() {
	viewfinder_change_iso(iso_inc(cameraMode.ISO));
}

void viewfinder_left() {
	viewfinder_change_iso(iso_dec(cameraMode.ISO));
}

void viewfinder_end() {
	// Only if being displayed
	if (status.iso_in_viewfinder) {
		// Restore previous state
		SendToIntercom(0x30, 1, storage.CfNotEmitFlash);
		SendToIntercom(0x08, 1, storage.TvVal);

		// Reset flag, viewfinder restored
		status.iso_in_viewfinder = FALSE;
	}
}

void viewfinder_change_iso(const int iso) {
	// Only if active and mode is P, Tv, Av, M
	if (settings.iso_in_viewfinder) {
		if (cameraMode.AEMode == AE_MODE_M || cameraMode.AEMode == AE_MODE_TV) {
			// Save current state
			storage.TvVal          = cameraMode.TvVal;
			storage.CfNotEmitFlash = cameraMode.CfNotEmitFlash;

			// Change to Tv=ISO, no flash
			SendToIntercom(0x30, 1, 1);
			SendToIntercom(0x08, 1, iso + 0x25);

			// Set flag to restore viewfinder later
			status.iso_in_viewfinder = TRUE;
		}

		// Set new ISO
		eventproc_SetIsoValue(&iso);
	}
}

