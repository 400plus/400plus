#include "firmware/gui.h"

#include "main.h"
#include "macros.h"
#include "firmware.h"

#include "cmodes.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_cmodes.h"
#include "menu_developer.h"
#include "menu_info.h"
#include "menu_params.h"
#include "menu_scripts.h"
#include "menu_settings.h"
#include "persist.h"
#include "settings.h"
#include "snapshots.h"
#include "utils.h"

#include "menu_main.h"

int changed;

void list_up     (menu_t *menu);
void list_down   (menu_t *menu);

void list_display(menu_t *menu);
void list_hide   (menu_t *menu);

void page_display(menu_t *menu);

menupage_t *menu_main_pages[] = {
	[MENUPAGE_PARAMS]   = &menupage_params,
	[MENUPAGE_SCRIPTS]  = &menupage_scripts,
	[MENUPAGE_INFO]     = &menupage_info,
	[MENUPAGE_SETTINGS] = &menupage_settings,
	[MENUPAGE_CMODES]   = &menupage_cmodes,
};

menu_t menu_main = {
	pages    : LIST(menu_main_pages),
	ordering : menu_order.main,
	actions  : {
		[MENU_EVENT_PLAY]    = menupage_drag_drop,
		[MENU_EVENT_UP]      = menupage_up,
		[MENU_EVENT_DOWN]    = menupage_down,
		[MENU_EVENT_SET]     = menu_set,
		[MENU_EVENT_LEFT]    = menu_left,
		[MENU_EVENT_RIGHT]   = menu_right,
		[MENU_EVENT_NEXT]    = menu_next,
		[MENU_EVENT_PREV]    = menu_prev,
		[MENU_EVENT_IN]      = menupage_pgdown,
		[MENU_EVENT_OUT]     = menupage_pgup,
		[MENU_EVENT_DISPLAY] = menupage_display,
		[MENU_EVENT_REFRESH] = menupage_refresh,
		[MENU_EVENT_FINISH]  = menu_finish,
		[MENU_EVENT_SAVE]    = menu_main_save,
		[MENU_EVENT_AV]      = list_display,
		[MENU_EVENT_TRASH]   = menupage_developer_start,
	}
};

menuitem_t main_list_items[] = {
	[MENUPAGE_PARAMS]   = MENUITEM_PAGE(0, LP_WORD(L_P_PARAMS)),
	[MENUPAGE_SCRIPTS]  = MENUITEM_PAGE(0, LP_WORD(L_P_SCRIPTS)),
	[MENUPAGE_INFO]     = MENUITEM_PAGE(0, LP_WORD(L_P_INFO)),
	[MENUPAGE_SETTINGS] = MENUITEM_PAGE(0, LP_WORD(L_P_SETTINGS)),
	[MENUPAGE_CMODES]   = MENUITEM_PAGE(0, LP_WORD(L_P_CMODES)),
};

menupage_t main_list = {
	name     : LP_WORD(L_P_400PLUS),
	items    : LIST(main_list_items),
	actions  : {
		[MENU_EVENT_PLAY]   = page_display,
		[MENU_EVENT_UP]     = list_up,
		[MENU_EVENT_DOWN]   = list_down,
		[MENU_EVENT_PREV]   = list_up,
		[MENU_EVENT_NEXT]   = list_down,
		[MENU_EVENT_AV_UP]  = list_hide,
		[MENU_EVENT_SET]    = page_display,
	},
	ordering : menu_order.main,
};

void menu_main_start() {
	if (settings.menu_autosave)
		menu_main.current_posn = persist.last_page;

	menu_create(&menu_main);

	if (settings.menu_entermain)
		list_display(&menu_main);
}

void menu_main_save(menu_t *menu) {
	if (persist.last_page != menu_main.current_posn || persist.aeb != DPData.ae_bkt) {
		persist.last_page = menu_main.current_posn;
		persist.aeb       = DPData.ae_bkt;

		if (persist.aeb)
			persist.last_aeb = persist.aeb;

		enqueue_action(persist_write);
	}

	if (menu->changed) {
		enqueue_action(settings_write);
		enqueue_action(cmodes_write);
		enqueue_action(lang_pack_config);
	}
}

void list_display(menu_t *menu) {
	main_list.current_line = 2;
	main_list.current_posn = menu->current_posn;

	menu_set_page(&main_list);
}

void list_up(menu_t *menu) {
	menupage_t *page = menu->current_page;

	page->current_posn--;

	menu_event_display();
}

void list_down(menu_t *menu) {
	menupage_t *page = menu->current_page;

	page->current_posn++;

	menu_event_display();
}

void list_hide(menu_t *menu) {
	menupage_t *page = menu->current_page;

	if (page->current_posn != menu->current_posn || !settings.menu_navmain)
		menu_set_posn(get_item_id(page, page->current_posn));
}

void page_display (menu_t *menu) {
	menupage_t *page = menu->current_page;

	menu_set_posn(get_item_id(page, page->current_posn));
}
