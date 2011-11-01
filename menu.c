#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menupage.h"
#include "menuitem.h"
#include "presets.h"
#include "utils.h"

#include "menu.h"

type_CAMERA_MODE menu_cameraMode;

void *menu_handler;
int   item_grabbed;

type_MENU     *current_menu;
type_MENUPAGE *current_page;

type_ACTION callbacks_standard[] = {
	{GUI_BUTTON_MENU,           FALSE, TRUE,  {menu_event_menu}},
	{GUI_BUTTON_DISP,           FALSE, FALSE, {menu_event_disp}},
	{GUI_BUTTON_JUMP,           FALSE, TRUE,  {menu_event_jump}},
	{GUI_BUTTON_PLAY,           FALSE, TRUE,  {menu_event_play}},
	{GUI_BUTTON_TRASH,          FALSE, TRUE,  {menu_event_trash}},
	{GUI_BUTTON_UP,             FALSE, TRUE,  {menu_event_up}},
	{GUI_BUTTON_DOWN,           FALSE, TRUE,  {menu_event_down}},
	{GUI_BUTTON_ZOOM_OUT_PRESS, FALSE, TRUE,  {menu_event_out}},
	{GUI_BUTTON_ZOOM_IN_PRESS,  FALSE, TRUE,  {menu_event_in}},
	END_OF_LIST
};

void menu_initialize();
void menu_destroy();

