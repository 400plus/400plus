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

void menupage_preset_action (type_MENU *menu);

void menu_preset_save   (const type_MENUITEM *item);
void menu_preset_load   (const type_MENUITEM *item);
void menu_preset_free   (const type_MENUITEM *item);
void menu_preset_rename (const type_MENUITEM *item);
void menu_preset_delete (const type_MENUITEM *item);

type_MENUITEM preset_1_items[] = {
	MENUITEM_LAUNCH(1, "",                  NULL),
	MENUITEM_LAUNCH(1, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(1, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_2_items[] = {
	MENUITEM_LAUNCH(2, "",                  NULL),
	MENUITEM_LAUNCH(2, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(2, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_3_items[] = {
	MENUITEM_LAUNCH(3, "",                  NULL),
	MENUITEM_LAUNCH(3, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(3, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_4_items[] = {
	MENUITEM_LAUNCH(4, "",                  NULL),
	MENUITEM_LAUNCH(4, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(4, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_5_items[] = {
	MENUITEM_LAUNCH(5, "",                  NULL),
	MENUITEM_LAUNCH(5, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(5, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_6_items[] = {
	MENUITEM_LAUNCH(6, "",                  NULL),
	MENUITEM_LAUNCH(6, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(6, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_7_items[] = {
	MENUITEM_LAUNCH(7, "",                  NULL),
	MENUITEM_LAUNCH(7, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(7, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_8_items[] = {
	MENUITEM_LAUNCH(8, "",                  NULL),
	MENUITEM_LAUNCH(8, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(8, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUITEM preset_9_items[] = {
	MENUITEM_LAUNCH(9, "",                  NULL),
	MENUITEM_LAUNCH(9, LP_WORD(L_I_RENAME), menu_preset_rename),
	MENUITEM_LAUNCH(9, LP_WORD(L_I_DELETE), menu_preset_delete),
};

type_MENUPAGE menupage_preset[] = {
	{
		name    : presets_config.names[0],
		length  : LENGTH(preset_1_items),
		items   : preset_1_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		},
	},
	{
		name    : presets_config.names[1],
		length  : LENGTH(preset_2_items),
		items   : preset_2_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[2],
		length  : LENGTH(preset_3_items),
		items   : preset_3_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[3],
		length  : LENGTH(preset_4_items),
		items   : preset_4_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[4],
		length  : LENGTH(preset_5_items),
		items   : preset_5_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[5],
		length  : LENGTH(preset_6_items),
		items   : preset_6_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[6],
		length  : LENGTH(preset_7_items),
		items   : preset_7_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[7],
		length  : LENGTH(preset_8_items),
		items   : preset_8_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	},
	{
		name    : presets_config.names[8],
		length  : LENGTH(preset_9_items),
		items   : preset_9_items,
		actions : {
			[MENU_EVENT_AV]   = menu_return,
		}
	}
};

type_MENUITEM preset_items[] = {
	MENUITEM_SUBMENU(1, presets_config.names[0], &menupage_preset[0], NULL),
	MENUITEM_SUBMENU(2, presets_config.names[1], &menupage_preset[1], NULL),
	MENUITEM_SUBMENU(3, presets_config.names[2], &menupage_preset[2], NULL),
	MENUITEM_SUBMENU(4, presets_config.names[3], &menupage_preset[3], NULL),
	MENUITEM_SUBMENU(5, presets_config.names[4], &menupage_preset[4], NULL),
	MENUITEM_SUBMENU(6, presets_config.names[5], &menupage_preset[5], NULL),
	MENUITEM_SUBMENU(7, presets_config.names[6], &menupage_preset[6], NULL),
	MENUITEM_SUBMENU(8, presets_config.names[7], &menupage_preset[7], NULL),
	MENUITEM_SUBMENU(9, presets_config.names[8], &menupage_preset[8], NULL),
};

type_MENUPAGE menupage_presets = {
	name      : LP_WORD(L_P_PRESETS),
	sibilings : true,
	length    : LENGTH(preset_items),
	items     : preset_items,
	rename    : true,
	ordering  : presets_config.order,
	actions   : {
		[MENU_EVENT_OPEN] = menu_preset_open,
		[MENU_EVENT_SET ] = menupage_preset_action,
	}
};

void menu_preset_open() {
	int i;

	menupage_presets.highlight        = status.preset_active ? true : false;
	menupage_presets.highlighted_item = presets_config.last_preset;

	if (status.main_dial_ae == AE_MODE_AUTO)
		for (i=0; i < 9; i++) {
			if(status.preset_active && i +1 == presets_config.last_preset) {
				menupage_presets.items[i].parm.menuitem_submenu.page->items[0].name   = LP_WORD(L_I_FREE);
				menupage_presets.items[i].parm.menuitem_submenu.page->items[0].action = menu_preset_free;
			} else {
				menupage_presets.items[i].parm.menuitem_submenu.page->items[0].name   = LP_WORD(L_I_LOAD);
				menupage_presets.items[i].parm.menuitem_submenu.page->items[0].action = menu_preset_load;
			}
		}
	else if (status.main_dial_ae < AE_MODE_AUTO)
		for (i=0; i < 9; i++) {
			menupage_presets.items[i].parm.menuitem_submenu.page->items[0].name   = LP_WORD(L_I_SAVE);
			menupage_presets.items[i].parm.menuitem_submenu.page->items[0].action = menu_preset_save;
		}
	else
		for (i=0; i < 9; i++) {
			menupage_presets.items[i].parm.menuitem_submenu.page->items[0].name   = "-";
			menupage_presets.items[i].parm.menuitem_submenu.page->items[0].action = NULL;
		}
}

void menupage_preset_action(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;
	type_MENUITEM *item = get_current_item(page);

	itemaction_t action = item->parm.menuitem_submenu.page->items[0].action;

	if (action)
		action(item);
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
		presets_config.last_preset = 0;

		send_to_intercom(IC_SET_AE, 1, AE_MODE_AUTO);

		beep();
		menu_close();
		presets_write();
	}
}

void menu_preset_rename(const type_MENUITEM *item) {
	rename_create(presets_config.names[item->id - 1]);
}

void menu_preset_delete(const type_MENUITEM *item) {
	if (preset_delete(item->id)) {
		beep();
		menu_close();
	}
}
