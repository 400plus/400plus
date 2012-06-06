#include "main.h"
#include "firmware.h"

#include "menu.h"
#include "languages.h"
#include "utils.h"

#include "menuitem.h"

OPTIONLIST_DEF(bool,      LP_WORD(L_V_NO), LP_WORD(L_V_YES))
OPTIONLIST_DEF(flash,     LP_WORD(L_V_ENABLED), LP_WORD(L_V_DISABLED), LP_WORD(L_V_EXT_ONLY))
OPTIONLIST_DEF(action,    LP_WORD(L_V_ONE_SHOT), LP_WORD(L_V_EXT_AEB), LP_WORD(L_V_EFL_AEB), LP_WORD(L_V_ISO_AEB), LP_WORD(L_V_LEXP))
OPTIONLIST_DEF(logfile,   LP_WORD(L_V_OVERWRITE), LP_WORD(L_V_NEW), LP_WORD(L_V_APPEND));
OPTIONLIST_DEF(btnactn,   LP_WORD(L_V_NONE), LP_WORD(L_V_INTISO), LP_WORD(L_V_REPEAT), LP_WORD(L_I_MIRROR_LOCKUP), LP_WORD(L_I_AEB), LP_WORD(L_V_HACK_MENU));
OPTIONLIST_DEF(direction, "+", "-", "+/-");
OPTIONLIST_DEF(languages, "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
                          "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
                          "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"); // place holders
OPTIONLIST_DEF(vformat,   "25", "30", "50", "60");
OPTIONLIST_DEF(scrind,    LP_WORD(L_V_NONE), LP_WORD(L_V_SLOW), LP_WORD(L_V_MEDIUM), LP_WORD(L_V_FAST));
OPTIONLIST_DEF(scrlcd,    LP_WORD(L_V_KEEP), LP_WORD(L_V_DIM), LP_WORD(L_V_OFF));

void menuitem_print(char *buffer, const char *name, const char *parameter, const int length);

void menuitem_display(const type_MENUITEM *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, "", length);
}

void menuitem_display_ev(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_V_OFF), length);
	} else {
		ev_print(value, *item->parm.menuitem_ev.value);
		menuitem_print(buffer, item->name, value, length);
	}
}

