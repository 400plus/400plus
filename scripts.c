/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <camera.h>
#include <stdbool.h>

#include "main.h"
#include "firmware.h"

#include "display.h"
#include "exposure.h"
#include "settings.h"
#include "utils.h"

#include "scripts.h"

int *feedback_task = NULL;

dpr_data_t st_DPData;

void script_start();
void script_stop();
void script_feedback();

void script_action(type_SHOT_ACTION action);

void action_ext_aeb();
void action_efl_aeb();
void action_iso_aeb();
void action_long_exp();

void script_delay(int seconds);

int can_continue();

void script_ext_aeb() {
	script_start();

	if (settings.eaeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_EXT_AEB);

	script_stop();

	status.last_script = SCRIPT_EXT_AEB;
}

void script_efl_aeb() {
	script_start();

	if (settings.efl_aeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_EFL_AEB);

	script_stop();

	status.last_script = SCRIPT_EFL_AEB;
}

void script_iso_aeb() {
	script_start();

	if (settings.iso_aeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_ISO_AEB);

	script_stop();

	status.last_script = SCRIPT_ISO_AEB;
}

void script_interval() {
	int i;
	int target, gap = 0, pause = 0, jump = 0;
	int delay = settings.interval_time * SCRIPT_DELAY_RESOLUTION;

	script_start();

	if (settings.interval_delay)
		script_delay(SCRIPT_DELAY_START);

	// "target" is the timestamp when we are supposed to shot
	target = timestamp();

	for (i = 0; i < settings.interval_shots || settings.interval_shots == 0; i++) {
		// We pause before each shot, after waiting for the camera to finish the previous one
		if (i > 0) {
			wait_for_camera();

			if (!can_continue())
				break;

			// Calculate how much time is left until target, and wait;
			// automatically aim for the next target, if already missed this
			gap    = target - timestamp();
			pause  = gap % delay;
			pause += pause > 0 ? 0 : delay;

			script_delay(pause);
		}

		if (!can_continue())
			break;

		script_action(settings.interval_action);

		// Recalculate the next target,
		// but considering we may have already missed it
		jump    = (pause % delay) - gap;
		jump   += jump > delay ? 0 : delay;
		target += jump;
	}

	script_stop();

	status.last_script = SCRIPT_INTERVAL;
}

void script_wave() {
	script_start();

	// First, wait for the sensor to be free, just in case
	while (can_continue() && FLAG_FACE_SENSOR)
		SleepTask(WAIT_USER_ACTION);

	do {
		// Now, wait until something blocks the sensor
		while (can_continue() && !FLAG_FACE_SENSOR)
			SleepTask(WAIT_USER_ACTION);

		// If instant not activated, wait until sensor is free again
		if (!settings.wave_instant) {
			while (can_continue() && FLAG_FACE_SENSOR)
				SleepTask(WAIT_USER_ACTION);
		}

		// Do the optional delay
		if (settings.wave_delay)
			script_delay(SCRIPT_DELAY_START);

		// And finally fire the camera
		if (can_continue())
			script_action(settings.wave_action);
	} while (can_continue() && settings.wave_repeat);

	script_stop();

	status.last_script = SCRIPT_WAVE;
}

void script_self_timer() {
	script_start();

	script_delay(settings.timer_timeout * SCRIPT_DELAY_RESOLUTION);

	if (can_continue())
		script_action(settings.timer_action);

	script_stop();

	status.last_script = SCRIPT_TIMER;
}


void script_long_exp() {
	script_start();

	if (settings.lexp_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_LONG_EXP);

	script_stop();

	status.last_script = SCRIPT_LONG_EXP;
}

void script_start() {
	beep();

	status.script_running  = true;
	status.script_stopping = false;

	st_DPData = DPData;

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, false);
	send_to_intercom(IC_SET_AE_BKT,            1, 0x00);

	if (settings.keep_power_on)
		send_to_intercom(IC_SET_AUTO_POWER_OFF, 1, false);

	switch (settings.script_lcd) {
	case SCRIPT_LCD_DIM:
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1, 1);
		break;
	case SCRIPT_LCD_OFF:
		display_off();
		break;
	default:
		break;
	}

	if (settings.script_indicator != SCRIPT_INDICATOR_NONE) {
		if (feedback_task == NULL)
			feedback_task = CreateTask("Feedback", 5, 0x2000, script_feedback, 0);
		else
			UnSuspendTask(feedback_task);
	}
}

void script_stop() {
	beep();

	status.script_running  = false;
	status.script_stopping = true;

	script_restore();
}

void script_restore_parameters() {
	wait_for_camera();

	send_to_intercom(IC_SET_AE,     1, st_DPData.ae);
	send_to_intercom(IC_SET_EFCOMP, 1, st_DPData.efcomp);
	send_to_intercom(IC_SET_TV_VAL, 1, st_DPData.tv_val);
	send_to_intercom(IC_SET_AV_VAL, 1, st_DPData.av_val);
	send_to_intercom(IC_SET_ISO,    2, st_DPData.iso);
}

void script_restore() {
	wait_for_camera();

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, st_DPData.cf_mirror_up_lock);
	send_to_intercom(IC_SET_AE_BKT,            1, st_DPData.ae_bkt);

	send_to_intercom(IC_SET_LCD_BRIGHTNESS,    1, st_DPData.lcd_brightness);
	send_to_intercom(IC_SET_AUTO_POWER_OFF,    1, st_DPData.auto_power_off);

	display_on();
}

