#include "main.h"
#include "settings.h"
#include "display.h"
#include "firmware.h"

#include "presets.h"

type_CAMERA_MODE preset;

void get_filename(char *filename, int id);

int preset_read(int id) {
	int  result  = FALSE;
	int  version =  0;
	int  file    = -1;

	char filename[16];

	get_filename(filename, id);
	file = FIO_OpenFile(SETTINGS_FILE, O_RDONLY, 644);

	if (file != -1) {
		FIO_ReadFile(file, &version, sizeof(version));

		if (version == SETTINGS_VERSION) {
			FIO_ReadFile(file, &settings, sizeof(settings));
			FIO_ReadFile(file, &preset,   sizeof(preset));
			result = TRUE;
		}

		FIO_CloseFile(file);
	}

	return result;
}

void preset_write(int id) {
	const int version = SETTINGS_VERSION;

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

extern void preset_apply() {
	settings_apply();

//	SendToIntercom(EVENT_SET_AE,         1, preset.ae);
//	SendToIntercom(EVENT_SET_METERING,   1, preset.metering);
//	SendToIntercom(EVENT_SET_EFCOMP,     1, preset.efcomp);
//	SendToIntercom(EVENT_SET_METERING,   1, preset.metering);
//	SendToIntercom(EVENT_SET_WB,         1, preset.wb);
//	SendToIntercom(EVENT_SET_AF_POINT,   2, preset.af_point);
//	SendToIntercom(EVENT_SET_TV_VAL,     1, preset.tv_val);
//	SendToIntercom(EVENT_SET_AV_VAL,     1, preset.av_val);
//	SendToIntercom(EVENT_SET_AV_COMP,    1, preset.av_comp);
//	SendToIntercom(EVENT_SET_ISO,        2, preset.iso);
//	SendToIntercom(EVENT_SET_RED_EYE,    1, preset.red_eye);
//	SendToIntercom(EVENT_SET_AE_BKT,     1, preset.ae_bkt);
//	SendToIntercom(EVENT_SET_WB_BKT,     1, preset.wb_bkt);
//	SendToIntercom(EVENT_SET_BEEP,       1, preset.beep);
//	SendToIntercom(EVENT_SET_COLOR_TEMP, 2, preset.color_temp);
/*
	SendToIntercom(EVENT_SET_IMG_FORMAT,  1, preset.img_format);
	SendToIntercom(EVENT_SET_IMG_SIZE,    1, preset.img_size);
	SendToIntercom(EVENT_SET_IMG_QUALITY, 1, preset.img_quality);

	SendToIntercom(EVENT_SET_CF_SET_BUTTON_FUNC,      1, preset.cf_set_button_func);
	SendToIntercom(EVENT_SET_CF_NR_FOR_LONG_EXPOSURE, 1, preset.cf_nr_for_long_exposure);
	SendToIntercom(EVENT_SET_CF_EFAV_FIX_X,           1, preset.cf_efav_fix_x);
	SendToIntercom(EVENT_SET_CF_AFAEL_ACTIVE_BUTTON,  1, preset.cf_afael_active_button);
	SendToIntercom(EVENT_SET_CF_EMIT_AUX,             1, preset.cf_emit_aux);
	SendToIntercom(EVENT_SET_CF_EXPLEVEL_INC_THIRD,   1, preset.cf_explevel_inc_third);
	SendToIntercom(EVENT_SET_CF_EMIT_FLASH,           1, preset.cf_emit_flash);
	SendToIntercom(EVENT_SET_CF_EXTEND_ISO,           1, preset.cf_extend_iso);
	SendToIntercom(EVENT_SET_CF_AEB_SEQUENCE,         1, preset.cf_aeb_sequence);
	SendToIntercom(EVENT_SET_CF_SI_INDICATE,          1, preset.cf_si_indicate);
	SendToIntercom(EVENT_SET_CF_MENU_POS,             1, preset.cf_menu_pos);
	SendToIntercom(EVENT_SET_CF_MIRROR_UP_LOCK,       1, preset.cf_mirror_up_lock);
	SendToIntercom(EVENT_SET_CF_FPSEL_METHOD,         1, preset.cf_fpsel_method);
	SendToIntercom(EVENT_SET_CF_FLASH_METERING,       1, preset.cf_flash_metering);
	SendToIntercom(EVENT_SET_CF_FLASH_SYNC_REAR,      1, preset.cf_flash_sync_rear);
	SendToIntercom(EVENT_SET_CF_SAFETY_SHIFT,         1, preset.cf_safety_shift);
	SendToIntercom(EVENT_SET_CF_LENS_BUTTON,          1, preset.cf_lens_button);
	SendToIntercom(EVENT_SET_CF_ORIGINAL_EVAL,        1, preset.cf_original_eval);
	SendToIntercom(EVENT_SET_CF_QR_MAGNIFY,           1, preset.cf_qr_magnify);
*/
	display_refresh();
}

void get_filename(char *filename, int id) {
	sprintf(filename, PRESET_FILE, id);
}
