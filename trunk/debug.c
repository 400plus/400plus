/**
 * $Revision$
 * $Date$
 * $Author$
 */


#include "mainctrl.h"

#ifdef ENABLE_DEBUG

const char * debug_mc_name(int event) {
	static char name[20];

	switch (event) {
	case GUI_GOT_TOP_OF_CONTROL: return "GUI_GOT_TOP_OF_CONTROL";
	case MC_INFOANDCTRL: return "MC_INFOANDCTRL";
	case MC_BUTTON: return "MC_BUTTON";
	case MC_ACTION: return "MC_ACTION";
	case MC_DISPLAY_MODE: return "MC_DISPLAY_MODE";
	case MC_START_MODE: return "MC_START_MODE";
	case MC_DriveNotifyCallBack: return "MC_DriveNotifyCallBack";
	case MC_ChangeAvailShot: return "MC_ChangeAvailShot";
	case MC_ShutDown: return "MC_ShutDown";
	case MC_ChangeNotifyCallback: return "MC_ChangeNotifyCallback";
	case MC_CardDoor_Emergency: return "MC_CardDoor_Emergency";
	case MC_REQ_UI_LOCK: return "MC_REQ_UI_LOCK";
	case MC_REQ_UI_UNLOCK: return "MC_REQ_UI_UNLOCK";
	default:
		sprintf(name, "0x%08X", event);
		return name;
	}
}

const char * debug_btn_name(int btn) {
	static char name[20];

	switch(btn) {
	case MC_BUTTON_MENU: return "MC_BUTTON_MENU";
	case MC_BUTTON_DISP: return "MC_BUTTON_DISP";
	case MC_BUTTON_JUMP: return "MC_BUTTON_JUMP";
	case MC_BUTTON_PLAY: return "MC_BUTTON_PLAY";
	case MC_BUTTON_TRASH: return "MC_BUTTON_TRASH";
	case MC_BUTTON_SET: return "MC_BUTTON_SET";
	case MC_DIALOG1: return "MC_DIALOG1";
	case MC_DIALOG2: return "MC_DIALOG2";
	case MC_BUTTON_DIAL: return "MC_BUTTON_DIAL";
	case MC_BUTTON_DIAL1: return "MC_BUTTON_DIAL1";
	case MC_BUTTON_DIAL_LEFT: return "MC_BUTTON_DIAL_LEFT";
	case MC_BUTTON_DIAL_RIGHT: return "MC_BUTTON_DIAL_RIGHT";
	case MC_BUTTON_CARD_DOOR_OPEN: return "MC_BUTTON_CARD_DOOR_OPEN";
	case MC_BUTTON_UNK1: return "MC_BUTTON_UNK1";
	case MC_BUTTON_POWER: return "MC_BUTTON_POWER";
	case MC_BUTTON_BATTERY_DOOR_OPEN: return "MC_BUTTON_BATTERY_DOOR_OPEN";
	case MC_BUTTON_UP: return "MC_BUTTON_UP";
	case MC_BUTTON_DOWN: return "MC_BUTTON_DOWN";
	case MC_BUTTON_RIGHT: return "MC_BUTTON_RIGHT";
	case MC_BUTTON_LEFT: return "MC_BUTTON_LEFT";
	case MC_BUTTON_HALF_SHUTTER: return "MC_BUTTON_HALF_SHUTTER";
	case MC_BUTTON_FULL_SHUTTER: return "MC_BUTTON_FULL_SHUTTER";
	case MC_BUTTON_DP: return "MC_BUTTON_DP";
	case MC_AFPDLGON: return "MC_AFPDLGON";
	case MC_BUTTON_DRIVE: return "MC_BUTTON_DRIVE";
	case MC_BUTTON_AV: return "MC_BUTTON_AV";
	case MC_BUTTON_UNK2: return "MC_BUTTON_UNK2";
	default:
		sprintf(name, "0x%08X", btn);
		return name;
	}
}

