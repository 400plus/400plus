#include <vxworks.h>

#include "firmware.h"
#include "firmware/camera.h"

#include "main.h"
#include "macros.h"
#include "exposure.h"
#include "utils.h"
#include "intercom.h"

#include "fexp.h"

void fexp_toggle(void) {
	if (status.vf_status == VF_STATUS_FEXP)
		fexp_disable();
	else
		fexp_enable();
}

void fexp_enable(void) {
	status.vf_status = VF_STATUS_FEXP;
	status.fexp_ev   = (int)DPData.av_val + (int)DPData.tv_val;
}

void fexp_disable(void) {
	status.vf_status = VF_STATUS_NONE;
}

void fexp_update_av(void) {
	if (DPData.ae == AE_MODE_M && DPData.tv_val != TV_VAL_BULB) {
		int av = status.fexp_ev - DPData.tv_val;

		av = CLAMP(av, AV_MIN, AV_MAX);
		av = ev_normalize(av);

		send_to_intercom(IC_SET_AV_VAL, av);
	}
}

void fexp_update_tv(void) {
	if (DPData.ae == AE_MODE_M && DPData.tv_val != TV_VAL_BULB) {
		int tv = status.fexp_ev - DPData.av_val;

		tv = CLAMP(tv, TV_MIN, TV_MAX);
		tv = ev_normalize(tv);

		send_to_intercom(IC_SET_TV_VAL, tv);
	}
}
