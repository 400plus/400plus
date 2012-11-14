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

#include "utils.h"

#include "settings.h"

type_SETTINGS settings_default = {
	iso_in_viewfinder: false,
	autoiso_enable   : false,
	autoiso_miniso   : 0x48, // ISO100
	autoiso_maxiso   : 0x68, // ISO1600
	autoiso_mintv    : 0x68, // 1/60s
	autoiso_maxav    : 0x28, // f/4.0
	eaeb_delay       : false,
	eaeb_frames      : 3,
	eaeb_ev          : 0x08, // 1EV
	eaeb_tv_min      : 0x78, // 1/250s
	eaeb_tv_max      : 0x68, // 1/60s
	eaeb_direction   : EAEB_DIRECTION_BOTH,
	efl_aeb_delay    : false,
	efl_aeb_frames   : 3,
	efl_aeb_ev       : 0x08, // 1EV
	efl_aeb_direction: EAEB_DIRECTION_BOTH,
	iso_aeb_delay    : false,
	iso_aeb          : {true, true, true, true, true},
	interval_delay   : false,
	interval_time    : 2,
	interval_action  : SHOT_ACTION_SHOT,
	interval_shots   : 0,
	wave_delay       : false,
	wave_action      : SHOT_ACTION_SHOT,
	wave_repeat      : false,
	wave_instant     : false,
	lexp_delay       : false,
	lexp_time        : 60,
	remote_delay     : false,
	timer_timeout    : 5,
	timer_action     : SHOT_ACTION_SHOT,
	main_order       : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	params_order     : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	scripts_order    : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	info_order       : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	developer_order  : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	settings_order   : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
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
	menu_warp        : true,
	menu_navmain     : false,
	menu_entermain   : false,
};

type_SETTINGS settings;

int settings_read() {
	int result  = false;

	int file    = -1;
	int version =  0;

	type_SETTINGS buffer;

	settings = settings_default;

	if ((file = FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	settings = buffer;
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
		FIO_WriteFile(file, &settings, sizeof(settings));
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
	settings = settings_default;

	settings_apply();
	settings_write();
}
