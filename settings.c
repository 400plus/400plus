#include <vxworks.h>
#include <string.h>
#include <ioLib.h>

#include "firmware/fio.h"

#include "main.h"
#include "macros.h"
#include "firmware.h"

#include "exposure.h"
#include "utils.h"

#include "settings.h"

settings_t settings_default = {
	use_dpad         : TRUE,
	autoiso_enable   : FALSE,
	autoiso_miniso   : ISO_MIN, // ISO100
	autoiso_maxiso   : ISO_MAX, // ISO1600
	autoiso_mintv    : EV_CODE(13, 0), // 1/60s
	autoiso_maxav    : EV_CODE( 1, 0), // 1EV
	autoiso_relaxed  : FALSE,
	eaeb_delay       : FALSE,
	eaeb_frames      : 3,
	eaeb_ev          : EV_CODE( 1, 0), // 1EV
	eaeb_tv_min      : TV_BULB(EV_CODE(15, 0)), // 1/250s
	eaeb_tv_max      : TV_BULB(EV_CODE(13, 0)), // 1/60s
	eaeb_direction   : EAEB_DIRECTION_BOTH,
	efl_aeb_delay    : FALSE,
	efl_aeb_frames   : 3,
	efl_aeb_ev       : EV_CODE( 1, 0), // 1EV
	efl_aeb_direction: EAEB_DIRECTION_BOTH,
	apt_aeb_delay    : FALSE,
	apt_aeb_frames   : 3,
	apt_aeb_ev       : EV_CODE( 1, 0), // 1EV
	apt_aeb_direction: EAEB_DIRECTION_BOTH,
	iso_aeb_delay    : FALSE,
	iso_aeb          : {TRUE, TRUE, TRUE, TRUE, TRUE},
	interval_delay   : FALSE,
	interval_time    : 2,
	interval_action  : SHOT_ACTION_SHOT,
	interval_shots   : 0,
	bramp_delay      : FALSE,
	bramp_time       : 60,
	bramp_shots      : 100,
	bramp_exp        : 1,
	bramp_ramp_t     : 300,
	bramp_ramp_s     : 0,
	bramp_ramp_exp   : EV_CODE(1, 0),
	bramp_ramp_time  : EV_ZERO,
	wave_delay       : FALSE,
	wave_action      : SHOT_ACTION_SHOT,
	wave_repeat      : FALSE,
	wave_instant     : FALSE,
	lexp_delay       : FALSE,
	lexp_time        : 60,
	remote_delay     : FALSE,
	timer_timeout    : 5,
	timer_action     : SHOT_ACTION_SHOT,
	keep_power_on    : TRUE,
	review_off       : FALSE,
	script_lcd       : SCRIPT_LCD_KEEP,
	script_indicator : SCRIPT_INDICATOR_MEDIUM,
	debug_on_poweron : FALSE,
	logfile_mode     : 0,
	remote_enable    : FALSE,
	developers_menu  : FALSE,
	shortcut_jump    : SHORTCUT_ISO,
	shortcut_trash   : SHORTCUT_SCRIPT,
	button_disp      : FALSE,
	language         : 0,
	digital_iso_step : 0,
	menu_navmain     : FALSE,
	menu_entermain   : FALSE,
	menu_autosave    : TRUE,
	qexp_mintv       : EV_CODE(13, 0), // 1/60s
	qexp_weight      : QEXP_WEIGHT_NONE,
	persist_aeb      : TRUE,
	invert_olc       : 0,
};

menu_order_t menu_order_default;

named_temps_t named_temps_default = {
	initd : FALSE,
	temps : {
		1700, // Match flame
		1900, // Candle flame
		2850, // Tungsten light
		2950, // Fl. Warm White
		3450, // Fl. White
		4225, // Fl. Cool White
		6525, // Fl. Daylight
		4850, // Daylight
		5200, // Sunny
		6000, // Flash
		6000, // Cloudy
		7000, // Shade
		5000, // D50
		5500, // D55
		6500, // D65
		7500, // D75
	},
};

settings_t    settings;
menu_order_t  menu_order;
named_temps_t named_temps;

