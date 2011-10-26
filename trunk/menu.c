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
int   current_page_id;
int   current_line;
int   current_item;
int   item_grabbed;

type_MENU     *current_menu;
type_MENUPAGE *current_page;

type_ACTION callbacks_standard[] = {
	{GUI_BUTTON_MENU,           FALSE, TRUE,  {menu_event_menu}},
	{GUI_BUTTON_DISP,           FALSE, FALSE, {menu_event_disp}},
	{GUI_BUTTON_JUMP,           FALSE, TRUE,  {menu_event_jump}},
	{GUI_BUTTON_PLAY,           FALSE, TRUE,  {menu_event_play}},
	{GUI_BUTTON_TRASH,          FALSE, TRUE,  {menu_event_trash}},
	{GUI_BUTTON_UP,             FALSE, FALSE, {menu_event_up}},
	{GUI_BUTTON_DOWN,           FALSE, FALSE, {menu_event_down}},
	{GUI_BUTTON_ZOOM_OUT_PRESS, FALSE, TRUE,  {menu_event_out}},
	{GUI_BUTTON_ZOOM_IN_PRESS,  FALSE, TRUE,  {menu_event_in}},
	END_OF_LIST
};

void menu_initialize();
void menu_destroy();

int button_menu_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

void menu_display();
void menu_refresh();

void menu_repeat(void (*action_first)(), void (*action_repeat)());

void menu_cycle_first();
void menu_right_first();
void menu_left_first ();

void menu_cycle_repeat();
void menu_right_repeat();
void menu_left_repeat ();

void menu_message(int line);
void get_item_name(const char *name, int item_id, type_MENUITEM *item);

type_MENUPAGE *get_current_page();
type_MENUITEM *get_current_item();
type_MENUITEM *get_item(int item_id);

int get_item_id(int item_pos);
int get_real_id(int item_pos);

void menu_create(type_MENU * menu) {
	current_menu = menu;
	FLAG_GUI_MODE = GUIMODE_400PLUS;

	menu_destroy();
	menu_initialize();

	GUI_Lock();
	GUI_PalleteInit();

	menu_handler = dialog_create(22, button_menu_handler);
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

	current_page_id = 0;
	current_page    = get_current_page();

	current_line = 0;
	current_item = 0;

	item_grabbed   = FALSE;
}

