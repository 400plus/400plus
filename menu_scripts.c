#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"
#include "scripts.h"

#include "menu_scripts.h"

void menu_scripts_apply_eaeb_tvmin (const type_MENUITEM *item);
void menu_scripts_apply_eaeb_tvmax (const type_MENUITEM *item);

void menu_scripts_extended_aeb (const type_MENUITEM *item);
void menu_scripts_interval     (const type_MENUITEM *item);
void menu_scripts_wave         (const type_MENUITEM *item);
void menu_scripts_self_timer   (const type_MENUITEM *item);

void menu_scripts_launch (type_TASK script);

type_MENUITEM wave_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_DELAY),   &settings.wave_delay,   NULL),
	MENUITEM_ACTION (LP_WORD(L_I_ACTION),  &settings.wave_action,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_REPEAT),  &settings.wave_repeat,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_INSTANT), &settings.wave_instant, NULL)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT(LP_WORD(L_I_TIME_S), &settings.timer_timeout, NULL),
	MENUITEM_ACTION (LP_WORD(L_I_ACTION), &settings.timer_action,  NULL)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_DELAY),     &settings.eaeb_delay,  NULL),
	MENUITEM_BRACKET(LP_WORD(L_I_FRAMES),    &settings.eaeb_frames, NULL),
	MENUITEM_EVEAEB (LP_WORD(L_I_STEP_EV),   &settings.eaeb_ev,     NULL),
	MENUITEM_BULB   (LP_WORD(L_I_MANUAL_L),  &settings.eaeb_tv_min, menu_scripts_apply_eaeb_tvmin),
	MENUITEM_BULB   (LP_WORD(L_I_MANUAL_R),  &settings.eaeb_tv_max, menu_scripts_apply_eaeb_tvmax)
};

type_MENUITEM interval_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_DELAY),    &settings.interval_delay, NULL),
	MENUITEM_TIMEOUT(LP_WORD(L_I_TIME_S),   &settings.interval_time,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_I_EAEB),     &settings.interval_eaeb,  NULL),
	MENUITEM_COUNTER(LP_WORD(L_I_SHOTS),    &settings.interval_shots, NULL)
};

type_MENUPAGE wave_page = {
	name   : LP_WORD(L_S_HANDWAVE),
	length : LENGTH(wave_items),
	items  : wave_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE timer_page = {
	name   : LP_WORD(L_S_TIMER),
	length : LENGTH(timer_items),
	items  : timer_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE eaeb_page = {
	name   : LP_WORD(L_S_EXT_AEB),
	length : LENGTH(eaeb_items),
	items  : eaeb_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE interval_page = {
	name   : LP_WORD(L_S_INTERVAL),
	length : LENGTH(interval_items),
	items  : interval_items,
	tasks  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUITEM menupage_scripts_items[] = {
	MENUITEM_SUBMENU(LP_WORD(L_S_EXT_AEB),  &eaeb_page,     menu_scripts_extended_aeb),
	MENUITEM_SUBMENU(LP_WORD(L_S_INTERVAL), &interval_page, menu_scripts_interval),
	MENUITEM_SUBMENU(LP_WORD(L_S_HANDWAVE), &wave_page,     menu_scripts_wave),
	MENUITEM_SUBMENU(LP_WORD(L_S_TIMER),    &timer_page,    menu_scripts_self_timer),
};

type_MENUPAGE menupage_scripts = {
	name      : LP_WORD(L_P_SCRIPTS),
	sibilings : TRUE,
	length    : LENGTH(menupage_scripts_items),
	items     : menupage_scripts_items,
	ordering  : settings.scripts_order,
};

void menu_scripts_apply_eaeb_tvmin(const type_MENUITEM *item) {
	settings.eaeb_tv_max = MIN(settings.eaeb_tv_min, settings.eaeb_tv_max);
	menu_event_display();
}

void menu_scripts_apply_eaeb_tvmax(const type_MENUITEM *item) {
	settings.eaeb_tv_min = MAX(settings.eaeb_tv_min, settings.eaeb_tv_max);
	menu_event_display();
}

void menu_scripts_extended_aeb(const type_MENUITEM *item) {
	menu_scripts_launch(script_extended_aeb);
}

void menu_scripts_interval(const type_MENUITEM *item) {
	menu_scripts_launch(script_interval);
}

void menu_scripts_wave(const type_MENUITEM *item) {
	menu_scripts_launch(script_wave);
}

void menu_scripts_self_timer(const type_MENUITEM *item) {
	menu_scripts_launch(script_self_timer);
}

void menu_scripts_launch(type_TASK script) {
	ENQUEUE_TASK(menu_close);
	ENQUEUE_TASK(restore_display);
	ENQUEUE_TASK(script);
}
