#include <vxworks.h>

#include "firmware.h"

#include "main.h"
#include "macros.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_rename.h"
#include "persist.h"
#include "settings.h"
#include "utils.h"
#include "intercom.h"

#include "menu_params.h"

void menu_params_apply_autoiso_miniso     (const menuitem_t *item);
void menu_params_apply_autoiso_maxiso     (const menuitem_t *item);
void menu_params_apply_iso                (const menuitem_t *item);
void menu_params_apply_av_comp            (const menuitem_t *item);
void menu_params_apply_efcomp             (const menuitem_t *item);
void menu_params_apply_cf_emit_flash      (const menuitem_t *item);
void menu_params_apply_ae_bkt             (const menuitem_t *item);
void menu_params_apply_color_temp         (const menuitem_t *item);
void menu_params_apply_named_temp         (const menuitem_t *item);
void menu_params_apply_cf_emit_aux        (const menuitem_t *item);
void menu_params_apply_cf_mirror_up_lock  (const menuitem_t *item);
void menu_params_apply_cf_flash_sync_rear (const menuitem_t *item);
void menu_params_apply_cf_safety_shift    (const menuitem_t *item);
void menu_params_apply_remote_enable      (const menuitem_t *item);
void menu_params_apply_remote_delay       (const menuitem_t *item);

void menu_params_rename (menu_t *menu);

menuitem_t autoiso_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_AUTOISO_ENABLE), &settings.autoiso_enable,  NULL),
	MENUITEM_BASEISO(0, LP_WORD(L_I_AUTOISO_MINISO), &settings.autoiso_miniso,  menu_params_apply_autoiso_miniso),
	MENUITEM_BASEISO(0, LP_WORD(L_I_AUTOISO_MAXISO), &settings.autoiso_maxiso,  menu_params_apply_autoiso_maxiso),
	MENUITEM_TV     (0, LP_WORD(L_I_AUTOISO_MINTV),  &settings.autoiso_mintv,   NULL),
	MENUITEM_EVEAEB (0, LP_WORD(L_I_AUTOISO_MAXAV),  &settings.autoiso_maxav,   NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_AUTOISO_RELAX),  &settings.autoiso_relaxed, NULL),
};

