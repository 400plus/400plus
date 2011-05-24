#include "main.h"
#include "utils.h"
#include "display.h"
#include "languages.h"
#include "menu_rename.h"
#include "firmware.h"
#include "debug.h"

#include "menu.h"

char menu_buffer[32];

type_MENU * current_menu;
type_MENU * last_menu; // used to save the current_menu while in rename dialog

OPTIONLIST_DEF(bool,    LP_WORD(L_NO), LP_WORD(L_YES))
OPTIONLIST_DEF(delay,   LP_WORD(L_NO), LP_WORD(L_2S))
OPTIONLIST_DEF(flash,   LP_WORD(L_ENABLED), LP_WORD(L_DISABLED), LP_WORD(L_EXT_ONLY))
OPTIONLIST_DEF(action,  LP_WORD(L_ONE_SHOT), LP_WORD(L_EXT_AEB), LP_WORD(L_INTERVAL))
OPTIONLIST_DEF(shutter, "16'", "8'", "4'", "2'", "1'", "30\"", "15\"", "8\"", "4\"", "2\"", "1\"", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000")

// Menu actions
type_ACTION actions_400plus[]  = {
	{GUI_BUTTON_UP,         TRUE,  RESP_RELEASE, {menu_up}},
	{GUI_BUTTON_DOWN,       TRUE,  RESP_RELEASE, {menu_down}},
	{GUI_BUTTON_RIGHT,      TRUE,  RESP_BLOCK,   {menu_right}},
	{GUI_BUTTON_LEFT,       TRUE,  RESP_BLOCK,   {menu_left}},
	//{GUI_BUTTON_AV,         TRUE,  RESP_BLOCK,   {menu_cycle}},
	{GUI_BUTTON_SET,        FALSE, RESP_BLOCK,   {menu_action}},
	{GUI_BUTTON_DP,         FALSE, RESP_BLOCK,   {menu_dp_action}},
	{GUI_BUTTON_MENU,       FALSE, RESP_BLOCK,   {menu_drag_drop}},
	{GUI_BUTTON_DIAL_LEFT,  FALSE, RESP_BLOCK,   {menu_submenu_prev}},
	{GUI_BUTTON_DIAL_RIGHT, FALSE, RESP_BLOCK,   {menu_submenu_next}},
	END_OF_LIST
};

type_ACTION actions_rename[]  = {
	{GUI_BUTTON_UP,         TRUE,  RESP_RELEASE, {rename_up}},
	{GUI_BUTTON_DOWN,       TRUE,  RESP_RELEASE, {rename_down}},
	{GUI_BUTTON_RIGHT,      TRUE,  RESP_BLOCK,   {rename_right}},
	{GUI_BUTTON_LEFT,       TRUE,  RESP_BLOCK,   {rename_left}},
	//{GUI_BUTTON_AV,         TRUE,  RESP_BLOCK,   {rename_cycle}},
	{GUI_BUTTON_SET,        FALSE, RESP_BLOCK,   {rename_action}},
	{GUI_BUTTON_DIAL_LEFT,  FALSE, RESP_BLOCK,   {rename_prev}},
	{GUI_BUTTON_DIAL_RIGHT, FALSE, RESP_BLOCK,   {rename_next}},
	END_OF_LIST
};

type_CHAIN menu_chains[] = {
	{MENU_400PLUS,  actions_400plus},
	{MENU_RENAME,   actions_rename},
	END_OF_LIST
};





void menu_repeat(void (*repeateable)(int repeating));

void menu_repeateable_cycle(int repeating);
void menu_repeateable_right(int repeating);
void menu_repeateable_left (int repeating);

void menu_display();
void menu_refresh();

char *menu_message(int item_id);

void menu_print_ev   (char *buffer, char *name, int   parameter);
void menu_print_iso  (char *buffer, char *name, int   parameter);
void menu_print_int  (char *buffer, char *name, int   parameter, char *format);
void menu_print_char (char *buffer, char *name, char *parameter);

type_MENUITEM *get_current_item();
type_MENUITEM *get_item(int item_id);

/** Menu buttons handler */
int menu_buttons_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code) {
	type_CHAIN  *chain;
	type_ACTION *action;

	// The SET btn comes in "code" and the current line in the menu is in "event".
	// Switch them for easier processing.
	if (code == GUI_BUTTON_SET)
		INT_SWAP(code, event);

	static char e_str[64], c_str[64];
	gui_event_name(e_str, event);
	gui_event_name(c_str, code);
	debug_printf("dialog=%p, type=%d, btn=[%s], code=[%s], R[1=%02X,3=%02X,4=%02X,5=%02X,6=%02X]\n",
			dialog, current_menu->type, e_str, c_str,
			r1, r3, r4, r5, r6);

	// there are 2 events comming to the handler upon creating the dialog:
	// 1. event:0x802, code:0x00
	// 2. event:0x800, code:0x4E20
	// they will get trapped by the next if, because we do not have current_menu yet.
	if (!current_menu || current_menu->handle != dialog || current_menu->type < 1) {
		//debug_printf("\n\nmenu_buttons_handler: cm->handle(%p) != dialog(%p) || cm->type < 1\n\n",
		//		current_menu ? current_menu->handle : 0, dialog);
		goto fallback;
	}

	// Loop over all the action chains
	for(chain = menu_chains; ! IS_EOL(chain); chain++) {
		// Check whether this action chain corresponds to the current menu type
		if (chain->type == current_menu->type) {
			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {
				// Check whether this action corresponds to the event received
				if (action->button == event) {
					// Launch the defined task
					if (action->task[0])
						ENQUEUE_TASK(action->task[0])
					else
						debug_printf("no task defined for menu_type=%d and btn:[%s]\n",
								current_menu->type, e_str);

					if (event == GUI_BUTTON_UP || event == GUI_BUTTON_DOWN)
						goto fallback;

					goto handled;
				}
			}
		}
	}

// on 1000003E
// BL      GUI_Lock
// BL      GUI_PalleteInit
// BL      sub_FF85F51C
// BL      GUI_UnLock
// BL      GUI_PalleteUnInit

	switch (event) {
	case GUI_BUTTON_CF_CARD:
		menu_close();
		break;
	// we use the DISP button to close the menu
	case GUI_BUTTON_DISP:
		menu_close();
		// when closing with DISP, we need to press it one more time.
		press_button(IC_BUTTON_DISP);
		goto handled;

	// someone else will take care of those
	case GUI_GOT_TOP_OF_CONTROL:
	case GUI_LOST_TOP_OF_CONTROL:
	case GUI_INITIALIZE_CONTROLLER:
	case GUI_UNKNOWN0:
		goto fallback;

	// these we block, so no one will interfare with our menus
	case GUI_BUTTON_DP:
	case GUI_BUTTON_UP:
	case GUI_BUTTON_DOWN:
	case GUI_BUTTON_LEFT:
	case GUI_BUTTON_RIGHT:
	case GUI_BUTTON_SET:
	case GUI_BUTTON_PLAY:
	case GUI_BUTTON_JUMP:
	case GUI_BUTTON_MENU:
	case GUI_BUTTON_TRASH:
	case GUI_BUTTON_DRIVE:
	case GUI_BUTTON_DIAL_LEFT:
	case GUI_BUTTON_DIAL_RIGHT:
	case GUI_BUTTON_ZOOM_IN_PRESS:
	case GUI_BUTTON_ZOOM_IN_RELEASE:
	case GUI_BUTTON_ZOOM_OUT_PRESS:
	case GUI_BUTTON_ZOOM_OUT_RELEASE:
	case GUI_UNKNOWN1:
	case GUI_UNKNOWN2:
		debug_printf("not handled but would block\n");
		goto handled;

	}

	// flash the blue led and log the event if we do not handle it.
	led_flash(BEEP_LED_LENGTH); // used for debugging
	debug_printf("!!!!!!!!!! unhandled event !!!!!!!!!!\n");

fallback:
	// reverse them back if we need to pass this event to the next handler().
	if (event == GUI_BUTTON_SET)
		INT_SWAP(code, event);
	debug_printf("passing to fallback\n");
	return 1;

handled:
	debug_printf("handled -> blocking\n");
	return 0;
}

