#include "main.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "menu.h"

type_SETTINGS menu_settings;

char *bool_strings[]   = {"No", "Yes"};
char *delay_strings[]  = {"No", "2s"};
char *action_strings[] = {"One shot", "Ext. AEB", "Interval"};
char *script_strings[] = {"Disabled", "Intm ISO", "Ext AEB", "Interval", "Handwave", "Timer"};
char *sspeed_strings[] = {"30", "15", "8", "4", "2", "1", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  ("Delay",   &menu_settings.wave_delay),
	MENUITEM_ACTION ("Action",  &menu_settings.wave_action),
	MENUITEM_BOOLEAN("Repeat",  &menu_settings.wave_repeat),
	MENUITEM_BOOLEAN("Instant", &menu_settings.wave_instant)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT("Delay",  &menu_settings.timer_timeout),
	MENUITEM_ACTION ("Action", &menu_settings.timer_action)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_DELAY  ("Delay",     &menu_settings.eaeb_delay),
	MENUITEM_BRACKET("Frames",    &menu_settings.eaeb_frames),
	MENUITEM_EVSEP  ("Step (EV)", &menu_settings.eaeb_ev),
	MENUITEM_SSPEED ("Manual [",  &menu_settings.eaeb_m_min),
	MENUITEM_SSPEED ("Manual ]",  &menu_settings.eaeb_m_max)
};

type_MENUITEM interval_items[] = {
	MENUITEM_DELAY  ("Delay",    &menu_settings.interval_delay),
	MENUITEM_TIMEOUT("Time (s)", &menu_settings.interval_time),
	MENUITEM_BOOLEAN("EAEB",     &menu_settings.interval_eaeb),
	MENUITEM_COUNTER("Shots",    &menu_settings.interval_shots)
};

type_MENUITEM main_items[] = {
	MENUITEM_EVCOMP   ("AV comp",           &menu_settings.av_comp),
	MENUITEM_EVCOMP   ("Flash comp",        &menu_settings.flash_comp),
	MENUITEM_EVSEP    ("AEB",               &menu_settings.aeb_ev),
	MENUITEM_BOOLEAN  ("ISO in viewfinder", &menu_settings.iso_in_viewfinder),
	MENUITEM_BOOLEAN  ("Safety Shift",      &menu_settings.safety_shift),
	MENUITEM_COLORTEMP("Color Temp. (K)",   &menu_settings.color_temp),
	MENUITEM_BOOLEAN  ("Use flash",         &menu_settings.emit_flash),
	MENUITEM_BOOLEAN  ("AF flash",          &menu_settings.af_flash),
	MENUITEM_SCRIPT   ("DP action",         &menu_settings.dp_action),
	MENUITEM_SUB      ("Handwave",           wave_items),
	MENUITEM_SUB      ("EAEB    ",           eaeb_items),
	MENUITEM_SUB      ("Interval",           interval_items),
	MENUITEM_SUB      ("Timer   ",           timer_items),
	MENUITEM_DELAY    ("IR remote delay",   &menu_settings.remote_delay)
};

type_MENUITEM_MENU main_menu = {
	length : LENGTH(main_items),
	items  : main_items,
};

int  menu_dialog  = 0;
int  current_line = 0;
char menu_buffer[32];

void menu_repeat(void (*repeateable)(int repeating));

void menu_repeateable_cycle  (int repeating);
void menu_repeateable_right  (int repeating);
void menu_repeateable_left   (int repeating);

void  menu_save();
void  menu_create();
void  menu_display();
char *menu_message(int item_id);

void menu_print_ev   (char *buffer, char *name, int   parameter);
void menu_print_int  (char *buffer, char *name, int   parameter, char *format);
void menu_print_char (char *buffer, char *name, char *parameter);

void menu_initialize() {
	beep();

	menu_settings = settings;

	menu_settings.av_comp        =  cameraMode.AvComp;
	menu_settings.flash_comp     =  cameraMode.FlashExComp;
	menu_settings.aeb_ev         =  cameraMode.AEB;
	menu_settings.emit_flash     = !cameraMode.CfNotEmitFlash;
	menu_settings.af_flash       = !cameraMode.CfAfAssistBeam;

	current_line           = 0;
	main_menu.current_item = 0;

	menu_create();
	menu_display();
}

void menu_up() {
	if (main_menu.current_item != 0)
		main_menu.current_item--;

	if (current_line != 0)
		current_line--;

	menu_display();
}

