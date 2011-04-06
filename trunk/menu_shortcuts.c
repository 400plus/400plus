#include "main.h"
#include "menu.h"
#include "utils.h"
#include "scripts.h"
#include "firmware.h"

#include "menu_shortcuts.h"

struct {
	int ISO;
	int CfMLU;
	int CfFlashSyncRear;
} shortcuts_storage;

char *yesno_strings[]   = {"No", "Yes"};

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    ("ISO",            &shortcuts_storage.ISO),
	MENUITEM_ACTION ("Extended AEB",   script_extended_aeb),
	MENUITEM_ACTION ("Intervalometer", script_interval),
	MENUITEM_ACTION ("Hand waving",    script_wave),
	MENUITEM_ACTION ("Self timer",     script_self_timer),
	MENUITEM_YESNO  ("Mirror lock",    &shortcuts_storage.CfMLU),
	MENUITEM_YESNO  ("Flash 2curt",    &shortcuts_storage.CfFlashSyncRear)
};

type_MENU menu_shortcuts = {
	name   : "Shortcuts",
	length : LENGTH(menu_shortcut_items),
	items  : menu_shortcut_items,
	action : menu_shortcuts_save
};

void menu_shortcuts_start() {
	beep();

	shortcuts_storage.ISO             = cameraMode.ISO;
	shortcuts_storage.CfMLU           = cameraMode.CfMLU;
	shortcuts_storage.CfFlashSyncRear = cameraMode.CfFlashSyncRear;

	pressButton_(BUTTON_MENU);
	SleepTask(100);

	menu_create(menu_shortcuts);
}

void menu_shortcuts_save() {
	beep();

	SendToIntercom(0x0B, 2, shortcuts_storage.ISO);
	SendToIntercom(0x35, 1, shortcuts_storage.CfMLU);
	SendToIntercom(0x38, 1, shortcuts_storage.CfFlashSyncRear);

	menu_close();
}
