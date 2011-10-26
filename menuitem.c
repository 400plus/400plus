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

void menu_print_ev   (const char *buffer, const char *name, int   parameter);
void menu_print_av   (const char *buffer, const char *name, int   parameter);
void menu_print_tv   (const char *buffer, const char *name, int   parameter);
void menu_print_iso  (const char *buffer, const char *name, int   parameter);
void menu_print_int  (const char *buffer, const char *name, int   parameter, const char *format);
void menu_print_char (const char *buffer, const char *name, const char *parameter);

void menuitem_display(type_MENUITEM *item, const char *buffer) {
	menu_print_char(buffer, item->name, "");
}

void menuitem_display_ev(type_MENUITEM *item, const char *buffer) {
	if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value == 0)
		menu_print_char(buffer, item->name, LP_WORD(L_OFF));
	else
		menu_print_ev(buffer, item->name, *item->parm.menuitem_ev.value);
}

void menuitem_display_av(type_MENUITEM *item, const char *buffer) {
	menu_print_av(buffer, item->name, *item->parm.menuitem_av.value);
}

void menuitem_display_tv(type_MENUITEM *item, const char *buffer) {
	menu_print_tv(buffer, item->name, *item->parm.menuitem_tv.value);
}

void menuitem_display_iso(type_MENUITEM *item, const char *buffer) {
	menu_print_iso(buffer, item->name, *item->parm.menuitem_iso.value);
}

void menuitem_display_int(type_MENUITEM *item, const char *buffer) {
	if (item->parm.menuitem_int.zero_means_unlimited && *item->parm.menuitem_int.value == 0)
		menu_print_char(buffer, item->name, LP_WORD(L_NO_LIMIT));
	else
		menu_print_int(buffer, item->name, *item->parm.menuitem_int.value, item->parm.menuitem_int.format);
}

void menuitem_display_enum(type_MENUITEM *item, const char *buffer) {
	menu_print_char(buffer, item->name, item->parm.menuitem_enum.list->data[*item->parm.menuitem_enum.value]);
}

void menuitem_display_sub(type_MENUITEM *item, const char *buffer) {
	menu_print_char(buffer, item->name, ">");
}

void menu_print_ev(const char *buffer, const char *name, int parameter) {
	char tmp[LP_MAX_WORD];

	ev_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_av(const char *buffer, const char *name, int parameter) {
	char tmp[LP_MAX_WORD];

	av_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_tv(const char *buffer, const char *name, int parameter) {
	char tmp[LP_MAX_WORD];

	tv_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_iso(const char *buffer, const char *name, int parameter) {
	char tmp[LP_MAX_WORD];

	iso_print(tmp, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_int(const char *buffer, const char *name, int parameter, const char *format) {
	char tmp[LP_MAX_WORD];

	sprintf(tmp, format, parameter);
	menu_print_char(buffer, name, tmp);
}

void menu_print_char(const char *buffer, const char *name, const char *parameter) {
	int pad = MENU_WIDTH - strlen(parameter) - 1;

	sprintf(buffer, "%-*.*s %s", pad, pad, name, parameter);
}

