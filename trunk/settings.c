#include "file.h"

#include "settings.h"

type_SETTINGS settings = {
	   0, // iso_in_viewfinder
	   1, // dp_opt
	   3, // eaeb_frames
	   0, // eaeb_delay
	0x08, // eaeb_ev
	0x10, // eaeb_m_min
	0x98, // eaeb_m_max
	   2, // interval_time
	   0  // ir_inst
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
	int version = SETTINGS_VERSION;
	int file = FIO_OpenFile(SETTINGS_FILE, O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, &version, sizeof(version));
		FIO_WriteFile(file, &settings, sizeof(settings));
		FIO_CloseFile(file);
	}
}
