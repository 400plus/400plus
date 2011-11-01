#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_developer.h"
#include "menu_info.h"
#include "menu_params.h"
#include "menu_presets.h"
#include "menu_scripts.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "menu_main.h"

int  changed;

void menu_save();
void menu_set_changed();
int  menu_get_changed();

void list_display(type_MENU     *menu);

void list_up  (type_MENUPAGE *menupage);
void list_down(type_MENUPAGE *menupage);
void list_hide(type_MENUPAGE *menupage);

void goto_params   (type_MENUITEM *item);
void goto_shortcuts(type_MENUITEM *item);
void goto_scripts  (type_MENUITEM *item);
void goto_info     (type_MENUITEM *item);
void goto_developer(type_MENUITEM *item);
void goto_settngs  (type_MENUITEM *item);
void goto_presets  (type_MENUITEM *item);

type_MENUPAGE *menu_main_pages[] = {
	&menupage_params,
	&menupage_shortcuts,
	&menupage_scripts,
	&menupage_info,
	&menupage_developer,
	&menupage_settings,
	&menupage_presets,
};

type_MENU menu_main = {
	length   : LENGTH(menu_main_pages),
	pages    : menu_main_pages,
	ordering : settings.main_order,
	tasks    : {
		[MENU_EVENT_PLAY]   = menu_drag_drop,
		[MENU_EVENT_UP]     = menu_up,
		[MENU_EVENT_DOWN]   = menu_down,
		[MENU_EVENT_LEFT]   = menu_left,
		[MENU_EVENT_RIGHT]  = menu_right,
		[MENU_EVENT_NEXT]   = menu_page_next,
		[MENU_EVENT_PREV]   = menu_page_prev,
		[MENU_EVENT_IN]     = menu_page_prev,
		[MENU_EVENT_OUT]    = menu_page_next,
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_save,
		[MENU_EVENT_AV]     = list_display,
	}
};

type_MENUITEM main_list_items[] = {
	MENUITEM_LAUNCH("Params",    goto_params),
	MENUITEM_LAUNCH("Shortcuts", goto_shortcuts),
	MENUITEM_LAUNCH("Scripts",   goto_scripts),
	MENUITEM_LAUNCH("Info",      goto_info),
	MENUITEM_LAUNCH("Developer", goto_developer),
	MENUITEM_LAUNCH("Settings",  goto_settngs),
	MENUITEM_LAUNCH("Presets",   goto_presets),
};

type_MENUPAGE main_list = {
	name     : "400plus",
	length   : LENGTH(main_list_items),
	items    : main_list_items,
	tasks    : {
		[MENU_EVENT_NEXT]   = list_up,
		[MENU_EVENT_PREV]   = list_down,
		[MENU_EVENT_AV_UP]  = list_hide,
	},
	ordering : settings.main_order,
};

void menu_main_start() {
	beep();

	//
	//GUI_Command(4,0);
	//press_button(IC_BUTTON_MENU);
	//
	SendToMC(6, 2, 0);
	SleepTask(100);

	changed         = FALSE;
	menu_cameraMode = *cameraMode;

	menu_create(&menu_main);
}

void menu_save() {
	if (menu_get_changed()) {
		settings_write();
		presets_write();
	}
}

void menu_set_changed() {
	changed = TRUE;
}

int menu_get_changed() {
	return changed;
}

void list_display(type_MENU *menu) {
	main_list.current_line = 2;
	main_list.current_posn = menu->current_posn;

	menu_set_page(&main_list);
}


void list_up(type_MENUPAGE *menupage) {
	menu_up(&menu_main);
}

void list_down(type_MENUPAGE *menupage) {
	menu_down(&menu_main);
}

void list_hide(type_MENUPAGE *page) {
	type_MENUITEM *item = get_current_item(page);

	if (item && item->tasks[MENU_EVENT_SET])
		item->tasks[MENU_EVENT_SET](item);
}

void goto_params(type_MENUITEM *item) {
	menu_set_page(&menupage_params);
}

void goto_shortcuts(type_MENUITEM *item) {
	menu_set_page(&menupage_shortcuts);
}

void goto_scripts(type_MENUITEM *item) {
	menu_set_page(&menupage_scripts);
}

void goto_info(type_MENUITEM *item) {
	menu_set_page(&menupage_info);
}

void goto_developer(type_MENUITEM *item) {
	menu_set_page(&menupage_developer);
}

void goto_settngs(type_MENUITEM *item) {
	menu_set_page(&menupage_settings);
}

void goto_presets(type_MENUITEM *item) {
	menu_set_page(&menupage_presets);
}
