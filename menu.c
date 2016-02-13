#include <vxworks.h>

#include "firmware/gui.h"

#include "macros.h"
#include "main.h"

#include "button.h"
#include "languages.h"
#include "menupage.h"
#include "menuitem.h"
#include "snapshots.h"
#include "utils.h"
#include "debug.h"

#include "menu.h"

dpr_data_t menu_DPData;

void *menu_handler;

menu_t *current_menu;

void menu_initialize(void);
void menu_destroy   (void);

int menu_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

void menu_set_page(menupage_t *page);
void menu_set_text(const int line, const char *text);

void menu_repeat(menu_t *menu, void (*action)(menu_t *menu, const int repeating));

void menu_repeat_right(menu_t *menu, const int repeating);
void menu_repeat_left (menu_t *menu, const int repeating);

menupage_t *get_selected_page(void);

void menu_create(menu_t *menu) {
	status.lock_redraw = TRUE;
	press_button(IC_BUTTON_MENU);
	SleepTask(MENU_WAIT_FW);
	status.lock_redraw = FALSE;

	GUI_StartMode(0x2D);

	current_menu = menu;
	menu_DPData  = DPData;

	GUI_Lock();
	GUI_PaletteInit();

	menu_destroy();
	menu_initialize();

	menu_handler = dialog_create(0x16, menu_event_handler);

	GUI_PalettePush();
	GUI_PaletteChange(current_menu->color);

	menu_event_display();

	GUI_UnLock();
	GUI_PaletteUnInit();
}

void menu_close() {
	press_button(IC_BUTTON_MENU);

	menu_destroy();
	menu_finish(NULL); //TODO:FixMe
}

void menu_initialize() {
	menu_return(current_menu);
	status.menu_running = TRUE;
}

void menu_destroy() {
	if (menu_handler != NULL) {
		GUI_PalettePop();
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
		GUI_ClearImage();
	}
}

void menu_finish(menu_t *menu) {
	menu_event_save();
	status.menu_running = FALSE;
}

int menu_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {
	button_t button;

	debug_log("r0: %08X", dialog);
	debug_log("r1: %08X", r1);
	debug_log("r2: %08X", event);
	debug_log("r3: %08X", r3);
	debug_log("r4: %08X", r4);
	debug_log("r5: %08X", r6);
	debug_log("r6: %08X", r6);
	debug_log("r7: %08X", code);

	switch (event) {
	case GUI_BUTTON_MENU            : button = BUTTON_MENU;     break;
	case GUI_BUTTON_DISP            : button = BUTTON_DISP;     break;
	case GUI_BUTTON_JUMP            : button = BUTTON_JUMP;     break;
	case GUI_BUTTON_PLAY            : button = BUTTON_PLAY;     break;
	case GUI_BUTTON_TRASH           : button = BUTTON_TRASH;    break;
	case GUI_BUTTON_UP              : button = BUTTON_UP;       break;
	case GUI_BUTTON_DOWN            : button = BUTTON_DOWN;     break;
	case GUI_BUTTON_ZOOM_OUT_PRESS  : button = BUTTON_ZOOM_OUT; break;
	case GUI_BUTTON_ZOOM_IN_PRESS   : button = BUTTON_ZOOM_IN;  break;
	default:
		goto pass_event;
	}

	if (button_handler(button, TRUE))
		return FALSE;

pass_event:
	return dialog_event_handler(dialog, r1, event, r3, r4, r5, r6, code);
}

void menu_return(menu_t *menu) {
	menu_set_page(get_selected_page());
}

void menu_set_posn(int posn) {
	current_menu->current_posn = posn;

	if (current_menu->ordering)
		menu_set_page(current_menu->pages.data[current_menu->ordering[posn]]);
	else
		menu_set_page(current_menu->pages.data[posn]);
}

void menu_set_page(menupage_t *page) {
	current_menu->current_page = page;

	menupage_initialize(page);

	menu_event_open();
	menu_event_display();
}

void menu_highlight(const int line) {
	GUI_Select_Item  (menu_handler, line + 1);
	GUI_Highlight_Sub(menu_handler, line + 1, FALSE);

	menu_redraw();
}

void menu_redraw() {
	dialog_redraw(menu_handler);
}

