#include "main.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "scripts.h"

void sub_extended_aeb();
void sub_interval();

void release_and_wait();
void wait_for_camera();
void script_delay(int seconds);

void script_extended_aeb() {
	beep();
	status.script_running = TRUE;

	if (settings.eaeb_delay)
		script_delay(2);

	if (! FLAG_FACE_SENSOR)
		sub_extended_aeb();

	beep();
	status.script_running = FALSE;
}

void script_interval() {
	int i = 0;

	beep();
	status.script_running = TRUE;

	if (settings.interval_delay)
		script_delay(2);

	sub_interval();

	beep();
	status.script_running = FALSE;
}

void script_wave() {
	beep();
	status.script_running = TRUE;

	while (!FLAG_FACE_SENSOR)
		SleepTask(SCRIPT_DELAY_TIME);

	if (settings.wave_delay)
		SleepTask(2000);

	while (FLAG_FACE_SENSOR)
		SleepTask(SCRIPT_DELAY_TIME);

	switch (settings.wave_action) {
	case WAVE_ACTION_SHOT:
		eventproc_Release();
		break;
	case WAVE_ACTION_EAEB:
		sub_extended_aeb();
		break;
	case WAVE_ACTION_INTERVAL:
		sub_interval();
		break;
	default:
		break;
	}

	wait_for_camera();

	beep();
	status.script_running = FALSE;
}

void sub_extended_aeb() {
	if (cameraMode.AEMode == AE_MODE_M) {
		int tv;

		int tv_value = cameraMode.TvVal;
		int tv_start = MIN(settings.eaeb_m_min, settings.eaeb_m_max);
		int tv_end   = MAX(settings.eaeb_m_min, settings.eaeb_m_max);

		for (tv = tv_start; tv <= tv_end; tv += 8) {
			SendToIntercom(0x08, 1, tv);
			release_and_wait();

			if (FLAG_FACE_SENSOR)
				break;
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

			if (FLAG_FACE_SENSOR)
				break;

			av_dec = ev_sub(av_dec, settings.eaeb_ev);
			SendToIntercom(0x0A, 1, av_dec);
			release_and_wait();

			if (FLAG_FACE_SENSOR)
				break;
		}

		SendToIntercom(0x0A, 1, av_comp);
	}
}

void sub_interval() {
	int i = 0;

	for (;;) {
		if (FLAG_FACE_SENSOR)
			break;

		wait_for_camera();

		if (settings.interval_eaeb)
			sub_extended_aeb();
		else
			eventproc_Release();

		if (++i < settings.interval_shots || settings.interval_shots == 0)
			script_delay(settings.interval_time);
		else
			break;
	}
}

void release_and_wait() {
	eventproc_Release();
	wait_for_camera();
}

void wait_for_camera() {
	while(FLAG_CAMERA_BUSY)
		SleepTask(WAIT_CAMERA_BUSY);
}

void script_delay(int seconds) {
	int i = SCRIPT_DELAY_REPEAT * seconds;

	while(--i && !FLAG_FACE_SENSOR)
		SleepTask(SCRIPT_DELAY_TIME);
}