void menu_destroy_fast(type_MENU * menu) {
	if (!menu)
		return;

	debug_printf("\ndestroying_fast menu [type:%d]@0x%08X\n", menu->type, menu->handle);
	if (menu->handle)
		DeleteDialogBox(menu->handle);

	menu->handle = 0;
	menu->current_line = 0;
	menu->current_item = 0;
	menu->item_grabbed = FALSE;
	menu = 0;
}

void menu_destroy_start_olc(type_MENU * menu) {
	// GUI_DisplayMode();
	GUI_Lock();
	GUI_PalleteInit();
	// PalettePop();
	// with_check_ae_mode();

	debug_printf("\ndestroying menu [type:%d]@0x%08X and starting OLC\n", menu->type, menu->handle);
	menu_destroy_fast(menu);

	// start the main screen
	GUI_StartMode(GUIMODE_OLC);
	CreateDialogBox_OlMain();
	GUIMode = GUIMODE_OLC;

	GUI_UnLock();
	GUI_PalleteUnInit();
}

void menu_create(type_MENU * menu) {
	GUI_Lock();
	GUI_PalleteInit();

	last_menu = current_menu; // save the current menu to last used menu

	// destroy the current menu if there is one
	// no destroying it = memory leak !
	menu_destroy_fast(current_menu);

	current_menu = menu;

	GUI_StartMode(GUIMODE_400PLUS);
	GUI_ClearImage();
	GUIMode = GUIMODE_400PLUS;

	if (!current_menu->btn_handler)
		current_menu->btn_handler = menu_buttons_handler; // default
	current_menu->handle = dialog_create(22, current_menu->btn_handler);
	debug_printf("\nnew menu [%d] created @0x%08X\n", current_menu->type, current_menu->handle);

	//PalettePush();
	dialog_set_property_str(current_menu->handle, 8, current_menu->name);
	PaletteChange(current_menu->color);

	if (current_menu->type != MENU_RENAME)
		menu_display();

	GUI_UnLock();
	GUI_PalleteUnInit();
	GUI_ClearImage();
	SetTurnDisplayEvent_1_after_2(); // turn on the screen
	//SetTurnDisplayEvent_2_after_1(); // turn off the screen
}

