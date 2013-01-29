/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "camera.h"

#include "main.h"
#include "macros.h"

#include "display.h"
#include "exposure.h"
#include "settings.h"
#include "utils.h"

#include "autoiso.h"

void autoiso() {
	ev_t limit;

	ec_t ec = EC_ZERO;
	ev_t ev = EV_ZERO;

	iso_t newiso;

	switch(DPData.ae) {
	case AE_MODE_M:
		if (DPData.tv_val == TV_VAL_BULB) {
			enqueue_action(autoiso_disable_restore);
		} else {
			// M mode: set ISO to match exposure
			ec = - (status.measured_ec - status.ev_comp);

			// Normalize an apply new ISO
			if (ec != EC_ZERO) {
				newiso = DPData.iso + ec;
				newiso = CLAMP(newiso, settings.autoiso_miniso, settings.autoiso_maxiso);
				newiso = EV_ROUND(newiso);

				send_to_intercom(IC_SET_ISO, newiso);
				enqueue_action(restore_display);
			}
		}

		return;
	case AE_MODE_P:
	case AE_MODE_AV:
		// P / Av mode: raise ISO if shutter time is lower than limit
		ev    = status.measured_tv;
		limit = settings.autoiso_mintv;
		break;
	case AE_MODE_TV:
		// Tv mode: raise ISO if apperture is larger than lens' max plus offset
		ev    = status.measured_av;
		limit = DPData.avo + settings.autoiso_maxav;
		break;
	default:
		return;
	}

	// Decide whether we need to change current ISO
	if (ev != EC_ZERO) {
		if (ev < limit)
			ec = (limit - ev) + EV_CODE(1, 0);
		else if (ev >= limit + EV_CODE(1, 0))
			ec = (limit - ev);
	}

	// Normalize an apply new ISO
	if (ec != EC_ZERO) {
		newiso = DPData.iso + ec;
		newiso = CLAMP(newiso, settings.autoiso_miniso, settings.autoiso_maxiso);
		newiso = EV_TRUNC(newiso);

		send_to_intercom(IC_SET_ISO, newiso);
		enqueue_action(restore_display);
	}
}

void autoiso_enable() {
	press_button(IC_BUTTON_SET);

	if (!settings.autoiso_enable) {
		settings.autoiso_enable = true;
		settings_write();
	}

	print_icu_info();
	beep();
}

void autoiso_disable() {
	if (settings.autoiso_enable) {
		settings.autoiso_enable = false;
		settings_write();
	}
}

void autoiso_disable_restore() {
	settings.autoiso_enable = false;

	send_to_intercom(IC_SET_ISO, ISO_MIN);

	enqueue_action(restore_display);
	enqueue_action(beep);
}
