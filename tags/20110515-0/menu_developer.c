#include "main.h"
#include "menu.h"
#include "utils.h"
#include "languages.h"
#include "menu_settings.h"
#include "firmware.h"

#include "menu_developer.h"

type_MENUITEM menu_developer_items[] = {
	MENUITEM_TASK (LP_WORD(L_ENTER_FACTORY_MODE), enter_factory_mode),
	MENUITEM_TASK (LP_WORD(L_EXIT_FACTORY_MODE),  exit_factory_mode),
	MENUITEM_TASK (LP_WORD(L_START_DEBUG_MODE),   start_debug_mode),
	MENUITEM_TASK ("",                   NULL),
	MENUITEM_TASK ("",                   NULL)
};

type_MENU menu_developer = {
	name        : LP_WORD(L_DEVELOPER),
	length      : LENGTH(menu_developer_items),
	items       : menu_developer_items,
	action      : NULL,
	reorder     : FALSE,
	dp_action   : menu_settings_start
};

void menu_developer_start() {
	beep();
	menu_create(&menu_developer);
}
