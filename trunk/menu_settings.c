/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <unistd.h>
#include <stdbool.h>

#include "macros.h"

#include "display.h"
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

void menu_restore_settings();
void menu_restore_presets();
void menu_delete_presets();

void reload_language_and_refresh(const type_MENUITEM *item);

type_MENUITEM scripts_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_KEEP_POWER_ON), &settings.keep_power_on,    NULL),
	MENUITEM_SCRLCD( LP_WORD(L_I_LCD_SCRIPT),    &settings.script_lcd,       NULL),
	MENUITEM_SCRIND( LP_WORD(L_I_INDICATOR),     &settings.script_indicator, NULL),
};

type_MENUITEM buttons_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_BUTTON_DISP), &settings.button_disp,  NULL),
	MENUITEM_BTNACTN(LP_WORD(L_I_BTN_JUMP),    &settings.button_jump,  NULL),
	MENUITEM_BTNACTN(LP_WORD(L_I_BTN_TRASH),   &settings.button_trash, NULL),
};

type_MENUITEM presets_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_ADEP),     &presets_config.use_adep,        NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CAMERA),   &presets_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_400PLUS),  &presets_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_SETTINGS), &presets_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_IMAGE),    &presets_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_PRESETS_CFN),      &presets_config.recall_cfn,      NULL),
};

type_MENUITEM menus_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_WARP_MENUS),    &settings.menu_warp,      NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_NAVIGATE_MAIN), &settings.menu_navmain,   NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_ENTER_MAIN),    &settings.menu_entermain, NULL),
};

type_MENUITEM pages_items[] = {
	MENUITEM_INFO(LP_WORD(L_P_PARAMS),     NULL),
	MENUITEM_INFO(LP_WORD(L_P_SCRIPTS),    NULL),
	MENUITEM_INFO(LP_WORD(L_P_INFO),       NULL),
	MENUITEM_INFO(LP_WORD(L_P_SETTINGS),   NULL),
	MENUITEM_INFO(LP_WORD(L_P_PRESETS),    NULL),
};

type_MENUITEM restore_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_RESTORE_SETTINGS), menu_restore_settings),
	MENUITEM_LAUNCH(LP_WORD(L_I_RESTORE_PRESETS),  menu_restore_presets),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE_PRESETS),   menu_delete_presets),
};

type_MENUPAGE scripts_page = {
	name    : LP_WORD(L_S_SCRIPTS),
	length  : LENGTH(scripts_items),
	items   : scripts_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE buttons_page = {
	name    : LP_WORD(L_S_BUTTONS),
	length  : LENGTH(buttons_items),
	items   : buttons_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE presets_page = {
	name    : LP_WORD(L_S_PRESETS),
	length  : LENGTH(presets_items),
	items   : presets_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menus_page = {
	name    : LP_WORD(L_S_MENUS),
	length  : LENGTH(menus_items),
	items   : menus_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE pages_page = {
	name     : LP_WORD(L_S_PAGES),
	length   : LENGTH(pages_items),
	items    : pages_items,
	ordering : settings.main_order,
	actions  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE restore_page = {
	name     : LP_WORD(L_I_RESTORE),
	length   : LENGTH(restore_items),
	items    : restore_items,
	actions  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUITEM menu_settings_items[] = {
	MENUITEM_LANG   (LP_WORD(L_I_LANGUAGE),         &settings.language,               reload_language_and_refresh),
	MENUITEM_BOOLEAN(LP_WORD(L_I_ISO_IN_VF),        &settings.iso_in_viewfinder,      NULL),
	MENUITEM_SUBMENU(LP_WORD(L_I_RESTORE),          &restore_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_SCRIPTS),          &scripts_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_BUTTONS),          &buttons_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PRESETS),          &presets_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_MENUS),            &menus_page,                      NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_PAGES),            &pages_page,                      NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_DEVELOPERS_MENU),  &settings.developers_menu,        NULL),
};

type_MENUPAGE menupage_settings = {
	name      : LP_WORD(L_P_SETTINGS),
	sibilings : true,
	length    : LENGTH(menu_settings_items),
	items     : menu_settings_items,
	ordering  : settings.settings_order,
	actions   : {
		[MENU_EVENT_OPEN] = menu_settings_open,
	}
};

void reload_language_and_refresh(const type_MENUITEM *item) {
	lang_pack_config();
	menu_event_display();
}

void menu_settings_open() {
	int i;

	for (i = 0; i<MAX_LANGUAGES && languages_found[i] != '\0' && languages_found[i][0] != '\0'; i++) {
		menupage_settings.items[0].parm.menuitem_enum.list->length  = i + 1;
		menupage_settings.items[0].parm.menuitem_enum.list->data[i] = languages_found[i];
	}
}

void menu_restore_settings() {
	settings_restore();
	menu_return();
	beep();
}

void menu_restore_presets() {
	presets_restore();
	menu_return();
	beep();
}

void menu_delete_presets() {
	presets_delete();
	menu_return();
	beep();
}