void script_feedback() {
	int cycles, counter;

	for (;;) {
		switch (settings.script_indicator) {
		case SCRIPT_INDICATOR_SLOW:
			cycles = 10;
			break;
		case SCRIPT_INDICATOR_MEDIUM:
			cycles = 5;
			break;
		case SCRIPT_INDICATOR_FAST:
			cycles = 1;
			break;
		default:
			cycles = 0;
			break;
		}

		counter = 0;

		while (can_continue()) {
			SleepTask(FEEDBACK_INTERVAL);

			if (++counter == cycles) {
				led_flash(FEEDBACK_LENGTH);
				counter = 0;
			}
		}

		SuspendTask(feedback_task);
	}
}

void script_action(type_SHOT_ACTION action) {
	switch (action) {
	case SHOT_ACTION_SHOT:
		shutter_release();
		break;
	case SHOT_ACTION_EXT_AEB:
		action_ext_aeb();
		break;
	case SHOT_ACTION_EFL_AEB:
		action_efl_aeb();
		break;
	case SHOT_ACTION_ISO_AEB:
		action_iso_aeb();
		break;
	case SHOT_ACTION_LONG_EXP:
		action_long_exp();
		break;
	default:
		break;
	}
}

void action_ext_aeb() {
	if (DPData.tv_val == TV_VAL_BULB) {
		int tv_val;

		for (tv_val = settings.eaeb_tv_max; tv_val <= settings.eaeb_tv_min; tv_val = bulb_next(tv_val)) {
			wait_for_camera();

			if (tv_val < 0120) {
				if (DPData.tv_val != TV_VAL_BULB)
					send_to_intercom(IC_SET_TV_VAL, 1, TV_VAL_BULB);

				shutter_release_bulb(60 * 1 << ((0110 - tv_val) / 0010));
			} else {
				send_to_intercom(IC_SET_TV_VAL, 1, tv_val - 0100);
				shutter_release();
			}

			if (!can_continue())
				break;
		}
	} else if (DPData.ae < AE_MODE_AUTO) {
		int tv_inc, av_inc;
		int tv_dec, av_dec;

		int tv_sep = 0x00, av_sep = 0x00;
		int frames = settings.eaeb_frames;

		if (DPData.ae == AE_MODE_TV) {
			// Fixed Tv, Variable Av
			av_sep = settings.eaeb_ev;
		} else {
			// Variable Tv, Fixed Av
			tv_sep = settings.eaeb_ev;
		}

		// First photo taken using default values
		shutter_release();
		frames--;

		// Grab the parameters used by the camera
		tv_inc = tv_dec = status.last_shot_tv;
		av_inc = av_dec = status.last_shot_av;

		// Enter manual mode...
		if (DPData.ae != AE_MODE_M) {
			wait_for_camera();
			send_to_intercom(IC_SET_AE, 1, AE_MODE_M);
		}

		// ...and do the rest ourselves
		while(frames) {
			if (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_DOWN) {
				wait_for_camera();

				tv_inc = tv_add(tv_inc, tv_sep);
				av_inc = av_add(av_inc, av_sep);

				send_to_intercom(IC_SET_TV_VAL, 1, tv_inc);
				send_to_intercom(IC_SET_AV_VAL, 1, av_inc);

				shutter_release();
				frames--;

				if (!can_continue())
					break;
			}

			if (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_UP) {
				wait_for_camera();

				tv_dec = tv_sub(tv_dec, tv_sep);
				av_dec = av_sub(av_dec, av_sep);

				send_to_intercom(IC_SET_TV_VAL, 1, tv_dec);
				send_to_intercom(IC_SET_AV_VAL, 1, av_dec);

				shutter_release();
				frames--;

				if (!can_continue())
					break;
			}
		}
	}

	script_restore_parameters();
}

void action_iso_aeb() {
	int i;

	for (i = 0; i < 5; i++) {
		if (settings.iso_aeb[i]) {
			wait_for_camera();

			send_to_intercom(IC_SET_ISO, 2, 0x40 | ((i + 1) << 3));
			SleepTask(WAIT_USER_ACTION);
			shutter_release();

			if (!can_continue())
				break;
		}
	}

	script_restore_parameters();
}

void action_efl_aeb() {
	int frames = settings.efl_aeb_frames;

	int ef_inc = DPData.efcomp;
	int ef_dec = DPData.efcomp;

	shutter_release();
	frames--;

	while(frames) {
		if (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_DOWN) {
			wait_for_camera();

			ef_inc = ec_add(ef_inc, settings.efl_aeb_ev);
			send_to_intercom(IC_SET_EFCOMP, 1, ef_inc);

			shutter_release();
			frames--;

			if (!can_continue())
				break;
		}

		if (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_UP) {
			wait_for_camera();

			ef_dec = ec_sub(ef_dec, settings.efl_aeb_ev);
			send_to_intercom(IC_SET_EFCOMP, 1, ef_dec);

			shutter_release();
			frames--;

			if (!can_continue())
				break;
		}
	}

	script_restore_parameters();
}

void action_long_exp() {
	wait_for_camera();

	if (DPData.ae != AE_MODE_M)
		send_to_intercom(IC_SET_AE,     1, AE_MODE_M);

	if (DPData.tv_val != TV_VAL_BULB)
		send_to_intercom(IC_SET_TV_VAL, 1, TV_VAL_BULB);

	shutter_release_bulb(settings.lexp_time);
}

void script_delay(int delay) {
	while(delay > SCRIPT_DELAY_TIME) {
		SleepTask(SCRIPT_DELAY_TIME);

		if (!can_continue())
			return;

		delay -= SCRIPT_DELAY_TIME;
	}

	if (delay > 0)
		SleepTask(delay);
}

int can_continue() {
	return ! (status.script_stopping || DPData.avail_shot < SCRIPT_MIN_SHOTS);
}
