#include <vxworks.h>

#include "main.h"
#include "macros.h"
#include "firmware.h"
#include "firmware/camera.h"

#include "exposure.h"
#include "utils.h"

#include "fexp.h"

void fexp_disable () {
	status.fexp = FALSE;
	enqueue_action(beep);
}

void fexp_toggle() {
	if (DPData.ae == AE_MODE_M) {
		if (status.fexp) {
			fexp_disable();
		} else {
			status.fexp    = TRUE;
			status.fexp_ev = (int)DPData.av_val + (int)DPData.tv_val;

			enqueue_action(beep);
		}
	}
}

void fexp_update_av() {
	if (DPData.ae == AE_MODE_M && DPData.tv_val != TV_VAL_BULB) {
		int av = status.fexp_ev - DPData.tv_val;

		av = CLAMP(av, AV_MIN, AV_MAX);
		av = ev_normalize(av);

		send_to_intercom(IC_SET_AV_VAL, av);
	}
}

void fexp_update_tv() {
	if (DPData.ae == AE_MODE_M && DPData.tv_val != TV_VAL_BULB) {
		int tv = status.fexp_ev - DPData.av_val;

		tv = CLAMP(tv, TV_MIN, TV_MAX);
		tv = ev_normalize(tv);

		send_to_intercom(IC_SET_TV_VAL, tv);
	}
}
