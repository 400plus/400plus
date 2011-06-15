#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu_rename.h"
#include "presets.h"
#include "utils.h"

#include "menu.h"

void *menu_handler;
int   current_line;
int   current_item;
int   item_grabbed;
int   show_filenames;
int   changed;

type_MENU *current_menu;

OPTIONLIST_DEF(bool,    LP_WORD(L_NO), LP_WORD(L_YES))
OPTIONLIST_DEF(delay,   LP_WORD(L_NO), LP_WORD(L_2S))
OPTIONLIST_DEF(flash,   LP_WORD(L_ENABLED), LP_WORD(L_DISABLED), LP_WORD(L_EXT_ONLY))
OPTIONLIST_DEF(action,  LP_WORD(L_ONE_SHOT), LP_WORD(L_EXT_AEB), LP_WORD(L_INTERVAL))
OPTIONLIST_DEF(shutter, "16'", "8'", "4'", "2'", "1'", "30\"", "15\"", "8\"", "4\"", "2\"", "1\"", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000")

type_ACTION callbacks_standard[] = {
	{GUI_BUTTON_UP,             FALSE, FALSE, {menu_up}},
	{GUI_BUTTON_DOWN,           FALSE, FALSE, {menu_down}},
	{GUI_BUTTON_DISP,           FALSE, FALSE, {NULL}},
	{GUI_BUTTON_MENU,           FALSE, TRUE,  {menu_toggle_filenames}},
	{GUI_BUTTON_JUMP,           FALSE, TRUE,  {menu_rename}},
	{GUI_BUTTON_PLAY,           FALSE, TRUE,  {menu_drag_drop}},
	{GUI_BUTTON_TRASH,          FALSE, TRUE,  {NULL}},
	{GUI_BUTTON_ZOOM_IN_PRESS,  FALSE, TRUE,  {menu_submenu_next}},
	{GUI_BUTTON_ZOOM_OUT_PRESS, FALSE, TRUE,  {menu_submenu_prev}},
	END_OF_LIST
};

void menu_initialize();
void menu_destroy();

int button_menu_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

void menu_display();
void menu_refresh();

void menu_repeat(void (*repeateable)(int repeating));

void menu_repeateable_cycle(int repeating);
void menu_repeateable_right(int repeating);
void menu_repeateable_left (int repeating);

void menu_message(const char *buffer, int item_id);

void menu_print_ev   (const char *buffer, const char *name, int   parameter);
void menu_print_iso  (const char *buffer, const char *name, int   parameter);
void menu_print_int  (const char *buffer, const char *name, int   parameter, const char *format);
void menu_print_char (const char *buffer, const char *name, const char *parameter);

type_MENUITEM *get_current_item();
type_MENUITEM *get_item(int item_id);

int get_real_id(int item_id);

void menu_create(type_MENU * menu) {
	current_menu = menu;
	FLAG_GUI_MODE = GUIMODE_400PLUS;

	menu_destroy();
	menu_initialize();

	menu_handler = dialog_create(22, button_menu_handler);
	dialog_set_property_str(menu_handler, 8, current_menu->name);

	menu_display();
}

void menu_close() {
	press_button(IC_BUTTON_DISP);
	menu_destroy();
}

void menu_initialize() {
	menu_handler = NULL;

	current_line = 0;
	current_item = 0;

	item_grabbed   = FALSE;
	show_filenames = FALSE;
	changed        = FALSE;
}

void menu_destroy() {
	if (menu_handler != NULL) {
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
	}
}

int button_menu_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code) {
	type_ACTION *action;

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
	return InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
}

void menu_event_dp() {
	menu_event(MENU_EVENT_DP);
}

void menu_event_set() {
	menu_event(MENU_EVENT_SET);
}

void menu_event_change() {
	menu_event(MENU_EVENT_CHANGE);
}

void menu_event_close() {
	menu_event(MENU_EVENT_CLOSE);
}

