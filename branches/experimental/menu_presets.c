#include "main.h"
#include "menu.h"
#include "utils.h"
#include "settings.h"
#include "scripts.h"
#include "presets.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "firmware.h"
#include "languages.h"

#include "menu_presets.h"

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

type_MENUITEM presets_save_items[] = {
	MENUITEM_TASK (presets_config.names[0], preset_save_1),
	MENUITEM_TASK (presets_config.names[1], preset_save_2),
	MENUITEM_TASK (presets_config.names[2], preset_save_3),
	MENUITEM_TASK (presets_config.names[3], preset_save_4),
	MENUITEM_TASK (presets_config.names[4], preset_save_5),
	MENUITEM_TASK (presets_config.names[5], preset_save_6),
	MENUITEM_TASK (presets_config.names[6], preset_save_7),
	MENUITEM_TASK (presets_config.names[7], preset_save_8),
	MENUITEM_TASK (presets_config.names[8], preset_save_9)
};

type_MENUITEM presets_load_items[] = {
	MENUITEM_TASK (presets_config.names[0], preset_load_1),
	MENUITEM_TASK (presets_config.names[1], preset_load_2),
	MENUITEM_TASK (presets_config.names[2], preset_load_3),
	MENUITEM_TASK (presets_config.names[3], preset_load_4),
	MENUITEM_TASK (presets_config.names[4], preset_load_5),
	MENUITEM_TASK (presets_config.names[5], preset_load_6),
	MENUITEM_TASK (presets_config.names[6], preset_load_7),
	MENUITEM_TASK (presets_config.names[7], preset_load_8),
	MENUITEM_TASK (presets_config.names[8], preset_load_9)
};

type_MENU menu_presets_save = {
	name        : LP_WORD(L_SAVE_PRESETS),
	length      : LENGTH(presets_save_items),
	items       : presets_save_items,
	dp_action   : menu_settings_start,
	rename      : TRUE,
	save        : presets_write,
	callback    : menu_presets_save_start,
	reorder     : TRUE,
	ordering    : presets_config.order
};

type_MENU menu_presets_load = {
	name        : LP_WORD(L_LOAD_PRESETS),
	length      : LENGTH(presets_load_items),
	items       : presets_load_items,
	dp_action   : menu_shortcuts_start,
	rename      : TRUE,
	save        : presets_write,
	callback    : menu_presets_load_start,
	reorder     : TRUE,
	ordering    : presets_config.order
};

void menu_presets_save_start() {
	menu_create(&menu_presets_save);
}

void menu_presets_load_start() {
	if (!presets_config.use_adep || status.main_dial_ae == AE_MODE_ADEP)
		menu_create(&menu_presets_load);
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
	beep();

	preset_write(id);

	menu_close();
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
	beep();

	if (preset_read(id))
		preset_apply();

	menu_close();
}
