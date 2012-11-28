/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "macros.h"
#include "main.h"

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

void preset_save_1();
void preset_save_2();
void preset_save_3();
void preset_save_4();
void preset_save_5();
void preset_save_6();
void preset_save_7();
void preset_save_8();
void preset_save_9();

void preset_load_1();
void preset_load_2();
void preset_load_3();
void preset_load_4();
void preset_load_5();
void preset_load_6();
void preset_load_7();
void preset_load_8();
void preset_load_9();

void preset_load(int id);

void preset_rename_1();
void preset_rename_2();
void preset_rename_3();
void preset_rename_4();
void preset_rename_5();
void preset_rename_6();
void preset_rename_7();
void preset_rename_8();
void preset_rename_9();

void preset_delete_1();
void preset_delete_2();
void preset_delete_3();
void preset_delete_4();
void preset_delete_5();
void preset_delete_6();
void preset_delete_7();
void preset_delete_8();
void preset_delete_9();

type_MENUITEM preset_1_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_1),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_1),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_1),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_1),
};

type_MENUITEM preset_2_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_2),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_2),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_2),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_2),
};

type_MENUITEM preset_3_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_3),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_3),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_3),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_3),
};

type_MENUITEM preset_4_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_4),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_4),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_4),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_4),
};

type_MENUITEM preset_5_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_5),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_5),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_5),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_5),
};

type_MENUITEM preset_6_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_6),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_6),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_6),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_6),
};

type_MENUITEM preset_7_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_7),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_7),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_7),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_7),
};

type_MENUITEM preset_8_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_8),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_8),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_8),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_8),
};

type_MENUITEM preset_9_items[] = {
	MENUITEM_LAUNCH(LP_WORD(L_I_LOAD),   preset_load_9),
	MENUITEM_LAUNCH(LP_WORD(L_I_SAVE),   preset_save_9),
	MENUITEM_LAUNCH(LP_WORD(L_I_RENAME), preset_rename_9),
	MENUITEM_LAUNCH(LP_WORD(L_I_DELETE), preset_delete_9),
};

type_MENUPAGE menupage_preset_1 = {
	name    : presets_config.names[0],
	length  : LENGTH(preset_1_items),
	items   : preset_1_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_2 = {
	name    : presets_config.names[1],
	length  : LENGTH(preset_2_items),
	items   : preset_2_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_3 = {
	name    : presets_config.names[2],
	length  : LENGTH(preset_3_items),
	items   : preset_3_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_4 = {
	name    : presets_config.names[3],
	length  : LENGTH(preset_4_items),
	items   : preset_4_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_5 = {
	name    : presets_config.names[4],
	length  : LENGTH(preset_5_items),
	items   : preset_5_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_6 = {
	name    : presets_config.names[5],
	length  : LENGTH(preset_6_items),
	items   : preset_6_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_7 = {
	name    : presets_config.names[6],
	length  : LENGTH(preset_7_items),
	items   : preset_7_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_8 = {
	name    : presets_config.names[7],
	length  : LENGTH(preset_8_items),
	items   : preset_8_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUPAGE menupage_preset_9 = {
	name    : presets_config.names[8],
	length  : LENGTH(preset_9_items),
	items   : preset_9_items,
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUITEM preset_items[] = {
	MENUITEM_SUBMENU(presets_config.names[0], &menupage_preset_1, preset_load_1),
	MENUITEM_SUBMENU(presets_config.names[1], &menupage_preset_2, preset_load_2),
	MENUITEM_SUBMENU(presets_config.names[2], &menupage_preset_3, preset_load_3),
	MENUITEM_SUBMENU(presets_config.names[3], &menupage_preset_4, preset_load_4),
	MENUITEM_SUBMENU(presets_config.names[4], &menupage_preset_5, preset_load_5),
	MENUITEM_SUBMENU(presets_config.names[5], &menupage_preset_6, preset_load_6),
	MENUITEM_SUBMENU(presets_config.names[6], &menupage_preset_7, preset_load_7),
	MENUITEM_SUBMENU(presets_config.names[7], &menupage_preset_8, preset_load_8),
	MENUITEM_SUBMENU(presets_config.names[8], &menupage_preset_9, preset_load_9),
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
	}
};

void menu_preset_open() {
	if (status.preset_active) {
		menupage_presets.highlight        = true;
		menupage_presets.highlighted_item = presets_config.last_preset;
	} else {
		menupage_presets.highlight        = false;
	}
}

void preset_save_1() { if (preset_write(1)) beep(); }
void preset_save_2() { if (preset_write(2)) beep(); }
void preset_save_3() { if (preset_write(3)) beep(); }
void preset_save_4() { if (preset_write(4)) beep(); }
void preset_save_5() { if (preset_write(5)) beep(); }
void preset_save_6() { if (preset_write(6)) beep(); }
void preset_save_7() { if (preset_write(7)) beep(); }
void preset_save_8() { if (preset_write(8)) beep(); }
void preset_save_9() { if (preset_write(9)) beep(); }

void preset_load_1() { preset_load(1); }
void preset_load_2() { preset_load(2); }
void preset_load_3() { preset_load(3); }
void preset_load_4() { preset_load(4); }
void preset_load_5() { preset_load(5); }
void preset_load_6() { preset_load(6); }
void preset_load_7() { preset_load(7); }
void preset_load_8() { preset_load(8); }
void preset_load_9() { preset_load(9); }

void preset_load(int id) {
	snapshot_t preset;

	if (!presets_config.use_adep || status.main_dial_ae == AE_MODE_ADEP) {
		if (preset_read(id, &preset)) {
			snapshot_apply_full(&preset);

			status.preset_active       = true;
			presets_config.last_preset = id;

			beep();
			menu_close();
			presets_write();
		}
	}
}

void preset_rename_1() { rename_create(presets_config.names[0]); }
void preset_rename_2() { rename_create(presets_config.names[1]); }
void preset_rename_3() { rename_create(presets_config.names[2]); }
void preset_rename_4() { rename_create(presets_config.names[3]); }
void preset_rename_5() { rename_create(presets_config.names[4]); }
void preset_rename_6() { rename_create(presets_config.names[5]); }
void preset_rename_7() { rename_create(presets_config.names[6]); }
void preset_rename_8() { rename_create(presets_config.names[7]); }
void preset_rename_9() { rename_create(presets_config.names[8]); }

void preset_delete_1() { preset_delete(1); beep(); }
void preset_delete_2() { preset_delete(2); beep(); }
void preset_delete_3() { preset_delete(3); beep(); }
void preset_delete_4() { preset_delete(4); beep(); }
void preset_delete_5() { preset_delete(5); beep(); }
void preset_delete_6() { preset_delete(6); beep(); }
void preset_delete_7() { preset_delete(7); beep(); }
void preset_delete_8() { preset_delete(8); beep(); }
void preset_delete_9() { preset_delete(9); beep(); }

