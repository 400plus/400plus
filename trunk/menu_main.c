#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menu_developer.h"
#include "menu_info.h"
#include "menu_params.h"
#include "menu_presets.h"
#include "menu_scripts.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

#include "menu_main.h"

int  changed;

void menu_save();
void menu_set_changed();
int  menu_get_changed();

type_MENUPAGE *menu_main_pages[] = {
	&menupage_params,
	&menupage_shortcuts,
	&menupage_scripts,
	&menupage_info,
	&menupage_developer,
	&menupage_settings,
	&menupage_presets,
};

type_MENU menu_main = {
	length   : LENGTH(menu_main_pages),
	pages    : menu_main_pages,
	ordering : settings.main_order,
	tasks    : {
		[MENU_EVENT_PLAY]   = menu_drag_drop,
		[MENU_EVENT_UP]     = menu_up,
		[MENU_EVENT_DOWN]   = menu_down,
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_save,
	}
};

void menu_main_start() {
	beep();

	//
	//GUI_Command(4,0);
	//press_button(IC_BUTTON_MENU);
	//
	SendToMC(6, 2, 0);
	SleepTask(100);

	changed         = FALSE;
	menu_cameraMode = *cameraMode;

	menu_create(&menu_main);
}

void menu_save() {
	if (menu_get_changed()) {
		settings_write();
		presets_write();
	}
}

void menu_set_changed() {
	changed = TRUE;
}

int menu_get_changed() {
	return changed;
}

