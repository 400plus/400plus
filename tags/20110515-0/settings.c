#include "main.h"
#include "utils.h"
#include "firmware.h"

#include "settings.h"

type_SETTINGS settings = {
	iso_in_viewfinder: FALSE,
	eaeb_frames      : 3,
	eaeb_delay       : FALSE,
	eaeb_ev          : 0x08,
	eaeb_tv_min      : 0,
	eaeb_tv_max      : 0,
	interval_delay   : FALSE,
	interval_time    : 2,
	interval_eaeb    : FALSE,
	interval_shots   : 0,
	wave_delay       : FALSE,
	wave_action      : SHOT_ACTION_FIRST,
	wave_repeat      : FALSE,
	wave_instant     : FALSE,
	color_temp       : 5200,
	av_comp          : 0,
	flash_comp       : 0,
	aeb_ev           : 0,
	safety_shift     : FALSE,
	emit_flash       : TRUE,
	remote_delay     : FALSE,
	timer_timeout    : 5,
	timer_action     : SHOT_ACTION_FIRST,
	shortcuts_menu   : TRUE,
	shortcuts_order  : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
	dim_lcd_down     : TRUE,
	keep_power_on    : TRUE
};

int settings_read() {
	int result  = FALSE;

	int file    = -1;
	int version =  0;

	type_SETTINGS buffer;

	if ((file = FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	settings = buffer;
	result   = TRUE;

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
	send_to_intercom(IC_SET_AV_COMP,         1,  settings.av_comp);
	send_to_intercom(IC_SET_EFCOMP,          1,  settings.flash_comp);
	send_to_intercom(IC_SET_AE_BKT,          1,  settings.aeb_ev);
	send_to_intercom(IC_SET_CF_SAFETY_SHIFT, 1,  settings.safety_shift);
	send_to_intercom(IC_SET_CF_EMIT_FLASH,   1, !settings.emit_flash);
	send_to_intercom(IC_SET_COLOR_TEMP,      2,  settings.color_temp);

	if(settings.remote_delay){
		RemReleaseSelfMax = 4500;
		RemReleaseInstMin = 5560;
	} else {
		RemReleaseSelfMax = 6160;
		RemReleaseInstMin = 7410;
	}
}