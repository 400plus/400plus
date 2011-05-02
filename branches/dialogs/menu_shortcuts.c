#include "main.h"
#include "menu.h"
#include "menu_presets.h"
#include "utils.h"
#include "scripts.h"
#include "settings.h"
#include "firmware.h"
#include "languages.h"

#include "menu_shortcuts.h"

struct {
	int iso;
	int cf_emit_aux;
	int cf_mirror_up_lock;
	int cf_flash_sync_rear;
} shortcuts_storage;

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    (LP_WORD(L_ISO),           &shortcuts_storage.iso),
	MENUITEM_SCRIPT (LP_WORD(L_EXTENDED_AEB),   script_extended_aeb),
	MENUITEM_SCRIPT (LP_WORD(L_INTERVALOMETER), script_interval),
	MENUITEM_SCRIPT (LP_WORD(L_HAND_WAVING),    script_wave),
	MENUITEM_SCRIPT (LP_WORD(L_SELF_TIMER),     script_self_timer),
	MENUITEM_AFFLASH(LP_WORD(L_AF_FLASH),      &shortcuts_storage.cf_emit_aux),
	MENUITEM_BOOLEAN(LP_WORD(L_MIRROR_LOCKUP), &shortcuts_storage.cf_mirror_up_lock),
	MENUITEM_BOOLEAN(LP_WORD(L_FLASH_2ND_CURT),&shortcuts_storage.cf_flash_sync_rear)
};

type_MENU menu_shortcuts = {
	name        : LP_WORD(L_SHORTCUTS),
	length      : LENGTH(menu_shortcut_items),
	items       : menu_shortcut_items,
	action      : menu_shortcuts_save,
	dp_action   : menu_presets_load_start,
	reorder     : TRUE,
	ordering    : settings.shortcuts_order,
	gui_mode    : GUIMODE_400PLUS,
	btn_handler : menu_buttons_handler
};

void menu_shortcuts_start() {
	beep();

	shortcuts_storage.iso                = cameraMode.iso;
	shortcuts_storage.cf_emit_aux        = cameraMode.cf_emit_aux;
	shortcuts_storage.cf_mirror_up_lock  = cameraMode.cf_mirror_up_lock;
	shortcuts_storage.cf_flash_sync_rear = cameraMode.cf_flash_sync_rear;

	//press_button(BUTTON_MENU);
	//SleepTask(100);

	menu_create(&menu_shortcuts);
}

void menu_shortcuts_save() {
	beep();

	send_to_intercom(IC_SET_ISO,                2, shortcuts_storage.iso);
	send_to_intercom(IC_SET_CF_EMIT_AUX,        1, shortcuts_storage.cf_emit_aux);
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK,  1, shortcuts_storage.cf_mirror_up_lock);
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, shortcuts_storage.cf_flash_sync_rear);

	settings_write();

	//menu_close();
}
