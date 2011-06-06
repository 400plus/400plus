#include "main.h"
#include "menu.h"
#include "menu_presets.h"
#include "menu_developer.h"
#include "utils.h"
#include "settings.h"
#include "presets.h"
#include "firmware.h"
#include "languages.h"

#include "menu_settings.h"

type_SETTINGS       menu_settings;
type_PRESETS_CONFIG menu_presets;

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_DIM_LCD_DOWN),  &menu_settings.dim_lcd_down,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_KEEP_POWER_ON), &menu_settings.keep_power_on, NULL)
};

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),   &menu_settings.wave_delay,   NULL),
	MENUITEM_ACTION (LP_WORD(L_ACTION),  &menu_settings.wave_action,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_REPEAT),  &menu_settings.wave_repeat,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_INSTANT), &menu_settings.wave_instant, NULL)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT(LP_WORD(L_DELAY),  &menu_settings.timer_timeout),
	MENUITEM_ACTION (LP_WORD(L_ACTION), &menu_settings.timer_action, NULL)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),     &menu_settings.eaeb_delay,  NULL),
	MENUITEM_BRACKET(LP_WORD(L_FRAMES),    &menu_settings.eaeb_frames),
	MENUITEM_EVSEP  (LP_WORD(L_STEP_EV),   &menu_settings.eaeb_ev),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_L),  &menu_settings.eaeb_tv_min, NULL),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_R),  &menu_settings.eaeb_tv_max, NULL)
};

type_MENUITEM interval_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),    &menu_settings.interval_delay, NULL),
	MENUITEM_TIMEOUT(LP_WORD(L_TIME_S),   &menu_settings.interval_time),
	MENUITEM_BOOLEAN(LP_WORD(L_EAEB),     &menu_settings.interval_eaeb,  NULL),
	MENUITEM_COUNTER(LP_WORD(L_SHOTS),    &menu_settings.interval_shots)
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_ADEP),     &menu_presets.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CAMERA),   &menu_presets.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_400PLUS),  &menu_presets.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_SETTINGS), &menu_presets.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_IMAGE),    &menu_presets.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CFN),      &menu_presets.recall_cfn,      NULL)
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_EVCOMP (LP_WORD(L_AV_COMP),           &menu_settings.av_comp),
	MENUITEM_EVCOMP (LP_WORD(L_FLASH_COMP),        &menu_settings.flash_comp),
	MENUITEM_BOOLEAN(LP_WORD(L_USE_FLASH),         &menu_settings.emit_flash,        NULL),
	MENUITEM_CLRTEMP(LP_WORD(L_COLOR_TEMP_K),      &menu_settings.color_temp),
	MENUITEM_EVSEP  (LP_WORD(L_AEB),               &menu_settings.aeb_ev),
	MENUITEM_BOOLEAN(LP_WORD(L_SAFETY_SHIFT),      &menu_settings.safety_shift,      NULL),
	MENUITEM_DELAY  (LP_WORD(L_IR_REMOTE_DELAY),   &menu_settings.remote_delay,      NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_ISO_IN_VF),         &menu_settings.iso_in_viewfinder, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_SHORTCUTS_MENU),    &menu_settings.shortcuts_menu,    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_SCRIPTS_SPACES),     scripts_items),
	MENUITEM_SUBMENU(LP_WORD(L_HANDWAVE),           wave_items),
	MENUITEM_SUBMENU(LP_WORD(L_EXT_AEB),            eaeb_items),
	MENUITEM_SUBMENU(LP_WORD(L_INTERVAL),           interval_items),
	MENUITEM_SUBMENU(LP_WORD(L_TIMER_SPACES),       timer_items),
	MENUITEM_SUBMENU(LP_WORD(L_PRESETS_SPACES),     presets_items),
	MENUITEM_TASK   ("---------------------------", NULL),
	MENUITEM_TASK   (LP_WORD(L_DEVELOPERS_MENU),    menu_developer_start)
};

type_MENU main_menu = {
	name        : LP_WORD(L_SETTINGS),
	length      : LENGTH(menu_settings_items),
	items       : menu_settings_items,
	save        : menu_settings_save,
	dp_action   : menu_presets_save_start,
	reorder     : FALSE
};

void menu_settings_start() {
	beep();
	menu_settings_create();
}

void menu_settings_create() {
	menu_settings = settings;

	menu_settings.av_comp        =  cameraMode.av_comp;
	menu_settings.flash_comp     =  cameraMode.efcomp;
	menu_settings.aeb_ev         =  cameraMode.ae_bkt;
	menu_settings.emit_flash     = !cameraMode.cf_emit_flash;

	menu_presets = presets_config;

	menu_create(&main_menu);
}

void menu_settings_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();

	presets_config = menu_presets;

	presets_write();

	beep();
}
