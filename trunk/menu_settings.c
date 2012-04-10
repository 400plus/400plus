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

extern char languages_found[MAX_LANGUAGES][LP_MAX_WORD];

void menu_settings_open();

void reload_language_and_refresh         (const type_MENUITEM *item);

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_KEEP_POWER_ON), &settings.keep_power_on,    NULL),
	MENUITEM_SCRLCD( LP_WORD(L_I_LCD_SCRIPT),    &settings.script_lcd,       NULL),
	MENUITEM_SCRIND( LP_WORD(L_I_INDICATOR),     &settings.script_indicator, NULL),
};

type_MENUITEM buttons_items[] = {
	MENUITEM_BTNACTN(LP_WORD(L_I_BTN_JUMP), &settings.button_jump, NULL),
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_ADEP),     &presets_config.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CAMERA),   &presets_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_400PLUS),  &presets_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_SETTINGS), &presets_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_IMAGE),    &presets_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CFN),      &presets_config.recall_cfn,      NULL),
};

type_MENUITEM pages_items[] = {
	MENUITEM_INFO(LP_WORD(L_P_PARAMS),     NULL),
	MENUITEM_INFO(LP_WORD(L_P_SCRIPTS),    NULL),
	MENUITEM_INFO(LP_WORD(L_P_INFO),       NULL),
	MENUITEM_INFO(LP_WORD(L_P_DEVELOPERS), NULL),
	MENUITEM_INFO(LP_WORD(L_P_SETTINGS),   NULL),
	MENUITEM_INFO(LP_WORD(L_P_PRESETS),    NULL),
};

type_MENUPAGE scripts_page = {
	name   : LP_WORD(L_S_SCRIPTS),
	length : LENGTH(scripts_items),
	items  : scripts_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE buttons_page = {
	name   : LP_WORD(L_S_BUTTONS),
	length : LENGTH(buttons_items),
	items  : buttons_items,
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
	MENUITEM_LANG   (LP_WORD(L_I_LANGUAGE),         &settings.language,               reload_language_and_refresh),
	MENUITEM_BOOLEAN(LP_WORD(L_I_ISO_IN_VF),        &settings.iso_in_viewfinder,      NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_BUTTON_DISP),      &settings.button_disp,            NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_SCRIPTS),          &scripts_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_BUTTONS),          &buttons_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PRESETS),          &presets_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PAGES),            &pages_page,                      NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_DEVELOPERS_MENU),  &settings.developers_menu,        NULL),
};

type_MENUPAGE menupage_settings = {
	name      : LP_WORD(L_P_SETTINGS),
	sibilings : TRUE,
	length    : LENGTH(menu_settings_items),
	items     : menu_settings_items,
	ordering  : settings.settings_order,
	tasks     : {
		[MENU_EVENT_OPEN] = menu_settings_open,
	}
};

void reload_language_and_refresh(const type_MENUITEM *item) {
	lang_pack_config();
	menu_event_display();
}

void menu_settings_open() {
	int i;

	for (i = 0; i<MAX_LANGUAGES && languages_found[i] != NULL && languages_found[i][0] != NULL; i++) {
		menupage_settings.items[0].parm.menuitem_enum.list->length  = i + 1;
		menupage_settings.items[0].parm.menuitem_enum.list->data[i] = languages_found[i];
	}
}
