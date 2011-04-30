#include "main.h"
#include "utils.h"
#include "display.h"
#include "languages.h"
#include "menu_rename.h"
#include "firmware.h"

#include "menu.h"

char menu_buffer[32];

type_MENU * current_menu;

OPTIONLIST_DEF(bool,    LP_WORD(L_NO), LP_WORD(L_YES))
OPTIONLIST_DEF(delay,   LP_WORD(L_NO), LP_WORD(L_2S))
OPTIONLIST_DEF(flash,   LP_WORD(L_ENABLED), LP_WORD(L_DISABLED), LP_WORD(L_EXT_ONLY))
OPTIONLIST_DEF(action,  LP_WORD(L_ONE_SHOT), LP_WORD(L_EXT_AEB), LP_WORD(L_INTERVAL))
OPTIONLIST_DEF(shutter, "30", "15", "8", "4", "2", "1", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000")

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

int menu_buttons_400plus(type_DIALOG * dialog, int r1, int code1, int r3, int r4, int r5, int r6, int button) {
	type_ACTION *action;

	//printf("AF1: dialog=%p[0x%02X], r1=%02X, code1=%02X, r3=%02X, r4=%02X, r5=%02X, r6=%02X, button=%02X\n",
	//		dialog,*((int*)dialog+1),r1,code1,r3,r4,r5,r6,button);

	//char str[27];
	//sprintf(str,"0x%02X, 0x%02X",code1,button);
	//dialog_set_property_str(current_menu->handle,8,str);
	//dialog_redraw(current_menu->handle);

	// Loop over all the actions from 400plus
	//for (action = actions_400plus; ! IS_EOL(action); action++) {
		// Check whether this action corresponds to the event received
	//	if (action->button == button) {
			beep();
			// Launch the defined task
			//if (action->task[0])
			//	ENQUEUE_TASK(action->task[0]);

			//printf("AF: catched\n");
	//		return 1;
	//		break;
	//	}
	//}

	//dialog_redraw(dialog);
	return 1;
}

void menu_destroy(type_MENU * menu) {
	// GUI_DisplayMode();
	GUI_Lock();
	GUI_PalleteInit();

	if (menu->handle != 0)
		DeleteDialogBox(menu->handle);
	menu->handle = 0;
	menu->current_line = 0;
	menu->current_item = 0;
	menu->item_grabbed = FALSE;

	GUI_StartMode(GUI_MODE_OLC);
	CreateDialogBox_OlMain();

	GUI_UnLock();
	GUI_PalleteUnInit();
}

void menu_create(type_MENU * menu) {
	current_menu = menu;
	FLAG_GUI_MODE = current_menu->gui_mode;

	GUI_Lock();
	GUI_PalleteInit();
	GUI_StartMode(current_menu->gui_mode);
	GUI_ClearImage();

	{ // do we need this block ?
		if (menu->handle != 0)
			DeleteDialogBox(menu->handle);
		menu->handle = 0;
		menu->current_line = 0;
		menu->current_item = 0;
		menu->item_grabbed = FALSE;
	}

	current_menu->handle = dialog_create(22, menu->btn_handler);
	dialog_set_property_str(current_menu->handle, 8, current_menu->name);

	menu_display();

	GUI_UnLock();
	GUI_PalleteUnInit();
	GUI_ClearImage();
	SetTurnDisplayEvent_1_after_2(); // ?? Every dialog ends with this. Could be "toggle screen on". Not tested.
	//SetTurnDisplayEvent_2_after_1(); // will turn screen off
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
		rename_create(item->name, current_menu->callback);
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
	if (current_menu->dp_action)
		current_menu->dp_action();
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
	menu_destroy(current_menu);

	press_button(BUTTON_DISP);
	SleepTask(250);

	display_refresh();
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
