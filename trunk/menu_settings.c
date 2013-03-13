/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <unistd.h>
#include <stdbool.h>

#include "macros.h"

#include "cmodes.h"
#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"
#include "utils.h"

#include "menu_settings.h"

extern char languages_found[MAX_LANGUAGES][LP_MAX_WORD];

void menu_settings_open();

void menu_restore_settings();
void menu_restore_cmodes  ();
void menu_delete_cmodes   ();

void reload_language_and_refresh(const menuitem_t *item);

menuitem_t scripts_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_KEEP_POWER_ON), &settings.keep_power_on,    NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_REVIEW_OFF),    &settings.review_off,       NULL),
	MENUITEM_SCRLCD( 0, LP_WORD(L_I_LCD_SCRIPT),    &settings.script_lcd,       NULL),
	MENUITEM_SCRIND( 0, LP_WORD(L_I_INDICATOR),     &settings.script_indicator, NULL),
};

menuitem_t buttons_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_USE_DPAD),    &settings.use_dpad,     NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_BUTTON_DISP), &settings.button_disp,  NULL),
	MENUITEM_BTNACTN(0, LP_WORD(L_I_BTN_JUMP),    &settings.button_jump,  NULL),
	MENUITEM_BTNACTN(0, LP_WORD(L_I_BTN_TRASH),   &settings.button_trash, NULL),
};

menuitem_t cmodes_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_CAMERA),   &cmodes_config.recall_camera,   NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_400PLUS),  &cmodes_config.recall_400plus,  NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_ORDERING), &cmodes_config.recall_ordering, NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_SETTINGS), &cmodes_config.recall_settings, NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_IMAGE),    &cmodes_config.recall_image,    NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_CMODES_CFN),      &cmodes_config.recall_cfn,      NULL),
};

menuitem_t menus_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_WRAP_MENUS),    &settings.menu_wrap,      NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_NAVIGATE_MAIN), &settings.menu_navmain,   NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_ENTER_MAIN),    &settings.menu_entermain, NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_AUTOSAVE),      &settings.menu_autosave,  NULL),
};

menuitem_t qexp_items[] = {
	MENUITEM_TV(    0, LP_WORD(L_I_QEXP_MINTV),  &settings.qexp_mintv,  NULL),
	MENUITEM_WEIGTH(0, LP_WORD(L_I_QEXP_WEIGTH), &settings.qexp_weight, NULL),
};

menuitem_t pages_items[] = {
	MENUITEM_INFO(0, LP_WORD(L_P_PARAMS),     NULL),
	MENUITEM_INFO(0, LP_WORD(L_P_SCRIPTS),    NULL),
	MENUITEM_INFO(0, LP_WORD(L_P_INFO),       NULL),
	MENUITEM_INFO(0, LP_WORD(L_P_SETTINGS),   NULL),
	MENUITEM_INFO(0, LP_WORD(L_P_CMODES),     NULL),
};

menuitem_t restore_items[] = {
	MENUITEM_LAUNCH(0, LP_WORD(L_I_RESTORE_SETTINGS), menu_restore_settings),
	MENUITEM_LAUNCH(0, LP_WORD(L_I_RESTORE_CMODES),   menu_restore_cmodes  ),
	MENUITEM_LAUNCH(0, LP_WORD(L_I_DELETE_CMODES),    menu_delete_cmodes   ),
};

menupage_t scripts_page = {
	name    : LP_WORD(L_S_SCRIPTS),
	items   : LIST(scripts_items),
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t buttons_page = {
	name    : LP_WORD(L_S_BUTTONS),
	items   : LIST(buttons_items),
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t cmodes_page = {
	name    : LP_WORD(L_S_CMODES),
	items   : LIST(cmodes_items),
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t menus_page = {
	name    : LP_WORD(L_S_MENUS),
	items   : LIST(menus_items),
	actions : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t qexp_page = {
	name     : LP_WORD(L_S_QEXP),
	items    : LIST(qexp_items),
	actions  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t pages_page = {
	name     : LP_WORD(L_S_PAGES),
	items    : LIST(pages_items),
	ordering : menu_order.main,
	actions  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t restore_page = {
	name     : LP_WORD(L_I_RESTORE),
	items    : LIST(restore_items),
	actions  : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

menuitem_t menu_settings_items[] = {
	MENUITEM_LANG   (0, LP_WORD(L_I_LANGUAGE),         &settings.language,         reload_language_and_refresh),
	MENUITEM_DIG_ISO(0, LP_WORD(L_I_DIG_ISO_STEP),     &settings.digital_iso_step, NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_PERSIST_AEB),      &settings.persist_aeb,      NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_SCRIPTS),          &scripts_page,              NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_BUTTONS),          &buttons_page,              NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_CMODES),           &cmodes_page,               NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_MENUS),            &menus_page,                NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_QEXP),             &qexp_page,                 NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_PAGES),            &pages_page,                NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_I_RESTORE),          &restore_page,              NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DEVELOPERS_MENU),  &settings.developers_menu,  NULL),
};

menupage_t menupage_settings = {
	name      : LP_WORD(L_P_SETTINGS),
	sibilings : true,
	items     : LIST(menu_settings_items),
	ordering  : menu_order.settings,
	actions   : {
		[MENU_EVENT_OPEN] = menu_settings_open,
	}
};

void reload_language_and_refresh(const menuitem_t *item) {
	lang_pack_config();
	menu_event_display();
}

void menu_settings_open() {
	int i;

	for (i = 0; i<MAX_LANGUAGES && languages_found[i] != '\0' && languages_found[i][0] != '\0'; i++) {
		menupage_settings.items.data[0].parm.menuitem_enum.list->size    = i + 1;
		menupage_settings.items.data[0].parm.menuitem_enum.list->data[i] = languages_found[i];
	}
}

void menu_restore_settings() {
	settings_restore();
	menu_return();
	beep();
}

void menu_restore_cmodes  () {
	cmodes_restore();
	menu_return();
	beep();
}

void menu_delete_cmodes   () {
	cmodes_delete();
	menu_return();
	beep();
}
