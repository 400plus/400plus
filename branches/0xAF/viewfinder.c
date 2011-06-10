#include "main.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "viewfinder.h"

type_CAMERA_MODE vf_cameraMode;

void viewfinder_change_iso(const int iso);

void viewfinder_right() {
	viewfinder_change_iso(iso_inc(cameraMode->iso));
}

void viewfinder_left() {
	viewfinder_change_iso(iso_dec(cameraMode->iso));
}

void viewfinder_end() {
	// Only if being displayed
	if (status.iso_in_viewfinder) {
		// Restore previous state
		send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, vf_cameraMode.cf_emit_aux);
		send_to_intercom(IC_SET_TV_VAL,        1, vf_cameraMode.tv_val);

		// Reset flag, viewfinder restored
		status.iso_in_viewfinder = FALSE;
	}
}

void viewfinder_change_iso(const int iso) {
	// Only if active and mode is P, Tv, Av, M
	if (settings.iso_in_viewfinder) {
		if (cameraMode->ae == AE_MODE_M || cameraMode->ae == AE_MODE_TV) {
			// Save current state
			vf_cameraMode = *cameraMode;

			// Change to Tv=ISO, no flash
			send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, 1);
			send_to_intercom(IC_SET_TV_VAL,        1, iso + 0x25);

			// Set flag to restore viewfinder later
			status.iso_in_viewfinder = TRUE;
		}

		// Set new ISO
		send_to_intercom(IC_SET_ISO, 2, iso);
	}
}