type_MENU * menu_get_current() {
	return current_menu;
}

void menu_create_last() {
	menu_create(last_menu);
}

void menu_display() {
	int i;
	int offset = current_menu->current_item > current_menu->current_line ?
		current_menu->current_item - current_menu->current_line : 0;

	for(i = 0; i < 5; i++)
		dialog_set_property_str(current_menu->handle, i + 1, menu_message(i + offset));

	dialog_redraw(current_menu->handle);
}

void menu_refresh() {
	dialog_set_property_str(current_menu->handle, current_menu->current_line + 1, menu_message(current_menu->current_item));
	dialog_redraw(current_menu->handle);
}

void menu_up() {
	int display = FALSE;

	if (current_menu->current_item != 0) {
		current_menu->current_item--;

		if (current_menu->item_grabbed) {
			INT_SWAP(current_menu->ordering[current_menu->current_item],
					current_menu->ordering[current_menu->current_item + 1]);
			display = TRUE;
		}
	}

	if (current_menu->current_line != 0)
		current_menu->current_line--;
	else
		display = TRUE;

	if (display)
		menu_display();
}

void menu_down() {
	int display = FALSE;

	if (current_menu->current_item != current_menu->length - 1) {
		current_menu->current_item++;

		if (current_menu->item_grabbed) {
			INT_SWAP(current_menu->ordering[current_menu->current_item],
					current_menu->ordering[current_menu->current_item - 1]);
			display = TRUE;
		}
	}

	if (current_menu->current_line != 4)
		current_menu->current_line++;
	else
		display = TRUE;

	if (display)
		menu_display();
}

void menu_right() {
	menu_repeat(menu_repeateable_right);
}

void menu_left() {
	menu_repeat(menu_repeateable_left);
}

void menu_cycle() {
	menu_repeat(menu_repeateable_cycle);
}

void menu_action() {
	int close;
	type_TASK action;
	type_MENUITEM *item = get_current_item();

	if (current_menu->rename && current_menu->item_grabbed) {
		rename_prepare(item->name, current_menu->callback);
		rename_create();
	} else {
		if (item->type == MENUITEM_TYPE_LAUNCH) {
			close  = item->menuitem_launch.close;
			action = item->menuitem_launch.action;
		} else {
			close  = FALSE;
			action = current_menu->action;
		}

		if (action) {
			if (close) {
				menu_close();
				ENQUEUE_TASK(action);
			} else {
				action();
			}
		}
	}
}

void menu_dp_action() {
	if (current_menu->dp_action) {
		current_menu->dp_action();
	}
}

void menu_drag_drop() {
	if (current_menu->reorder) {
		current_menu->item_grabbed = ! current_menu->item_grabbed;
		menu_refresh();
	}
}

void menu_submenu_next() {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		if (item->menuitem_submenu.current_item == item->menuitem_submenu.length - 1)
			item->menuitem_submenu.current_item = 0;
		else
			item->menuitem_submenu.current_item++;

		menu_refresh();
	}
}

void menu_submenu_prev() {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		if (item->menuitem_submenu.current_item == 0)
			item->menuitem_submenu.current_item = item->menuitem_submenu.length - 1;
		else
			item->menuitem_submenu.current_item--;

		menu_refresh();
	}
}

