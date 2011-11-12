#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"
#include "utils.h"

#include "menu_params.h"

void menu_params_apply_autoiso_miniso (const type_MENUITEM *item);
void menu_params_apply_autoiso_maxiso (const type_MENUITEM *item);
void menu_params_apply_iso            (const type_MENUITEM *item);
void menu_params_apply_av_comp        (const type_MENUITEM *item);
void menu_params_apply_efcomp         (const type_MENUITEM *item);
void menu_params_apply_cf_emit_flash  (const type_MENUITEM *item);
void menu_params_apply_ae_bkt         (const type_MENUITEM *item);
void menu_params_apply_color_temp     (const type_MENUITEM *item);

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
	tasks    : {
		[MENU_EVENT_AV]   = menu_return,
	}
};

type_MENUITEM menupage_params_items[] = {
	MENUITEM_SUBMENU(LP_WORD(L_S_AUTOISO),      &autoiso_page,                  NULL),
	MENUITEM_FULLISO(LP_WORD(L_I_ISO),          &menu_cameraMode.iso,           menu_params_apply_iso),
	MENUITEM_EVCOMP (LP_WORD(L_I_AV_COMP),      &menu_cameraMode.av_comp,       menu_params_apply_av_comp),
	MENUITEM_EVCOMP (LP_WORD(L_I_FLASH_COMP),   &menu_cameraMode.efcomp,        menu_params_apply_efcomp),
	MENUITEM_BOOLEAN(LP_WORD(L_I_USE_FLASH),    &menu_cameraMode.cf_emit_flash, menu_params_apply_cf_emit_flash),
	MENUITEM_EVSEP  (LP_WORD(L_I_AEB),          &menu_cameraMode.ae_bkt,        menu_params_apply_ae_bkt),
	MENUITEM_CLRTEMP(LP_WORD(L_I_COLOR_TEMP_K), &menu_cameraMode.color_temp,    menu_params_apply_color_temp),
};

type_MENUPAGE menupage_params = {
	name      : LP_WORD(L_P_PARAMS),
	sibilings : TRUE,
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
	send_to_intercom(IC_SET_AV_COMP, 1, *item->parm.menuitem_ev.value);
}

void menu_params_apply_efcomp(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_EFCOMP, 1, *item->parm.menuitem_ev.value);
}

void menu_params_apply_cf_emit_flash(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_CF_EMIT_FLASH, 1, *item->parm.menuitem_enum.value);
}

void menu_params_apply_ae_bkt(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_AE_BKT, 1, *item->parm.menuitem_ev.value);
}

void menu_params_apply_color_temp(const type_MENUITEM *item) {
	send_to_intercom(IC_SET_WB,         1, WB_MODE_COLORTEMP);
	send_to_intercom(IC_SET_COLOR_TEMP, 2, *item->parm.menuitem_int.value);
}

