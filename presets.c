#include "main.h"
#include "utils.h"
#include "settings.h"
#include "display.h"
#include "languages.h"
#include "firmware.h"

#include "presets.h"

type_PRESET preset;

type_PRESETS_CONFIG presets_config = {
	use_adep        : TRUE,
	recall_camera   : TRUE,
	recall_400plus  : TRUE,
	recall_settings : FALSE,
	recall_image    : TRUE,
	recall_cfn      : TRUE,
	order           : {0, 1, 2, 3, 4, 5, 6, 7, 8}
};

void sub_preset_recall(int full);
void get_filename(char *filename, int id);

void presets_read() {
	int id;
	int file    = -1;
	int version =  0;

	char name[25];

	type_PRESETS_CONFIG buffer;

	for (id = 0; id < 9; id ++) {
		sprintf(name, "%s %i", LP_WORD(L_PRESET_NAME), id + 1);
		sprintf(presets_config.names[id], "%-25s", name);
	}

	if ((file = FIO_OpenFile(PRESETS_CONFIG, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != PRESETS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	presets_config = buffer;

end:
	if (file != -1)
		FIO_CloseFile(file);
}

void presets_write() {
	const int version = PRESETS_VERSION;

	int file = FIO_OpenFile(PRESETS_CONFIG, O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, (void*)&version,        sizeof(version));
		FIO_WriteFile(file, (void*)&presets_config, sizeof(presets_config));
		FIO_CloseFile(file);
	}
}

int preset_read(int id) {
	int result  = FALSE;
	int file    = -1;
	int version =  0;

	char filename[16];

	type_PRESET buffer;

	get_preset_filename(filename, id);

	if ((file = FIO_OpenFile(filename, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	preset = buffer;
	result = TRUE;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

int preset_write(int id) {
	const int version = SETTINGS_VERSION;

	int  result = FALSE;
	int  file   = -1;

	char filename[16];

	type_PRESET buffer = {
		settings    : settings,
		camera_mode : *cameraMode
	};

	get_preset_filename(filename, id);

	if ((file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644)) == -1)
		goto end;

	if (FIO_WriteFile(file, (void*)&version, sizeof(version)) != sizeof(version))
		goto end;

	if (FIO_WriteFile(file, (void*)&buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	if (FIO_CloseFile(file) == -1)
		goto end;

	result = TRUE;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

void preset_apply() {
	if (presets_config.recall_camera) {
		status.ignore_ae_change = TRUE;

		send_to_intercom(IC_SET_AE, 1, preset.camera_mode.ae);
	}

	display_refresh();
}

void preset_apply_full() {
	if (presets_config.recall_400plus) {
		settings = preset.settings;
		settings_apply();
	}

	if (presets_config.recall_camera) {
		status.ignore_ae_change = TRUE;

		send_to_intercom(IC_SET_AE,         1, preset.camera_mode.ae);
		send_to_intercom(IC_SET_METERING,   1, preset.camera_mode.metering);
		send_to_intercom(IC_SET_EFCOMP,     1, preset.camera_mode.efcomp);
		send_to_intercom(IC_SET_DRIVE,      1, preset.camera_mode.drive);
		send_to_intercom(IC_SET_WB,         1, preset.camera_mode.wb);
		send_to_intercom(IC_SET_AF,         1, preset.camera_mode.af);
		send_to_intercom(IC_SET_AF_POINT,   2, preset.camera_mode.af_point);
		send_to_intercom(IC_SET_TV_VAL,     1, preset.camera_mode.tv_val);
		send_to_intercom(IC_SET_AV_VAL,     1, preset.camera_mode.av_val);
		send_to_intercom(IC_SET_AV_COMP,    1, preset.camera_mode.av_comp);
		send_to_intercom(IC_SET_ISO,        2, preset.camera_mode.iso);
		send_to_intercom(IC_SET_RED_EYE,    1, preset.camera_mode.red_eye);
		send_to_intercom(IC_SET_AE_BKT,     1, preset.camera_mode.ae_bkt);
		send_to_intercom(IC_SET_WB_BKT,     1, preset.camera_mode.wb_bkt);
		send_to_intercom(IC_SET_BEEP,       1, preset.camera_mode.beep);
		send_to_intercom(IC_SET_COLOR_TEMP, 2, preset.camera_mode.color_temp);
		send_to_intercom(IC_SET_WBCOMP_GM,  1, preset.camera_mode.wbcomp_gm);
		send_to_intercom(IC_SET_WBCOMP_AB,  1, preset.camera_mode.wbcomp_ab);
	}

	if (presets_config.recall_settings) {
		send_to_intercom(IC_SET_AUTO_POWER_OFF, 2, preset.camera_mode.auto_power_off);
		send_to_intercom(IC_SET_VIEW_TYPE,      1, preset.camera_mode.view_type);
		send_to_intercom(IC_SET_REVIEW_TIME,    1, preset.camera_mode.review_time);
		send_to_intercom(IC_SET_AUTO_ROTATE,    1, preset.camera_mode.auto_rotate);
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1, preset.camera_mode.lcd_brightness);
		send_to_intercom(IC_SET_DATE_TIME,      1, preset.camera_mode.date_time);
		send_to_intercom(IC_SET_FILE_NUMBERING, 1, preset.camera_mode.file_numbering);
		send_to_intercom(IC_SET_LANGUAGE,       1, preset.camera_mode.language);
		send_to_intercom(IC_SET_VIDEO_SYSTEM,   1, preset.camera_mode.video_system);
		send_to_intercom(IC_SET_HISTOGRAM,      1, preset.camera_mode.histogram);
		send_to_intercom(IC_SET_COLOR_SPACE,    1, preset.camera_mode.color_space);
	}

	if (presets_config.recall_image) {
		send_to_intercom(IC_SET_IMG_FORMAT,  1, preset.camera_mode.img_format);
		send_to_intercom(IC_SET_IMG_SIZE,    1, preset.camera_mode.img_size);
		send_to_intercom(IC_SET_IMG_QUALITY, 1, preset.camera_mode.img_quality);
	}

	if (presets_config.recall_cfn) {
		send_to_intercom(IC_SET_CF_SET_BUTTON_FUNC,      1, preset.camera_mode.cf_set_button_func);
		send_to_intercom(IC_SET_CF_NR_FOR_LONG_EXPOSURE, 1, preset.camera_mode.cf_nr_for_long_exposure);
		send_to_intercom(IC_SET_CF_EFAV_FIX_X,           1, preset.camera_mode.cf_efav_fix_x);
		send_to_intercom(IC_SET_CF_AFAEL_ACTIVE_BUTTON,  1, preset.camera_mode.cf_afael_active_button);
		send_to_intercom(IC_SET_CF_EMIT_AUX,             1, preset.camera_mode.cf_emit_aux);
		send_to_intercom(IC_SET_CF_EXPLEVEL_INC_THIRD,   1, preset.camera_mode.cf_explevel_inc_third);
		send_to_intercom(IC_SET_CF_EMIT_FLASH,           1, preset.camera_mode.cf_emit_flash);
		send_to_intercom(IC_SET_CF_EXTEND_ISO,           1, preset.camera_mode.cf_extend_iso);
		send_to_intercom(IC_SET_CF_AEB_SEQUENCE,         1, preset.camera_mode.cf_aeb_sequence);
		send_to_intercom(IC_SET_CF_SI_INDICATE,          1, preset.camera_mode.cf_si_indicate);
		send_to_intercom(IC_SET_CF_MENU_POS,             1, preset.camera_mode.cf_menu_pos);
		send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK,       1, preset.camera_mode.cf_mirror_up_lock);
		send_to_intercom(IC_SET_CF_FPSEL_METHOD,         1, preset.camera_mode.cf_fpsel_method);
		send_to_intercom(IC_SET_CF_FLASH_METERING,       1, preset.camera_mode.cf_flash_metering);
		send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR,      1, preset.camera_mode.cf_flash_sync_rear);
		send_to_intercom(IC_SET_CF_SAFETY_SHIFT,         1, preset.camera_mode.cf_safety_shift);
		send_to_intercom(IC_SET_CF_LENS_BUTTON,          1, preset.camera_mode.cf_lens_button);
		send_to_intercom(IC_SET_CF_ORIGINAL_EVAL,        1, preset.camera_mode.cf_original_eval);
		send_to_intercom(IC_SET_CF_QR_MAGNIFY,           1, preset.camera_mode.cf_qr_magnify);
		send_to_intercom(IC_SET_CF_TFT_ON_POWER_ON,      1, preset.camera_mode.cf_tft_on_power_on);
	}

	display_refresh();
}

void preset_recall() {
	sub_preset_recall(FALSE);
}

void preset_recall_full() {
	sub_preset_recall(TRUE);
}

void sub_preset_recall(int full) {
	if (preset_read(0)) {
		if (full) {
			preset_apply_full();
		} else {
			preset_apply();
		}
	}
}

void get_preset_filename(char *filename, int id) {
	sprintf(filename, PRESETS_FILE, id);
}
