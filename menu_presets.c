#include "main.h"

#include "languages.h"
#include "menu.h"
#include "menu_rename.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "presets.h"
#include "utils.h"

#include "menu_presets.h"

void menu_preset_display();

void preset_save_1();
void preset_save_2();
void preset_save_3();
void preset_save_4();
void preset_save_5();
void preset_save_6();
void preset_save_7();
void preset_save_8();
void preset_save_9();

void preset_save(int id);

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

void preset_rename(int id);

type_MENUITEM preset_1_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_1),
	MENUITEM_LAUNCH("Save",   preset_save_1),
	MENUITEM_LAUNCH("Rename", preset_rename_1),
};

type_MENUITEM preset_2_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_2),
	MENUITEM_LAUNCH("Save",   preset_save_2),
	MENUITEM_LAUNCH("Rename", preset_rename_2),
};

type_MENUITEM preset_3_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_3),
	MENUITEM_LAUNCH("Save",   preset_save_3),
	MENUITEM_LAUNCH("Rename", preset_rename_3),
};

type_MENUITEM preset_4_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_4),
	MENUITEM_LAUNCH("Save",   preset_save_4),
	MENUITEM_LAUNCH("Rename", preset_rename_4),
};

type_MENUITEM preset_5_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_5),
	MENUITEM_LAUNCH("Save",   preset_save_5),
	MENUITEM_LAUNCH("Rename", preset_rename_5),
};

type_MENUITEM preset_6_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_6),
	MENUITEM_LAUNCH("Save",   preset_save_6),
	MENUITEM_LAUNCH("Rename", preset_rename_6),
};

type_MENUITEM preset_7_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_7),
	MENUITEM_LAUNCH("Save",   preset_save_7),
	MENUITEM_LAUNCH("Rename", preset_rename_7),
};

type_MENUITEM preset_8_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_8),
	MENUITEM_LAUNCH("Save",   preset_save_8),
	MENUITEM_LAUNCH("Rename", preset_rename_8),
};

type_MENUITEM preset_9_items[] = {
	MENUITEM_LAUNCH("Load",   preset_load_9),
	MENUITEM_LAUNCH("Save",   preset_save_9),
	MENUITEM_LAUNCH("Rename", preset_rename_9),
};

type_MENUPAGE menupage_preset_1 = {
	name        : presets_config.names[0],
	length      : LENGTH(preset_1_items),
	items       : preset_1_items,
};

type_MENUPAGE menupage_preset_2 = {
	name        : presets_config.names[1],
	length      : LENGTH(preset_2_items),
	items       : preset_2_items,
};

type_MENUPAGE menupage_preset_3 = {
	name        : presets_config.names[2],
	length      : LENGTH(preset_3_items),
	items       : preset_3_items,
};

type_MENUPAGE menupage_preset_4 = {
	name        : presets_config.names[3],
	length      : LENGTH(preset_4_items),
	items       : preset_4_items,
};

type_MENUPAGE menupage_preset_5 = {
	name        : presets_config.names[4],
	length      : LENGTH(preset_5_items),
	items       : preset_5_items,
};

type_MENUPAGE menupage_preset_6 = {
	name        : presets_config.names[5],
	length      : LENGTH(preset_6_items),
	items       : preset_6_items,
};

type_MENUPAGE menupage_preset_7 = {
	name        : presets_config.names[6],
	length      : LENGTH(preset_7_items),
	items       : preset_7_items,
};

type_MENUPAGE menupage_preset_8 = {
	name        : presets_config.names[7],
	length      : LENGTH(preset_8_items),
	items       : preset_8_items,
};

type_MENUPAGE menupage_preset_9 = {
	name        : presets_config.names[8],
	length      : LENGTH(preset_9_items),
	items       : preset_9_items,
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
	name        : "Presets",
	length      : LENGTH(preset_items),
	items       : preset_items,
	rename      : TRUE,
	reorder     : TRUE,
	ordering    : presets_config.order,
	tasks       : {
		[MENU_EVENT_DISP] = menu_preset_display,
	}
};

void menu_preset_display() {
	if (status.last_preset) {
		menupage_presets.highlight        = TRUE;
		menupage_presets.highlighted_item = status.last_preset;
	} else {
		menupage_presets.highlight        = FALSE;
	}
}

void preset_save_1() { preset_save(1); }

void preset_save_2() { preset_save(2); }

void preset_save_3() { preset_save(3); }

void preset_save_4() { preset_save(4); }

void preset_save_5() { preset_save(5); }

void preset_save_6() { preset_save(6); }

void preset_save_7() { preset_save(7); }

void preset_save_8() { preset_save(8); }

void preset_save_9() { preset_save(9); }

void preset_save(int id) {
	if (preset_write(id)) {
		status.last_preset = id;

		beep();
		menu_close();
	}
}

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
	if (!presets_config.use_adep || status.main_dial_ae == AE_MODE_ADEP) {
		if (preset_read(id)) {
			preset_apply_full();
			preset_write(0);

			status.last_preset = id;

			beep();
			menu_close();
		}
	}
}

void preset_rename_1() { preset_rename(1); }
void preset_rename_2() { preset_rename(2); }
void preset_rename_3() { preset_rename(3); }
void preset_rename_4() { preset_rename(4); }
void preset_rename_5() { preset_rename(5); }
void preset_rename_6() { preset_rename(6); }
void preset_rename_7() { preset_rename(7); }
void preset_rename_8() { preset_rename(8); }
void preset_rename_9() { preset_rename(9); }

void preset_rename(int id) {
	rename_create(presets_config.names[0], presets_write);
}
