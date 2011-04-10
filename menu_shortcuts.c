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

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    ("ISO",            &shortcuts_storage.ISO),
	MENUITEM_LAUNCH ("Extended AEB",   script_extended_aeb),
	MENUITEM_LAUNCH ("Intervalometer", script_interval),
	MENUITEM_LAUNCH ("Hand waving",    script_wave),
	MENUITEM_LAUNCH ("Self timer",     script_self_timer),
	MENUITEM_BOOLEAN("Mirror lock",    &shortcuts_storage.CfMLU),
	MENUITEM_BOOLEAN("Flash 2curt",    &shortcuts_storage.CfFlashSyncRear)
};

int ordering[LENGTH(menu_shortcut_items)] = {0,1,2,3,4,5,6};

type_MENU menu_shortcuts = {
	name     : "Shortcuts",
	length   : LENGTH(menu_shortcut_items),
	items    : menu_shortcut_items,
	action   : menu_shortcuts_save,
	reorder  : TRUE,
	ordering : ordering
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

	SendToIntercom(EVENT_SET_ISO,            2, shortcuts_storage.ISO);
	SendToIntercom(EVENT_SET_CFN_MLU,        1, shortcuts_storage.CfMLU);
	SendToIntercom(EVENT_SET_CFN_FLASHSYNCR, 1, shortcuts_storage.CfFlashSyncRear);

	menu_close();
}
