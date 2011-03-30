#include "main.h"
#include "utils.h"
#include "display.h"
#include "settings.h"
#include "firmware.h"

#include "scripts.h"

int *feedback_task = NULL;

void script_start();
void script_stop();
void script_feedback();

void script_shot(type_SHOT_ACTION action);
void sub_extended_aeb();
void sub_interval();

void release_and_wait();
void wait_for_camera();
void script_delay(int seconds);

void script_extended_aeb() {
	script_start();

	if (settings.eaeb_delay)
		script_delay(2);

	if (status.script_running)
		script_shot(SHOT_ACTION_EAEB);

	script_stop();
}

void script_interval() {
	script_start();

	if (settings.interval_delay)
		script_delay(2);

	if (status.script_running)
		script_shot(SHOT_ACTION_INTERVAL);

	script_stop();
}

void script_wave() {
	script_start();

	// First, wait for the sensor to be free, just in case
	while (status.script_running && FLAG_FACE_SENSOR)
		SleepTask(WAIT_USER_ACTION);

	do {
		// Now, wait until something blocks the sensor
		while (status.script_running && !FLAG_FACE_SENSOR)
			SleepTask(WAIT_USER_ACTION);

		// If instant not activated, wait until sensor is free again
		if (!settings.wave_instant) {
			while (status.script_running && FLAG_FACE_SENSOR)
				SleepTask(WAIT_USER_ACTION);
		}

		// Do the optional delay
		if (settings.wave_delay)
			script_delay(2);

		// And finally fire the camera
		if (status.script_running)
			script_shot(settings.wave_action);
	} while (status.script_running && settings.wave_repeat);

	script_stop();
}

void script_self_timer() {
	script_start();

	script_delay(settings.timer_timeout);

	if (status.script_running)
		script_shot(settings.timer_action);

	script_stop();
}

void script_start() {
	beep();
	status.script_running = TRUE;

	if (feedback_task == NULL)
		feedback_task = (int *)CreateTask("Feedback", 0x1A, 0x2000, script_feedback, 0);
	else
		UnSuspendTask(feedback_task);
}

void script_stop() {
	wait_for_camera();

	beep();
	status.script_running = FALSE;
}

void script_feedback() {
	for (;;) {
		while (status.script_running) {
			eventproc_EdLedOn();
			SleepTask(FEEDBACK_LENGTH);
			eventproc_EdLedOff();

			SleepTask(FEEDBACK_INTERVAL);
		}

		SuspendTask(feedback_task);
	}
}

void script_shot(type_SHOT_ACTION action) {
	int aeb = cameraMode.AEB;
	SendToIntercom(0x0D, 1, 0x00);

	switch (action) {
	case SHOT_ACTION_SHOT:
		release_and_wait();
		break;
	case SHOT_ACTION_EAEB:
		sub_extended_aeb();
		break;
	case SHOT_ACTION_INTERVAL:
		sub_interval();
		break;
	default:
		break;
	}

	SendToIntercom(0x0D, 1, aeb);
}

void sub_extended_aeb() {
	if (cameraMode.AEMode == AE_MODE_M) {
		int tv;

		int tv_value = cameraMode.TvVal;
		int tv_start = MIN(settings.eaeb_m_min, settings.eaeb_m_max);
		int tv_end   = MAX(settings.eaeb_m_min, settings.eaeb_m_max);

		for (tv = tv_start; tv <= tv_end; tv ++) {
			SendToIntercom(0x08, 1, (tv << 3) + 0x10);
			release_and_wait();

			if (!status.script_running)
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

			if (!status.script_running)
				break;

			av_dec = ev_sub(av_dec, settings.eaeb_ev);
			SendToIntercom(0x0A, 1, av_dec);
			release_and_wait();

			if (!status.script_running)
				break;
		}

		SendToIntercom(0x0A, 1, av_comp);
	}
}

void sub_interval() {
	int i = 0;

	for (;;) {
		if (!status.script_running)
			break;

		wait_for_camera();

		if (settings.interval_eaeb)
			script_shot(SHOT_ACTION_EAEB);
		else
			eventproc_Release();

		if (++i < settings.interval_shots || settings.interval_shots == 0)
			script_delay(settings.interval_time);
		else
			break;
	}

	wait_for_camera();
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
	int i;

	while (seconds--) {
		display_countdown(1 + seconds);
		for (i = 0; i < SCRIPT_DELAY_REPEAT; i++) {
			SleepTask(SCRIPT_DELAY_TIME);
			if (!status.script_running)
				return;
		}

	}

	display_countdown(0);
}
