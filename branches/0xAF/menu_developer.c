#include "main.h"

#include "languages.h"
#include "menu.h"
#include "menu_settings.h"
#include "utils.h"
#include "settings.h"

#include "menu_developer.h"

type_MENUITEM menu_developer_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_ENTER_FACTORY_MODE), enter_factory_mode),
	MENUITEM_LAUNCH(LP_WORD(L_EXIT_FACTORY_MODE),  exit_factory_mode),
	MENUITEM_BOOLEAN(LP_WORD(L_DEBUG_ON_POWERON),  &settings.debug_on_poweron, NULL),
	MENUITEM_LOGFILE(LP_WORD(L_LOGFILE),           &settings.logfile_mode, NULL),
	MENUITEM_LAUNCH("",                            NULL)
};

type_MENU menu_developer = {
	name        : LP_WORD(L_DEVELOPER),
	length      : LENGTH(menu_developer_items),
	items       : menu_developer_items,
	reorder     : FALSE,
	tasks       : {
		[MENU_EVENT_DP] = menu_settings_start,
		[MENU_EVENT_CLOSE] = menu_settings_save,
	}
};

void menu_developer_start() {
	beep();
	menu_create(&menu_developer);
}
