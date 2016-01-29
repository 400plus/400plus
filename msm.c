#include <vxworks.h>

#include "firmware/camera.h"

#include "main.h"
#include "macros.h"

#include "button.h"
#include "utils.h"
#include "shutter.h"
#include "intercom.h"

#include "msm.h"

int  msm_ae_return; // Multi-spot metering: AE mode to return after first shot
tv_t msm_tv_return; // Multi-spot metering: Tv value in M mode to return
av_t msm_av_return; // Multi-spot metering: Av value in M mode to return

void msm_reset(void);

void msm_reset(void) {
	status.msm_count  = 0;
	status.msm_tv     = EV_ZERO;
	status.msm_av     = EV_ZERO;
	status.msm_active = FALSE;
}

void msm_register(void) {
	static int  last_flag; // Last value registered can be deleted
	static tv_t last_tv;   // Last Tv value registered
	static av_t last_av;   // Last Av value registered

	int ts_start = timestamp();

	if (status.measuring) {
		if (status.msm_count < 8) {
			status.vf_status = VF_STATUS_MSM;
			send_to_intercom(IC_SET_BURST_COUNTER, status.msm_count + 1);
		}

		beep();
	}

	while (status.button_down == BUTTON_DOWN) {
		if (timestamp() - ts_start > MSM_TIMEOUT) {
			if (last_flag) {
				status.msm_count--;

				status.msm_tv -= last_tv;
				status.msm_av -= last_av;

				last_flag = FALSE;

				send_to_intercom(IC_SET_BURST_COUNTER, status.msm_count);
				beep();
			}

			return;
		}

		SleepTask(MSM_RETRY);
	}

	status.msm_count++;

	status.msm_tv += status.measured_tv;
	status.msm_av += status.measured_av;

	last_flag = TRUE;
	last_tv   = status.measured_tv;
	last_av   = status.measured_av;
}

void msm_release(void) {
	send_to_intercom(IC_SET_BURST_COUNTER, 9);
}

void msm_start(void) {
	if (status.msm_count > 0) {
		status.msm_active = TRUE;

		tv_t tv = ev_normalize(status.msm_tv / status.msm_count);
		av_t av = ev_normalize(status.msm_av / status.msm_count);

		av_t av_max = DPData.ef_lens_exist ? DPData.avmax : AV_MAX;
		av_t av_min = DPData.ef_lens_exist ? DPData.avo   : AV_MIN;

		msm_ae_return = DPData.ae;
		send_to_intercom(IC_SET_AE, AE_MODE_M);

		msm_tv_return = DPData.tv_val;
		msm_av_return = DPData.av_val;

		send_to_intercom(IC_SET_TV_VAL, CLAMP(tv, TV_MIN, TV_MAX));
		send_to_intercom(IC_SET_AV_VAL, CLAMP(av, av_min, av_max));

		enqueue_action(beep);
	}
}

void msm_stop(void) {
	wait_for_camera();
	SleepTask(RELEASE_WAIT);

	send_to_intercom(IC_SET_TV_VAL, msm_tv_return);
	send_to_intercom(IC_SET_AV_VAL, msm_av_return);
	send_to_intercom(IC_SET_AE,     msm_ae_return);

	enqueue_action(msm_reset);
}
