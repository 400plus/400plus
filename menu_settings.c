#include "main.h"
#include "menu.h"
#include "menu_presets.h"
#include "menu_developer.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"
#include "languages.h"

#include "menu_settings.h"

type_SETTINGS menu_settings;

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),   &menu_settings.wave_delay),
	MENUITEM_ACTION (LP_WORD(L_ACTION),  &menu_settings.wave_action),
	MENUITEM_BOOLEAN(LP_WORD(L_REPEAT),  &menu_settings.wave_repeat),
	MENUITEM_BOOLEAN(LP_WORD(L_INSTANT), &menu_settings.wave_instant)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT(LP_WORD(L_DELAY),  &menu_settings.timer_timeout),
	MENUITEM_ACTION (LP_WORD(L_ACTION), &menu_settings.timer_action)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),     &menu_settings.eaeb_delay),
	MENUITEM_BRACKET(LP_WORD(L_FRAMES),    &menu_settings.eaeb_frames),
	MENUITEM_EVSEP  (LP_WORD(L_STEP_EV),   &menu_settings.eaeb_ev),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_L),  &menu_settings.eaeb_m_min),
	MENUITEM_SHUTTER(LP_WORD(L_MANUAL_R),  &menu_settings.eaeb_m_max)
};

type_MENUITEM interval_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),    &menu_settings.interval_delay),
	MENUITEM_TIMEOUT(LP_WORD(L_TIME_S),   &menu_settings.interval_time),
	MENUITEM_BOOLEAN(LP_WORD(L_EAEB),     &menu_settings.interval_eaeb),
	MENUITEM_COUNTER(LP_WORD(L_SHOTS),    &menu_settings.interval_shots)
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_ADEP),     &menu_settings.presets_adep),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CAMERA),   &menu_settings.presets_camera),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_400PLUS),  &menu_settings.presets_400plus),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_SETTINGS), &menu_settings.presets_settings),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_IMAGE),    &menu_settings.presets_image),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CFN),      &menu_settings.presets_cfn)
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_EVCOMP (LP_WORD(L_AV_COMP),           &menu_settings.av_comp),
	MENUITEM_EVCOMP (LP_WORD(L_FLASH_COMP),        &menu_settings.flash_comp),
	MENUITEM_EVSEP  (LP_WORD(L_AEB),               &menu_settings.aeb_ev),
	MENUITEM_BOOLEAN(LP_WORD(L_ISO_IN_VF),         &menu_settings.iso_in_viewfinder),
	MENUITEM_BOOLEAN(LP_WORD(L_SHORTCUTS_MENU),    &menu_settings.shortcuts_menu),
	MENUITEM_BOOLEAN(LP_WORD(L_SAFETY_SHIFT),      &menu_settings.safety_shift),
	MENUITEM_CLRTEMP(LP_WORD(L_COLOR_TEMP_K),      &menu_settings.color_temp),
	MENUITEM_BOOLEAN(LP_WORD(L_USE_FLASH),         &menu_settings.emit_flash),
	MENUITEM_DELAY  (LP_WORD(L_IR_REMOTE_DELAY),   &menu_settings.remote_delay),
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
	action      : menu_settings_save,
	dp_action   : menu_presets_save_start,
	reorder     : FALSE,
	gui_mode    : GUI_MODE_400PLUS,
	btn_handler : InfoCreativeAppProc
};

void menu_settings_start() {
	beep();

	menu_settings = settings;

	menu_settings.av_comp        =  cameraMode.av_comp;
	menu_settings.flash_comp     =  cameraMode.efcomp;
	menu_settings.aeb_ev         =  cameraMode.ae_bkt;
	menu_settings.emit_flash     = !cameraMode.cf_emit_flash;

	menu_create(&main_menu);
}

void menu_settings_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();

	beep();
}
