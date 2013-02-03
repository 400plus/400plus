/**
 * $Revision$
 * $Date $
 * $Author$
 *
 * Multi-spot metering
 *
 */

#include <stdbool.h>

#include "main.h"
#include "macros.h"

#include "camera.h"
#include "utils.h"

#include "msm.h"

int msm_timestamp;  // Multi-spot metering: timestap when button was held down

int  msm_ae_return; // Multi-spot metering: AE mode to return after first shot
tv_t msm_tv_return; // Multi-spot metering: Tv value in M mode to return
av_t msm_av_return; // Multi-spot metering: Av value in M mode to return

tv_t msm_tv_last; // Multi-spot metering: last Tv value registered
av_t msm_av_last; // Multi-spot metering: last Av value registered

void msm_reset() {
	status.msm_count = 0;
	status.msm_tv    = EV_ZERO;
	status.msm_av    = EV_ZERO;
}

void msm_register() {
	msm_timestamp = timestamp();

	if (status.measuring) {
		if (status.msm_count < 8) {
			status.vf_status = VF_STATUS_MSM;
			send_to_intercom(IC_SET_BURST_COUNTER, status.msm_count + 1);
		}

		beep();
	}
}

void msm_release() {
	send_to_intercom(IC_SET_BURST_COUNTER, 9);

	if (status.measuring && timestamp() - msm_timestamp < MSM_TIMEOUT) {
		status.msm_count++;

		status.msm_tv += status.measured_tv;
		status.msm_av += status.measured_av;

		msm_tv_last    = status.measured_tv;
		msm_av_last    = status.measured_av;
	} else if (status.msm_count > 0) {
		status.msm_count--;

		status.msm_tv -= msm_tv_last;
		status.msm_av -= msm_av_last;

		beep();
	}
}

void msm_start() {
	if (status.msm_count > 0) {
		status.msm_active = true;

		tv_t tv = EV_ROUND(status.msm_tv / status.msm_count);
		av_t av = EV_ROUND(status.msm_av / status.msm_count);

		av_t av_max = DPData.ef_lens_exist ? DPData.avmax : AV_MAX;
		av_t av_min = DPData.ef_lens_exist ? DPData.avo   : AV_MIN;

		msm_ae_return = DPData.ae;
		send_to_intercom(IC_SET_AE, AE_MODE_M);

		msm_tv_return = DPData.tv_val;
		msm_av_return = DPData.av_val;

		send_to_intercom(IC_SET_TV_VAL, CLAMP(tv, TV_MIN, TV_MAX));
		send_to_intercom(IC_SET_AV_VAL, CLAMP(av, av_min, av_max));

		msm_reset();
		beep();
	}
}

void msm_stop() {
	wait_for_camera();
	SleepTask(RELEASE_WAIT);

	send_to_intercom(IC_SET_TV_VAL, msm_tv_return);
	send_to_intercom(IC_SET_AV_VAL, msm_av_return);
	send_to_intercom(IC_SET_AE,     msm_ae_return);

	status.msm_active = false;
}
