/**
 * $Revision$
 * $Date$
 * $Author$
 *
 * Quick exposure for M mode
 *
 */

#include "main.h"
#include "macros.h"
#include "camera.h"

#include "exposure.h"
#include "utils.h"

void qexp() {
	ec_t tmp, tmp2;

	av_t av = status.measured_av;
	tv_t tv = status.measured_tv;
	ec_t ec = status.measured_ec;

	av_t av_max = DPData.ef_lens_exist ? DPData.avmax : AV_MAX;
	av_t av_min = DPData.ef_lens_exist ? DPData.avo   : AV_MIN;

	if (ec != 0) {
		// Set lens to maximum aperture
		tmp = av_min - av;

		av += tmp;
		ec -= tmp;

		// Set shutter to 1/60
		tmp = EV_CODE(13, 0) - tv;

		tv += tmp;
		ec -= tmp;

		// If under-exposing, increase shutter speed
		if (ec < 0) {
			tmp = MAX(tv + ec, TV_MIN) - tv;

			tv += tmp;
			ec -= tmp;
		}

		// If over-exposing, split the blame
		if (ec > 0) {
			tmp2 = ec / 2;

			tmp = MIN(av + tmp2, av_max) - av;

			av += tmp;
			ec -= tmp;

			tmp  = MIN(tv + tmp2, TV_MAX) - tv;

			tv += tmp;
			ec -= tmp;
		}

		// If still over-exposing, one of Av / Tv reached a maximum
		if (ec > 0) {
			tmp = MIN(tv + ec, TV_MAX) - tv;

			tv += tmp;
			ec -= tmp;

			tmp = MIN(av + ec, av_max) - av;

			av += tmp;
			ec -= tmp;
		}

		send_to_intercom(IC_SET_AV_VAL, ev_normalize(av));
		send_to_intercom(IC_SET_TV_VAL, ev_normalize(tv));
	}

	beep();
}
