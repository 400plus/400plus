#include <vxworks.h>

#include "firmware.h"
#include "macros.h"
#include "main.h"

#include "cmodes.h"
#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_rename.h"
#include "menu_settings.h"
#include "utils.h"
#include "intercom.h"

#include "menu_cmodes.h"

void menu_cmodes_open(menu_t *menu);

void menu_cmodes_save   (const menuitem_t *item);
void menu_cmodes_load   (const menuitem_t *item);
void menu_cmodes_free   (const menuitem_t *item);
void menu_cmodes_rename (const menuitem_t *item);
void menu_cmodes_delete (const menuitem_t *item);

// One sub-menu for each custom mode, and 3 / 4 items on each sub-menu
menuitem_t menupage_cmodes_subitems[CMODES_MAX][4];
menupage_t menupage_cmodes_submenus[CMODES_MAX];

menuitem_t menupage_cmodes_items[CMODES_MAX];

menupage_t menupage_cmodes = {
	name      : LP_WORD(L_P_CMODES),
	sibilings : TRUE,
	items     : LIST(menupage_cmodes_items),
	show_id   : TRUE,
	ordering  : cmodes_config.order,
	actions   : {
		[MENU_EVENT_OPEN] = menu_cmodes_open,
	}
};

void menu_cmodes_open(menu_t *menu) {
	int i, length;
	int current_cmode = get_current_cmode();

	menupage_cmodes.highlight        = status.cmode_active;
	menupage_cmodes.highlighted_item = current_cmode;

	for (i = 0; i < CMODES_MAX; i++) {
		if (AE_IS_AUTO(status.main_dial_ae)) {
			if(status.cmode_active && i == current_cmode) {
				length = 4;

				// Current custom mode: create first item in sub-menu: UPDATE
				menupage_cmodes_subitems[i][0].id      = i;
				menupage_cmodes_subitems[i][0].display = menuitem_display;
				menupage_cmodes_subitems[i][0].name    = LP_WORD(L_I_UPDATE);
				menupage_cmodes_subitems[i][0].action  = menu_cmodes_save;

				// Current custom mode: create extra item in sub-menu: UNASSIGN
				menupage_cmodes_subitems[i][3].id      = i;
				menupage_cmodes_subitems[i][3].display = menuitem_display;
				menupage_cmodes_subitems[i][3].name    = LP_WORD(L_I_UNASSIGN);
				menupage_cmodes_subitems[i][3].action  = menu_cmodes_free;
			} else {
				length = 3;

				// Other custom mode: create first item in sub-menu: ASSIGN
				menupage_cmodes_subitems[i][0].id      = i;
				menupage_cmodes_subitems[i][0].display = menuitem_display;
				menupage_cmodes_subitems[i][0].name    = LP_WORD(L_I_ASSIGN);
				menupage_cmodes_subitems[i][0].action  = menu_cmodes_load;
			}
		} else {
			length = 3;

			// Creative mode: create first item in sub-menu: SAVE
			menupage_cmodes_subitems[i][0].id      = i;
			menupage_cmodes_subitems[i][0].display = menuitem_display;
			menupage_cmodes_subitems[i][0].name    = LP_WORD(L_I_SAVE);
			menupage_cmodes_subitems[i][0].action  = menu_cmodes_save;
		}

		// Create second item in sub-menu: RENAME
		menupage_cmodes_subitems[i][1].id      = i;
		menupage_cmodes_subitems[i][1].display = menuitem_display;
		menupage_cmodes_subitems[i][1].name    = LP_WORD(L_I_RENAME);
		menupage_cmodes_subitems[i][1].action  = menu_cmodes_rename;

		// Create third item in sub-menu: DELETE
		menupage_cmodes_subitems[i][2].id      = i;
		menupage_cmodes_subitems[i][2].display = menuitem_display;
		menupage_cmodes_subitems[i][2].name    = LP_WORD(L_I_DELETE);
		menupage_cmodes_subitems[i][2].action  = menu_cmodes_delete;

		// Configure sub-menu
		menupage_cmodes_submenus[i].name        = cmodes_config.names[i];
		menupage_cmodes_submenus[i].items.size  = length;
		menupage_cmodes_submenus[i].items.data  = menupage_cmodes_subitems[i];

		menupage_cmodes_submenus[i].actions[MENU_EVENT_AV] = menu_return;

		// Add sub-menu to page
		menupage_cmodes_items[i].id      = i;
		menupage_cmodes_items[i].name    = cmodes_config.names[i];
		menupage_cmodes_items[i].display = menuitem_display_sub;
		menupage_cmodes_items[i].inc     = menuitem_inc_sub;
		menupage_cmodes_items[i].action  = menupage_cmodes_subitems[i][0].action;

		menupage_cmodes_items[i].parm.menuitem_submenu.page =  &menupage_cmodes_submenus[i];
	}
}

void menu_cmodes_save(const menuitem_t *item) {
	if (AE_IS_CREATIVE(status.main_dial_ae) || status.cmode_active)
		if (cmode_write(item->id)) {
			beep();
			menu_close();
		}
}

void menu_cmodes_load(const menuitem_t *item) {
	snapshot_t cmode;

	if (AE_IS_AUTO(status.main_dial_ae)) {
		if (cmode_read(item->id, &cmode)) {
			snapshot_recall(&cmode);
			snapshot_apply (&cmode);

			set_current_cmode(item->id);

			beep();
			menu_close();
			cmodes_write();
		}
	}
}

void menu_cmodes_free(const menuitem_t *item) {
	if (AE_IS_AUTO(status.main_dial_ae)) {
		set_current_cmode(CMODE_NONE);

		send_to_intercom(IC_SET_AE, status.main_dial_ae);

		beep();
		menu_close();
		cmodes_write();
	}
}

void menu_cmodes_rename(const menuitem_t *item) {
	rename_create(cmodes_config.names[item->id]);
}

void menu_cmodes_delete(const menuitem_t *item) {
	if (cmode_delete(item->id)) {
		beep();
		menu_close();
	}
}
