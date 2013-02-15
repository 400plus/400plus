/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "main.h"
#include "firmware.h"

#include "exposure.h"
#include "utils.h"

#include "settings.h"

settings_t settings_default = {
	use_dpad         : true,
	autoiso_enable   : false,
	autoiso_miniso   : ISO_MIN, // ISO100
	autoiso_maxiso   : ISO_MAX, // ISO1600
	autoiso_mintv    : EV_CODE(13, 0), // 1/60s
	autoiso_maxav    : EV_CODE( 1, 0), // 1EV
	autoiso_relaxed  : false,
	eaeb_delay       : false,
	eaeb_frames      : 3,
	eaeb_ev          : EV_CODE( 1, 0), // 1EV
	eaeb_tv_min      : TV_BULB(EV_CODE(15, 0)), // 1/250s
	eaeb_tv_max      : TV_BULB(EV_CODE(13, 0)), // 1/60s
	eaeb_direction   : EAEB_DIRECTION_BOTH,
	efl_aeb_delay    : false,
	efl_aeb_frames   : 3,
	efl_aeb_ev       : EV_CODE( 1, 0), // 1EV
	efl_aeb_direction: EAEB_DIRECTION_BOTH,
	apt_aeb_delay    : false,
	apt_aeb_frames   : 3,
	apt_aeb_ev       : EV_CODE( 1, 0), // 1EV
	apt_aeb_direction: EAEB_DIRECTION_BOTH,
	iso_aeb_delay    : false,
	iso_aeb          : {true, true, true, true, true},
	interval_delay   : false,
	interval_time    : 2,
	interval_action  : SHOT_ACTION_SHOT,
	interval_shots   : 0,
	bramp_delay      : false,
	bramp_time       : 60,
	bramp_shots      : 100,
	bramp_exp        : 1,
	bramp_ramp_t     : 300,
	bramp_ramp_s     : 0,
	bramp_ramp_exp   : EV_CODE(1, 0),
	bramp_ramp_time  : EV_ZERO,
	wave_delay       : false,
	wave_action      : SHOT_ACTION_SHOT,
	wave_repeat      : false,
	wave_instant     : false,
	lexp_delay       : false,
	lexp_time        : 60,
	remote_delay     : false,
	timer_timeout    : 5,
	timer_action     : SHOT_ACTION_SHOT,
	keep_power_on    : true,
	script_lcd       : SCRIPT_LCD_KEEP,
	script_indicator : SCRIPT_INDICATOR_MEDIUM,
	debug_on_poweron : false,
	logfile_mode     : 0,
	remote_enable    : false,
	developers_menu  : false,
	button_jump      : BUTTON_ACTION_ISO,
	button_trash     : BUTTON_ACTION_SCRIPT,
	button_disp      : false,
	language         : 0,
	digital_iso_step : 0,
	menu_navmain     : false,
	menu_entermain   : false,
	menu_autosave    : true,
	qexp_mintv       : EV_CODE(13, 0), // 1/60s
	qexp_weight      : QEXP_WEIGHT_NONE,
};

menu_order_t menu_order_default = {
	main_order       : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	params_order     : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	scripts_order    : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	info_order       : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	developer_order  : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	settings_order   : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
};

settings_t   settings;
menu_order_t menu_order;

int settings_read() {
	int result  = false;

	int file    = -1;
	int version =  0;

	settings_t   settings_buffer;
	menu_order_t menu_order_buffer;

	settings   = settings_default;
	menu_order = menu_order_default;

	if ((file = FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &settings_buffer, sizeof(settings_buffer)) != sizeof(settings_buffer))
		goto end;

	if (FIO_ReadFile(file, &menu_order_buffer, sizeof(menu_order_buffer)) != sizeof(menu_order_buffer))
		goto end;

	settings   = settings_buffer;
	menu_order = menu_order_buffer;

	result   = true;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

void settings_write() {
	const int version = SETTINGS_VERSION;
	int file = FIO_OpenFile(SETTINGS_FILE, O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, (void*)&version, sizeof(version));

		FIO_WriteFile(file, &settings,   sizeof(settings));
		FIO_WriteFile(file, &menu_order, sizeof(menu_order));

		FIO_CloseFile(file);
	}
}

extern void settings_apply() {
	if (settings.remote_delay) {
		RemReleaseSelfMax = 4500;
		RemReleaseInstMin = 5560;
	} else {
		RemReleaseSelfMax = 6160;
		RemReleaseInstMin = 7410;
	}

	if (settings.remote_enable) {
		remote_on();
	} else {
		remote_off();
	}
}

void settings_restore() {
	settings   = settings_default;
	menu_order = menu_order_default;

	settings_apply();
	settings_write();
}
