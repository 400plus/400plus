#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menu_developer.h"
#include "menu_presets.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "menu_settings.h"

type_CAMERA_MODE menu_cameraMode;

void menu_settings_apply_av_comp         (type_MENUITEM *item);
void menu_settings_apply_efcomp          (type_MENUITEM *item);
void menu_settings_apply_cf_emit_flash   (type_MENUITEM *item);
void menu_settings_apply_color_temp      (type_MENUITEM *item);
void menu_settings_apply_ae_bkt          (type_MENUITEM *item);
void menu_settings_apply_cf_safety_shift (type_MENUITEM *item);
void menu_settings_apply_remote_enable   (type_MENUITEM *item);
void menu_settings_apply_remote_delay    (type_MENUITEM *item);

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_DIM_LCD_DOWN),  &settings.dim_lcd_down,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_KEEP_POWER_ON), &settings.keep_power_on, NULL)
};

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),   &settings.wave_delay,   NULL),
	MENUITEM_ACTION (LP_WORD(L_ACTION),  &settings.wave_action,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_REPEAT),  &settings.wave_repeat,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_INSTANT), &settings.wave_instant, NULL)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT(LP_WORD(L_DELAY),  &settings.timer_timeout, NULL),
	MENUITEM_ACTION (LP_WORD(L_ACTION), &settings.timer_action,  NULL)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),     &settings.eaeb_delay,  NULL),
	MENUITEM_BRACKET(LP_WORD(L_FRAMES),    &settings.eaeb_frames, NULL),
	MENUITEM_EVSEP  (LP_WORD(L_STEP_EV),   &settings.eaeb_ev,     NULL),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_L),  &settings.eaeb_tv_min, NULL),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_R),  &settings.eaeb_tv_max, NULL)
};

type_MENUITEM interval_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),    &settings.interval_delay, NULL),
	MENUITEM_TIMEOUT(LP_WORD(L_TIME_S),   &settings.interval_time,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_EAEB),     &settings.interval_eaeb,  NULL),
	MENUITEM_COUNTER(LP_WORD(L_SHOTS),    &settings.interval_shots, NULL)
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_ADEP),     &presets_config.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CAMERA),   &presets_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_400PLUS),  &presets_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_SETTINGS), &presets_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_IMAGE),    &presets_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CFN),      &presets_config.recall_cfn,      NULL)
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_EVCOMP (LP_WORD(L_AV_COMP),           &menu_cameraMode.av_comp,         menu_settings_apply_av_comp),
	MENUITEM_EVCOMP (LP_WORD(L_FLASH_COMP),        &menu_cameraMode.efcomp,          menu_settings_apply_efcomp),
	MENUITEM_BOOLEAN(LP_WORD(L_USE_FLASH),         &menu_cameraMode.cf_emit_flash,   menu_settings_apply_cf_emit_flash),
	MENUITEM_CLRTEMP(LP_WORD(L_COLOR_TEMP_K),      &menu_cameraMode.color_temp,      menu_settings_apply_color_temp),
	MENUITEM_EVSEP  (LP_WORD(L_AEB),               &menu_cameraMode.ae_bkt,          menu_settings_apply_ae_bkt),
	MENUITEM_BOOLEAN(LP_WORD(L_SAFETY_SHIFT),      &menu_cameraMode.cf_safety_shift, menu_settings_apply_cf_safety_shift),
	MENUITEM_BOOLEAN(LP_WORD(L_IR_REMOTE_ENABLE),  &settings.remote_enable,          menu_settings_apply_remote_enable),
	MENUITEM_DELAY  (LP_WORD(L_IR_REMOTE_DELAY),   &settings.remote_delay,           menu_settings_apply_remote_delay),
	MENUITEM_BOOLEAN(LP_WORD(L_ISO_IN_VF),         &settings.iso_in_viewfinder,      NULL),
	MENUITEM_SUBMENU(LP_WORD(L_SCRIPTS_SPACES),     scripts_items),
	MENUITEM_SUBMENU(LP_WORD(L_HANDWAVE),           wave_items),
	MENUITEM_SUBMENU(LP_WORD(L_EXT_AEB),            eaeb_items),
	MENUITEM_SUBMENU(LP_WORD(L_INTERVAL),           interval_items),
	MENUITEM_SUBMENU(LP_WORD(L_TIMER_SPACES),       timer_items),
	MENUITEM_SUBMENU(LP_WORD(L_PRESETS_SPACES),     presets_items),
	MENUITEM_BREAK  ("---------------------------"),
	MENUITEM_LAUNCH (LP_WORD(L_DEVELOPERS_MENU),    menu_developer_start),
	MENUITEM_BREAK  ("===========================")
};

type_MENU main_menu = {
	name        : LP_WORD(L_SETTINGS),
	length      : LENGTH(menu_settings_items),
	items       : menu_settings_items,
	reorder     : FALSE,
	tasks       : {
		[MENU_EVENT_DP]     = menu_presets_save_start,
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_settings_save,
	}
};

void menu_settings_start() {
	beep();
	menu_settings_create();
}

void menu_settings_create() {
	menu_cameraMode = *cameraMode;

	menu_create(&main_menu);
}

void menu_settings_save() {
	if (menu_get_changed()) {
		settings_write();
		presets_write();
	}
}

void menu_settings_apply_av_comp(type_MENUITEM *item) {
	send_to_intercom(IC_SET_AV_COMP, 1, *item->parm.menuitem_ev.value);
}

void menu_settings_apply_efcomp(type_MENUITEM *item) {
	send_to_intercom(IC_SET_EFCOMP, 1, *item->parm.menuitem_ev.value);
}

void menu_settings_apply_cf_emit_flash(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, *item->parm.menuitem_enum.value);
}

void menu_settings_apply_color_temp(type_MENUITEM *item) {
	send_to_intercom(IC_SET_WB,         1, WB_MODE_COLORTEMP);
	send_to_intercom(IC_SET_COLOR_TEMP, 2, *item->parm.menuitem_int.value);
}

void menu_settings_apply_ae_bkt(type_MENUITEM *item) {
	send_to_intercom(IC_SET_AE_BKT, 1, *item->parm.menuitem_ev.value);
}

void menu_settings_apply_cf_safety_shift(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_SAFETY_SHIFT, 1, *item->parm.menuitem_enum.value);
}

void menu_settings_apply_remote_enable(type_MENUITEM *item) {
	if(*item->parm.menuitem_enum.value){
		remote_on();
	} else {
		remote_off();
	}
}
void menu_settings_apply_remote_delay(type_MENUITEM *item) {
	if(*item->parm.menuitem_enum.value){
		RemReleaseSelfMax = 4500;
		RemReleaseInstMin = 5560;
	} else {
		RemReleaseSelfMax = 6160;
		RemReleaseInstMin = 7410;
	}
}
