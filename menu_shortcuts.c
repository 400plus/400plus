#include "main.h"
#include "menu.h"
#include "menu_presets.h"
#include "utils.h"
#include "scripts.h"
#include "settings.h"
#include "firmware.h"
#include "languages.h"

#include "menu_shortcuts.h"

type_CAMERA_MODE sc_cameraMode;

void menu_shortcuts_apply_iso                (type_MENUITEM *item);
void menu_shortcuts_apply_cf_emit_aux        (type_MENUITEM *item);
void menu_shortcuts_apply_cf_mirror_up_lock  (type_MENUITEM *item);
void menu_shortcuts_apply_cf_flash_sync_rear (type_MENUITEM *item);

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    (LP_WORD(L_ISO),           &sc_cameraMode.iso,                menu_shortcuts_apply_iso),
	MENUITEM_SCRIPT (LP_WORD(L_EXTENDED_AEB),   script_extended_aeb),
	MENUITEM_SCRIPT (LP_WORD(L_INTERVALOMETER), script_interval),
	MENUITEM_SCRIPT (LP_WORD(L_HAND_WAVING),    script_wave),
	MENUITEM_SCRIPT (LP_WORD(L_SELF_TIMER),     script_self_timer),
	MENUITEM_AFFLASH(LP_WORD(L_AF_FLASH),      &sc_cameraMode.cf_emit_aux,        menu_shortcuts_apply_cf_emit_aux),
	MENUITEM_BOOLEAN(LP_WORD(L_MIRROR_LOCKUP), &sc_cameraMode.cf_mirror_up_lock,  menu_shortcuts_apply_cf_mirror_up_lock),
	MENUITEM_BOOLEAN(LP_WORD(L_FLASH_2ND_CURT),&sc_cameraMode.cf_flash_sync_rear, menu_shortcuts_apply_cf_flash_sync_rear)
};

type_MENU menu_shortcuts = {
	name        : LP_WORD(L_SHORTCUTS),
	length      : LENGTH(menu_shortcut_items),
	items       : menu_shortcut_items,
	reorder     : TRUE,
	save        : settings_write,
	dp_action   : menu_presets_load_start,
	ordering    : settings.shortcuts_order
};

void menu_shortcuts_start() {
	beep();

	press_button(IC_BUTTON_MENU);
	SleepTask(100);

	menu_shortcuts_create();
}

void menu_shortcuts_create() {
	sc_cameraMode = cameraMode;
	menu_create(&menu_shortcuts);
}

void menu_shortcuts_apply_iso(type_MENUITEM *item) {
	send_to_intercom(IC_SET_ISO, 2, *item->parm.menuitem_iso.value);
}

void menu_shortcuts_apply_cf_emit_aux(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_AUX, 1, *item->parm.menuitem_enum.value);
}

void menu_shortcuts_apply_cf_mirror_up_lock(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, *item->parm.menuitem_enum.value);
}

void menu_shortcuts_apply_cf_flash_sync_rear(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, *item->parm.menuitem_enum.value);
}
