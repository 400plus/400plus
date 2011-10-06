#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu.h"
#include "scripts.h"

#include "menu_scripts.h"

void menu_scripts_extended_aeb (type_MENUITEM *item);
void menu_scripts_interval     (type_MENUITEM *item);
void menu_scripts_wave         (type_MENUITEM *item);
void menu_scripts_self_timer   (type_MENUITEM *item);

void menu_scripts_launch (type_TASK script);

type_MENUITEM menupage_scripts_items[] = {
	MENUITEM_LAUNCH (LP_WORD(L_EXTENDED_AEB),   menu_scripts_extended_aeb),
	MENUITEM_LAUNCH (LP_WORD(L_INTERVALOMETER), menu_scripts_interval),
	MENUITEM_LAUNCH (LP_WORD(L_HAND_WAVING),    menu_scripts_wave),
	MENUITEM_LAUNCH (LP_WORD(L_SELF_TIMER),     menu_scripts_self_timer),
};

type_MENUPAGE menupage_scripts = {
	name        : "Scripts",
	length      : LENGTH(menupage_scripts_items),
	items       : menupage_scripts_items,
	reorder     : FALSE,
};

void menu_scripts_extended_aeb(type_MENUITEM *item) {
	menu_scripts_launch(script_extended_aeb);
}

void menu_scripts_interval(type_MENUITEM *item) {
	menu_scripts_launch(script_interval);
}

void menu_scripts_wave(type_MENUITEM *item) {
	menu_scripts_launch(script_wave);
}

void menu_scripts_self_timer(type_MENUITEM *item) {
	menu_scripts_launch(script_self_timer);
}

void menu_scripts_launch(type_TASK script) {
	ENQUEUE_TASK(menu_close);
	ENQUEUE_TASK(restore_display);
	ENQUEUE_TASK(script);
}
