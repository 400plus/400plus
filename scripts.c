#include <vxworks.h>

#include "firmware.h"
#include "firmware/camera.h"

#include "main.h"
#include "macros.h"

#include "display.h"
#include "exposure.h"
#include "float.h"
#include "persist.h"
#include "settings.h"
#include "utils.h"
#include "shutter.h"
#include "intercom.h"

#include "scripts.h"

int *feedback_task = NULL;

dpr_data_t st_DPData;

void script_start   (void);
void script_stop    (void);
void script_feedback(void);

void script_restore_parameters(void);

void script_action(shot_action_t action);

void action_ext_aeb (void);
void action_efl_aeb (void);
void action_apt_aeb (void);
void action_iso_aeb (void);
void action_long_exp(void);

void script_delay(int seconds);

int can_continue(void);

void script_ext_aeb() {
	script_start();

	if (settings.eaeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_EXT_AEB);

	script_stop();

	persist.last_script = SCRIPT_EXT_AEB;
}

void script_efl_aeb() {
	script_start();

	if (settings.efl_aeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_EFL_AEB);

	script_stop();

	persist.last_script = SCRIPT_EFL_AEB;
}

void script_apt_aeb() {
	script_start();

	if (settings.apt_aeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_APT_AEB);

	script_stop();

	persist.last_script = SCRIPT_APT_AEB;
}

void script_iso_aeb() {
	script_start();

	if (settings.iso_aeb_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_ISO_AEB);

	script_stop();

	persist.last_script = SCRIPT_ISO_AEB;
}

void script_interval() {
	int i;
	int target, gap = 0, pause = 0, jump = 0;
	int delay = settings.interval_time * TIME_RESOLUTION;

	script_start();

	if (settings.interval_delay)
		script_delay(SCRIPT_DELAY_START);

	// "target" is the timestamp when we are supposed to shot
	target  = timestamp();

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

	persist.last_script = SCRIPT_INTERVAL;
}

void script_bramp() {
	script_start();

	if (settings.bramp_delay)
		script_delay(SCRIPT_DELAY_START);

	if (DPData.ae != AE_MODE_M)
		send_to_intercom(IC_SET_AE,     AE_MODE_M);

	if (DPData.tv_val != TV_VAL_BULB)
		send_to_intercom(IC_SET_TV_VAL, TV_VAL_BULB);

	float coef_s_expo, coef_s_delay, coef_t_expo, coef_t_delay;

	if (settings.bramp_ramp_s > 0) {
		coef_s_expo  = ((float)settings.bramp_ramp_exp  / 8.0f) / (float)settings.bramp_ramp_s;
		coef_s_delay = ((float)settings.bramp_ramp_time / 8.0f) / (float)settings.bramp_ramp_s;
	} else {
		coef_s_expo  = 0.0f;
		coef_s_delay = 0.0f;
	}

	if (settings.bramp_ramp_t > 0) {
		coef_t_expo  = ((float)settings.bramp_ramp_exp  / 8.0f) / ((float)settings.bramp_ramp_t * (float)TIME_RESOLUTION);
		coef_t_delay = ((float)settings.bramp_ramp_time / 8.0f) / ((float)settings.bramp_ramp_t * (float)TIME_RESOLUTION);
	} else {
		coef_t_expo  = 0.0f;
		coef_t_delay = 0.0f;
	}

	int shot;

	int start  = timestamp();
	int target = start;

	for (shot = 0; shot < settings.bramp_shots || settings.bramp_shots == 0; shot++) {
		int delay = (float)TIME_RESOLUTION * (float)settings.bramp_time *
				float_pow2((float)shot * coef_s_delay) *
				float_pow2((float)(timestamp() - start) * coef_t_delay);

		if (shot > 0) {
			wait_for_camera();

			if (!can_continue())
				break;

			int pause = target - timestamp();

			if (pause > BRAMP_MAX_INTERVAL)
				break;
			else if (pause > BRAMP_MIN_INTERVAL)
				script_delay(pause);
			else
				beep();
		}

		target += delay;

		int expo = (float)TIME_RESOLUTION * (float)settings.bramp_exp  *
				float_pow2((float)shot * coef_s_expo) *
				float_pow2((float)(timestamp() - start) * coef_t_expo);

		if (expo > BRAMP_MAX_EXPOSURE)
			break;
		else if (expo > BRAMP_MIN_EXPOSURE)
			shutter_release_bulb(expo);
		else
			beep();
	}

	script_stop();

	persist.last_script = SCRIPT_BRAMP;
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

	persist.last_script = SCRIPT_WAVE;
}