int settings_read() {
	int i;

	int result    = FALSE;
	int file    = -1;
	int   version = 0;

	for (i = 0; i < LENGTH(menu_order_default.main); i++)
		menu_order_default.main[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.params); i++)
		menu_order_default.params[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.scripts); i++)
		menu_order_default.scripts[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.info); i++)
		menu_order_default.info[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.developer); i++)
		menu_order_default.developer[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.settings); i++)
		menu_order_default.settings[i] = i;

	for (i = 0; i < LENGTH(menu_order_default.named_temps); i++)
		menu_order_default.named_temps[i] = i;

	settings_t    settings_buffer;
	menu_order_t  menu_order_buffer;
	named_temps_t named_temps_buffer;

	settings    = settings_default;
	menu_order  = menu_order_default;
	named_temps = named_temps_default;

	if ((file = FIO_OpenFile(MKPATH_NEW(SETTINGS_FILENAME), O_RDONLY)) == -1)
		if ((file = FIO_OpenFile(MKPATH_OLD(SETTINGS_FILENAME), O_RDONLY)) == -1)
			goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &settings_buffer,    sizeof(settings_buffer))    != sizeof(settings_buffer))
		goto end;

	if (FIO_ReadFile(file, &menu_order_buffer,  sizeof(menu_order_buffer))  != sizeof(menu_order_buffer))
		goto end;

	if (FIO_ReadFile(file, &named_temps_buffer, sizeof(named_temps_buffer)) != sizeof(named_temps_buffer))
		goto end;

	settings    = settings_buffer;
	menu_order  = menu_order_buffer;
	named_temps = named_temps_buffer;

	result   = TRUE;

#if SETTINGS_VERSION == 0x4A
	int nt;
	// Temporal fix for those affected by issue #333
	// Remove after increasing the version of the settings file
	if (menu_order.named_temps[0] == 0 && menu_order.named_temps[1] == 0)
		for (nt = 0; nt < LENGTH(menu_order.named_temps); nt++)
			menu_order.named_temps[nt] = nt;
#endif

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

void settings_write() {
	const int version = SETTINGS_VERSION;

	int file = -1;

	if ((file = FIO_OpenFile(MKPATH_NEW(SETTINGS_FILENAME), O_CREAT | O_WRONLY)) == -1)
		if (status.folder_exists || (file = FIO_OpenFile(MKPATH_OLD(SETTINGS_FILENAME), O_CREAT | O_WRONLY)) == -1)
			goto end;

	FIO_WriteFile(file, (void*)&version, sizeof(version));

	FIO_WriteFile(file, &settings,    sizeof(settings));
	FIO_WriteFile(file, &menu_order,  sizeof(menu_order));
	FIO_WriteFile(file, &named_temps, sizeof(named_temps));

end:
	if (file != -1)
		FIO_CloseFile(file);
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

void named_temps_init(menu_t *menu) {
	if (!named_temps.initd) {
		strncpy(named_temps.names[ 0], LP_WORD(L_V_NAMED_TEMP_0), LP_MAX_WORD);
		strncpy(named_temps.names[ 1], LP_WORD(L_V_NAMED_TEMP_1), LP_MAX_WORD);
		strncpy(named_temps.names[ 2], LP_WORD(L_V_NAMED_TEMP_2), LP_MAX_WORD);
		strncpy(named_temps.names[ 3], LP_WORD(L_V_NAMED_TEMP_3), LP_MAX_WORD);
		strncpy(named_temps.names[ 4], LP_WORD(L_V_NAMED_TEMP_4), LP_MAX_WORD);
		strncpy(named_temps.names[ 5], LP_WORD(L_V_NAMED_TEMP_5), LP_MAX_WORD);
		strncpy(named_temps.names[ 6], LP_WORD(L_V_NAMED_TEMP_6), LP_MAX_WORD);
		strncpy(named_temps.names[ 7], LP_WORD(L_V_NAMED_TEMP_7), LP_MAX_WORD);
		strncpy(named_temps.names[ 8], LP_WORD(L_V_NAMED_TEMP_8), LP_MAX_WORD);
		strncpy(named_temps.names[ 9], LP_WORD(L_V_NAMED_TEMP_9), LP_MAX_WORD);
		strncpy(named_temps.names[10], LP_WORD(L_V_NAMED_TEMP_A), LP_MAX_WORD);
		strncpy(named_temps.names[11], LP_WORD(L_V_NAMED_TEMP_B), LP_MAX_WORD);
		strncpy(named_temps.names[12], LP_WORD(L_V_NAMED_TEMP_C), LP_MAX_WORD);
		strncpy(named_temps.names[13], LP_WORD(L_V_NAMED_TEMP_D), LP_MAX_WORD);
		strncpy(named_temps.names[14], LP_WORD(L_V_NAMED_TEMP_E), LP_MAX_WORD);
		strncpy(named_temps.names[15], LP_WORD(L_V_NAMED_TEMP_F), LP_MAX_WORD);

		named_temps.initd = TRUE;
	}
}

