#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu.h"
#include "settings.h"
#include "scripts.h"

#include "menu_scripts.h"

void menu_scripts_apply_eaeb_tvmin      (type_MENUITEM *item);
void menu_scripts_apply_eaeb_tvmax      (type_MENUITEM *item);

void menu_scripts_extended_aeb (type_MENUITEM *item);
void menu_scripts_interval     (type_MENUITEM *item);
void menu_scripts_wave         (type_MENUITEM *item);
void menu_scripts_self_timer   (type_MENUITEM *item);

void menu_scripts_launch (type_TASK script);

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),   &settings.wave_delay,   NULL),
	MENUITEM_ACTION (LP_WORD(L_ACTION),  &settings.wave_action,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_REPEAT),  &settings.wave_repeat,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_INSTANT), &settings.wave_instant, NULL)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT(LP_WORD(L_DELAY),  &settings.timer_timeout, NULL),
	MENUITEM_ACTION (LP_WORD(L_ACTION), &settings.timer_action,  NULL)
};

type_MENUITEM eaeb_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),     &settings.eaeb_delay,  NULL),
	MENUITEM_BRACKET(LP_WORD(L_FRAMES),    &settings.eaeb_frames, NULL),
	MENUITEM_EVSEP  (LP_WORD(L_STEP_EV),   &settings.eaeb_ev,     NULL),
	MENUITEM_BULB   (LP_WORD(L_MANUAL_L),  &settings.eaeb_tv_min, menu_scripts_apply_eaeb_tvmin),
	MENUITEM_BULB   (LP_WORD(L_MANUAL_R),  &settings.eaeb_tv_max, menu_scripts_apply_eaeb_tvmax)
};

type_MENUITEM interval_items[] = {
	MENUITEM_DELAY  (LP_WORD(L_DELAY),    &settings.interval_delay, NULL),
	MENUITEM_TIMEOUT(LP_WORD(L_TIME_S),   &settings.interval_time,  NULL),
	MENUITEM_BOOLEAN(LP_WORD(L_EAEB),     &settings.interval_eaeb,  NULL),
	MENUITEM_COUNTER(LP_WORD(L_SHOTS),    &settings.interval_shots, NULL)
};

type_MENUPAGE wave_page = {
	name   : LP_WORD(L_HANDWAVE),
	length : LENGTH(wave_items),
	items  : wave_items,
	tasks  : {
		[MENU_EVENT_SET]  = menu_return,
		[MENU_EVENT_NEXT] = menu_void,
		[MENU_EVENT_PREV] = menu_void,
		[MENU_EVENT_IN]   = menu_void,
		[MENU_EVENT_OUT]  = menu_void,
	}
};

type_MENUPAGE timer_page = {
	name   : LP_WORD(L_TIMER_SPACES),
	length : LENGTH(timer_items),
	items  : timer_items,
	tasks  : {
		[MENU_EVENT_SET]  = menu_return,
		[MENU_EVENT_NEXT] = menu_void,
		[MENU_EVENT_PREV] = menu_void,
		[MENU_EVENT_IN]   = menu_void,
		[MENU_EVENT_OUT]  = menu_void,
	}
};

type_MENUPAGE eaeb_page = {
	name   : LP_WORD(L_EXT_AEB),
	length : LENGTH(eaeb_items),
	items  : eaeb_items,
	tasks  : {
		[MENU_EVENT_SET]  = menu_return,
		[MENU_EVENT_NEXT] = menu_void,
		[MENU_EVENT_PREV] = menu_void,
		[MENU_EVENT_IN]   = menu_void,
		[MENU_EVENT_OUT]  = menu_void,
	}
};

type_MENUPAGE interval_page = {
	name   : LP_WORD(L_INTERVAL),
	length : LENGTH(interval_items),
	items  : interval_items,
	tasks  : {
		[MENU_EVENT_SET] = menu_return,
	}
};

type_MENUITEM menupage_scripts_items[] = {
	MENUITEM_SUBMENU(LP_WORD(L_EXT_AEB),      &eaeb_page,     menu_scripts_extended_aeb),
	MENUITEM_SUBMENU(LP_WORD(L_INTERVAL),     &interval_page, menu_scripts_interval),
	MENUITEM_SUBMENU(LP_WORD(L_HANDWAVE),     &wave_page,     menu_scripts_wave),
	MENUITEM_SUBMENU(LP_WORD(L_TIMER_SPACES), &timer_page,    menu_scripts_self_timer),
};

type_MENUPAGE menupage_scripts = {
	name        : "Scripts",
	length      : LENGTH(menupage_scripts_items),
	items       : menupage_scripts_items,
	reorder     : TRUE,
	ordering    : settings.scripts_order,
};

void menu_scripts_apply_eaeb_tvmin(type_MENUITEM *item) {
	settings.eaeb_tv_max = MIN(settings.eaeb_tv_min, settings.eaeb_tv_max);
}

void menu_scripts_apply_eaeb_tvmax(type_MENUITEM *item) {
	settings.eaeb_tv_min = MAX(settings.eaeb_tv_min, settings.eaeb_tv_max);
}

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