void script_self_timer() {
	int delay;

	delay  = settings.timer_timeout * TIME_RESOLUTION;
	delay -= DPData.drive == DRIVE_MODE_TIMER ? SELF_TIMER_MS : 0;
	delay  = MAX(delay, 0);

	script_start();
	script_delay(delay);

	if (can_continue())
		script_action(settings.timer_action);

	script_stop();

	persist.last_script = SCRIPT_TIMER;
}


void script_long_exp() {
	script_start();

	if (settings.lexp_delay)
		script_delay(SCRIPT_DELAY_START);

	if (can_continue())
		script_action(SHOT_ACTION_LONG_EXP);

	script_restore_parameters();
	script_stop();

	persist.last_script = SCRIPT_LONG_EXP;
}

void script_start() {
	beep();

	status.script_running  = TRUE;
	status.script_stopping = FALSE;

	st_DPData = DPData;

	// Force MLU to on if drive mode is self-timer, force MLU to off otherwise
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, DPData.drive == DRIVE_MODE_TIMER);

	// To avoid interferences with our EAEB script, disable AEB
	send_to_intercom(IC_SET_AE_BKT, EC_ZERO);

	if (settings.keep_power_on)
		send_to_intercom(IC_SET_AUTO_POWER_OFF, FALSE);

	if (settings.review_off)
		send_to_intercom(IC_SET_REVIEW_TIME, REVIEW_OFF);

	switch (settings.script_lcd) {
	case SCRIPT_LCD_DIM:
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1);
		break;
	case SCRIPT_LCD_OFF:
		if (FLAG_DISPLAY_ON)
			press_button(IC_BUTTON_DISP);
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

	status.script_running  = FALSE;
	status.script_stopping = TRUE;

	script_restore();
}

void script_restore_parameters() {
	wait_for_camera();

	send_to_intercom(IC_SET_EFCOMP, st_DPData.efcomp);
	send_to_intercom(IC_SET_TV_VAL, st_DPData.tv_val);
	send_to_intercom(IC_SET_AV_VAL, st_DPData.av_val);
	send_to_intercom(IC_SET_AE,     st_DPData.ae);
	send_to_intercom(IC_SET_ISO,    st_DPData.iso);
}

void script_restore() {
	wait_for_camera();

	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, st_DPData.cf_mirror_up_lock);
	send_to_intercom(IC_SET_AE_BKT,            st_DPData.ae_bkt);

	send_to_intercom(IC_SET_AUTO_POWER_OFF,    st_DPData.auto_power_off);
	send_to_intercom(IC_SET_REVIEW_TIME,       st_DPData.review_time);

	switch (settings.script_lcd) {
	case SCRIPT_LCD_DIM:
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, st_DPData.lcd_brightness);
		break;
	case SCRIPT_LCD_OFF:
		if (! FLAG_DISPLAY_ON)
			press_button(IC_BUTTON_DISP);
		break;
	default:
		break;
	}
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