void menu_destroy() {
	if (menu_handler != NULL) {
		PalettePop();
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
		GUI_ClearImage();
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
void menu_event_out()    { menu_event(MENU_EVENT_OUT);    };
void menu_event_in()     { menu_event(MENU_EVENT_IN);     };
void menu_event_open()   { menu_event(MENU_EVENT_OPEN);   };
void menu_event_change() { menu_event(MENU_EVENT_CHANGE); };
void menu_event_close()  { menu_event(MENU_EVENT_CLOSE);  };

void menu_event(type_MENU_EVENT event) {
	type_MENUITEM *item = get_current_item();

	if (item && item->tasks && item->tasks[event])
		item->tasks[event](item);

	if (current_page->tasks && current_page->tasks[event])
		current_page->tasks[event](current_page);
	else if (current_menu->tasks && current_menu->tasks[event])
		current_menu->tasks[event](current_menu);
}

void menu_void() {
}

void menu_display() {
	char buffer[LP_MAX_WORD];

	int i;

	int len  = strlen(current_page->name);
	int pad1 = (    MENU_WIDTH - 2 - len) / 2;
	int pad2 = (1 + MENU_WIDTH - 4 - len) / 2;

	sprintf(buffer, "<<%*s%s%*s>>", pad1, "", current_page->name, pad2, "");

	dialog_set_property_str(menu_handler, 8, buffer);

	menu_event_open();

	for(i = 0; i < MENU_HEIGHT; i++)
		menu_message(i);

	dialog_redraw(menu_handler);
}

void menu_refresh() {
	menu_message(current_line);
	dialog_redraw(menu_handler);
}

void menu_return() {
	item_grabbed = FALSE;

	current_page = get_current_page();
	current_item = current_line;

	menu_display();
}

void menu_up() {
	int display = FALSE;

	if (current_page->length > MENU_HEIGHT || current_item > 0) {
		current_item--;

		if (item_grabbed) {
			INT_SWAP(current_page->ordering[get_item_id(current_item)], current_page->ordering[get_item_id(current_item + 1)]);
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

	if (current_page->length > MENU_HEIGHT || current_item < MENU_HEIGHT - 1) {
		current_item++;

		if (item_grabbed) {
			INT_SWAP(current_page->ordering[get_item_id(current_item)], current_page->ordering[get_item_id(current_item - 1)]);
			display = TRUE;
		}
	}

	if (current_line < MENU_HEIGHT - 1)
		current_line++;
	else
		display = TRUE;

	if (display)
		menu_display();
}

void menu_right() {
	menu_repeat(menu_right_first, menu_right_repeat);
}

void menu_left() {
	menu_repeat(menu_left_first, menu_left_repeat);
}

void menu_cycle() {
	menu_repeat(menu_cycle_first, menu_cycle_repeat);
}

void menu_drag_drop() {
	if (current_page->ordering) {
		item_grabbed = ! item_grabbed;
		menu_event_change();
		menu_refresh();
	}
}

void menu_page_next() {
	if (current_page_id == current_menu->length - 1)
		current_page_id = 0;
	else
		current_page_id++;

	menu_return();
}

void menu_page_prev() {
	if (current_page_id == 0)
		current_page_id = current_menu->length - 1;
	else
		current_page_id--;

	menu_return();
}

void menu_repeat(void (*action_first)(), void (*action_repeat)()){
	int delay;
	int button = status.button_down;

	SleepTask(50);

	action_first();
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			action_repeat();
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void menu_right_first() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			*item->parm.menuitem_ev.value = ev_inc(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_AV:
			*item->parm.menuitem_av.value = av_inc(*item->parm.menuitem_av.value);
			break;
		case MENUITEM_TYPE_TV:
			if (item->parm.menuitem_tv.bulb)
				*item->parm.menuitem_tv.value = tv_next(*item->parm.menuitem_tv.value);
			else
				*item->parm.menuitem_tv.value = tv_inc(*item->parm.menuitem_tv.value);
			break;
		case MENUITEM_TYPE_ISO:
			if (item->parm.menuitem_iso.full)
				*item->parm.menuitem_iso.value = iso_next(*item->parm.menuitem_iso.value);
			else
				*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value += item->parm.menuitem_int.small_step;
			*item->parm.menuitem_int.value  = MIN(*item->parm.menuitem_int.value, item->parm.menuitem_int.max);
			break;
		case MENUITEM_TYPE_ENUM:
			if (*item->parm.menuitem_enum.value == item->parm.menuitem_enum.list->length - 1) {
				if (item->parm.menuitem_enum.cycle)
					*item->parm.menuitem_enum.value = 0;
			} else
				(*item->parm.menuitem_enum.value)++;
			break;
		case MENUITEM_TYPE_SUBMENU:
			current_page = item->parm.menuitem_submenu.page;
			current_item =  current_line;

			menu_display();
			break;
		default:
			break;
		}

		menu_event_change();
		menu_refresh();
	}
}

void menu_right_repeat() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			*item->parm.menuitem_ev.value = ev_inc(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_AV:
			*item->parm.menuitem_av.value = av_inc(*item->parm.menuitem_av.value);
			break;
		case MENUITEM_TYPE_TV:
			if (item->parm.menuitem_tv.bulb)
				*item->parm.menuitem_tv.value = tv_next(*item->parm.menuitem_tv.value);
			else
				*item->parm.menuitem_tv.value = tv_inc(*item->parm.menuitem_tv.value);
			break;
		case MENUITEM_TYPE_ISO:
			*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value += item->parm.menuitem_int.big_step;
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
}

void menu_left_first() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value < 0x05)
					*item->parm.menuitem_ev.value = 0x00;
			else
				*item->parm.menuitem_ev.value = ev_dec(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_AV:
			*item->parm.menuitem_av.value = av_dec(*item->parm.menuitem_av.value);
			break;
		case MENUITEM_TYPE_TV:
			if (item->parm.menuitem_tv.bulb)
				*item->parm.menuitem_tv.value = tv_prev(*item->parm.menuitem_tv.value);
			else
				*item->parm.menuitem_tv.value = tv_dec(*item->parm.menuitem_tv.value);
			break;
		case MENUITEM_TYPE_ISO:
			if (item->parm.menuitem_iso.full)
				*item->parm.menuitem_iso.value = iso_prev(*item->parm.menuitem_iso.value);
			else
				*item->parm.menuitem_iso.value = iso_dec(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value -= item->parm.menuitem_int.small_step;
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
}

void menu_left_repeat() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value < 0x05)
					*item->parm.menuitem_ev.value = 0x00;
			else
				*item->parm.menuitem_ev.value = ev_dec(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_AV:
			*item->parm.menuitem_av.value = av_dec(*item->parm.menuitem_av.value);
			break;
		case MENUITEM_TYPE_TV:
			if (item->parm.menuitem_tv.bulb)
				*item->parm.menuitem_tv.value = tv_prev(*item->parm.menuitem_tv.value);
			else
				*item->parm.menuitem_tv.value = tv_dec(*item->parm.menuitem_tv.value);
			break;
		case MENUITEM_TYPE_ISO:
			*item->parm.menuitem_iso.value = iso_dec(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value -= item->parm.menuitem_int.big_step;
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
}

void menu_cycle_first() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			if (!item->parm.menuitem_ev.zero_means_off)
				*item->parm.menuitem_ev.value = ev_sgn(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_ISO:
			*item->parm.menuitem_iso.value = iso_next(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value += item->parm.menuitem_int.small_step;
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
}

void menu_cycle_repeat() {
	type_MENUITEM *item = get_current_item();

	if (item && !item->readonly) {
		switch(item->type) {
		case MENUITEM_TYPE_EV:
			if (!item->parm.menuitem_ev.zero_means_off)
				*item->parm.menuitem_ev.value = ev_sgn(*item->parm.menuitem_ev.value);
			break;
		case MENUITEM_TYPE_ISO:
			*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
			break;
		case MENUITEM_TYPE_INT:
			*item->parm.menuitem_int.value += item->parm.menuitem_int.big_step;
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
}

void menu_message(int line) {
	char message[LP_MAX_WORD] = "";

	int item_id = line + current_item - current_line;

	type_MENUITEM *item = get_item(item_id);

	if (item) {
		if (current_page->ordering && item_grabbed && get_item_id(item_id) == get_item_id(current_item))
			message[0] = '>';
		else if (current_page->highlight && current_page->highlighted_item == 1 + get_real_id(item_id))
			message[0] = '*';
		else
			message[0] = ' ';

		if (item->display)
			item->display(item, message + 1);
	}

	dialog_set_property_str(menu_handler, line + 1, message);
}

void get_item_name(const char *name, int item_id, type_MENUITEM *item) {
	char item_name[LP_MAX_WORD];
	char pad = ' ';

	if (current_page->rename)
		sprintf(item_name, "%i %s", 1 + get_real_id(item_id), item->name);
	else
		sprintf(item_name, "%s", item->name);

	sprintf(name, "%c%s", pad, item_name);
}

type_MENUPAGE *get_current_page() {
	if (current_menu->ordering) {
		return current_menu->pages[current_menu->ordering[current_page_id]];
	} else {
		return current_menu->pages[current_page_id];
	}
}

type_MENUITEM *get_current_item() {
	return get_item(current_item);
}

type_MENUITEM *get_item(int item_pos) {
	int item_id = get_real_id(item_pos);

	return (item_id < current_page->length) ? &current_page->items[item_id] : NULL;
}

int get_real_id(int item_pos) {
	if (current_page->ordering)
		return current_page->ordering[get_item_id(item_pos)];
	else
		return get_item_id(item_pos);
}

int get_item_id(int item_pos) {
	int max_pos = MAX(current_page->length, MENU_HEIGHT);
	int item_id = item_pos - max_pos * (item_pos / max_pos);

	return (item_id < 0) ? (item_id + max_pos) : item_id;
}