void menu_down() {
	if (main_menu.current_item != main_menu.length - 1)
		main_menu.current_item++;

	if (current_line != 4)
		current_line++;

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
	type_MENUITEM *item = &main_menu.items[main_menu.current_item];

	if (item->type == MENUITEM_TYPE_MENU)
		item = &item->def.def_menu.items[item->def.def_menu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		*item->def.def_ev.value = ev_inc(*item->def.def_ev.value);
		break;
	case MENUITEM_TYPE_INT:
		if (!item->def.def_int.readonly) {
			*item->def.def_int.value += repeating ? item->def.def_int.big_step : item->def.def_int.small_step;
			*item->def.def_int.value  = MIN(*item->def.def_int.value, item->def.def_int.max);
		}
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->def.def_enum.value == item->def.def_enum.count - 1) {
			if (item->def.def_enum.cycle)
				*item->def.def_enum.value = 0;
		} else
			(*item->def.def_enum.value)++;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_repeateable_left(int repeating) {
	type_MENUITEM *item = &main_menu.items[main_menu.current_item];

	if (item->type == MENUITEM_TYPE_MENU)
		item = &item->def.def_menu.items[item->def.def_menu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->def.def_ev.zero_means_off && *item->def.def_ev.value < 0x05)
				*item->def.def_ev.value = 0x00;
		else
			*item->def.def_ev.value = ev_dec(*item->def.def_ev.value);
		break;
	case MENUITEM_TYPE_INT:
		if (!item->def.def_int.readonly) {
			*item->def.def_int.value -= repeating ? item->def.def_int.big_step : item->def.def_int.small_step;
			*item->def.def_int.value  = MAX(*item->def.def_int.value, item->def.def_int.min);
		}
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->def.def_enum.value == 0) {
			if (item->def.def_enum.cycle)
				*item->def.def_enum.value = item->def.def_enum.count - 1;
		} else
			*item->def.def_enum.value -= 1;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_repeateable_cycle(int repeating) {
	type_MENUITEM *item = &main_menu.items[main_menu.current_item];

	if (item->type == MENUITEM_TYPE_MENU)
		item = &item->def.def_menu.items[item->def.def_menu.current_item];

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (!item->def.def_ev.zero_means_off)
			*item->def.def_ev.value = ev_sgn(*item->def.def_ev.value);
		break;
	case MENUITEM_TYPE_INT:
		*item->def.def_int.value += repeating ? item->def.def_int.big_step : item->def.def_int.small_step;
		*item->def.def_int.value  = MIN(*item->def.def_int.value, item->def.def_int.max);
		break;
	case MENUITEM_TYPE_ENUM:
		if (*item->def.def_enum.value == item->def.def_enum.count - 1)
			*item->def.def_enum.value = 0;
		else
			*item->def.def_enum.value += 1;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_submenu() {
	type_MENUITEM *item = &main_menu.items[main_menu.current_item];

	if (item->type == MENUITEM_TYPE_MENU) {
		if (item->def.def_menu.current_item == item->def.def_menu.length - 1)
			item->def.def_menu.current_item = 0;
		else
			item->def.def_menu.current_item++;
	}

	menu_display();
}

void menu_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();

	beep();
}

void menu_create() {
	FLAG_GUI_MODE = GUI_MODE_400PLUS;

	menu_dialog = CreateDialogBox(0, 0, (int*)0xFF840AC4, 22);
	sub_FF837FA8(menu_dialog, 8, "400plus");
}

void menu_display() {
	int i;

	int offset = main_menu.current_item > current_line ? main_menu.current_item - current_line : 0;

	for(i = 0; i < 5; i++)
		sub_FF837FA8(menu_dialog, i + 1, menu_message(offset + i));

	do_some_with_dialog(menu_dialog);
}

char *menu_message(int item_id) {
	char name[32];

	type_MENUITEM *item = &main_menu.items[item_id];

	sprintf(name, "%s", item->name);

	if (item->type == MENUITEM_TYPE_MENU) {
		item = &item->def.def_menu.items[item->def.def_menu.current_item];
		sprintf(name + strlen(name), ">%s", item->name);
	}

	switch(item->type) {
	case MENUITEM_TYPE_EV:
		if (item->def.def_ev.zero_means_off && *item->def.def_ev.value == 0)
			menu_print_char(menu_buffer, name, "Off");
		else
			menu_print_ev(menu_buffer, name, *item->def.def_ev.value);
		break;
	case MENUITEM_TYPE_INT:
		if (item->def.def_int.zero_means_unlimited && *item->def.def_int.value == 0)
			menu_print_char(menu_buffer, name, "No limit");
		else
			menu_print_int(menu_buffer, name, *item->def.def_int.value, item->def.def_int.format);
		break;
	case MENUITEM_TYPE_ENUM:
		menu_print_char(menu_buffer, name, item->def.def_enum.texts[*item->def.def_enum.value]);
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

void menu_print_int(char *buffer, char *name, int parameter, char *format) {
	char tmp[32];

	sprintf(tmp, format, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_char(char *buffer, char *name, char *parameter) {
	sprintf(buffer, "%-18s:%s", name, parameter);
}
