#include "main.h"
#include "settings.h"
#include "display.h"
#include "firmware.h"

#include "custom.h"

type_CAMERA_MODE customCameraMode;

void get_filename(char *filename, int id);

void custom_read(int id) {
	int  version = 0;
	int  file   = -1;
	char filename[16];

	get_filename(filename, id);
	FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644);

	if (file != -1) {
		FIO_ReadFile(file, &version, sizeof(version));

		if (version == CUSTOM_VERSION) {
			FIO_ReadFile(file, &settings,         sizeof(settings));
			FIO_ReadFile(file, &customCameraMode, sizeof(customCameraMode));
		}

		FIO_CloseFile(file);
	}
}

void custom_write(int id) {
	const int version = CUSTOM_VERSION;

	int  file;
	char filename[16];

	get_filename(filename, id);
	file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, (void*)&version, sizeof(version));
		FIO_WriteFile(file, &settings,   sizeof(settings));
		FIO_WriteFile(file, &cameraMode, sizeof(cameraMode));
		FIO_CloseFile(file);
	}
}

extern void custom_apply() {
	settings_apply();

	SendToIntercom(EVENT_SET_AE,         1, customCameraMode.ae);
	SendToIntercom(EVENT_SET_METERING,   1, customCameraMode.metering);
	SendToIntercom(EVENT_SET_EFCOMP,     1, customCameraMode.efcomp);
	SendToIntercom(EVENT_SET_WB,         1, customCameraMode.wb);
	SendToIntercom(EVENT_SET_AF_POINT,   2, customCameraMode.af_point);
	SendToIntercom(EVENT_SET_TV_VAL,     1, customCameraMode.tv_val);
	SendToIntercom(EVENT_SET_AV_VAL,     1, customCameraMode.av_val);
	SendToIntercom(EVENT_SET_AV_COMP,    1, customCameraMode.av_comp);
	SendToIntercom(EVENT_SET_ISO,        2, customCameraMode.iso);
	SendToIntercom(EVENT_SET_AE_BKT,     1, customCameraMode.ae_bkt);
	SendToIntercom(EVENT_SET_COLOR_TEMP, 2, customCameraMode.color_temp);

	SendToIntercom(EVENT_SET_CF_EMIT_AUX,        1, customCameraMode.cf_emit_aux);
	SendToIntercom(EVENT_SET_CF_EMIT_FLASH,      1, customCameraMode.cf_emit_flash);
	SendToIntercom(EVENT_SET_CF_MIRROR_UP_LOCK,  1, customCameraMode.cf_mirror_up_lock);
	SendToIntercom(EVENT_SET_CF_FLASH_SYNC_REAR, 1, customCameraMode.cf_flash_sync_rear);
	SendToIntercom(EVENT_SET_CF_SAFETY_SHIFT,    1, customCameraMode.cf_safety_shift);

	display_refresh();
}

void get_filename(char *filename, int id) {
	sprintf(filename, CUSTOM_FILE, id);
}
