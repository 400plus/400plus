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
#include "settings.h"
#include "utils.h"

#include "menu_shortcuts.h"

void menu_shortcuts_close();

void menu_shortcuts_apply_cf_emit_aux        (type_MENUITEM *item);
void menu_shortcuts_apply_cf_mirror_up_lock  (type_MENUITEM *item);
void menu_shortcuts_apply_cf_flash_sync_rear (type_MENUITEM *item);

type_MENUITEM menu_shortcut_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_MIRROR_LOCKUP), &menu_cameraMode.cf_mirror_up_lock,  menu_shortcuts_apply_cf_mirror_up_lock),
	MENUITEM_BOOLEAN(LP_WORD(L_FLASH_2ND_CURT),&menu_cameraMode.cf_flash_sync_rear, menu_shortcuts_apply_cf_flash_sync_rear),
	MENUITEM_AFFLASH(LP_WORD(L_AF_FLASH),      &menu_cameraMode.cf_emit_aux,        menu_shortcuts_apply_cf_emit_aux),
};

type_MENUPAGE menupage_shortcuts = {
	name        : LP_WORD(L_SHORTCUTS),
	//color       : MENU_COLOR_YELLOW_AND_GREEN,
	length      : LENGTH(menu_shortcut_items),
	items       : menu_shortcut_items,
	reorder     : TRUE,
	ordering    : settings.shortcuts_order,
	tasks       : {
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE]  = menu_shortcuts_close,
	}
};

type_MENUPAGE *menu_shortcuts_pages[] = {
	&menupage_shortcuts,
	&menupage_scripts,
	&menupage_params,
	&menupage_main,
	&menupage_info,
#ifdef BREAK_CAMERA
	&menupage_developer,
#endif
};

type_MENU menu_shortcuts = {
	length : LENGTH(menu_shortcuts_pages),
	pages  : menu_shortcuts_pages,
	tasks  : {
		[MENU_EVENT_DP]     = menu_presets_load_start,
	}
};

void menu_shortcuts_start() {
	beep();

	press_button(IC_BUTTON_MENU);
	SleepTask(100);

	menu_shortcuts_create();
}

void menu_shortcuts_create() {
	menu_cameraMode = *cameraMode;
	menu_create(&menu_shortcuts);
}

void menu_shortcuts_close() {
	if (menu_get_changed()) {
		settings_write();
	}
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
