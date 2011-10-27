#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
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
	name      : LP_WORD(L_SHORTCUTS),
	sibilings : TRUE,
	length    : LENGTH(menu_shortcut_items),
	items     : menu_shortcut_items,
	ordering  : settings.shortcuts_order,
};

void menu_shortcuts_apply_cf_emit_aux(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_AUX, 1, *item->parm.menuitem_enum.value);
}

void menu_shortcuts_apply_cf_mirror_up_lock(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, *item->parm.menuitem_enum.value);
}

void menu_shortcuts_apply_cf_flash_sync_rear(type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, *item->parm.menuitem_enum.value);
}
