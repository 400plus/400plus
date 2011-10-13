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
#include "utils.h"

#include "menu_main.h"

type_MENUPAGE *menu_main_pages[] = {
	&menupage_shortcuts,
	&menupage_scripts,
	&menupage_presets,
	&menupage_params,
	&menupage_settings,
	&menupage_info,
#ifdef BREAK_CAMERA
	&menupage_developer,
#endif
};

type_MENU menu_main = {
	length : LENGTH(menu_main_pages),
	pages  : menu_main_pages,
};

void menu_main_start() {
	beep();

	press_button(IC_BUTTON_MENU);
	SleepTask(100);

	menu_cameraMode = *cameraMode;
	menu_create(&menu_main);
}
