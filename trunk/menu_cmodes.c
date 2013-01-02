/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

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

#include "menu_cmodes.h"

void menu_cmodes_open();

void menu_cmodes_save   (const type_MENUITEM *item);
void menu_cmodes_load   (const type_MENUITEM *item);
void menu_cmodes_free   (const type_MENUITEM *item);
void menu_cmodes_rename (const type_MENUITEM *item);
void menu_cmodes_delete (const type_MENUITEM *item);

// One sub-menu for each custom mode, and 3 items on each sub-menu
type_MENUITEM menupage_cmodes_subitems[CMODES_MAX][3];
type_MENUPAGE menupage_cmodes_submenus[CMODES_MAX];

type_MENUITEM menupage_cmodes_items[CMODES_MAX];

type_MENUPAGE menupage_cmodes = {
	name      : LP_WORD(L_P_CMODES),
	sibilings : true,
	length    : LENGTH(menupage_cmodes_items),
	items     : menupage_cmodes_items,
	show_id   : true,
	ordering  : cmodes_config.order,
	actions   : {
		[MENU_EVENT_OPEN] = menu_cmodes_open,
	}
};

void menu_cmodes_open() {
	int i;
	int current_cmode = get_current_cmode();

	menupage_cmodes.highlight        = status.cmode_active;
	menupage_cmodes.highlighted_item = current_cmode;

	for (i = 0; i < CMODES_MAX; i++) {
		// Create first item in sub-menu: FREE / LOAD / SAVE
		if (AE_IS_AUTO(status.main_dial_ae)) {
			if(status.cmode_active && i == current_cmode) {
				menupage_cmodes_subitems[i][0].id      = i;
				menupage_cmodes_subitems[i][0].display = menuitem_display;
				menupage_cmodes_subitems[i][0].name    = LP_WORD(L_I_UNASSIGN);
				menupage_cmodes_subitems[i][0].action  = menu_cmodes_free;
			} else {
				menupage_cmodes_subitems[i][0].id      = i;
				menupage_cmodes_subitems[i][0].display = menuitem_display;
				menupage_cmodes_subitems[i][0].name    = LP_WORD(L_I_ASSIGN);
				menupage_cmodes_subitems[i][0].action  = menu_cmodes_load;
			}
		} else {
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
		menupage_cmodes_submenus[i].name    = cmodes_config.names[i];
		menupage_cmodes_submenus[i].length  = LENGTH(menupage_cmodes_subitems[i]);
		menupage_cmodes_submenus[i].items   = menupage_cmodes_subitems[i];

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

void menu_cmodes_save(const type_MENUITEM *item) {
	if (AE_IS_CREATIVE(status.main_dial_ae))
		if (cmode_write(item->id)) {
			beep();
			menu_close();
		}
}

void menu_cmodes_load(const type_MENUITEM *item) {
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

void menu_cmodes_free(const type_MENUITEM *item) {
	if (AE_IS_AUTO(status.main_dial_ae)) {
		set_current_cmode(CMODE_NONE);

		status.main_dial_moved = false;
		send_to_intercom(IC_SET_AE, 1, status.main_dial_ae);

		beep();
		menu_close();
		cmodes_write();
	}
}

void menu_cmodes_rename(const type_MENUITEM *item) {
	rename_create(cmodes_config.names[item->id]);
}

void menu_cmodes_delete(const type_MENUITEM *item) {
	if (cmode_delete(item->id)) {
		beep();
		menu_close();
	}
}