menupage_t autoiso_page = {
	name     : LP_WORD(L_S_AUTOISO),
	items    : LIST(autoiso_items),
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menuitem_t named_temps_items[] = {
	MENUITEM_NAMEDCT( 0, named_temps.names[ 0], &named_temps.temps[ 0], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 1, named_temps.names[ 1], &named_temps.temps[ 1], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 2, named_temps.names[ 2], &named_temps.temps[ 2], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 3, named_temps.names[ 3], &named_temps.temps[ 3], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 4, named_temps.names[ 4], &named_temps.temps[ 4], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 5, named_temps.names[ 5], &named_temps.temps[ 5], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 6, named_temps.names[ 6], &named_temps.temps[ 6], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 7, named_temps.names[ 7], &named_temps.temps[ 7], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 8, named_temps.names[ 8], &named_temps.temps[ 8], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT( 9, named_temps.names[ 9], &named_temps.temps[ 9], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(10, named_temps.names[10], &named_temps.temps[10], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(11, named_temps.names[11], &named_temps.temps[11], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(12, named_temps.names[12], &named_temps.temps[12], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(13, named_temps.names[13], &named_temps.temps[13], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(14, named_temps.names[14], &named_temps.temps[14], menu_params_apply_named_temp),
	MENUITEM_NAMEDCT(15, named_temps.names[15], &named_temps.temps[15], menu_params_apply_named_temp),
};

menupage_t named_temps_page = {
	name     : LP_WORD(L_S_NAMED_TEMPS),
	items    : LIST(named_temps_items),
	ordering : menu_order.named_temps,
	actions  : {
		[MENU_EVENT_OPEN] = named_temps_init,
		[MENU_EVENT_AV]   = menu_return,
		[MENU_EVENT_JUMP] = menu_params_rename,
	}
};

menuitem_t flash_items[] = {
	MENUITEM_EVCOMP (0, LP_WORD(L_I_FLASH_COMP),    &menu_DPData.efcomp,             menu_params_apply_efcomp),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_USE_FLASH),     &menu_DPData.cf_emit_flash,      menu_params_apply_cf_emit_flash),
	MENUITEM_AFFLASH(0, LP_WORD(L_I_AF_FLASH),      &menu_DPData.cf_emit_aux,        menu_params_apply_cf_emit_aux),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_FLASH_2ND_CURT),&menu_DPData.cf_flash_sync_rear, menu_params_apply_cf_flash_sync_rear),
};

menupage_t flash_page = {
	name     : LP_WORD(L_S_FLASH),
	items    : LIST(flash_items),
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};
/*
menuitem_t ir_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_IR_REMOTE_ENABLE), &settings.remote_enable,          menu_params_apply_remote_enable),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_IR_REMOTE_DELAY),  &settings.remote_delay,           menu_params_apply_remote_delay),
};

menupage_t ir_page = {
	name     : LP_WORD(L_S_IR),
	length   : LENGTH(ir_items),
	items    : ir_items,
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};
*/
menuitem_t menupage_params_items[] = {
	MENUITEM_SUBMENU(MENUPAGE_PARAMS_AUTOISO,       LP_WORD(L_S_AUTOISO),          &autoiso_page,                  NULL),
	MENUITEM_FULLISO(MENUPAGE_PARAMS_ISO,           LP_WORD(L_I_ISO),              &menu_DPData.iso,               menu_params_apply_iso),
	MENUITEM_EVCOMP (MENUPAGE_PARAMS_AVCOMP,        LP_WORD(L_I_AV_COMP),          &menu_DPData.av_comp,           menu_params_apply_av_comp),
	MENUITEM_EVSEP  (MENUPAGE_PARAMS_AEB,           LP_WORD(L_I_AEB),              &menu_DPData.ae_bkt,            menu_params_apply_ae_bkt),
	MENUITEM_CLRTEMP(MENUPAGE_PARAMS_COLOR_TEMP,    LP_WORD(L_I_COLOR_TEMP_K),     &menu_DPData.color_temp,        menu_params_apply_color_temp),
	MENUITEM_SUBMENU(MENUPAGE_PARAMS_NAMED_TEMPS,   LP_WORD(L_S_NAMED_TEMPS),      &named_temps_page,              NULL),
	MENUITEM_BOOLEAN(MENUPAGE_PARAMS_MIRROR_LOCKUP, LP_WORD(L_I_MIRROR_LOCKUP),    &menu_DPData.cf_mirror_up_lock, menu_params_apply_cf_mirror_up_lock),
	MENUITEM_BOOLEAN(MENUPAGE_PARAMS_SAFETY_SHIFT,  LP_WORD(L_I_SAFETY_SHIFT),     &menu_DPData.cf_safety_shift,   menu_params_apply_cf_safety_shift),
	MENUITEM_BOOLEAN(MENUPAGE_PARAMS_IR_REMOTE,     LP_WORD(L_I_IR_REMOTE_ENABLE), &settings.remote_enable,        menu_params_apply_remote_enable),
	MENUITEM_SUBMENU(MENUPAGE_PARAMS_FLASH,         LP_WORD(L_S_FLASH),            &flash_page,                    NULL),
};

menupage_t menupage_params = {
	name      : LP_WORD(L_P_PARAMS),
	sibilings : TRUE,
	items     : LIST(menupage_params_items),
	ordering  : menu_order.params,
};

void menu_params_apply_autoiso_miniso(const menuitem_t *item) {
	settings.autoiso_maxiso = MAX(settings.autoiso_miniso, settings.autoiso_maxiso);
	menu_event_display();
}

void menu_params_apply_autoiso_maxiso(const menuitem_t *item) {
	settings.autoiso_miniso = MIN(settings.autoiso_miniso, settings.autoiso_maxiso);
	menu_event_display();
}

void menu_params_apply_iso(const menuitem_t *item) {
	send_to_intercom(IC_SET_ISO, *item->parm.menuitem_iso.value);
}

void menu_params_apply_av_comp(const menuitem_t *item) {
	send_to_intercom(IC_SET_AV_COMP, *item->parm.menuitem_ec.value);
}

void menu_params_apply_efcomp(const menuitem_t *item) {
	send_to_intercom(IC_SET_EFCOMP, *item->parm.menuitem_ec.value);
}

void menu_params_apply_cf_emit_flash(const menuitem_t *item) {
	send_to_intercom(IC_SET_CF_EMIT_FLASH, *item->parm.menuitem_enum.value);
}

void menu_params_apply_ae_bkt(const menuitem_t *item) {
	send_to_intercom(IC_SET_AE_BKT, *item->parm.menuitem_ec.value);
}

void menu_params_apply_color_temp(const menuitem_t *item) {
	send_to_intercom(IC_SET_WB,         WB_MODE_COLORTEMP);
	send_to_intercom(IC_SET_COLOR_TEMP, *item->parm.menuitem_int.value);
}

void menu_params_apply_named_temp(const menuitem_t *item) {
	menu_params_apply_color_temp(item);

	beep();
	menu_close();
}

void menu_params_apply_cf_emit_aux(const menuitem_t *item) {
	send_to_intercom(IC_SET_CF_EMIT_AUX, *item->parm.menuitem_enum.value);
}

void menu_params_apply_cf_mirror_up_lock(const menuitem_t *item) {
	if (!settings.remote_enable)
		send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, *item->parm.menuitem_enum.value);
	else
		menu_DPData.cf_mirror_up_lock = 0;
}

void menu_params_apply_cf_flash_sync_rear(const menuitem_t *item) {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, *item->parm.menuitem_enum.value);
}

void menu_params_apply_cf_safety_shift(const menuitem_t *item) {
	send_to_intercom(IC_SET_CF_SAFETY_SHIFT, *item->parm.menuitem_enum.value);
}

void menu_params_apply_remote_enable(const menuitem_t *item) {
	if(*item->parm.menuitem_enum.value)
		remote_on();
	else
		remote_off();
}

void menu_params_apply_remote_delay(const menuitem_t *item) {
	if(*item->parm.menuitem_enum.value)
		remote_delay(1);
	else
		remote_delay(0);
}

void menu_params_rename (menu_t *menu) {
	menupage_t *page = menu->current_page;
	menuitem_t *item = get_current_item(page);

	rename_create(named_temps.names[item->id]);
	beep();
}
