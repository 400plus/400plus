#include "main.h"
#include "menu.h"
#include "menu_custom.h"
#include "utils.h"
#include "scripts.h"
#include "settings.h"
#include "firmware.h"

#include "menu_shortcuts.h"

struct {
	int ISO;
	int CfMLU;
	int CfFlashSyncRear;
} shortcuts_storage;

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    ("ISO",            &shortcuts_storage.ISO),
	MENUITEM_SCRIPT ("Extended AEB",   script_extended_aeb),
	MENUITEM_SCRIPT ("Intervalometer", script_interval),
	MENUITEM_SCRIPT ("Hand waving",    script_wave),
	MENUITEM_SCRIPT ("Self timer",     script_self_timer),
	MENUITEM_BOOLEAN("Mirror lock",    &shortcuts_storage.CfMLU),
	MENUITEM_BOOLEAN("Flash 2curt",    &shortcuts_storage.CfFlashSyncRear)
};

type_MENU menu_shortcuts = {
	name      : "Shortcuts",
	length    : LENGTH(menu_shortcut_items),
	items     : menu_shortcut_items,
	action    : menu_shortcuts_save,
	dp_action : menu_custom_load_start,
	reorder   : TRUE,
	ordering  : settings.shortcuts_order
};

void menu_shortcuts_start() {
	beep();

	shortcuts_storage.ISO             = cameraMode.iso;
	shortcuts_storage.CfMLU           = cameraMode.cf_mirror_up_lock;
	shortcuts_storage.CfFlashSyncRear = cameraMode.cf_flash_sync_rear;

	pressButton_(BUTTON_MENU);
	SleepTask(100);

	menu_create(menu_shortcuts);
}

void menu_shortcuts_save() {
	beep();

	SendToIntercom(EVENT_SET_ISO,                2, shortcuts_storage.ISO);
	SendToIntercom(EVENT_SET_CF_MIRROR_UP_LOCK,  1, shortcuts_storage.CfMLU);
	SendToIntercom(EVENT_SET_CF_FLASH_SYNC_REAR, 1, shortcuts_storage.CfFlashSyncRear);

	settings_write();

	menu_close();
}
