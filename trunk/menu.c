#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menupage.h"
#include "menuitem.h"
#include "presets.h"
#include "utils.h"
#include "debug.h"

#include "menu.h"

type_CAMERA_MODE menu_cameraMode;

void *menu_handler;

type_MENU     *current_menu;

type_ACTION callbacks_standard[] = {
	{GUI_BUTTON_MENU,           FALSE, TRUE,  {menu_event_menu}},
	{GUI_BUTTON_DISP,           FALSE, TRUE,  {menu_event_disp}},
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

int menu_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

void menu_set_page(type_MENUPAGE *page);
void menu_set_text(const int line, const char *text);

void menu_highlight(const int line);

void menu_repeat(type_MENU *menu, void (*action)(type_MENU *menu, const int repeating));

void menu_repeat_right(type_MENU *menu, const int repeating);
void menu_repeat_left (type_MENU *menu, const int repeating);

type_MENUPAGE *get_selected_page();

int my_central_handler(dialog_t *dialog, int event, int r2, int r3) {
	debug_log("CENTRAL!");
	debug_log("central: dlg:0x%08X, ev:0x%08X, r2:0x%08X, r3:0x%08X", dialog, event, r2, r3);
	return DIALOGHandler(dialog, event, r2, r3);
}

void menu_create(type_MENU *menu) {
	beep();

	//GUI_Command(4,0);
	//press_button(IC_BUTTON_MENU);
	SendToMC(6, 2, 0);
	SleepTask(100);

	status.menu_running = TRUE;
	FLAG_GUI_MODE = 0x2D; // Just a temporary value solution
	//cameraMode->gui_mode = 0x2D; // this is not the same as FLAG_GUI_MODE, but so far i do not see what it does

	current_menu    = menu;
	menu_cameraMode = *cameraMode;

	menu_destroy();
	menu_initialize();

	GUI_Lock();
	GUI_PalleteInit();

	menu_handler = dialog_create(22, menu_event_handler);
	//*(int*)((int)(menu_handler+0x58)) = (int)my_central_handler;
	//*(int*)((int)(menu_handler+0x7C)) = (int)menu_event_handler;

	PalettePush();
	PaletteChange(current_menu->color);

	menu_event_display();

	GUI_UnLock();
	GUI_PalleteUnInit();
}

void menu_close() {
    GUI_Lock();
    GUI_PalleteInit();

	DeleteDialogBox(menu_handler);
	menu_handler = NULL;

	GUI_StartMode(GUIMODE_OLC);
    CreateDialogBox_OlMain();
    GUIMode = GUIMODE_OLC;

    GUI_UnLock();
    GUI_PalleteUnInit();
}

void menu_initialize() {
	menu_handler = NULL;
	menu_set_page(get_selected_page());
}

void menu_destroy() {
	if (menu_handler != NULL) {
		PalettePop();
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
		GUI_ClearImage();
	}
}

int menu_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {
	int ret;
	type_ACTION *action;

// FW:FF915990
// this seems to be one of the addresses where the handler is called

// standard menu 55-63
#ifdef ENABLE_DEBUG
	// print the dialog structure and diff the both cases of menu creation
	debug_log("_BTN_ [%s][guimode:%08X]", debug_btn_name(event), FLAG_GUI_MODE);
	//debug_log("_BTN_: 84=[%08X] 88=[%08X]", GET_FROM_MEM(menu_handler+0x84), GET_FROM_MEM(menu_handler+0x88) );
	//debug_log("_BTN_: r1=[%08X], r3=[%08X], 90=[%08X]", *r1, *r3, /* *(int*) */(*(int*)((int)dialog+0x90)) );
	//debug_log("_BTN_: r4=[%08X], r5=[%08X], r6=[%08X]", r4, r5, r6);
#endif

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

void menu_return() {
	menu_set_page(get_selected_page());
}

void menu_set_posn(int posn) {
	current_menu->current_posn = posn;

	if (current_menu->ordering)
		menu_set_page(current_menu->pages[current_menu->ordering[posn]]);
	else
		menu_set_page(current_menu->pages[posn]);
}

void menu_set_page(type_MENUPAGE *page) {
	current_menu->current_page = page;

	menupage_initialize(page);
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
void menu_event_close()  { menu_event(MENU_EVENT_CLOSE);   };

void menu_event(type_MENU_EVENT event) {
	type_MENU     *menu = current_menu;
	type_MENUPAGE *page = menu->current_page;

	if (page->tasks && page->tasks[event])
		page->tasks[event](menu);
	else if (menu->tasks && menu->tasks[event])
		menu->tasks[event](menu);
}

void menu_set(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;
	type_MENUITEM *item = get_current_item(page);

	if (item && item->action)
		item->action(item);
}

void menu_right(type_MENU *menu) {
	menu_repeat(menu, menu_repeat_right);
}

void menu_left(type_MENU *menu) {
	menu_repeat(menu, menu_repeat_left);
}

void menu_next(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	if (page->sibilings) {
		do {
			if (menu->current_posn == menu->length - 1)
				menu->current_posn = 0;
			else
				menu->current_posn++;

			page = get_selected_page();
		} while (!menupage_active(page));

		menu_set_page(page);
	}
}

void menu_prev(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	if (page->sibilings) {
		do {
			if (menu->current_posn == 0)
				menu->current_posn = menu->length - 1;
			else
				menu->current_posn--;
			page = get_selected_page();
		} while (!menupage_active(page));

		menu_set_page(page);
	}
}

void menu_repeat(type_MENU *menu, void (*action)(type_MENU *menu, const int repeating)){
	int delay;
	int button = status.button_down;

	SleepTask(50);

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

void menu_repeat_right(type_MENU *menu, const int repeating) {
	type_MENUPAGE *page = menu->current_page;
	type_MENUITEM *item = get_current_item(page);

	if (item && !item->readonly && item->inc) {
		item->inc(item, repeating);

		if (item->change)
			item->change(item);

		menu->changed = TRUE;
		menu_event_refresh();
	}
}

void menu_repeat_left(type_MENU *menu, const int repeating) {
	type_MENUPAGE *page = menu->current_page;
	type_MENUITEM *item = get_current_item(page);

	if (item && !item->readonly && item->dec) {
		item->dec(item, repeating);

		if (item->change)
			item->change(item);

		menu->changed = TRUE;
		menu_event_refresh();
	}
}

type_MENUPAGE *get_selected_page() {
	if (current_menu->ordering)
		return current_menu->pages[current_menu->ordering[current_menu->current_posn]];
	else
		return current_menu->pages[current_menu->current_posn];
}
