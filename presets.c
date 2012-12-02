/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "utils.h"

#include "presets.h"

type_PRESETS_CONFIG presets_default = {
	recall_camera   : true,
	recall_400plus  : true,
	recall_settings : false,
	recall_image    : true,
	recall_cfn      : true,
	order           : {0, 1, 2, 3, 4, 5, 6, 7, 8}
};

type_PRESETS_CONFIG presets_config;

int snapshot_read  (char *name, snapshot_t *snapshot);
int snapshot_write (char *name);
int snapshot_delete(char *name);

void sub_preset_recall(int full);

void presets_read() {
	int id;
	int file    = -1;
	int version =  0;

	type_PRESETS_CONFIG buffer;

	for (id = 0; id < 9; id ++)
		sprintf(presets_default.names[id], "%s %i", LP_WORD(L_S_PRESET_NAME), 1 + id);

	presets_config = presets_default;

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

void presets_restore() {
	presets_config = presets_default;

	presets_write();
}

void presets_delete() {
	int  id;

	for(id = 0; id < 9; id++)
		preset_delete(id);
}

int preset_read(int id, snapshot_t *preset) {
	char filename[FILENAME_LENGTH];

	get_preset_filename(filename, id);

	return snapshot_read(filename, preset);
}

int preset_write(int id) {
	char filename[FILENAME_LENGTH];

	get_preset_filename(filename, id);

	return snapshot_write(filename);
}

int preset_delete(int id) {
	char filename[FILENAME_LENGTH];

	get_preset_filename(filename, id);

	return snapshot_delete(filename);
}

int snapshot_read(char *name, snapshot_t *snapshot) {
	int result  = false;
	int file    = -1;
	int version =  0;

	snapshot_t buffer;

	if ((file = FIO_OpenFile(name, O_RDONLY, 644)) == -1)
		goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	*snapshot = buffer;

	result = true;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

int snapshot_write(char *name) {
	const int version = SETTINGS_VERSION;

	int  result = false;
	int  file   = -1;

	snapshot_t buffer = {
		settings : settings,
		DPData   : DPData
	};

	if ((file = FIO_OpenFile(name, O_CREAT | O_WRONLY , 644)) == -1)
		goto end;

	if (FIO_WriteFile(file, (void*)&version, sizeof(version)) != sizeof(version))
		goto end;

	if (FIO_WriteFile(file, (void*)&buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	if (FIO_CloseFile(file) == -1)
		goto end;

	result = true;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

int snapshot_delete(char *name) {
	return (FIO_RemoveFile(name) != -1);
}

void snapshot_apply(snapshot_t *snapshot) {
	if (presets_config.recall_camera)
		send_to_intercom(IC_SET_AE, 1, snapshot->DPData.ae);
}

void snapshot_apply_full(snapshot_t *snapshot) {
	snapshot_apply(snapshot);

	if (presets_config.recall_camera) {
		send_to_intercom(IC_SET_METERING,   1, snapshot->DPData.metering);
		send_to_intercom(IC_SET_EFCOMP,     1, snapshot->DPData.efcomp);
		send_to_intercom(IC_SET_DRIVE,      1, snapshot->DPData.drive);
		send_to_intercom(IC_SET_WB,         1, snapshot->DPData.wb);
		send_to_intercom(IC_SET_AF_POINT,   2, snapshot->DPData.af_point);
		send_to_intercom(IC_SET_TV_VAL,     1, snapshot->DPData.tv_val);
		send_to_intercom(IC_SET_AV_VAL,     1, snapshot->DPData.av_val);
		send_to_intercom(IC_SET_AV_COMP,    1, snapshot->DPData.av_comp);
		send_to_intercom(IC_SET_ISO,        2, snapshot->DPData.iso);
		send_to_intercom(IC_SET_RED_EYE,    1, snapshot->DPData.red_eye);
		send_to_intercom(IC_SET_AE_BKT,     1, snapshot->DPData.ae_bkt);
		send_to_intercom(IC_SET_WB_BKT,     1, snapshot->DPData.wb_bkt);
		send_to_intercom(IC_SET_BEEP,       1, snapshot->DPData.beep);
		send_to_intercom(IC_SET_COLOR_TEMP, 2, snapshot->DPData.color_temp);
		send_to_intercom(IC_SET_WBCOMP_GM,  1, snapshot->DPData.wbcomp_gm);
		send_to_intercom(IC_SET_WBCOMP_AB,  1, snapshot->DPData.wbcomp_ab);

		/**
		 *  We cannot switch AF off when loading a preset,
		 *  because the switch on the lens could be set to on.
		 */
		if (snapshot->DPData.af)
			send_to_intercom(IC_SET_AF, 1, snapshot->DPData.af);
	}

	if (presets_config.recall_settings) {
		send_to_intercom(IC_SET_AUTO_POWER_OFF, 2, snapshot->DPData.auto_power_off);
		send_to_intercom(IC_SET_VIEW_TYPE,      1, snapshot->DPData.view_type);
		send_to_intercom(IC_SET_REVIEW_TIME,    1, snapshot->DPData.review_time);
		send_to_intercom(IC_SET_AUTO_ROTATE,    1, snapshot->DPData.auto_rotate);
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1, snapshot->DPData.lcd_brightness);
		send_to_intercom(IC_SET_DATE_TIME,      1, snapshot->DPData.date_time);
		send_to_intercom(IC_SET_FILE_NUMBERING, 1, snapshot->DPData.file_numbering);
		send_to_intercom(IC_SET_LANGUAGE,       1, snapshot->DPData.language);
		send_to_intercom(IC_SET_VIDEO_SYSTEM,   1, snapshot->DPData.video_system);
		send_to_intercom(IC_SET_HISTOGRAM,      1, snapshot->DPData.histogram);
		send_to_intercom(IC_SET_COLOR_SPACE,    1, snapshot->DPData.color_space);
	}

	if (presets_config.recall_image) {
		send_to_intercom(IC_SET_IMG_FORMAT,  1, snapshot->DPData.img_format);
		send_to_intercom(IC_SET_IMG_SIZE,    1, snapshot->DPData.img_size);
		send_to_intercom(IC_SET_IMG_QUALITY, 1, snapshot->DPData.img_quality);
	}

	if (presets_config.recall_cfn) {
		send_to_intercom(IC_SET_CF_SET_BUTTON_FUNC,      1, snapshot->DPData.cf_set_button_func);
		send_to_intercom(IC_SET_CF_NR_FOR_LONG_EXPOSURE, 1, snapshot->DPData.cf_nr_for_long_exposure);
		send_to_intercom(IC_SET_CF_EFAV_FIX_X,           1, snapshot->DPData.cf_efav_fix_x);
		send_to_intercom(IC_SET_CF_AFAEL_ACTIVE_BUTTON,  1, snapshot->DPData.cf_afael_active_button);
		send_to_intercom(IC_SET_CF_EMIT_AUX,             1, snapshot->DPData.cf_emit_aux);
		send_to_intercom(IC_SET_CF_EXPLEVEL_INC_THIRD,   1, snapshot->DPData.cf_explevel_inc_third);
		send_to_intercom(IC_SET_CF_EMIT_FLASH,           1, snapshot->DPData.cf_emit_flash);
		send_to_intercom(IC_SET_CF_EXTEND_ISO,           1, snapshot->DPData.cf_extend_iso);
		send_to_intercom(IC_SET_CF_AEB_SEQUENCE,         1, snapshot->DPData.cf_aeb_sequence);
		send_to_intercom(IC_SET_CF_SI_INDICATE,          1, snapshot->DPData.cf_si_indicate);
		send_to_intercom(IC_SET_CF_MENU_POS,             1, snapshot->DPData.cf_menu_pos);
		send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK,       1, snapshot->DPData.cf_mirror_up_lock);
		send_to_intercom(IC_SET_CF_FPSEL_METHOD,         1, snapshot->DPData.cf_fpsel_method);
		send_to_intercom(IC_SET_CF_FLASH_METERING,       1, snapshot->DPData.cf_flash_metering);
		send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR,      1, snapshot->DPData.cf_flash_sync_rear);
		send_to_intercom(IC_SET_CF_SAFETY_SHIFT,         1, snapshot->DPData.cf_safety_shift);
		send_to_intercom(IC_SET_CF_LENS_BUTTON,          1, snapshot->DPData.cf_lens_button);
		send_to_intercom(IC_SET_CF_ORIGINAL_EVAL,        1, snapshot->DPData.cf_original_eval);
		send_to_intercom(IC_SET_CF_QR_MAGNIFY,           1, snapshot->DPData.cf_qr_magnify);
		send_to_intercom(IC_SET_CF_TFT_ON_POWER_ON,      1, snapshot->DPData.cf_tft_on_power_on);
	}

	if (presets_config.recall_400plus) {
		settings = snapshot->settings;
		settings_apply();
	}
}

void preset_recall() {
	sub_preset_recall(false);
}

void preset_recall_full() {
	sub_preset_recall(true);
}

void sub_preset_recall(int full) {
	snapshot_t preset;

	// Preventively, we assume no preset is active now
	status.preset_active = false;

	// Only if configured to hijack ADEP and entering ADEP
	if (status.main_dial_ae == AE_MODE_ADEP) {
		// Only if a preset was loaded, and we can read it back
		if (presets_config.last_preset && preset_read(presets_config.last_preset, &preset)) {
			// Apply full preset or just revert AE mode
			if (full)
				snapshot_apply_full(&preset);
			else {
				snapshot_apply(&preset);
			}

			// Well, looks like we did recall a preset after all
			status.preset_active = true;
		}
	}

	// Refresh display to show new preset (or lack of thereof)
	display_refresh();
}

void get_preset_filename(char *filename, int id) {
	sprintf(filename, PRESETS_FILE, id);
}
