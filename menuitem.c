#include "main.h"
#include "firmware.h"

#include "menu.h"
#include "languages.h"

#include "menuitem.h"

OPTIONLIST_DEF(bool,     LP_WORD(L_NO), LP_WORD(L_YES))
OPTIONLIST_DEF(delay,    LP_WORD(L_NO), LP_WORD(L_2S))
OPTIONLIST_DEF(flash,    LP_WORD(L_ENABLED), LP_WORD(L_DISABLED), LP_WORD(L_EXT_ONLY))
OPTIONLIST_DEF(action,   LP_WORD(L_ONE_SHOT), LP_WORD(L_EXT_AEB), LP_WORD(L_INTERVAL))
OPTIONLIST_DEF(logfile,  LP_WORD(L_OVERWRITE), LP_WORD(L_NEW), LP_WORD(L_APPEND));

void menuitem_print(const char *buffer, const char *name, const char *parameter);

void menuitem_display(type_MENUITEM *item, const char *buffer) {
	menuitem_print(buffer, item->name, "");
}

void menuitem_display_ev(type_MENUITEM *item, const char *buffer) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_OFF));
	} else {
		ev_print(value, *item->parm.menuitem_ev.value);
		menuitem_print(buffer, item->name, value);
	}
}

void menuitem_display_av(type_MENUITEM *item, const char *buffer) {
	char value[LP_MAX_WORD];

	av_print(value, *item->parm.menuitem_av.value);
	menuitem_print(buffer, item->name, value);
}

void menuitem_display_tv(type_MENUITEM *item, const char *buffer) {
	char value[LP_MAX_WORD];

	tv_print(value, *item->parm.menuitem_tv.value);
	menuitem_print(buffer, item->name, value);
}

void menuitem_display_iso(type_MENUITEM *item, const char *buffer) {
	char value[LP_MAX_WORD];

	iso_print(value, *item->parm.menuitem_iso.value);
	menuitem_print(buffer, item->name, value);
}

void menuitem_display_int(type_MENUITEM *item, const char *buffer) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_int.zero_means_unlimited && *item->parm.menuitem_int.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_NO_LIMIT));
	} else {
		sprintf(value, item->parm.menuitem_int.format, *item->parm.menuitem_int.value);
		menuitem_print(buffer, item->name, value);
	}
}

void menuitem_display_enum(type_MENUITEM *item, const char *buffer) {
	menuitem_print(buffer, item->name, item->parm.menuitem_enum.list->data[*item->parm.menuitem_enum.value]);
}

void menuitem_display_sub(type_MENUITEM *item, const char *buffer) {
	menuitem_print(buffer, item->name, ">");
}

void menuitem_print(const char *buffer, const char *name, const char *parameter) {
	int pad = MENU_WIDTH - strlen(parameter) - 2;

	sprintf(buffer, "%-*.*s %s", pad, pad, name, parameter);
}

