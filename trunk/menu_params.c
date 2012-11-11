/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "macros.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"
#include "utils.h"

#include "menu_params.h"

void menu_params_apply_autoiso_miniso     (const type_MENUITEM *item);
void menu_params_apply_autoiso_maxiso     (const type_MENUITEM *item);
void menu_params_apply_iso                (const type_MENUITEM *item);
void menu_params_apply_av_comp            (const type_MENUITEM *item);
void menu_params_apply_efcomp             (const type_MENUITEM *item);
void menu_params_apply_cf_emit_flash      (const type_MENUITEM *item);
void menu_params_apply_ae_bkt             (const type_MENUITEM *item);
void menu_params_apply_color_temp         (const type_MENUITEM *item);
void menu_params_apply_cf_emit_aux        (const type_MENUITEM *item);
void menu_params_apply_cf_mirror_up_lock  (const type_MENUITEM *item);
void menu_params_apply_cf_flash_sync_rear (const type_MENUITEM *item);
void menu_params_apply_cf_safety_shift    (const type_MENUITEM *item);
void menu_params_apply_remote_enable      (const type_MENUITEM *item);
void menu_params_apply_remote_delay       (const type_MENUITEM *item);

type_MENUITEM autoiso_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_AUTOISO_ENABLE), &settings.autoiso_enable, NULL),
	MENUITEM_BASEISO(LP_WORD(L_I_AUTOISO_MINISO), &settings.autoiso_miniso, menu_params_apply_autoiso_miniso),
	MENUITEM_BASEISO(LP_WORD(L_I_AUTOISO_MAXISO), &settings.autoiso_maxiso, menu_params_apply_autoiso_maxiso),
	MENUITEM_TV     (LP_WORD(L_I_AUTOISO_MINTV),  &settings.autoiso_mintv,  NULL),
	MENUITEM_AV     (LP_WORD(L_I_AUTOISO_MAXAV),  &settings.autoiso_maxav,  NULL),
};

type_MENUPAGE autoiso_page = {
	name     : LP_WORD(L_S_AUTOISO),
	length   : LENGTH(autoiso_items),
	items    : autoiso_items,
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};

type_MENUITEM flash_items[] = {
	MENUITEM_EVCOMP (LP_WORD(L_I_FLASH_COMP),    &menu_DPData.efcomp,             menu_params_apply_efcomp),
	MENUITEM_BOOLEAN(LP_WORD(L_I_USE_FLASH),     &menu_DPData.cf_emit_flash,      menu_params_apply_cf_emit_flash),
	MENUITEM_AFFLASH(LP_WORD(L_I_AF_FLASH),      &menu_DPData.cf_emit_aux,        menu_params_apply_cf_emit_aux),
	MENUITEM_BOOLEAN(LP_WORD(L_I_FLASH_2ND_CURT),&menu_DPData.cf_flash_sync_rear, menu_params_apply_cf_flash_sync_rear),
};

type_MENUPAGE flash_page = {
	name     : LP_WORD(L_S_FLASH),
	length   : LENGTH(flash_items),
	items    : flash_items,
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};

type_MENUITEM ir_items[] = {
	MENUITEM_BOOLEAN(LP_WORD(L_I_IR_REMOTE_ENABLE), &settings.remote_enable,          menu_params_apply_remote_enable),
	MENUITEM_BOOLEAN(LP_WORD(L_I_IR_REMOTE_DELAY),  &settings.remote_delay,           menu_params_apply_remote_delay),
};

type_MENUPAGE ir_page = {
	name     : LP_WORD(L_S_IR),
	length   : LENGTH(ir_items),
	items    : ir_items,
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};

type_MENUITEM menupage_params_items[] = {
	MENUITEM_SUBMENU(LP_WORD(L_S_AUTOISO),       &autoiso_page,                  NULL),
	MENUITEM_FULLISO(LP_WORD(L_I_ISO),           &menu_DPData.iso,               menu_params_apply_iso),
	MENUITEM_EVCOMP (LP_WORD(L_I_AV_COMP),       &menu_DPData.av_comp,           menu_params_apply_av_comp),
	MENUITEM_EVSEP  (LP_WORD(L_I_AEB),           &menu_DPData.ae_bkt,            menu_params_apply_ae_bkt),
	MENUITEM_CLRTEMP(LP_WORD(L_I_COLOR_TEMP_K),  &menu_DPData.color_temp,        menu_params_apply_color_temp),
	MENUITEM_BOOLEAN(LP_WORD(L_I_MIRROR_LOCKUP), &menu_DPData.cf_mirror_up_lock, menu_params_apply_cf_mirror_up_lock),
	MENUITEM_BOOLEAN(LP_WORD(L_I_SAFETY_SHIFT),  &menu_DPData.cf_safety_shift,   menu_params_apply_cf_safety_shift),
	MENUITEM_SUBMENU(LP_WORD(L_S_FLASH),         &flash_page,                    NULL),
	MENUITEM_SUBMENU(LP_WORD(L_S_IR),            &ir_page,                       NULL),
};

type_MENUPAGE menupage_params = {
	name      : LP_WORD(L_P_PARAMS),
	sibilings : true,
	length    : LENGTH(menupage_params_items),
	items     : menupage_params_items,
	ordering  : settings.params_order,
};

void menu_params_apply_autoiso_miniso(const type_MENUITEM *item) {
	settings.autoiso_maxiso = MAX(settings.autoiso_miniso, settings.autoiso_maxiso);
	menu_event_display();
}

void menu_params_apply_autoiso_maxiso(const type_MENUITEM *item) {
	settings.autoiso_miniso = MIN(settings.autoiso_miniso, settings.autoiso_maxiso);
	menu_event_display();
}

void menu_params_apply_iso(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_ISO, 2, *item->parm.menuitem_iso.value);
}

void menu_params_apply_av_comp(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_AV_COMP, 1, *item->parm.menuitem_ec.value);
}

void menu_params_apply_efcomp(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_EFCOMP, 1, *item->parm.menuitem_ec.value);
}

void menu_params_apply_cf_emit_flash(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_ae_bkt(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_AE_BKT, 1, *item->parm.menuitem_ec.value);
}

void menu_params_apply_color_temp(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_WB,         1, WB_MODE_COLORTEMP);
	send_to_intercom(IC_SET_COLOR_TEMP, 2, *item->parm.menuitem_int.value);
}

void menu_params_apply_cf_emit_aux(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_AUX, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_cf_mirror_up_lock(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_cf_flash_sync_rear(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_FLASH_SYNC_REAR, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_cf_safety_shift(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_SAFETY_SHIFT, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_remote_enable(const type_MENUITEM *item) {
	if(*item->parm.menuitem_enum.value)
		remote_on();
	else
		remote_off();
}

void menu_params_apply_remote_delay(const type_MENUITEM *item) {
	if(*item->parm.menuitem_enum.value){
		RemReleaseSelfMax = 4500;
		RemReleaseInstMin = 5560;
	} else {
		RemReleaseSelfMax = 6160;
		RemReleaseInstMin = 7410;
	}
}
