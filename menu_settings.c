#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menu_presets.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "menu_settings.h"

void menu_settings_apply_cf_safety_shift (type_MENUITEM *item);
void menu_settings_apply_remote_enable   (type_MENUITEM *item);
void menu_settings_apply_remote_delay    (type_MENUITEM *item);

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_DIM_LCD_DOWN),  &settings.dim_lcd_down,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_KEEP_POWER_ON), &settings.keep_power_on, NULL)
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_ADEP),     &presets_config.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CAMERA),   &presets_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_400PLUS),  &presets_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_SETTINGS), &presets_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_IMAGE),    &presets_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_PRESETS_CFN),      &presets_config.recall_cfn,      NULL)
};

type_MENUPAGE scripts_page = {
	name   : LP_WORD(L_SCRIPTS_SPACES),
	length : LENGTH(scripts_items),
	items  : scripts_items,
	tasks  : {
		[MENU_EVENT_SET] = menu_return,
	}
};

type_MENUPAGE presets_page = {
	name   : LP_WORD(L_PRESETS_SPACES),
	length : LENGTH(presets_items),
	items  : presets_items,
	tasks  : {
		[MENU_EVENT_SET] = menu_return,
	}
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_SAFETY_SHIFT),      &menu_cameraMode.cf_safety_shift, menu_settings_apply_cf_safety_shift),
	MENUITEM_BOOLEAN(LP_WORD(L_IR_REMOTE_ENABLE),  &settings.remote_enable,          menu_settings_apply_remote_enable),
	MENUITEM_DELAY  (LP_WORD(L_IR_REMOTE_DELAY),   &settings.remote_delay,           menu_settings_apply_remote_delay),
	MENUITEM_BOOLEAN(LP_WORD(L_ISO_IN_VF),         &settings.iso_in_viewfinder,      NULL),
	MENUITEM_SUBMENU(LP_WORD(L_SCRIPTS_SPACES),    &scripts_page,                    NULL),
};

type_MENUPAGE menupage_main = {
	name        : LP_WORD(L_SETTINGS),
	length      : LENGTH(menu_settings_items),
	items       : menu_settings_items,
	reorder     : FALSE,
	tasks       : {
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_settings_save,
	}
};

type_MENUPAGE *main_menu_pages[] = {
	&menupage_main,
};

type_MENU main_menu = {
	length : 1,
	pages  : main_menu_pages,
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