int menu_event_handler(type_DIALOG * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

void menu_set_page(type_MENUPAGE *page);
void menu_set_text(const int line, const char *text);

void menu_highlight(const int line);

void menu_repeat(void (*action)(const int repeating));

void menu_repeat_right(const int repeating);
void menu_repeat_left (const int repeating);

type_MENUPAGE *get_current_page();

int get_item_id(int item_pos);
int get_real_id(int item_pos);

void menu_create(type_MENU * menu) {
	current_menu = menu;
	FLAG_GUI_MODE = GUIMODE_400PLUS;

	menu_destroy();
	menu_initialize();

	GUI_Lock();
	GUI_PalleteInit();

	menu_handler = dialog_create(22, menu_event_handler);
	PalettePush();

	PaletteChange(current_menu->color);

	menu_display();

	GUI_UnLock();
	GUI_PalleteUnInit();
}

void menu_close() {
	// press_button(IC_BUTTON_DISP);
	menu_destroy();
}

void menu_initialize() {
	menu_handler = NULL;
	current_page = get_current_page();
	item_grabbed = FALSE;
}

void menu_destroy() {
	if (menu_handler != NULL) {
		PalettePop();
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
		GUI_ClearImage();
	}
}

int menu_event_handler(type_DIALOG * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {
	int ret;
	type_ACTION *action;

// FW:FF915990 
// this seems to be one of the addresses where the handler is called

// standard menu 55-63
#ifdef ENABLE_DEBUG
	printf_log(1,6, "_BTN_ [%s][guimode:%08X]", debug_btn_name(event), FLAG_GUI_MODE);
	printf_log(1,6, "_BTN_: r1=[%08X], r3=[%08X], handler=[%08X]", *r1, *r3, *(int*)((int)dialog+0x7C) );
	printf_log(1,6, "_BTN_: r4=[%08X], r5=[%08X], r6=[%08X]", r4, r5, r6);
#endif

	*(int*)((int)dialog + 0x90) = 1;

	// Loop over all the actions from this action chain
	for (action = callbacks_standard; ! IS_EOL(action); action++) {

		// Check whether this action corresponds to the event received
		if (action->button == event) {

			// Launch the defined task
			if (action->task[0])
				action->task[0]();

			// Decide how to respond to this button
			if (action->block)
				return FALSE;
			else
				goto pass_event;
		}
	}

pass_event:
	ret = InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
#ifdef ENABLE_DEBUG
	printf_log(1,6, "_BTN_ after: r1=[%08X], r3=[%08X]", *r1, *r3);
#endif
	return ret;
}

void menu_display() {
	if (current_page->display)
		current_page->display(current_page);
	else
		menupage_display(current_page);
}

void menu_refresh() {
	if (current_page->refresh)
		current_page->refresh(current_page);
	else
		menupage_refresh(current_page);
}

void menu_return() {
	menu_set_page(get_current_page());
}

void menu_set_page(type_MENUPAGE *page) {
	current_page = page;

	item_grabbed = FALSE;

	menu_display();
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

void menu_event_menu()   { menu_event(MENU_EVENT_MENU);   };
void menu_event_disp()   { menu_event(MENU_EVENT_DISP);   };
void menu_event_jump()   { menu_event(MENU_EVENT_JUMP);   };
void menu_event_play()   { menu_event(MENU_EVENT_PLAY);   };
void menu_event_trash()  { menu_event(MENU_EVENT_TRASH);  };
void menu_event_set()    { menu_event(MENU_EVENT_SET);    };
void menu_event_prev()   { menu_event(MENU_EVENT_PREV);   };
void menu_event_next()   { menu_event(MENU_EVENT_NEXT);   };
void menu_event_up()     { menu_event(MENU_EVENT_UP);     };
void menu_event_down()   { menu_event(MENU_EVENT_DOWN);   };
void menu_event_right()  { menu_event(MENU_EVENT_RIGHT);  };
void menu_event_left()   { menu_event(MENU_EVENT_LEFT);   };
void menu_event_dp()     { menu_event(MENU_EVENT_DP);     };
void menu_event_av()     { menu_event(MENU_EVENT_AV);     };
void menu_event_av_up()  { menu_event(MENU_EVENT_AV_UP);  };
void menu_event_out()    { menu_event(MENU_EVENT_OUT);    };
void menu_event_in()     { menu_event(MENU_EVENT_IN);     };
void menu_event_open()   { menu_event(MENU_EVENT_OPEN);   };
void menu_event_change() { menu_event(MENU_EVENT_CHANGE); };
void menu_event_close()  { menu_event(MENU_EVENT_CLOSE);  };

void menu_event(type_MENU_EVENT event) {
	type_MENUITEM *item = get_current_item(current_page);

	if (item && item->tasks && item->tasks[event])
		item->tasks[event](item);

	if (current_page->tasks && current_page->tasks[event])
		current_page->tasks[event](current_page);
	else if (current_menu->tasks && current_menu->tasks[event])
		current_menu->tasks[event](current_menu);
}

void menu_up(type_MENU *menu) {
	int display = FALSE;

	if (current_page->length > MENU_HEIGHT || current_page->current_posn > 0) {
		current_page->current_posn--;

		if (item_grabbed) {
			INT_SWAP(current_page->ordering[get_item_id(current_page->current_posn)], current_page->ordering[get_item_id(current_page->current_posn + 1)]);
			display = TRUE;
		}
	}

	if (current_page->current_line > 0) {
		current_page->current_line--;
		menu_highlight(current_page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_display();
}

void menu_down(type_MENU *menu) {
	const int height = MIN(MENU_HEIGHT, current_page->length) - 1;
	int display = FALSE;

	if (current_page->length > MENU_HEIGHT || current_page->current_posn < height) {
		current_page->current_posn++;

		if (item_grabbed) {
			INT_SWAP(current_page->ordering[get_item_id(current_page->current_posn)], current_page->ordering[get_item_id(current_page->current_posn - 1)]);
			display = TRUE;
		}
	}

	if (current_page->current_line < height) {
		current_page->current_line++;
		menu_highlight(current_page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_display();
}

void menu_right(type_MENU *menu) {
	menu_repeat(menu_repeat_right);
}

void menu_left(type_MENU *menu) {
	menu_repeat(menu_repeat_left);
}

void menu_drag_drop(type_MENU *menu) {
	if (current_page->ordering) {
		item_grabbed = ! item_grabbed;
		menu_event_change();
		menu_refresh();
	}
}

void menu_page_next(type_MENU *menu) {
	if (current_page->sibilings) {
		if (current_menu->current_posn == current_menu->length - 1)
			current_menu->current_posn = 0;
		else
			current_menu->current_posn++;

		menu_return();
	}
}

void menu_page_prev(type_MENU *menu) {
	if (current_page->sibilings) {
		if (current_menu->current_posn == 0)
			current_menu->current_posn = current_menu->length - 1;
		else
			current_menu->current_posn--;

		menu_return();
	}
}

void menu_repeat(void (*action)(const int repeating)){
	int delay;
	int button = status.button_down;

	SleepTask(50);

	action(FALSE);
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			action(TRUE);
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void menu_repeat_right(const int repeating) {
	const type_MENUITEM *item = get_current_item(current_page);

	if (item && !item->readonly && item->right) {
		item->right(item, repeating);

		menu_event_change();
		menu_refresh();
	}
}

void menu_repeat_left(const int repeating) {
	const type_MENUITEM *item = get_current_item(current_page);

	if (item && !item->readonly && item->left) {
		item->left(item, repeating);

		menu_event_change();
		menu_refresh();
	}
}

type_MENUPAGE *get_current_page() {
	if (current_menu->ordering)
		return current_menu->pages[current_menu->ordering[current_menu->current_posn]];
	else
		return current_menu->pages[current_menu->current_posn];
}

int get_real_id(int item_pos) {
	if (current_page->ordering)
		return current_page->ordering[get_item_id(item_pos)];
	else
		return get_item_id(item_pos);
}

int get_item_id(int item_pos) {
	const int max_pos = MAX(current_page->length, MENU_HEIGHT);
	const int item_id = item_pos - max_pos * (item_pos / max_pos);

	return (item_id < 0) ? (item_id + max_pos) : item_id;
}