void script_action(shot_action_t action) {
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
	case SHOT_ACTION_APT_AEB:
		action_apt_aeb();
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
		tv_t tv_val;

		for (tv_val = settings.eaeb_tv_max; tv_val <= settings.eaeb_tv_min; tv_val = bulb_next(tv_val)) {
			wait_for_camera();

			if (tv_val < BULB_VAL) {
				if (DPData.tv_val != TV_VAL_BULB)
					send_to_intercom(IC_SET_TV_VAL, TV_VAL_BULB);

				shutter_release_bulb(60 * BULB_MN(tv_val) * TIME_RESOLUTION);
			} else {
				send_to_intercom(IC_SET_TV_VAL, BULB_TV(tv_val));
				shutter_release();
			}

			if (!can_continue())
				break;
		}
	} else if (AE_IS_CREATIVE(DPData.ae)) {
		tv_t tv_inc, tv_dec;
		av_t av_inc, av_dec;

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
			send_to_intercom(IC_SET_AE, AE_MODE_M);
		}

		// ...and do the rest ourselves
		while (frames > 0) {
			if (frames > 0 && (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_DOWN)) {
				wait_for_camera();

				tv_inc = tv_add(tv_inc, tv_sep);
				av_inc = av_add(av_inc, av_sep);

				send_to_intercom(IC_SET_TV_VAL, tv_inc);
				send_to_intercom(IC_SET_AV_VAL, av_inc);

				shutter_release();
				frames--;

				if (!can_continue())
					break;
			}

			if (frames > 0 && (settings.eaeb_direction == EAEB_DIRECTION_BOTH || settings.eaeb_direction == EAEB_DIRECTION_UP)) {
				wait_for_camera();

				tv_dec = tv_sub(tv_dec, tv_sep);
				av_dec = av_sub(av_dec, av_sep);

				send_to_intercom(IC_SET_TV_VAL, tv_dec);
				send_to_intercom(IC_SET_AV_VAL, av_dec);

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

			send_to_intercom(IC_SET_ISO, 0x40 | ((i + 1) << 3));
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

	ec_t ef_inc = DPData.efcomp;
	ec_t ef_dec = DPData.efcomp;

	shutter_release();
	frames--;

	while (frames > 0) {
		if (frames > 0 && (settings.efl_aeb_direction == EAEB_DIRECTION_BOTH || settings.efl_aeb_direction == EAEB_DIRECTION_DOWN)) {
			wait_for_camera();

			ef_inc = ec_add(ef_inc, settings.efl_aeb_ev);
			send_to_intercom(IC_SET_EFCOMP, ef_inc);

			shutter_release();
			frames--;

			if (!can_continue())
				break;
		}

		if (frames > 0 && (settings.efl_aeb_direction == EAEB_DIRECTION_BOTH || settings.efl_aeb_direction == EAEB_DIRECTION_UP)) {
			wait_for_camera();

			ef_dec = ec_sub(ef_dec, settings.efl_aeb_ev);
			send_to_intercom(IC_SET_EFCOMP, ef_dec);

			shutter_release();
			frames--;

			if (!can_continue())
				break;
		}
	}

	script_restore_parameters();
}

void action_apt_aeb() {
	int frames = settings.apt_aeb_frames;

	tv_t tv_inc, tv_dec;
	av_t av_inc, av_dec;

	// First photo taken using default values
	shutter_release();
	frames--;

	// Grab the parameters used by the camera
	tv_inc = tv_dec = status.last_shot_tv;
	av_inc = av_dec = status.last_shot_av;

	// Enter manual mode...
	if (DPData.ae != AE_MODE_M) {
		wait_for_camera();
		send_to_intercom(IC_SET_AE, AE_MODE_M);
	}

	// ...and do the rest ourselves
	while (frames > 0) {
		if (frames > 0 && (settings.apt_aeb_direction == EAEB_DIRECTION_BOTH || settings.apt_aeb_direction == EAEB_DIRECTION_DOWN)) {
			wait_for_camera();

			tv_inc = tv_add(tv_inc, settings.apt_aeb_ev);
			send_to_intercom(IC_SET_TV_VAL, tv_inc);

			av_inc = av_sub(av_inc, settings.apt_aeb_ev);
			send_to_intercom(IC_SET_AV_VAL, av_inc);

			shutter_release();
			frames--;

			if (!can_continue())
				break;
		}

		if (frames > 0 && (settings.apt_aeb_direction == EAEB_DIRECTION_BOTH || settings.apt_aeb_direction == EAEB_DIRECTION_UP)) {
			wait_for_camera();

			tv_dec = tv_sub(tv_dec, settings.apt_aeb_ev);
			send_to_intercom(IC_SET_TV_VAL, tv_dec);

			av_dec = av_add(av_dec, settings.apt_aeb_ev);
			send_to_intercom(IC_SET_AV_VAL, av_dec);

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
		send_to_intercom(IC_SET_AE,     AE_MODE_M);

	if (DPData.tv_val != TV_VAL_BULB)
		send_to_intercom(IC_SET_TV_VAL, TV_VAL_BULB);

	shutter_release_bulb(settings.lexp_time * TIME_RESOLUTION);
}

void script_delay(int delay) {
	while (delay > SCRIPT_DELAY_TIME) {
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