void menuitem_display_av(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	av_print(value, *item->parm.menuitem_av.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_tv(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	tv_print(value, *item->parm.menuitem_tv.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_iso(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	iso_print(value, *item->parm.menuitem_iso.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_int(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_int.zero_means_unlimited && *item->parm.menuitem_int.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_V_NO_LIMIT), length);
	} else {
		sprintf(value, item->parm.menuitem_int.format, *item->parm.menuitem_int.value);
		menuitem_print(buffer, item->name, value, length);
	}
}

void menuitem_display_time(const type_MENUITEM *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	if (*item->parm.menuitem_int.value < 3600) {
		sprintf(value, "%02i:%02i", *item->parm.menuitem_int.value / 60, *item->parm.menuitem_int.value % 60);
	} else {
		sprintf(value, "%02i:%02i:%02i", *item->parm.menuitem_int.value / 3600, (*item->parm.menuitem_int.value % 3600) / 60, *item->parm.menuitem_int.value % 60);
	}

	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_enum(const type_MENUITEM *item, char *buffer, const int length) {
	if (*item->parm.menuitem_enum.value >= 0 && *item->parm.menuitem_enum.value < item->parm.menuitem_enum.list->length)
		menuitem_print(buffer, item->name, item->parm.menuitem_enum.list->data[*item->parm.menuitem_enum.value], length);
	else
		menuitem_print(buffer, item->name, "?", length);
}

void menuitem_display_info(const type_MENUITEM *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, item->parm.menuitem_info.value ? item->parm.menuitem_info.value : "", length);
}

void menuitem_display_sub(const type_MENUITEM *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, ">", length);
}

void menuitem_print(char *buffer, const char *name, const char *parameter, const int length) {
	const int pad = length - strlen_utf8(name) - strlen_utf8(parameter);

	if (pad > 0)
		sprintf(buffer, "%s%*s%s", name, pad, "", parameter);
	else
		sprintf(buffer, "%s %.*s.", name, strlen(parameter) + pad - 1, parameter);
}

void menuitem_inc_ev(const type_MENUITEM *item, const int repeating) {
	*item->parm.menuitem_ev.value = ev_inc(*item->parm.menuitem_ev.value);
}

void menuitem_inc_av(const type_MENUITEM *item, const int repeating) {
	*item->parm.menuitem_av.value = av_inc(*item->parm.menuitem_av.value);
}

void menuitem_inc_tv(const type_MENUITEM *item, const int repeating) {
	if (repeating || item->parm.menuitem_tv.bulb)
		*item->parm.menuitem_tv.value = tv_next(*item->parm.menuitem_tv.value);
	else
		*item->parm.menuitem_tv.value = tv_inc(*item->parm.menuitem_tv.value);
}

void menuitem_inc_iso(const type_MENUITEM *item, const int repeating) {
	if (repeating || item->parm.menuitem_iso.full)
		*item->parm.menuitem_iso.value = MAX(*item->parm.menuitem_iso.value, iso_next(*item->parm.menuitem_iso.value));
	else
		*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
}

void menuitem_inc_int(const type_MENUITEM *item, const int repeating) {
	*item->parm.menuitem_int.value += repeating ? item->parm.menuitem_int.big_step : item->parm.menuitem_int.small_step;
	*item->parm.menuitem_int.value  = MIN(*item->parm.menuitem_int.value, item->parm.menuitem_int.max);
}

void menuitem_inc_flen(const type_MENUITEM *item, const int repeating) {
	if (*item->parm.menuitem_int.value < 10)
		*item->parm.menuitem_int.value += 1;
	else if (*item->parm.menuitem_int.value < 20)
		*item->parm.menuitem_int.value += 2;
	else if (*item->parm.menuitem_int.value < 100)
		*item->parm.menuitem_int.value += 5;
	else if (*item->parm.menuitem_int.value < 200)
		*item->parm.menuitem_int.value += 25;
	else if (*item->parm.menuitem_int.value < 600)
		*item->parm.menuitem_int.value += 100;
	else if (*item->parm.menuitem_int.value < 1200)
		*item->parm.menuitem_int.value += 200;
}

void menuitem_inc_enum(const type_MENUITEM *item, const int repeating) {
	if (*item->parm.menuitem_enum.value >= item->parm.menuitem_enum.list->length - 1) {
		if (item->parm.menuitem_enum.cycle || *item->parm.menuitem_enum.value > item->parm.menuitem_enum.list->length - 1)
			*item->parm.menuitem_enum.value = 0;
	} else
		(*item->parm.menuitem_enum.value)++;
}

void menuitem_inc_sub(const type_MENUITEM *item, const int repeating) {
	if (!repeating)
		menu_set_page(item->parm.menuitem_submenu.page);
}

void menuitem_dec_ev(const type_MENUITEM *item, const int repeating) {
	if (item->parm.menuitem_ev.zero_means_off && *item->parm.menuitem_ev.value < 0x05)
		*item->parm.menuitem_ev.value = item->parm.menuitem_ev.can_do_zero ? 0x00 : (cameraMode->cf_explevel_inc_third ? 0x04 : 0x03);
	else
		*item->parm.menuitem_ev.value = ev_dec(*item->parm.menuitem_ev.value);
}

void menuitem_dec_av(const type_MENUITEM *item, const int repeating) {
	*item->parm.menuitem_av.value = av_dec(*item->parm.menuitem_av.value);
}

void menuitem_dec_tv(const type_MENUITEM *item, const int repeating) {
	if (repeating || item->parm.menuitem_tv.bulb)
		*item->parm.menuitem_tv.value = tv_prev(*item->parm.menuitem_tv.value);
	else
		*item->parm.menuitem_tv.value = tv_dec(*item->parm.menuitem_tv.value);
}

void menuitem_dec_iso(const type_MENUITEM *item, const int repeating) {
	if (repeating || item->parm.menuitem_iso.full)
		*item->parm.menuitem_iso.value = iso_prev(*item->parm.menuitem_iso.value);
	else
		*item->parm.menuitem_iso.value = iso_dec(*item->parm.menuitem_iso.value);
}

void menuitem_dec_int(const type_MENUITEM *item, const int repeating) {
	*item->parm.menuitem_int.value -= repeating ? item->parm.menuitem_int.big_step : item->parm.menuitem_int.small_step;
	*item->parm.menuitem_int.value  = MAX(*item->parm.menuitem_int.value, item->parm.menuitem_int.min);
}

void menuitem_dec_flen(const type_MENUITEM *item, const int repeating) {
	if (*item->parm.menuitem_int.value > 600)
		*item->parm.menuitem_int.value -= 200;
	else if (*item->parm.menuitem_int.value > 200)
		*item->parm.menuitem_int.value -= 100;
	else if (*item->parm.menuitem_int.value > 100)
		*item->parm.menuitem_int.value -= 25;
	else if (*item->parm.menuitem_int.value > 20)
		*item->parm.menuitem_int.value -= 5;
	else if (*item->parm.menuitem_int.value > 10)
		*item->parm.menuitem_int.value -= 2;
	else if (*item->parm.menuitem_int.value > 5)
		*item->parm.menuitem_int.value -= 1;
}

void menuitem_dec_enum(const type_MENUITEM *item, const int repeating) {
	if (*item->parm.menuitem_enum.value <= 0) {
		if (item->parm.menuitem_enum.cycle || *item->parm.menuitem_enum.value < 0)
			*item->parm.menuitem_enum.value = item->parm.menuitem_enum.list->length - 1;
	} else
		(*item->parm.menuitem_enum.value)--;
}
