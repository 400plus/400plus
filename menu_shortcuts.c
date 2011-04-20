#include "main.h"
#include "menu.h"
#include "menu_presets.h"
#include "utils.h"
#include "scripts.h"
#include "settings.h"
#include "firmware.h"

#include "menu_shortcuts.h"

struct {
	int iso;
	int cf_emit_aux;
	int cf_mirror_up_lock;
	int cf_flash_sync_rear;
} shortcuts_storage;

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    ("ISO",            &shortcuts_storage.iso),
	MENUITEM_SCRIPT ("Extended AEB",   script_extended_aeb),
	MENUITEM_SCRIPT ("Intervalometer", script_interval),
	MENUITEM_SCRIPT ("Hand waving",    script_wave),
	MENUITEM_SCRIPT ("Self timer",     script_self_timer),
	MENUITEM_AFFLASH("AF flash",       &shortcuts_storage.cf_emit_aux),
	MENUITEM_BOOLEAN("Mirror lock",    &shortcuts_storage.cf_mirror_up_lock),
	MENUITEM_BOOLEAN("Flash 2curt",    &shortcuts_storage.cf_flash_sync_rear)
};

type_MENU menu_shortcuts = {
	name      : "Shortcuts",
	length    : LENGTH(menu_shortcut_items),
	items     : menu_shortcut_items,
	action    : menu_shortcuts_save,
	dp_action : menu_presets_load_start,
	reorder   : TRUE,
	ordering  : settings.shortcuts_order
};

void menu_shortcuts_start() {
	beep();

	shortcuts_storage.iso                = cameraMode.iso;
	shortcuts_storage.cf_emit_aux        = cameraMode.cf_emit_aux;
	shortcuts_storage.cf_mirror_up_lock  = cameraMode.cf_mirror_up_lock;
	shortcuts_storage.cf_flash_sync_rear = cameraMode.cf_flash_sync_rear;

	press_button(BUTTON_MENU);
	SleepTask(100);

	menu_create(menu_shortcuts);
}

void menu_shortcuts_save() {
	beep();

	send_to_intercom(EVENT_SET_ISO,                2, shortcuts_storage.iso);
	send_to_intercom(EVENT_SET_CF_EMIT_AUX,        1, shortcuts_storage.cf_emit_aux);
	send_to_intercom(EVENT_SET_CF_MIRROR_UP_LOCK,  1, shortcuts_storage.cf_mirror_up_lock);
	send_to_intercom(EVENT_SET_CF_FLASH_SYNC_REAR, 1, shortcuts_storage.cf_flash_sync_rear);

	settings_write();

	menu_close();
}
