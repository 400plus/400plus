#include "main.h"

#include "settings.h"

type_SETTINGS settings = {
	FALSE, // iso_in_viewfinder
	    0, // dp_action
	    3, // eaeb_frames
	FALSE, // eaeb_delay
	 0x08, // eaeb_ev
	 0x10, // eaeb_m_min
	 0x98, // eaeb_m_max
	    2, // interval_time
	FALSE, // ir_inst
	 0x00, // white_balance
	 5200, // color_temp
	    0, // av_comp
	    0, // flash_comp
	    0, // aeb_ev
	FALSE, // safety_shift;
	FALSE, // not_emit_flash;
	FALSE  // not_af_flash;
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
	SendToIntercom(0x0A, 1, settings.av_comp);
	SendToIntercom(0x03, 1, settings.flash_comp);
	SendToIntercom(0x0D, 1, settings.aeb_ev);
	SendToIntercom(0x39, 1, settings.safety_shift);
	SendToIntercom(0x30, 1, settings.not_emit_flash);
	SendToIntercom(0x2E, 1, settings.not_af_flash);
	SendToIntercom(0x05, 1, settings.white_balance);
	SendToIntercom(0x10, 1, settings.color_temp);

	if(settings.remote_delay){
		*(int*)0x229AC = 4500;
		*(int*)0x229B0 = 5560;
	} else {
		*(int*)0x229AC = 6160;
		*(int*)0x229B0 = 7410;
	}
}