const char * debug_gui_name(int event) {
	static char name[20];

	switch (event) {
	case GUI_GOT_TOP_OF_CONTROL: return "GUI_GOT_TOP_OF_CONTROL";
	case GUI_LOST_TOP_OF_CONTROL: return "GUI_LOST_TOP_OF_CONTROL";
	case GUI_INITIALIZE_CONTROLLER: return "GUI_INITIALIZE_CONTROLLER";
	case GUI_TERMINATE_WINSYS: return "GUI_TERMINATE_WINSYS";
	case GUI_DELETE_DIALOG_REQUEST: return "GUI_DELETE_DIALOG_REQUEST";
	case GUI_BUTTON_RIGHT: return "GUI_BUTTON_RIGHT";
	case GUI_BUTTON_LEFT: return "GUI_BUTTON_LEFT";
	case GUI_BUTTON_UP: return "GUI_BUTTON_UP";
	case GUI_BUTTON_DOWN: return "GUI_BUTTON_DOWN";
	case GUI_BUTTON_MENU: return "GUI_BUTTON_MENU";
	case GUI_BUTTON_JUMP: return "GUI_BUTTON_JUMP";
	case GUI_BUTTON_SET: return "GUI_BUTTON_SET";
	case GUI_BUTTON_ZOOM_IN_PRESS: return "GUI_BUTTON_ZOOM_IN_PRESS";
	case GUI_BUTTON_ZOOM_IN_RELEASE: return "GUI_BUTTON_ZOOM_IN_RELEASE";
	case GUI_BUTTON_ZOOM_OUT_PRESS: return "GUI_BUTTON_ZOOM_OUT_PRESS";
	case GUI_BUTTON_ZOOM_OUT_RELEASE: return "GUI_BUTTON_ZOOM_OUT_RELEASE";
	case GUI_BUTTON_DISP: return "GUI_BUTTON_DISP";
	case GUI_BUTTON_DIAL_RIGHT: return "GUI_BUTTON_DIAL_RIGHT";
	case GUI_BUTTON_DIAL_LEFT: return "GUI_BUTTON_DIAL_LEFT";
	case GUI_BUTTON_PLAY: return "GUI_BUTTON_PLAY";
	case GUI_BUTTON_TRASH: return "GUI_BUTTON_TRASH";
	case GUI_BUTTON_DP: return "GUI_BUTTON_DP";
	case GUI_BUTTON_CF_CARD: return "GUI_BUTTON_CF_CARD";
	case GUI_START_MENU_MODE: return "GUI_START_MENU_MODE";
	case GUI_START_INFO_MODE: return "GUI_START_INFO_MODE";
	case GUI_START_PLAY_MODE: return "GUI_START_PLAY_MODE";
	case GUI_START_QR_MODE: return "GUI_START_QR_MODE";
	case GUI_START_NOCFWARNING_MODE: return "GUI_START_NOCFWARNING_MODE";
	case GUI_START_FULLNOWARNING_MODE: return "GUI_START_FULLNOWARNING_MODE";
	case GUI_START_FULLCF: return "GUI_START_FULLCF";
	case GUI_START_ERRCF_ERROR: return "GUI_START_ERRCF_ERROR";
	case GUI_START_ERRCF_FULLNO: return "GUI_START_ERRCF_FULLNO";
	case GUI_START_ERRCF_PROTECT: return "GUI_START_ERRCF_PROTECT";
	case GUI_START_ERRORCODE_MODE: return "GUI_START_ERRORCODE_MODE";
	case GUI_START_INCOMPIMAGE_MODE: return "GUI_START_INCOMPIMAGE_MODE";
	case GUI_START_RTCSET_MODE: return "GUI_START_RTCSET_MODE";
	case GUI_START_IDLE_MODE: return "GUI_START_IDLE_MODE";
	case GUI_POST_QR_IMAGE: return "GUI_POST_QR_IMAGE";
	case GUI_DISP_RTCSET_MODE: return "GUI_DISP_RTCSET_MODE";
	case GUI_DISP_NOCFWARNING_MODE: return "GUI_DISP_NOCFWARNING_MODE";
	case GUI_DISP_FULLNOWARNING_MODE: return "GUI_DISP_FULLNOWARNING_MODE";
	case GUI_DISP_FULLCF: return "GUI_DISP_FULLCF";
	case GUI_DISP_ERRCF_ERROR: return "GUI_DISP_ERRCF_ERROR";
	case GUI_DISP_ERRCF_FULLNO: return "GUI_DISP_ERRCF_FULLNO";
	case GUI_DISP_ERRCF_PROTECT: return "GUI_DISP_ERRCF_PROTECT";
	case GUI_DISP_ERRORCODE_MODE: return "GUI_DISP_ERRORCODE_MODE";
	case GUI_DISP_INCOMPIMAGE_MODE: return "GUI_DISP_INCOMPIMAGE_MODE";
	case GUI_FINISH_QR_MODE: return "GUI_FINISH_QR_MODE";
	case GUI_DISP_USBCONNECTTYPE_MODE: return "GUI_DISP_USBCONNECTTYPE_MODE";
	case GUI_DISP_DIRECTTRANSFER_MODE: return "GUI_DISP_DIRECTTRANSFER_MODE";
	case GUI_START_USBCONNECTTYPE_MODE: return "GUI_START_USBCONNECTTYPE_MODE";
	case GUI_START_DIRECTTRANSFER_MODE: return "GUI_START_DIRECTTRANSFER_MODE";
	case GUI_DISP_OLC_MODE: return "GUI_DISP_OLC_MODE";
	case GUI_DISP_BULBCOUNT_MODE: return "GUI_DISP_BULBCOUNT_MODE";
	case GUI_START_OLC_MODE: return "GUI_START_OLC_MODE";
	case GUI_START_BULBCOUNT_MODE: return "GUI_START_BULBCOUNT_MODE";
	case GUI_DISP_ISO_MODE: return "GUI_DISP_ISO_MODE";
	case GUI_DISP_AF_MODE: return "GUI_DISP_AF_MODE";
	case GUI_DISP_WB_MODE: return "GUI_DISP_WB_MODE";
	case GUI_DISP_MES_MODE: return "GUI_DISP_MES_MODE";
	case GUI_BUTTON_DRIVE: return "GUI_BUTTON_DRIVE";
	case GUI_DISP_FP_SEL: return "GUI_DISP_FP_SEL";
	case GUI_DISP_QUAL_MODE: return "GUI_DISP_QUAL_MODE";
	case GUI_DISP_PICTURESTYLE_MODE: return "GUI_DISP_PICTURESTYLE_MODE";
	case GUI_DISP_FECOMP_MODE: return "GUI_DISP_FECOMP_MODE";
	case GUI_DISP_ACTIVESWEEP: return "GUI_DISP_ACTIVESWEEP";
	case GUI_DISP_ACTIVESWEEP_OLC: return "GUI_DISP_ACTIVESWEEP_OLC";
	case GUI_DISP_BATTEMPTY: return "GUI_DISP_BATTEMPTY";
	case GUI_START_ISO_MODE: return "GUI_START_ISO_MODE";
	case GUI_START_AF_MODE: return "GUI_START_AF_MODE";
	case GUI_START_WB_MODE: return "GUI_START_WB_MODE";
	case GUI_START_MES_MODE: return "GUI_START_MES_MODE";
	case GUI_START_DRIVE_MODE: return "GUI_START_DRIVE_MODE";
	case GUI_START_FP_SEL: return "GUI_START_FP_SEL";
	case GUI_START_QUAL_MODE: return "GUI_START_QUAL_MODE";
	case GUI_START_PICTURESTYLE_MODE: return "GUI_START_PICTURESTYLE_MODE";
	case GUI_START_FECOMP_MODE: return "GUI_START_FECOMP_MODE";
	case GUI_START_ACTIVESWEEP: return "GUI_START_ACTIVESWEEP";
	case GUI_START_ACTIVESWEEP_OLC: return "GUI_START_ACTIVESWEEP_OLC";
	case GUI_START_BATTEMPTY: return "GUI_START_BATTEMPTY";
	case GUI_FINISH_ACTIVESWEEP: return "GUI_FINISH_ACTIVESWEEP";
	case GUI_START_COLORBAR_DIALOG: return "GUI_START_COLORBAR_DIALOG";
	case GUI_START_LCDADJUST_DIALOG: return "GUI_START_LCDADJUST_DIALOG";
	case GUI_DELETE_COLORBAR_DIALOG: return "GUI_DELETE_COLORBAR_DIALOG";
	case GUI_DELETE_LCDADJUST_DIALOG: return "GUI_DELETE_LCDADJUST_DIALOG";
	case GUI_UNKNOWN1: return "GUI_UNKNOWN1";
	case GUI_UNKNOWN2: return "GUI_UNKNOWN2";

	default:
		sprintf(name, "0x%08X", event);
		return name;
	}
}

