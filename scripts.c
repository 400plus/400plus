#include "main.h"
#include "settings.h"

#include "scripts.h"

#define WAIT_CAMERA_BUSY 250

void release_and_wait();
void wait_for_camera();

void script_extended_aeb() {

	if (settings.eaeb_delay) {
		eventproc_RiseEvent("RequestBuzzer");
		SleepTask(2000);
	}

	if (cameraMode.AEMode == AE_MODE_M) {
		int tv_value = cameraMode.TvVal;

		int tv_start = MIN(settings.eaeb_m_min, settings.eaeb_m_max);
		int tv_end   = MAX(settings.eaeb_m_min, settings.eaeb_m_max);

		int tv;
		for (tv = tv_start; tv <= tv_end; tv += 8) {
			SendToIntercom(0x08, 1, tv);
			release_and_wait();
		};

		SendToIntercom(0x08, 1, tv_value);
	} else {
		int av_comp = cameraMode.AvComp;
		int av_inc  = av_comp;
		int av_dec  = av_comp;

		release_and_wait();

		int i;
		for(i = 0; i < (settings.eaeb_frames - 1) / 2; i++) {
			av_inc = ev_add(av_inc, settings.eaeb_ev);
			SendToIntercom(0x0A, 1, av_inc);
			release_and_wait();

			av_dec = ev_sub(av_dec, settings.eaeb_ev);
			SendToIntercom(0x0A, 1, av_dec);
			release_and_wait();
		}

		SendToIntercom(0x0A, 1, av_comp);
	}

	eventproc_RiseEvent("RequestBuzzer");
}

void script_interval() {
	int i;
	int ae_mode = cameraMode.AEMode;

	while (ae_mode == cameraMode.AEMode) {
		wait_for_camera();
		eventproc_Release();

		for(i = 0; i < settings.interval_time; i++) {
			if(ae_mode == cameraMode.AEMode)
				SleepTask(1000);
		}
	}

	eventproc_RiseEvent("RequestBuzzer");
}

void release_and_wait() {
	eventproc_Release();
	wait_for_camera();
}

void wait_for_camera() {
	while(FLAG_CAMERA_BUSY)
		SleepTask(WAIT_CAMERA_BUSY);
}
