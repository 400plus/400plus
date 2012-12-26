/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "firmware.h"
#include "macros.h"
#include "main.h"

#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_rename.h"
#include "menu_settings.h"
#include "presets.h"
#include "utils.h"

#include "menu_presets.h"

void menu_preset_open();

void menu_preset_save   (const type_MENUITEM *item);
void menu_preset_load   (const type_MENUITEM *item);
void menu_preset_free   (const type_MENUITEM *item);
void menu_preset_rename (const type_MENUITEM *item);
void menu_preset_delete (const type_MENUITEM *item);

type_MENUITEM menupage_preset_items[PRESETS_MAX][3];

type_MENUPAGE menupage_preset[PRESETS_MAX];

type_MENUITEM preset_items[PRESETS_MAX];

type_MENUPAGE menupage_presets = {
	name      : LP_WORD(L_P_PRESETS),
	sibilings : true,
	length    : LENGTH(preset_items),
	items     : preset_items,
	rename    : true,
	ordering  : presets_config.order,
	actions   : {
		[MENU_EVENT_OPEN] = menu_preset_open,
	}
};

void menu_preset_open() {
	int i;

	menupage_presets.highlight        = status.preset_active ? true : false;
	menupage_presets.highlighted_item = presets_config.last_preset;

	for (i = 0; i < PRESETS_MAX; i++) {
		// Create first item in sub-menu: FREE / LOAD / SAVE
		if (status.main_dial_ae == AE_MODE_AUTO) {
			if(status.preset_active && i == presets_config.last_preset) {
				menupage_preset_items[i][0].id      = i;
				menupage_preset_items[i][0].display = menuitem_display;
				menupage_preset_items[i][0].name    = LP_WORD(L_I_FREE);
				menupage_preset_items[i][0].action  = menu_preset_free;
			} else {
				menupage_preset_items[i][0].id      = i;
				menupage_preset_items[i][0].display = menuitem_display;
				menupage_preset_items[i][0].name    = LP_WORD(L_I_LOAD);
				menupage_preset_items[i][0].action  = menu_preset_load;
			}
		} else if (status.main_dial_ae < AE_MODE_AUTO) {
			menupage_preset_items[i][0].id      = i;
			menupage_preset_items[i][0].display = menuitem_display;
			menupage_preset_items[i][0].name    = LP_WORD(L_I_SAVE);
			menupage_preset_items[i][0].action  = menu_preset_save;
		} else {
			menupage_preset_items[i][0].id      = i;
			menupage_preset_items[i][0].display = menuitem_display;
			menupage_preset_items[i][0].name    = "-";
		}

		// Create second item in sub-menu: RENAME
		menupage_preset_items[i][1].id      = i;
		menupage_preset_items[i][1].display = menuitem_display;
		menupage_preset_items[i][1].name    = LP_WORD(L_I_RENAME);
		menupage_preset_items[i][1].action  = menu_preset_rename;

		// Create third item in sub-menu: DELETE
		menupage_preset_items[i][2].id      = i;
		menupage_preset_items[i][2].display = menuitem_display;
		menupage_preset_items[i][2].name    = LP_WORD(L_I_DELETE);
		menupage_preset_items[i][2].action  = menu_preset_delete;

		// Configure sub-menu
		menupage_preset[i].name    = presets_config.names[i];
		menupage_preset[i].length  = LENGTH(menupage_preset_items[i]);
		menupage_preset[i].items   = menupage_preset_items[i];

		menupage_preset[i].actions[MENU_EVENT_AV] = menu_return;

		// Add sub-menu to page
		preset_items[i].id      = i;
		preset_items[i].name    = presets_config.names[i];
		preset_items[i].display = menuitem_display_sub;
		preset_items[i].inc     = menuitem_inc_sub;
		preset_items[i].action  = menupage_preset_items[i][0].action;

		preset_items[i].parm.menuitem_submenu.page =  &menupage_preset[i];
	}
}

void menu_preset_save(const type_MENUITEM *item) {
	if (status.main_dial_ae < AE_MODE_AUTO)
		if (preset_write(item->id)) {
			beep();
			menu_close();
		}
}

void menu_preset_load(const type_MENUITEM *item) {
	snapshot_t preset;

	if (status.main_dial_ae == AE_MODE_AUTO) {
		if (preset_read(item->id, &preset)) {
			snapshot_recall(&preset);
			snapshot_apply (&preset);

			status.preset_active       = true;
			presets_config.last_preset = item->id;

			beep();
			menu_close();
			presets_write();
		}
	}
}

void menu_preset_free(const type_MENUITEM *item) {
	if (status.main_dial_ae == AE_MODE_AUTO) {
		status.preset_active       = false;
		presets_config.last_preset = PRESET_NONE;

		send_to_intercom(IC_SET_AE, 1, AE_MODE_AUTO);

		beep();
		menu_close();
		presets_write();
	}
}

void menu_preset_rename(const type_MENUITEM *item) {
	rename_create(presets_config.names[item->id]);
}

void menu_preset_delete(const type_MENUITEM *item) {
	if (preset_delete(item->id)) {
		beep();
		menu_close();
	}
}
