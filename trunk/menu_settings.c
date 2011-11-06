#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "menu_settings.h"

void menu_settings_apply_cf_safety_shift (type_MENUITEM *item);
void menu_settings_apply_remote_enable   (type_MENUITEM *item);
void menu_settings_apply_remote_delay    (type_MENUITEM *item);

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_DIM_LCD_DOWN),  &settings.dim_lcd_down,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_KEEP_POWER_ON), &settings.keep_power_on, NULL)
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_ADEP),     &presets_config.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CAMERA),   &presets_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_400PLUS),  &presets_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_SETTINGS), &presets_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_IMAGE),    &presets_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CFN),      &presets_config.recall_cfn,      NULL)
};

type_MENUITEM pages_items[] = {
	MENUITEM_BREAK(LP_WORD(L_P_PARAMS)),
	MENUITEM_BREAK(LP_WORD(L_P_SHORTCUTS)),
	MENUITEM_BREAK(LP_WORD(L_P_SCRIPTS)),
	MENUITEM_BREAK(LP_WORD(L_P_INFO)),
	MENUITEM_BREAK(LP_WORD(L_P_DEVELOPERS)),
	MENUITEM_BREAK(LP_WORD(L_P_SETTINGS)),
	MENUITEM_BREAK(LP_WORD(L_P_PRESETS)),
};

type_MENUPAGE scripts_page = {
	name   : LP_WORD(L_S_SCRIPTS),
	length : LENGTH(scripts_items),
	items  : scripts_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE presets_page = {
	name   : LP_WORD(L_S_PRESETS),
	length : LENGTH(presets_items),
	items  : presets_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE pages_page = {
	name     : LP_WORD(L_S_PAGES),
	length   : LENGTH(pages_items),
	items    : pages_items,
	ordering : settings.main_order,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_SAFETY_SHIFT),     &menu_cameraMode.cf_safety_shift, menu_settings_apply_cf_safety_shift),
	MENUITEM_BOOLEAN(LP_WORD(L_I_IR_REMOTE_ENABLE), &settings.remote_enable,          menu_settings_apply_remote_enable),
	MENUITEM_BOOLEAN(LP_WORD(L_I_IR_REMOTE_DELAY),  &settings.remote_delay,           menu_settings_apply_remote_delay),
	MENUITEM_BOOLEAN(LP_WORD(L_I_ISO_IN_VF),        &settings.iso_in_viewfinder,      NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_SCRIPTS),          &scripts_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PRESETS),          &presets_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PAGES),            &pages_page,                      NULL),
};

type_MENUPAGE menupage_settings = {
	name      : LP_WORD(L_P_SETTINGS),
	sibilings : TRUE,
	length    : LENGTH(menu_settings_items),
	items     : menu_settings_items,
	ordering  : settings.settings_order,
};

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
