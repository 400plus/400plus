/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <camera.h>
#include <stdbool.h>

#include "main.h"
#include "firmware.h"

#include "exposure.h"
#include "settings.h"
#include "utils.h"


#include "viewfinder.h"

dpr_data_t vf_DPData;

void viewfinder_change_iso (const int iso);
void viewfinder_display_iso(const int iso);

void viewfinder_change_evc(const int av_comp);

void viewfinder_right() {
	if (settings.autoiso_enable) {
		// AutoISO + M => change exposure compensation
		if (DPData.ae == AE_MODE_M)
			viewfinder_change_evc(ec_inc(status.ev_comp));
	} else {
		// Only for creative modes
		if (DPData.ae < AE_MODE_AUTO)
			viewfinder_change_iso(iso_next(DPData.iso));
	}
}

void viewfinder_left() {
	if (settings.autoiso_enable) {
		// AutoISO + M => change exposure compensation
		if (DPData.ae == AE_MODE_M)
			viewfinder_change_evc(ec_dec(status.ev_comp));
	} else {
		// Only for creative modes
		if (DPData.ae < AE_MODE_AUTO)
			viewfinder_change_iso(iso_prev(DPData.iso));
	}
}

void viewfinder_up() {
	if (settings.autoiso_enable) {
		// AutoISO + M => reset exposure compensation
		if (DPData.ae == AE_MODE_M)
			viewfinder_change_evc(0x00);
	} else {
		// Only for creative modes
		if (DPData.ae < AE_MODE_AUTO)
			viewfinder_display_iso(DPData.iso);
	}
}

void viewfinder_end() {
	// Only if being displayed
	if (status.iso_in_viewfinder) {
		// Restore previous state
		send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, vf_DPData.cf_emit_aux);
		send_to_intercom(IC_SET_TV_VAL,        1, vf_DPData.tv_val);

		// Reset flag, viewfinder restored
		status.iso_in_viewfinder = false;
	}
}

void viewfinder_change_iso(const int iso) {
	// Set new ISO
	send_to_intercom(IC_SET_ISO, 2, iso);

	// Display new ISO
	viewfinder_display_iso(iso);
}

void viewfinder_display_iso(const int iso) {
	// Display new ISO only in M and Tv modes
	if (DPData.ae == AE_MODE_M || DPData.ae == AE_MODE_TV) {
		// Save current state
		vf_DPData = DPData;

		// Change to Tv=ISO, no flash
		send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, true);
		send_to_intercom(IC_SET_TV_VAL,        1, (iso & 0xF8) + 0x25);

		// Set flag to restore viewfinder later
		status.iso_in_viewfinder = true;
	}
}

void viewfinder_change_evc(const int ev_comp) {
	if (((ev_comp & 0x80) && ev_comp >= 0xF0) || ev_comp <= 0x10)
		status.ev_comp = ev_comp;
}
