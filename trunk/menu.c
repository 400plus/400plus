#include "main.h"
#include "utils.h"
#include "display.h"
#include "firmware.h"

#include "menu.h"

char menu_buffer[32];

int  menu_dialog  = 0;
int  current_line = 0;
int  current_item = 0;
int  item_grabbed = FALSE;

type_MENU current_menu;

char *bool_strings[]   = {"No", "Yes"};
char *delay_strings[]  = {"No", "2s"};
char *action_strings[] = {"One shot", "Ext. AEB", "Interval"};
char *sspeed_strings[] = {"30", "15", "8", "4", "2", "1", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;

type_LIST bool_list   = {length: LENGTH(bool_strings),   data : bool_strings};
type_LIST delay_list  = {length: LENGTH(delay_strings),  data : delay_strings};
type_LIST action_list = {length: LENGTH(action_strings), data : action_strings};
type_LIST sspeed_list = {length: LENGTH(sspeed_strings), data : sspeed_strings};

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

void menu_create(type_MENU menu) {
	FLAG_GUI_MODE = GUI_MODE_400PLUS;

	current_line = 0;
	current_item = 0;
	item_grabbed = FALSE;

	current_menu = menu;

	menu_dialog = CreateDialogBox(0, 0, (int*)0xFF840AC4, 22);
	sub_FF837FA8(menu_dialog, 8, menu.name);

	menu_display();
}

void menu_display() {
	int i;
	int offset = current_item > current_line ? current_item - current_line : 0;

	for(i = 0; i < 5; i++)
		sub_FF837FA8(menu_dialog, i + 1, menu_message(i + offset));

	do_some_with_dialog(menu_dialog);
}

void menu_refresh() {
	sub_FF837FA8(menu_dialog, current_line + 1, menu_message(current_item));
	do_some_with_dialog(menu_dialog);
}

void menu_up() {
	int display = FALSE;

	if (current_item != 0) {
		current_item--;

		if (item_grabbed) {
			INT_SWAP(current_menu.ordering[current_item], current_menu.ordering[current_item + 1]);
			display = TRUE;
		}
	}

	if (current_line != 0)
		current_line--;
	else
		display = TRUE;

	if (display)
		menu_display();
}

void menu_down() {
	int display = FALSE;

	if (current_item != current_menu.length - 1) {
		current_item++;

		if (item_grabbed) {
			INT_SWAP(current_menu.ordering[current_item], current_menu.ordering[current_item - 1]);
			display = TRUE;
		}
	}

	if (current_line != 4)
		current_line++;
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
	type_TASK action;
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_LAUNCH) {
		if ((action = item->menuitem_launch.action)) {
			menu_close();
			ENQUEUE_TASK(action);
		}
	} else {
		if ((action = current_menu.action))
			action();
	}
}

void menu_dp_action() {
	if (current_menu.dp_action)
		current_menu.dp_action();
}

void menu_drag_drop() {
	if (current_menu.reorder) {
		item_grabbed = ! item_grabbed;
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
	DeleteDialogBox(menu_dialog);

	pressButton_(BUTTON_DISP);
	SleepTask(250);

	display_refresh();
}

char *menu_message(int item_id) {
	char name[32];

	type_MENUITEM *item = get_item(item_id);

	if (current_menu.reorder) {
		sprintf(name, "%c%s", (item_grabbed && item_id == current_item) ? '>' : ' ', item->name);
	} else
		sprintf(name, "%s", item->name);

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		item = &item->menuitem_submenu.items[item->menuitem_submenu.current_item];
		sprintf(name + strlen(name), ">%s", item->name);
	}

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->menuitem_ev.zero_means_off && *item->menuitem_ev.value == 0)
			menu_print_char(menu_buffer, name, "Off");
		else
			menu_print_ev(menu_buffer, name, *item->menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		menu_print_iso(menu_buffer, name, *item->menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		if (item->menuitem_int.zero_means_unlimited && *item->menuitem_int.value == 0)
			menu_print_char(menu_buffer, name, "No limit");
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
	return get_item(current_item);
}

type_MENUITEM *get_item(int item_id) {
	if (current_menu.reorder)
		return &current_menu.items[current_menu.ordering[item_id]];
	else
		return &current_menu.items[item_id];
}