#ifdef ENABLE_DEBUG_DPR_DATA
void dump_dpr_data() {
	printf("\n\nDUMPING DPR_DATA\n\n");
	printf("\t%24s : 0x%08X [%d]\n", "ae", DPData->ae, DPData->ae);
	printf("\t%24s : 0x%08X [%d]\n", "metering", DPData->metering, DPData->metering);
	printf("\t%24s : 0x%08X [%d]\n", "efcomp", DPData->efcomp, DPData->efcomp);
	printf("\t%24s : 0x%08X [%d]\n", "drive", DPData->drive, DPData->drive);
	printf("\t%24s : 0x%08X [%d]\n", "wb", DPData->wb, DPData->wb);
	printf("\t%24s : 0x%08X [%d]\n", "af", DPData->af, DPData->af);
	printf("\t%24s : 0x%08X [%d]\n", "af_point", DPData->af_point, DPData->af_point);
	printf("\t%24s : 0x%08X [%d]\n", "tv_val", DPData->tv_val, DPData->tv_val);
	printf("\t%24s : 0x%08X [%d]\n", "av_val", DPData->av_val, DPData->av_val);
	printf("\t%24s : 0x%08X [%d]\n", "av_comp", DPData->av_comp, DPData->av_comp);
	printf("\t%24s : 0x%08X [%d]\n", "iso", DPData->iso, DPData->iso);
	printf("\t%24s : 0x%08X [%d]\n", "red_eye", DPData->red_eye, DPData->red_eye);
	printf("\t%24s : 0x%08X [%d]\n", "ae_bkt", DPData->ae_bkt, DPData->ae_bkt);
	printf("\t%24s : 0x%08X [%d]\n", "wb_bkt", DPData->wb_bkt, DPData->wb_bkt);
	printf("\t%24s : 0x%08X [%d]\n", "beep", DPData->beep, DPData->beep);
	printf("\t%24s : 0x%08X [%d]\n", "color_temp", DPData->color_temp, DPData->color_temp);
	printf("\t%24s : 0x%08X [%d]\n", "auto_power_off", DPData->auto_power_off, DPData->auto_power_off);
	printf("\t%24s : 0x%08X [%d]\n", "view_type", DPData->view_type, DPData->view_type);
	printf("\t%24s : 0x%08X [%d]\n", "review_time", DPData->review_time, DPData->review_time);
	printf("\t%24s : 0x%08X [%d]\n", "auto_rotate", DPData->auto_rotate, DPData->auto_rotate);
	printf("\t%24s : 0x%08X [%d]\n", "lcd_brightness", DPData->lcd_brightness, DPData->lcd_brightness);
	printf("\t%24s : 0x%08X [%d]\n", "date_time", DPData->date_time, DPData->date_time);
	printf("\t%24s : 0x%08X [%d]\n", "file_numbering", DPData->file_numbering, DPData->file_numbering);
	printf("\t%24s : 0x%08X [%d]\n", "language", DPData->language, DPData->language);
	printf("\t%24s : 0x%08X [%d]\n", "video_system", DPData->video_system, DPData->video_system);
	printf("\t%24s : 0x%08X [%d]\n", "picture_style_mode", DPData->picture_style_mode, DPData->picture_style_mode);
	printf("\t%24s : 0x%08X [%d]\n", "histogram", DPData->histogram, DPData->histogram);
	printf("\t%24s : 0x%08X [%d]\n", "disp_afpoint", DPData->disp_afpoint, DPData->disp_afpoint);
	printf("\t%24s : 0x%08X [%d]\n", "color_space", DPData->color_space, DPData->color_space);
	printf("\t%24s : 0x%08X [%d]\n", "img_format", DPData->img_format, DPData->img_format);
	printf("\t%24s : 0x%08X [%d]\n", "img_size", DPData->img_size, DPData->img_size);
	printf("\t%24s : 0x%08X [%d]\n", "img_quality", DPData->img_quality, DPData->img_quality);
	printf("\t%24s : 0x%08X [%d]\n", "cfmenupos", DPData->cfmenupos, DPData->cfmenupos);
	printf("\t%24s : 0x%08X [%d]\n", "menupos", DPData->menupos, DPData->menupos);
	printf("\t%24s : 0x%08X [%d]\n", "wbcomp_gm", DPData->wbcomp_gm, DPData->wbcomp_gm);
	printf("\t%24s : 0x%08X [%d]\n", "wbcomp_ab", DPData->wbcomp_ab, DPData->wbcomp_ab);
	printf("\t%24s : 0x%08X [%d]\n", "forbid_rel", DPData->forbid_rel, DPData->forbid_rel);
	printf("\t%24s : 0x%08X [%d]\n", "cf_set_button_func", DPData->cf_set_button_func, DPData->cf_set_button_func);
	printf("\t%24s : 0x%08X [%d]\n", "cf_nr_for_long_exposure", DPData->cf_nr_for_long_exposure, DPData->cf_nr_for_long_exposure);
	printf("\t%24s : 0x%08X [%d]\n", "cf_efav_fix_x", DPData->cf_efav_fix_x, DPData->cf_efav_fix_x);
	printf("\t%24s : 0x%08X [%d]\n", "cf_afael_active_button", DPData->cf_afael_active_button, DPData->cf_afael_active_button);
	printf("\t%24s : 0x%08X [%d]\n", "cf_emit_aux", DPData->cf_emit_aux, DPData->cf_emit_aux);
	printf("\t%24s : 0x%08X [%d]\n", "cf_explevel_inc_third", DPData->cf_explevel_inc_third, DPData->cf_explevel_inc_third);
	printf("\t%24s : 0x%08X [%d]\n", "cf_emit_flash", DPData->cf_emit_flash, DPData->cf_emit_flash);
	printf("\t%24s : 0x%08X [%d]\n", "cf_extend_iso", DPData->cf_extend_iso, DPData->cf_extend_iso);
	printf("\t%24s : 0x%08X [%d]\n", "cf_aeb_sequence", DPData->cf_aeb_sequence, DPData->cf_aeb_sequence);
	printf("\t%24s : 0x%08X [%d]\n", "cf_si_indicate", DPData->cf_si_indicate, DPData->cf_si_indicate);
	printf("\t%24s : 0x%08X [%d]\n", "cf_menu_pos", DPData->cf_menu_pos, DPData->cf_menu_pos);
	printf("\t%24s : 0x%08X [%d]\n", "cf_mirror_up_lock", DPData->cf_mirror_up_lock, DPData->cf_mirror_up_lock);
	printf("\t%24s : 0x%08X [%d]\n", "cf_fpsel_method", DPData->cf_fpsel_method, DPData->cf_fpsel_method);
	printf("\t%24s : 0x%08X [%d]\n", "cf_flash_metering", DPData->cf_flash_metering, DPData->cf_flash_metering);
	printf("\t%24s : 0x%08X [%d]\n", "cf_flash_sync_rear", DPData->cf_flash_sync_rear, DPData->cf_flash_sync_rear);
	printf("\t%24s : 0x%08X [%d]\n", "cf_safety_shift", DPData->cf_safety_shift, DPData->cf_safety_shift);
	printf("\t%24s : 0x%08X [%d]\n", "cf_lens_button", DPData->cf_lens_button, DPData->cf_lens_button);
	printf("\t%24s : 0x%08X [%d]\n", "cf_original_eval", DPData->cf_original_eval, DPData->cf_original_eval);
	printf("\t%24s : 0x%08X [%d]\n", "cf_qr_magnify", DPData->cf_qr_magnify, DPData->cf_qr_magnify);
	printf("\t%24s : 0x%08X [%d]\n", "batt_bclevel", DPData->batt_bclevel, DPData->batt_bclevel);
	printf("\t%24s : 0x%08X [%d]\n", "batt_type", DPData->batt_type, DPData->batt_type);
	printf("\t%24s : 0x%08X [%d]\n", "print_user_property", DPData->print_user_property, DPData->print_user_property);
	printf("\t%24s : 0x%08X [%d]\n", "printer_property", DPData->printer_property, DPData->printer_property);
	printf("\t%24s : 0x%08X [%d]\n", "cluster_size", DPData->cluster_size, DPData->cluster_size);
	printf("\t%24s : 0x%08X [%d]\n", "remain_cluster", DPData->remain_cluster, DPData->remain_cluster);
	printf("\t%24s : 0x%08X [%d]\n", "file_id", DPData->file_id, DPData->file_id);
	printf("\t%24s : 0x%08X [%d]\n", "avo", DPData->avo, DPData->avo);
	printf("\t%24s : 0x%08X [%d]\n", "avmax", DPData->avmax, DPData->avmax);
	printf("\t%24s : 0x%08X [%d]\n", "ef_lens_exist", DPData->ef_lens_exist, DPData->ef_lens_exist);
	printf("\t%24s : 0x%08X [%d]\n", "avail_shot", DPData->avail_shot, DPData->avail_shot);
	printf("\t%24s : 0x%08X [%d]\n", "qrev_imgprop", DPData->qrev_imgprop, DPData->qrev_imgprop);
	printf("\t%24s : 0x%08X [%d]\n", "printer_connect_type", DPData->printer_connect_type, DPData->printer_connect_type);
	printf("\t%24s : 0x%08X [%d]\n", "mwbdat_red", DPData->mwbdat_red, DPData->mwbdat_red);
	printf("\t%24s : 0x%08X [%d]\n", "mwbdat_green1", DPData->mwbdat_green1, DPData->mwbdat_green1);
	printf("\t%24s : 0x%08X [%d]\n", "mwbdat_green2", DPData->mwbdat_green2, DPData->mwbdat_green2);
	printf("\t%24s : 0x%08X [%d]\n", "mwbdat_blue", DPData->mwbdat_blue, DPData->mwbdat_blue);
	printf("\t%24s : 0x%08X [%d]\n", "videojack_connect", DPData->videojack_connect, DPData->videojack_connect);
	printf("\t%24s : 0x%08X [%d]\n", "incomp_image", DPData->incomp_image, DPData->incomp_image);
	printf("\t%24s : 0x%08X [%d]\n", "status_busy_flag", DPData->status_busy_flag, DPData->status_busy_flag);
	printf("\t%24s : 0x%08X [%d]\n", "special_bc_result", DPData->special_bc_result, DPData->special_bc_result);
	printf("\t%24s : 0x%08X [%d]\n", "reset_offtimer", DPData->reset_offtimer, DPData->reset_offtimer);
	printf("\t%24s : 0x%08X [%d]\n", "printer_device_property", DPData->printer_device_property, DPData->printer_device_property);
	printf("\t%24s : 0x%08X [%d]\n", "printer_job_property", DPData->printer_job_property, DPData->printer_job_property);
	printf("\t%24s : 0x%08X [%d]\n", "dpof_setting", DPData->dpof_setting, DPData->dpof_setting);
	printf("\t%24s : 0x%08X [%d]\n", "gui_mode", DPData->gui_mode, DPData->gui_mode);
	printf("\t%24s : 0x%08X [%d]\n", "dp_request_return", DPData->dp_request_return, DPData->dp_request_return);
	printf("\t%24s : 0x%08X [%d]\n", "commadp_chg_config", DPData->commadp_chg_config, DPData->commadp_chg_config);
	printf("\t%24s : 0x%08X [%d]\n", "play_jump_type", DPData->play_jump_type, DPData->play_jump_type);
	printf("\t%24s : 0x%08X [%d]\n", "capability_setting", DPData->capability_setting, DPData->capability_setting);
	printf("\t%24s : 0x%08X [%d]\n", "selected_af_mode", DPData->selected_af_mode, DPData->selected_af_mode);
	printf("\t%24s : 0x%08X [%d]\n", "disable_ui_lock", DPData->disable_ui_lock, DPData->disable_ui_lock);
	printf("\t%24s : 0x%08X [%d]\n", "isd_style_flag", DPData->isd_style_flag, DPData->isd_style_flag);
	printf("\t%24s : 0x%08X [%d]\n", "ptp", DPData->ptp, DPData->ptp);
	printf("\t%24s : 0x%08X [%d]\n", "playback_file_id", DPData->playback_file_id, DPData->playback_file_id);
	printf("\t%24s : 0x%08X [%d]\n", "playback_file_id_pos", DPData->playback_file_id_pos, DPData->playback_file_id_pos);
	printf("\t%24s : 0x%08X [%d]\n", "usb_connect_type", DPData->usb_connect_type, DPData->usb_connect_type);
	printf("\t%24s : 0x%08X [%d]\n", "face_sensor_disable", DPData->face_sensor_disable, DPData->face_sensor_disable);
	printf("\t%24s : 0x%08X [%d]\n", "field_178", DPData->field_178, DPData->field_178);
	printf("\t%24s : 0x%08X [%d]\n", "field_17C", DPData->field_17C, DPData->field_17C);
	printf("\t%24s : 0x%08X [%d]\n", "field_180", DPData->field_180, DPData->field_180);
	printf("\t%24s : 0x%08X [%d]\n", "field_184", DPData->field_184, DPData->field_184);
	printf("\t%24s : 0x%08X [%d]\n", "cf_tft_on_power_on", DPData->cf_tft_on_power_on, DPData->cf_tft_on_power_on);
	printf("\t%24s : 0x%08X [%d]\n", "field_18C", DPData->field_18C, DPData->field_18C);
	printf("\t%24s : 0x%08X [%d]\n", "field_190", DPData->field_190, DPData->field_190);

	printf("\n\nEND\n\n");
}
#endif // ENABLE_DEBUG_DPR_DATA

#endif
