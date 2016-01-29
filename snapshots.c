#include <vxworks.h>
#include <ioLib.h>

#include "firmware.h"
#include "firmware/fio.h"

#include "main.h"
#include "macros.h"

#include "cmodes.h"
#include "display.h"
#include "languages.h"
#include "utils.h"
#include "intercom.h"

#include "snapshots.h"

int snapshot_read(char names[][FILENAME_LENGTH], snapshot_t *snapshot) {
	int result  = FALSE;
	int file    = -1;
	int version =  0;

	snapshot_t buffer;

	if ((file = FIO_OpenFile(names[0], O_RDONLY)) == -1)
		if ((file = FIO_OpenFile(names[1], O_RDONLY)) == -1)
			goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SETTINGS_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	*snapshot = buffer;

	result = TRUE;

#if SETTINGS_VERSION == 0x4A
	int nt;
	// Temporal fix for those affected by issue #333
	// Remove after increasing the version of the settings file
	if (snapshot->menu_order.named_temps[0] == 0 && snapshot->menu_order.named_temps[1] == 0)
		for (nt = 0; nt < LENGTH(snapshot->menu_order.named_temps); nt++)
			snapshot->menu_order.named_temps[nt] = nt;
#endif

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

int snapshot_write(char names[][FILENAME_LENGTH]) {
	const int version = SETTINGS_VERSION;

	int  result = FALSE;
	int  file   = -1;

	snapshot_t buffer = {
		DPData     : DPData,
		settings   : settings,
		menu_order : menu_order,
	};

	if ((file = FIO_OpenFile(names[0], O_CREAT | O_WRONLY)) == -1)
		if (status.folder_exists || (file = FIO_OpenFile(names[1], O_CREAT | O_WRONLY)) == -1)
			goto end;

	if (FIO_WriteFile(file, (void*)&version, sizeof(version)) != sizeof(version))
		goto end;

	if (FIO_WriteFile(file, (void*)&buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	FIO_CloseFile(file);

	result = TRUE;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

int snapshot_delete(char names[][FILENAME_LENGTH]) {
	if (status.folder_exists) {
		FIO_RemoveFile(names[0]);
		return (FIO_RemoveFile(names[1]) != -1);
	} else {
		return (FIO_RemoveFile(names[0]) != -1);
	}
}

void snapshot_recall(snapshot_t *snapshot) {
	send_to_intercom(IC_SET_AE, snapshot->DPData.ae);
}

void snapshot_apply(snapshot_t *snapshot) {
	if (cmodes_config.recall_camera) {
		send_to_intercom(IC_SET_METERING,   snapshot->DPData.metering);
		send_to_intercom(IC_SET_EFCOMP,     snapshot->DPData.efcomp);
		send_to_intercom(IC_SET_DRIVE,      snapshot->DPData.drive);
		send_to_intercom(IC_SET_WB,         snapshot->DPData.wb);
		send_to_intercom(IC_SET_AF_POINT,   snapshot->DPData.af_point);
		send_to_intercom(IC_SET_TV_VAL,     snapshot->DPData.tv_val);
		send_to_intercom(IC_SET_AV_VAL,     snapshot->DPData.av_val);
		send_to_intercom(IC_SET_AV_COMP,    snapshot->DPData.av_comp);
		send_to_intercom(IC_SET_ISO,        snapshot->DPData.iso);
		send_to_intercom(IC_SET_RED_EYE,    snapshot->DPData.red_eye);
		send_to_intercom(IC_SET_AE_BKT,     snapshot->DPData.ae_bkt);
		send_to_intercom(IC_SET_WB_BKT,     snapshot->DPData.wb_bkt);
		send_to_intercom(IC_SET_BEEP,       snapshot->DPData.beep);
		send_to_intercom(IC_SET_COLOR_TEMP, snapshot->DPData.color_temp);
		send_to_intercom(IC_SET_WBCOMP_GM,  snapshot->DPData.wbcomp_gm);
		send_to_intercom(IC_SET_WBCOMP_AB,  snapshot->DPData.wbcomp_ab);

		/**
		 *  We cannot switch AF off when loading a custom mode,
		 *  because the switch on the lens could be set to on.
		 */
		if (snapshot->DPData.af)
			send_to_intercom(IC_SET_AF, snapshot->DPData.af);
	}

	if (cmodes_config.recall_settings) {
		send_to_intercom(IC_SET_AUTO_POWER_OFF, snapshot->DPData.auto_power_off);
		send_to_intercom(IC_SET_VIEW_TYPE,      snapshot->DPData.view_type);
		send_to_intercom(IC_SET_REVIEW_TIME,    snapshot->DPData.review_time);
		send_to_intercom(IC_SET_AUTO_ROTATE,    snapshot->DPData.auto_rotate);
		send_to_intercom(IC_SET_LCD_BRIGHTNESS, snapshot->DPData.lcd_brightness);
		send_to_intercom(IC_SET_DATE_TIME,      snapshot->DPData.date_time);
		send_to_intercom(IC_SET_FILE_NUMBERING, snapshot->DPData.file_numbering);
		send_to_intercom(IC_SET_LANGUAGE,       snapshot->DPData.language);
		send_to_intercom(IC_SET_VIDEO_SYSTEM,   snapshot->DPData.video_system);
		send_to_intercom(IC_SET_HISTOGRAM,      snapshot->DPData.histogram);
		send_to_intercom(IC_SET_COLOR_SPACE,    snapshot->DPData.color_space);
	}

	if (cmodes_config.recall_image) {
		send_to_intercom(IC_SET_IMG_FORMAT,  snapshot->DPData.img_format);
		send_to_intercom(IC_SET_IMG_SIZE,    snapshot->DPData.img_size);
		send_to_intercom(IC_SET_IMG_QUALITY, snapshot->DPData.img_quality);
	}

	if (cmodes_config.recall_cfn) {
		send_to_intercom(IC_SET_CF_SET_BUTTON_FUNC,      snapshot->DPData.cf_set_button_func);
		send_to_intercom(IC_SET_CF_NR_FOR_LONG_EXPOSURE, snapshot->DPData.cf_nr_for_long_exposure);
		send_to_intercom(IC_SET_CF_EFAV_FIX_X,           snapshot->DPData.cf_efav_fix_x);
		send_to_intercom(IC_SET_CF_AFAEL_ACTIVE_BUTTON,  snapshot->DPData.cf_afael_active_button);
		send_to_intercom(IC_SET_CF_EMIT_AUX,             snapshot->DPData.cf_emit_aux);
		send_to_intercom(IC_SET_CF_EXPLEVEL_INC_THIRD,   snapshot->DPData.cf_explevel_inc_third);
		send_to_intercom(IC_SET_CF_EMIT_FLASH,           snapshot->DPData.cf_emit_flash);
		send_to_intercom(IC_SET_CF_EXTEND_ISO,           snapshot->DPData.cf_extend_iso);
		send_to_intercom(IC_SET_CF_AEB_SEQUENCE,         snapshot->DPData.cf_aeb_sequence);
		send_to_intercom(IC_SET_CF_SI_INDICATE,          snapshot->DPData.cf_si_indicate);
		send_to_intercom(IC_SET_CF_MENU_POS,             snapshot->DPData.cf_menu_pos);
		send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK,       snapshot->DPData.cf_mirror_up_lock);
		send_to_intercom(IC_SET_CF_FPSEL_METHOD,         snapshot->DPData.cf_fpsel_method);
		send_to_intercom(IC_SET_CF_FLASH_METERING,       snapshot->DPData.cf_flash_metering);
		send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR,      snapshot->DPData.cf_flash_sync_rear);
		send_to_intercom(IC_SET_CF_SAFETY_SHIFT,         snapshot->DPData.cf_safety_shift);
		send_to_intercom(IC_SET_CF_LENS_BUTTON,          snapshot->DPData.cf_lens_button);
		send_to_intercom(IC_SET_CF_ORIGINAL_EVAL,        snapshot->DPData.cf_original_eval);
		send_to_intercom(IC_SET_CF_QR_MAGNIFY,           snapshot->DPData.cf_qr_magnify);
		send_to_intercom(IC_SET_CF_TFT_ON_POWER_ON,      snapshot->DPData.cf_tft_on_power_on);
	}

	if (cmodes_config.recall_ordering) {
		menu_order = snapshot->menu_order;
	}

	if (cmodes_config.recall_400plus) {
		settings = snapshot->settings;
		settings_apply();
	}
}
