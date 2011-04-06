#include "main.h"
#include "firmware.h"

#include "settings.h"

type_SETTINGS settings = {
	iso_in_viewfinder: FALSE,
	eaeb_frames      : 3,
	eaeb_delay       : FALSE,
	eaeb_ev          : 0x08,
	eaeb_m_min       : 0,
	eaeb_m_max       : 0,
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
	af_flash         : TRUE,
	remote_delay     : FALSE,
	timer_timeout    : 5,
	timer_action     : SHOT_ACTION_FIRST
};

void settings_read() {
	int version = 0;
	int file = FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644);

	if (file != -1) {
		FIO_ReadFile(file, &version, sizeof(version));

		if (version == SETTINGS_VERSION) {
			FIO_ReadFile(file, &settings, sizeof(settings));
		}

		FIO_CloseFile(file);
	}
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
	SendToIntercom(0x0A, 1,  settings.av_comp);
	SendToIntercom(0x03, 1,  settings.flash_comp);
	SendToIntercom(0x0D, 1,  settings.aeb_ev);
	SendToIntercom(0x39, 1,  settings.safety_shift);
	SendToIntercom(0x30, 1, !settings.emit_flash);
	SendToIntercom(0x2E, 1, !settings.af_flash);
	SendToIntercom(0x10, 2,  settings.color_temp);

	if(settings.remote_delay){
		*(int*)0x229AC = 4500;
		*(int*)0x229B0 = 5560;
	} else {
		*(int*)0x229AC = 6160;
		*(int*)0x229B0 = 7410;
	}
}
