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

void list_up     (type_MENU *menu);
void list_down   (type_MENU *menu);

void list_display(type_MENU *menu);
void list_hide   (type_MENU *menu);

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
		[MENU_EVENT_PLAY]    = menupage_drag_drop,
		[MENU_EVENT_UP]      = menupage_up,
		[MENU_EVENT_DOWN]    = menupage_down,
		[MENU_EVENT_LEFT]    = menu_left,
		[MENU_EVENT_RIGHT]   = menu_right,
		[MENU_EVENT_NEXT]    = menu_next,
		[MENU_EVENT_PREV]    = menu_prev,
		[MENU_EVENT_IN]      = menu_prev,
		[MENU_EVENT_OUT]     = menu_next,
		[MENU_EVENT_DISPLAY] = menupage_display,
		[MENU_EVENT_REFRESH] = menupage_refresh,
		[MENU_EVENT_CHANGE]  = menu_set_changed,
		[MENU_EVENT_CLOSE]   = menu_save,
		[MENU_EVENT_AV]      = list_display,
	}
};

type_MENUITEM main_list_items[LENGTH(menu_main_pages)];

type_MENUPAGE main_list = {
	name     : LP_WORD(L_P_400PLUS),
	length   : LENGTH(main_list_items),
	items    : main_list_items,
	tasks    : {
		[MENU_EVENT_PREV]   = list_up,
		[MENU_EVENT_NEXT]   = list_down,
		[MENU_EVENT_AV_UP]  = list_hide,
	},
	ordering : settings.main_order,
};

void menu_main_start() {
	int i;

	changed = FALSE;

	for (i = 0; i < LENGTH(menu_main_pages); i++) {
		main_list.items[i].parm.menuitem_page.id = i;
		main_list_items[i].name    = menu_main_pages[i]->name;
		main_list_items[i].display = menuitem_display;
	}

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

void list_up(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	page->current_posn--;

	menu_event_display();
}

void list_down(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	page->current_posn++;

	menu_event_display();
}

void list_hide(type_MENU *menu) {
	type_MENUPAGE *page =  menu->current_page;
	type_MENUITEM *item = &page->items[get_item_id(page, page->current_posn)];

	menu_set_posn(item->parm.menuitem_page.id);
}