void menu_set_text(const int line, const char *text) {
	dialog_set_property_str(menu_handler, line + 1, text);
}

void menu_event_menu()   { menu_event(MENU_EVENT_MENU);    };
void menu_event_disp()   { menu_event(MENU_EVENT_DISP);    };
void menu_event_jump()   { menu_event(MENU_EVENT_JUMP);    };
void menu_event_play()   { menu_event(MENU_EVENT_PLAY);    };
void menu_event_trash()  { menu_event(MENU_EVENT_TRASH);   };
void menu_event_set()    { menu_event(MENU_EVENT_SET);     };
void menu_event_prev()   { menu_event(MENU_EVENT_PREV);    };
void menu_event_next()   { menu_event(MENU_EVENT_NEXT);    };
void menu_event_up()     { menu_event(MENU_EVENT_UP);      };
void menu_event_down()   { menu_event(MENU_EVENT_DOWN);    };
void menu_event_right()  { menu_event(MENU_EVENT_RIGHT);   };
void menu_event_left()   { menu_event(MENU_EVENT_LEFT);    };
void menu_event_dp()     { menu_event(MENU_EVENT_DP);      };
void menu_event_av()     { menu_event(MENU_EVENT_AV);      };
void menu_event_av_up()  { menu_event(MENU_EVENT_AV_UP);   };
void menu_event_out()    { menu_event(MENU_EVENT_OUT);     };
void menu_event_in()     { menu_event(MENU_EVENT_IN);      };
void menu_event_open()   { menu_event(MENU_EVENT_OPEN);    };
void menu_event_display(){ menu_event(MENU_EVENT_DISPLAY); };
void menu_event_refresh(){ menu_event(MENU_EVENT_REFRESH); };
void menu_event_finish() { menu_event(MENU_EVENT_FINISH);  };
void menu_event_save()   { menu_event(MENU_EVENT_SAVE);    };

void menu_event(menu_event_t event) {
	menu_t     *menu = current_menu;
	menupage_t *page = menu->current_page;

	if (page->actions && page->actions[event])
		page->actions[event](menu);
	else if (menu->actions && menu->actions[event])
		menu->actions[event](menu);
}

void menu_set(menu_t *menu) {
	menupage_t *page = menu->current_page;
	menuitem_t *item = get_current_item(page);

	if (item && item->action)
		item->action(item);
}

void menu_right(menu_t *menu) {
	menu_repeat(menu, menu_repeat_right);
}

void menu_left(menu_t *menu) {
	menu_repeat(menu, menu_repeat_left);
}

void menu_next(menu_t *menu) {
	menupage_t *page = menu->current_page;

	if (page->sibilings) {
		if (menu->current_posn == menu->pages.size - 1)
			menu->current_posn = 0;
		else
			menu->current_posn++;

		menu_return(menu);
	}
}

void menu_prev(menu_t *menu) {
	menupage_t *page = menu->current_page;

	if (page->sibilings) {
		if (menu->current_posn == 0)
			menu->current_posn = menu->pages.size - 1;
		else
			menu->current_posn--;

		menu_return(menu);
	}
}

void menu_repeat(menu_t *menu, void (*action)(menu_t *menu, const int repeating)){
	int delay;
	int button = status.button_down;

	SleepTask(AUTOREPEAT_DELAY_UNIT);

	action(menu, FALSE);
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			action(menu, TRUE);
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void menu_repeat_right(menu_t *menu, const int repeating) {
	menupage_t *page = menu->current_page;
	menuitem_t *item = get_current_item(page);

	if (item && !item->readonly && item->inc) {
		item->inc(item, repeating);

		if (item->change)
			item->change(item);

		menu->changed = TRUE;
		menu_event_refresh();
	}
}

void menu_repeat_left(menu_t *menu, const int repeating) {
	menupage_t *page = menu->current_page;
	menuitem_t *item = get_current_item(page);

	if (item && !item->readonly && item->dec) {
		item->dec(item, repeating);

		if (item->change)
			item->change(item);

		menu->changed = TRUE;
		menu_event_refresh();
	}
}

menupage_t *get_selected_page() {
	if (current_menu->ordering)
		return current_menu->pages.data[current_menu->ordering[current_menu->current_posn]];
	else
		return current_menu->pages.data[current_menu->current_posn];
}