void menu_event(type_MENU_EVENT event) {
	type_MENUITEM *item = get_current_item();

	if (item->tasks && item->tasks[event])
		item->tasks[event](item);

	if (current_menu->tasks && current_menu->tasks[event])
		current_menu->tasks[event](current_menu);
}

void menu_display() {
	int i;
	int offset = current_item > current_line ? current_item - current_line : 0;

	char buffer[32];

	for(i = 0; i < 5; i++) {
		menu_message(buffer, i + offset);
		dialog_set_property_str(menu_handler, i + 1, buffer);
	}

	dialog_redraw(menu_handler);
}

void menu_refresh() {
	char buffer[32];

	menu_message(buffer, current_item);
	dialog_set_property_str(menu_handler, current_line + 1, buffer);
	dialog_redraw(menu_handler);
}

void menu_up() {
	int display = FALSE;

	if (current_item != 0) {
		current_item--;

		if (item_grabbed) {
			INT_SWAP(current_menu->ordering[current_item],
					current_menu->ordering[current_item + 1]);
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

	if (current_item != current_menu->length - 1) {
		current_item++;

		if (item_grabbed) {
			INT_SWAP(current_menu->ordering[current_item],
					current_menu->ordering[current_item - 1]);
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

void menu_toggle_filenames() {
	if (current_menu->rename) {
		show_filenames = ! show_filenames;
		menu_display();
	}
}

void menu_rename() {
	type_MENUITEM *item = get_current_item();

	if (current_menu->rename) {
		rename_create(item->name, current_menu);
	}
}

void menu_drag_drop() {
	if (current_menu->reorder) {
		item_grabbed = ! item_grabbed;
		menu_event_change();
		menu_refresh();
	}
}

void menu_submenu_next() {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		if (item->parm.menuitem_submenu.current_item == item->parm.menuitem_submenu.length - 1)
			item->parm.menuitem_submenu.current_item = 0;
		else
			item->parm.menuitem_submenu.current_item++;

		menu_refresh();
	}
}

void menu_submenu_prev() {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		if (item->parm.menuitem_submenu.current_item == 0)
			item->parm.menuitem_submenu.current_item = item->parm.menuitem_submenu.length - 1;
		else
			item->parm.menuitem_submenu.current_item--;

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
		item = &item->parm.menuitem_submenu.items[item->parm.menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		*item->parm.menuitem_ev.value = ev_inc(*item->parm.menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
		else
			*item->parm.menuitem_iso.value = iso_next(*item->parm.menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		*item->parm.menuitem_int.value += repeating ? item->parm.menuitem_int.big_step : item->parm.menuitem_int.small_step;
		*item->parm.menuitem_int.value  = MIN(*item->parm.menuitem_int.value, item->parm.menuitem_int.max);
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->parm.menuitem_enum.value == item->parm.menuitem_enum.list->length - 1) {
			if (item->parm.menuitem_enum.cycle)
				*item->parm.menuitem_enum.value = 0;
		} else
			(*item->parm.menuitem_enum.value)++;
		break;
	default:
		break;
	}

	menu_event_change();
	menu_refresh();
}

void menu_repeateable_left(int repeating) {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU)
		item = &item->parm.menuitem_submenu.items[item->parm.menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value < 0x05)
				*item->parm.menuitem_ev.value = 0x00;
		else
			*item->parm.menuitem_ev.value = ev_dec(*item->parm.menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->parm.menuitem_iso.value = iso_dec(*item->parm.menuitem_iso.value);
		else
			*item->parm.menuitem_iso.value = iso_prev(*item->parm.menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		*item->parm.menuitem_int.value -= repeating ? item->parm.menuitem_int.big_step : item->parm.menuitem_int.small_step;
		*item->parm.menuitem_int.value  = MAX(*item->parm.menuitem_int.value, item->parm.menuitem_int.min);
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->parm.menuitem_enum.value == 0) {
			if (item->parm.menuitem_enum.cycle)
				*item->parm.menuitem_enum.value = item->parm.menuitem_enum.list->length - 1;
		} else
			*item->parm.menuitem_enum.value -= 1;
		break;
	default:
		break;
	}

	menu_event_change();
	menu_refresh();
}

void menu_repeateable_cycle(int repeating) {
	type_MENUITEM *item = get_current_item();

	if (item->type == MENUITEM_TYPE_SUBMENU)
		item = &item->parm.menuitem_submenu.items[item->parm.menuitem_submenu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (!item->parm.menuitem_ev.zero_means_off)
			*item->parm.menuitem_ev.value = ev_sgn(*item->parm.menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		if (repeating)
			*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
		else
			*item->parm.menuitem_iso.value = iso_next(*item->parm.menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		*item->parm.menuitem_int.value += repeating ? item->parm.menuitem_int.big_step : item->parm.menuitem_int.small_step;
		*item->parm.menuitem_int.value  = MIN(*item->parm.menuitem_int.value, item->parm.menuitem_int.max);
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->parm.menuitem_enum.value == item->parm.menuitem_enum.list->length - 1)
			*item->parm.menuitem_enum.value = 0;
		else
			*item->parm.menuitem_enum.value += 1;
		break;
	default:
		break;
	}

	menu_event_change();
	menu_refresh();
}

void menu_set_changed() {
	changed = TRUE;
}

int menu_get_changed() {
	return changed;
}

void menu_message(const char *buffer, int item_id) {
	char item_name[32];
	char name[32];

	type_MENUITEM *item = get_item(item_id);

	if (show_filenames)
		get_preset_filename(item_name, 1 + get_real_id(item_id));
	else
		sprintf(item_name, "%s", item->name);

	if (current_menu->highlight || current_menu->reorder) {
		if (current_menu->reorder && item_grabbed && item_id == current_item)
			sprintf(name, "%c%s", '>', item_name);
		else if (current_menu->highlight && current_menu->highlighted_item == 1 + get_real_id(item_id))
			sprintf(name, "%c%s", '*', item_name);
		else
			sprintf(name, "%c%s", ' ', item_name);
	} else
		sprintf(name, "%s", item_name);

	if (item->type == MENUITEM_TYPE_SUBMENU) {
		item = &item->parm.menuitem_submenu.items[item->parm.menuitem_submenu.current_item];
		sprintf(name + strlen(name), ">%s", item->name);
	}

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value == 0)
			menu_print_char(buffer, name, LP_WORD(L_OFF));
		else
			menu_print_ev(buffer, name, *item->parm.menuitem_ev.value);
		break;
	case MENUITEM_TYPE_ISO:
		menu_print_iso(buffer, name, *item->parm.menuitem_iso.value);
		break;
	case MENUITEM_TYPE_INT:
		if (item->parm.menuitem_int.zero_means_unlimited && *item->parm.menuitem_int.value == 0)
			menu_print_char(buffer, name, LP_WORD(L_NO_LIMIT));
		else
			menu_print_int(buffer, name, *item->parm.menuitem_int.value, item->parm.menuitem_int.format);
		break;
	case MENUITEM_TYPE_ENUM:
		menu_print_char(buffer, name, item->parm.menuitem_enum.list->data[*item->parm.menuitem_enum.value]);
		break;
	case MENUITEM_TYPE_LAUNCH:
		sprintf(buffer, "%s", name);
		break;
	default:
		break;
	}
}

void menu_print_ev(const char *buffer, const char *name, int parameter) {
	char tmp[32];

	ev_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_iso(const char *buffer, const char *name, int parameter) {
	menu_print_char(buffer, name, iso_display(parameter));
}

void menu_print_int(const char *buffer, const char *name, int parameter, const char *format) {
	char tmp[32];

	sprintf(tmp, format, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_char(const char *buffer, const char *name, const char *parameter) {
	sprintf(buffer, "%-18s:%s", name, parameter);
}

type_MENUITEM *get_current_item() {
	return get_item(current_item);
}

type_MENUITEM *get_item(int item_id) {
	return &current_menu->items[get_real_id(item_id)];
}

int get_real_id(int item_id) {
	if (current_menu->reorder)
		return current_menu->ordering[item_id];
	else
		return item_id;
}
