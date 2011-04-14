#include "main.h"
#include "menu.h"
#include "utils.h"
#include "firmware.h"

#include "menu_developer.h"

type_MENUITEM menu_developer_items[] = {
	MENUITEM_TASK ("Enter factory mode", enter_factory_mode),
	MENUITEM_TASK ("Exit  factory mode", exit_factory_mode),
	MENUITEM_TASK ("Start debug   mode", start_debug_mode),
	MENUITEM_TASK ("",                   NULL),
	MENUITEM_TASK ("",                   NULL)
};

type_MENU menu_developer = {
	name    : "Developer",
	length  : LENGTH(menu_developer_items),
	items   : menu_developer_items,
	action  : NULL,
	reorder : FALSE
};

void menu_developer_start() {
	beep();
	menu_create(menu_developer);
}