void menu_repeat(void(*repeateable)()){
	int delay;
	int button = status.button_down;

	SleepTask(50);

	repeateable(FALSE);
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			repeateable(TRUE);
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void menu_repeateable_right(int repeating) {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU)
		item = &item->menuitem_submenu.items[item->menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		*item->menuitem_ev.value = ev_inc(*item->menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->menuitem_iso.value = iso_inc(*item->menuitem_iso.value);
		else
			*item->menuitem_iso.value = iso_next(*item->menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		if (!item->menuitem_int.readonly) {
			*item->menuitem_int.value += repeating ? item->menuitem_int.big_step : item->menuitem_int.small_step;
			*item->menuitem_int.value  = MIN(*item->menuitem_int.value, item->menuitem_int.max);
		}
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->menuitem_enum.value == item->menuitem_enum.list->length - 1) {
			if (item->menuitem_enum.cycle)
				*item->menuitem_enum.value = 0;
		} else
			(*item->menuitem_enum.value)++;
		break;
	default:
		break;
	}

	menu_refresh();
}

void menu_repeateable_left(int repeating) {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU)
		item = &item->menuitem_submenu.items[item->menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->menuitem_ev.zero_means_off && *item->menuitem_ev.value < 0x05)
				*item->menuitem_ev.value = 0x00;
		else
			*item->menuitem_ev.value = ev_dec(*item->menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->menuitem_iso.value = iso_dec(*item->menuitem_iso.value);
		else
			*item->menuitem_iso.value = iso_prev(*item->menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		if (!item->menuitem_int.readonly) {
			*item->menuitem_int.value -= repeating ? item->menuitem_int.big_step : item->menuitem_int.small_step;
			*item->menuitem_int.value  = MAX(*item->menuitem_int.value, item->menuitem_int.min);
		}
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->menuitem_enum.value == 0) {
			if (item->menuitem_enum.cycle)
				*item->menuitem_enum.value = item->menuitem_enum.list->length - 1;
		} else
			*item->menuitem_enum.value -= 1;
		break;
	default:
		break;
	}

	menu_refresh();
}

void menu_repeateable_cycle(int repeating) {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU)
		item = &item->menuitem_submenu.items[item->menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (!item->menuitem_ev.zero_means_off)
			*item->menuitem_ev.value = ev_sgn(*item->menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->menuitem_iso.value = iso_inc(*item->menuitem_iso.value);
		else
			*item->menuitem_iso.value = iso_next(*item->menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		*item->menuitem_int.value += repeating ? item->menuitem_int.big_step : item->menuitem_int.small_step;
		*item->menuitem_int.value  = MIN(*item->menuitem_int.value, item->menuitem_int.max);
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->menuitem_enum.value == item->menuitem_enum.list->length - 1)
			*item->menuitem_enum.value = 0;
		else
			*item->menuitem_enum.value += 1;
		break;
	default:
		break;
	}

	menu_refresh();
}

void menu_close() {
	debug_printf("\nclosing current menu and starting OLC\n");
	menu_destroy_start_olc(current_menu);

	//SetTurnDisplayEvent_2_after_1();
	//press_button(IC_BUTTON_DISP);
	//SleepTask(250);

	//display_refresh();
}

char *menu_message(int item_id) {
	char name[32];

	type_MENUITEM *item = get_item(item_id);

	if (current_menu->reorder) {
		sprintf(name, "%c%s",
			(current_menu->item_grabbed && item_id == current_menu->current_item) ? '>' : ' ',
			item->name);
	} else
		sprintf(name, "%s", item->name);

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		item = &item->menuitem_submenu.items[item->menuitem_submenu.current_item];
		sprintf(name + strlen(name), ">%s", item->name);
	}

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->menuitem_ev.zero_means_off && *item->menuitem_ev.value == 0)
			menu_print_char(menu_buffer, name, LP_WORD(L_OFF));
		else
			menu_print_ev(menu_buffer, name, *item->menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		menu_print_iso(menu_buffer, name, *item->menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		if (item->menuitem_int.zero_means_unlimited && *item->menuitem_int.value == 0)
			menu_print_char(menu_buffer, name, LP_WORD(L_NO_LIMIT));
		else
			menu_print_int(menu_buffer, name, *item->menuitem_int.value, item->menuitem_int.format);
		break;
	case MENUITEM_TYPE_ENUM:
		menu_print_char(menu_buffer, name, item->menuitem_enum.list->data[*item->menuitem_enum.value]);
		break;
	case MENUITEM_TYPE_LAUNCH:
		sprintf(menu_buffer, "%s", name);
		break;
	default:
		break;
	}

	return menu_buffer;
}

void menu_print_ev(char *buffer, char *name, int parameter) {
	char tmp[32];

	ev_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_iso(char *buffer, char *name, int parameter) {
	char tmp[32];

	iso_display(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_int(char *buffer, char *name, int parameter, char *format) {
	char tmp[32];

	sprintf(tmp, format, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_char(char *buffer, char *name, char *parameter) {
	sprintf(buffer, "%-18s:%s", name, parameter);
}

type_MENUITEM *get_current_item() {
	return get_item(current_menu->current_item);
}

type_MENUITEM *get_item(int item_id) {
	if (current_menu->reorder)
		return &current_menu->items[current_menu->ordering[item_id]];
	else
		return &current_menu->items[item_id];
}
