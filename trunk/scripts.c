#include "main.h"
#include "firmware.h"

#include "display.h"
#include "settings.h"
#include "utils.h"

#include "scripts.h"

int *feedback_task = NULL;

type_CAMERA_MODE st_cameraMode;

void script_start();
void script_stop();
void script_feedback();

void script_shot(type_SHOT_ACTION action);
void sub_extended_aeb();
void sub_interval();

void release_and_wait();
void wait_for_camera(int strict);
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

	st_cameraMode = *cameraMode;

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, FALSE);

	if (settings.dim_lcd_down)
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1, 1);

	if (settings.keep_power_on)
		send_to_intercom(IC_SET_AUTO_POWER_OFF, 1, FALSE);

	if (feedback_task == NULL)
		feedback_task = CreateTask("Feedback", 5, 0x2000, script_feedback, 0);
	else
		UnSuspendTask(feedback_task);

	wait_for_camera(TRUE);
}

void script_stop() {
	beep();
	status.script_running = FALSE;

	send_to_intercom(IC_SET_AUTO_POWER_OFF,    1, st_cameraMode.auto_power_off);
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, st_cameraMode.cf_mirror_up_lock);
	send_to_intercom(IC_SET_LCD_BRIGHTNESS,    1, st_cameraMode.lcd_brightness);

	wait_for_camera(TRUE);
}

void script_feedback() {
	for (;;) {
		while (status.script_running) {
			led_flash(FEEDBACK_LENGTH);
			SleepTask(FEEDBACK_INTERVAL);
		}

		SuspendTask(feedback_task);
	}
}

void script_shot(type_SHOT_ACTION action) {
	int aeb = cameraMode->ae_bkt;
	send_to_intercom(IC_SET_AE_BKT, 1, 0x00);

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

	send_to_intercom(IC_SET_AE_BKT, 1, aeb);
}

void sub_extended_aeb() {
	if (cameraMode->ae == AE_MODE_M) {
		if (cameraMode->tv_val == TV_VAL_BULB) {
			int tv_val;

			int tv_start = MIN(settings.eaeb_tv_min, settings.eaeb_tv_max) - 5;
			int tv_end   = MAX(settings.eaeb_tv_min, settings.eaeb_tv_max) - 5;

			for (tv_val = tv_start; tv_val <= tv_end; tv_val ++) {
				if (tv_val < 0) {
					send_to_intercom(IC_SET_TV_VAL, 1, TV_VAL_BULB);

					press_button(0xB6);
					SleepTask((1 << (-1 - tv_val)) * 1000 * 60);

					press_button(0xB6);
					wait_for_camera(TRUE);

					script_delay(1);
				} else {
					send_to_intercom(IC_SET_TV_VAL, 1, (tv_val << 3) + 0x10);
					release_and_wait();
				}

				if (!status.script_running)
					break;
			};
		} else {
			int i;

			int tv_inc = cameraMode->tv_val;
			int tv_dec = cameraMode->tv_val;

			release_and_wait();

			for(i = 0; i < (settings.eaeb_frames - 1) / 2; i++) {
				tv_inc = tv_add(tv_inc, settings.eaeb_ev);
				send_to_intercom(IC_SET_TV_VAL, 1, tv_inc);
				release_and_wait();

				if (!status.script_running)
					break;

				tv_dec = tv_sub(tv_dec, settings.eaeb_ev);
				send_to_intercom(IC_SET_TV_VAL, 1, tv_dec);
				release_and_wait();

				if (!status.script_running)
					break;
			}
		}

		send_to_intercom(IC_SET_TV_VAL, 1, st_cameraMode.tv_val);
	} else {
		int i;

		int av_inc = cameraMode->av_comp;
		int av_dec = cameraMode->av_comp;

		release_and_wait();

		for(i = 0; i < (settings.eaeb_frames - 1) / 2; i++) {
			av_inc = ev_add(av_inc, settings.eaeb_ev);
			send_to_intercom(IC_SET_AV_COMP, 1, av_inc);
			release_and_wait();

			if (!status.script_running)
				break;

			av_dec = ev_sub(av_dec, settings.eaeb_ev);
			send_to_intercom(IC_SET_AV_COMP, 1, av_dec);
			release_and_wait();

			if (!status.script_running)
				break;
		}

		send_to_intercom(IC_SET_AV_COMP, 1, st_cameraMode.av_comp);
	}
}

void sub_interval() {
	int i = 0;

	for (;;) {
		if (!status.script_running)
			break;

		wait_for_camera(TRUE);

		if (settings.interval_eaeb)
			script_shot(SHOT_ACTION_EAEB);
		else
			shutter_release();

		if (++i < settings.interval_shots || settings.interval_shots == 0)
			script_delay(settings.interval_time);
		else
			break;
	}

	wait_for_camera(TRUE);
}

void release_and_wait() {
	shutter_release();
	wait_for_camera(FALSE);
}

void wait_for_camera(int strict) {
	while(FLAG_CAMERA_BUSY)
		SleepTask(WAIT_CAMERA_BUSY);

	if (strict)
		while(cameraMode->status_busy_flag)
			SleepTask(WAIT_CAMERA_BUSY);
	else
		SleepTask(WAIT_CAMERA_BUSY);
}

void script_delay(int seconds) {
	int i;

	display_countdown_dialog_create();

	while (seconds--) {
		display_countdown(1 + seconds);
		for (i = 0; i < SCRIPT_DELAY_REPEAT; i++) {
			SleepTask(SCRIPT_DELAY_TIME);
			if (!status.script_running)
				goto end;
		}

	}

	display_countdown(0);
	SleepTask(SCRIPT_DELAY_TIME);

end:
	display_countdown_dialog_destroy();
}
