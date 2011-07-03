#include "main.h"
#include "firmware.h"

#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menu_presets.h"
#include "scripts.h"
#include "settings.h"
#include "utils.h"

#include "menu_shortcuts.h"

type_CAMERA_MODE sc_cameraMode;

void menu_shortcuts_close();

void menu_shortcuts_script_extended_aeb (type_MENUITEM *item);
void menu_shortcuts_script_interval     (type_MENUITEM *item);
void menu_shortcuts_script_wave         (type_MENUITEM *item);
void menu_shortcuts_script_self_timer   (type_MENUITEM *item);

void menu_shortcuts_apply_iso                (type_MENUITEM *item);
void menu_shortcuts_apply_color_temp         (type_MENUITEM *item);
void menu_shortcuts_apply_cf_emit_aux        (type_MENUITEM *item);
void menu_shortcuts_apply_cf_mirror_up_lock  (type_MENUITEM *item);
void menu_shortcuts_apply_cf_flash_sync_rear (type_MENUITEM *item);

void menu_shortcuts_script (type_TASK script);

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_ISO    (LP_WORD(L_ISO),           &sc_cameraMode.iso,                menu_shortcuts_apply_iso),
	MENUITEM_CLRTEMP(LP_WORD(L_COLOR_TEMP_K),  &sc_cameraMode.color_temp,         menu_shortcuts_apply_color_temp),
	MENUITEM_LAUNCH (LP_WORD(L_EXTENDED_AEB),   menu_shortcuts_script_extended_aeb),
	MENUITEM_LAUNCH (LP_WORD(L_INTERVALOMETER), menu_shortcuts_script_interval),
	MENUITEM_LAUNCH (LP_WORD(L_HAND_WAVING),    menu_shortcuts_script_wave),
	MENUITEM_LAUNCH (LP_WORD(L_SELF_TIMER),     menu_shortcuts_script_self_timer),
	MENUITEM_AFFLASH(LP_WORD(L_AF_FLASH),      &sc_cameraMode.cf_emit_aux,        menu_shortcuts_apply_cf_emit_aux),
	MENUITEM_BOOLEAN(LP_WORD(L_MIRROR_LOCKUP), &sc_cameraMode.cf_mirror_up_lock,  menu_shortcuts_apply_cf_mirror_up_lock),
	MENUITEM_BOOLEAN(LP_WORD(L_FLASH_2ND_CURT),&sc_cameraMode.cf_flash_sync_rear, menu_shortcuts_apply_cf_flash_sync_rear)
};

type_MENU menu_shortcuts = {
	name        : LP_WORD(L_SHORTCUTS),
	color       : MENU_COLOR_YELLOW_AND_GREEN,
	length      : LENGTH(menu_shortcut_items),
	items       : menu_shortcut_items,
	reorder     : TRUE,
	ordering    : settings.shortcuts_order,
	tasks       : {
		[MENU_EVENT_DP]     = menu_presets_load_start,
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_shortcuts_close,
	}
};

void menu_shortcuts_start() {
	beep();

	press_button(IC_BUTTON_MENU);
	SleepTask(100);

	menu_shortcuts_create();
}

void menu_shortcuts_create() {
	sc_cameraMode = *cameraMode;
	menu_create(&menu_shortcuts);
}

void menu_shortcuts_close() {
	if (menu_get_changed()) {
		settings_write();
	}
}

void menu_shortcuts_apply_iso(type_MENUITEM *item) {
	send_to_intercom(IC_SET_ISO, 2, *item->parm.menuitem_iso.value);
}

void menu_shortcuts_apply_color_temp(type_MENUITEM *item) {
	send_to_intercom(IC_SET_WB,         1, WB_MODE_COLORTEMP);
	send_to_intercom(IC_SET_COLOR_TEMP, 2, *item->parm.menuitem_int.value);
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

void menu_shortcuts_script_extended_aeb(type_MENUITEM *item) {
	menu_shortcuts_script(script_extended_aeb);
}

void menu_shortcuts_script_interval(type_MENUITEM *item) {
	menu_shortcuts_script(script_interval);
}

void menu_shortcuts_script_wave(type_MENUITEM *item) {
	menu_shortcuts_script(script_wave);
}

void menu_shortcuts_script_self_timer(type_MENUITEM *item) {
	menu_shortcuts_script(script_self_timer);
}

void menu_shortcuts_script(type_TASK script) {
	ENQUEUE_TASK(menu_close);
	ENQUEUE_TASK(restore_display);
	ENQUEUE_TASK(script);
}
