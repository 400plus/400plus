#include "main.h"
#include "menu.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "menu_settings.h"

type_SETTINGS menu_settings;

char *bool_strings[]   = {"No", "Yes"};
char *delay_strings[]  = {"No", "2s"};
char *action_strings[] = {"One shot", "Ext. AEB", "Interval"};
char *sspeed_strings[] = {"30", "15", "8", "4", "2", "1", "1/2", "1/4", "1/8", "1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;

type_MENUITEM wave_items[] = {
	MENUITEM_DELAY  ("Delay",   &menu_settings.wave_delay),
	MENUITEM_SCRACT ("Action",  &menu_settings.wave_action),
	MENUITEM_BOOLEAN("Repeat",  &menu_settings.wave_repeat),
	MENUITEM_BOOLEAN("Instant", &menu_settings.wave_instant)
};

type_MENUITEM timer_items[] = {
	MENUITEM_TIMEOUT("Delay",  &menu_settings.timer_timeout),
	MENUITEM_SCRACT ("Action", &menu_settings.timer_action)
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

type_MENUITEM menu_items[] = {
	MENUITEM_EVCOMP ("AV comp",           &menu_settings.av_comp),
	MENUITEM_EVCOMP ("Flash comp",        &menu_settings.flash_comp),
	MENUITEM_EVSEP  ("AEB",               &menu_settings.aeb_ev),
	MENUITEM_BOOLEAN("ISO in viewfinder", &menu_settings.iso_in_viewfinder),
	MENUITEM_BOOLEAN("Safety Shift",      &menu_settings.safety_shift),
	MENUITEM_CLRTEMP("Color Temp. (K)",   &menu_settings.color_temp),
	MENUITEM_BOOLEAN("Use flash",         &menu_settings.emit_flash),
	MENUITEM_BOOLEAN("AF flash",          &menu_settings.af_flash),
	MENUITEM_SUBMENU("Handwave",           wave_items),
	MENUITEM_SUBMENU("EAEB    ",           eaeb_items),
	MENUITEM_SUBMENU("Interval",           interval_items),
	MENUITEM_SUBMENU("Timer   ",           timer_items),
	MENUITEM_DELAY  ("IR remote delay",   &menu_settings.remote_delay),
	MENUITEM_ACTION ("Developers menu",    menu_settings_developer)
};

type_MENU main_menu = {
	name   : "Settings",
	length : LENGTH(menu_items),
	items  : menu_items,
	action : menu_settings_save
};

void menu_settings_start() {
	beep();

	menu_settings = settings;

	menu_settings.av_comp        =  cameraMode.AvComp;
	menu_settings.flash_comp     =  cameraMode.FlashExComp;
	menu_settings.aeb_ev         =  cameraMode.AEB;
	menu_settings.emit_flash     = !cameraMode.CfNotEmitFlash;
	menu_settings.af_flash       = !cameraMode.CfAfAssistBeam;

	menu_create(main_menu);
}

void menu_settings_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();

	beep();
}

void menu_settings_developer() {
	factory_or_debug();
}
