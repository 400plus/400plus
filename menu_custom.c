#include "main.h"
#include "menu.h"
#include "utils.h"
#include "scripts.h"
#include "custom.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "firmware.h"

#include "menu_custom.h"

void custom_save_1();
void custom_save_2();
void custom_save_3();
void custom_save_4();
void custom_save_5();

void custom_save(int id);

void custom_load_1();
void custom_load_2();
void custom_load_3();
void custom_load_4();
void custom_load_5();

void custom_load(int id);

type_MENUITEM custom_save_items[] = {
	MENUITEM_TASK ("Save custom 1", custom_save_1),
	MENUITEM_TASK ("Save custom 2", custom_save_2),
	MENUITEM_TASK ("Save custom 3", custom_save_3),
	MENUITEM_TASK ("Save custom 4", custom_save_4),
	MENUITEM_TASK ("Save custom 5", custom_save_5)
};

type_MENUITEM custom_load_items[] = {
	MENUITEM_TASK ("Load custom 1", custom_load_1),
	MENUITEM_TASK ("Load custom 2", custom_load_2),
	MENUITEM_TASK ("Load custom 3", custom_load_3),
	MENUITEM_TASK ("Load custom 4", custom_load_4),
	MENUITEM_TASK ("Load custom 5", custom_load_5)
};

type_MENU menu_custom_save = {
	name      : "Custom modes",
	length    : LENGTH(custom_save_items),
	items     : custom_save_items,
	dp_action : menu_settings_start
};

type_MENU menu_custom_load = {
	name      : "Custom modes",
	length    : LENGTH(custom_load_items),
	items     : custom_load_items,
	dp_action : menu_shortcuts_start
};

void menu_custom_save_start() {
	beep();
	menu_create(menu_custom_save);
}

void menu_custom_load_start() {
	beep();
	menu_create(menu_custom_load);
}

void custom_save_1() {
	custom_save(1);
}

void custom_save_2() {
	custom_save(2);
}

void custom_save_3() {
	custom_save(3);
}

void custom_save_4() {
	custom_save(4);
}

void custom_save_5() {
	custom_save(5);
}

void custom_save(int id) {
	beep();

	custom_write(id);

	menu_close();
}

void custom_load_1() {
	custom_load(1);
}

void custom_load_2() {
	custom_load(2);
}

void custom_load_3() {
	custom_load(3);
}

void custom_load_4() {
	custom_load(4);
}

void custom_load_5() {
	custom_load(5);
}

void custom_load(int id) {
	beep();

	if (custom_read(id))
		custom_apply();

	menu_close();
}
