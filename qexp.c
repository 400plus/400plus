#include <vxworks.h>
#include <stdlib.h>

#include "firmware/camera.h"

#include "main.h"
#include "macros.h"

#include "exposure.h"
#include "settings.h"
#include "utils.h"
#include "intercom.h"

#include "qexp.h"

void qexp_enable(void) {
	status.vf_status = VF_STATUS_QEXP;
}

void qexp_disable(void) {
	status.vf_status = VF_STATUS_NONE;
}

void qexp_update(void) {
	int weight;

	ec_t diff, ec_tmp;

	av_t av = status.measured_av;
	tv_t tv = status.measured_tv;
	ec_t ec = status.measured_ec;

	av_t av_max = DPData.ef_lens_exist ? DPData.avmax : AV_MAX;
	av_t av_min = DPData.ef_lens_exist ? DPData.avo   : AV_MIN;

	if (status.measuring && abs(status.measured_ec) > QEXP_TOLERANCE) {
		// Set lens to maximum aperture
		diff = av_min - av;

		av += diff;
		ec -= diff;

		// Set shutter to 1/60
		diff = settings.qexp_mintv - tv;

		tv += diff;
		ec -= diff;

		// If under-exposing, increase shutter speed
		if (ec < 0) {
			diff = MAX(tv + ec, TV_MIN) - tv;

			tv += diff;
			ec -= diff;
		}

		// If over-exposing, split the blame
		if (ec > 0) {
			ec_tmp = ec;

			switch (settings.qexp_weight) {
			default:
			case QEXP_WEIGHT_NONE: weight = 2; break;
			case QEXP_WEIGHT_AV  : weight = 3; break;
			case QEXP_WEIGHT_TV  : weight = 1; break;
			}

			diff = MIN(av + weight * ec_tmp / 4, av_max) - av;

			av += diff;
			ec -= diff;

			weight = 3 - weight;

			diff  = MIN(tv + weight * ec_tmp / 4, TV_MAX) - tv;

			tv += diff;
			ec -= diff;
		}

		// If still over-exposing, one of Av / Tv reached a maximum
		if (ec > 0) {
			diff = MIN(tv + ec, TV_MAX) - tv;

			tv += diff;
			ec -= diff;

			diff = MIN(av + ec, av_max) - av;

			av += diff;
			ec -= diff;
		}

		av = ev_normalize(av);
		tv = ev_normalize(tv);

		if (av != DPData.av_val)
			send_to_intercom(IC_SET_AV_VAL, ev_normalize(av));

		if (tv != DPData.tv_val)
			send_to_intercom(IC_SET_TV_VAL, ev_normalize(tv));
	}
}
