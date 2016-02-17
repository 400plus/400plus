#include "macros.h"
#include "firmware.h"

#include "exposure.h"
#include "languages.h"
#include "menu.h"
#include "utils.h"

#include "menuitem.h"

void menuitem_print(char *buffer, const char *name, const char *parameter, const int length);

void menuitem_display(const menuitem_t *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, "", length);
}

void menuitem_display_ec(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_ec.zero_means_off && *item->parm.menuitem_ec.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_V_OFF), length);
	} else {
		ec_print(value, *item->parm.menuitem_ec.value);
		menuitem_print(buffer, item->name, value, length);
	}
}

void menuitem_display_av(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	av_print(value, *item->parm.menuitem_av.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_tv(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	tv_print(value, *item->parm.menuitem_tv.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_bulb(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	bulb_print(value, *item->parm.menuitem_tv.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_iso(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	iso_print(value, *item->parm.menuitem_iso.value);
	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_int(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	if (item->parm.menuitem_int.zero_means_unlimited && *item->parm.menuitem_int.value == 0) {
		menuitem_print(buffer, item->name, LP_WORD(L_V_NO_LIMIT), length);
	} else {
		sprintf(value, item->parm.menuitem_int.format, *item->parm.menuitem_int.value);
		menuitem_print(buffer, item->name, value, length);
	}
}

void menuitem_display_time(const menuitem_t *item, char *buffer, const int length) {
	char value[LP_MAX_WORD];

	int h, m, s = *item->parm.menuitem_int.value;

	h = s / 3600;
	s = s % 3600;

	m = s / 60;
	s = s % 60;

	if (h > 99)
		sprintf(value, "##:##:##");
	else if (h > 0)
		sprintf(value, "%02i:%02i:%02i", h, m, s);
	else if (m > 0)
		sprintf(value,      "%02i:%02i",    m, s);
	else
		sprintf(value,           "%02i",       s);

	menuitem_print(buffer, item->name, value, length);
}

void menuitem_display_enum(const menuitem_t *item, char *buffer, const int length) {
	if (*item->parm.menuitem_enum.value >= 0 && *item->parm.menuitem_enum.value < item->parm.menuitem_enum.list->size)
		menuitem_print(buffer, item->name, item->parm.menuitem_enum.list->data[*item->parm.menuitem_enum.value], length);
	else
		menuitem_print(buffer, item->name, "?", length);
}

void menuitem_display_info(const menuitem_t *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, item->parm.menuitem_info.value ? item->parm.menuitem_info.value : "", length);
}

void menuitem_display_sub(const menuitem_t *item, char *buffer, const int length) {
	menuitem_print(buffer, item->name, ">", length);
}

void menuitem_print(char *buffer, const char *name, const char *parameter, const int length) {
	const int pad = length - strlen_utf8(name) - strlen_utf8(parameter);

	if (pad > 0)
		sprintf(buffer, "%s%*s%s", name, pad, "", parameter);
	else
		sprintf(buffer, "%s %.*s.", name, strlen_utf8(parameter) + pad - 1, parameter);
}

void menuitem_inc_ec(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_ec.value = ec_inc(*item->parm.menuitem_ec.value, item->parm.menuitem_ec.extended);
}

void menuitem_inc_av(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_av.value = av_inc(*item->parm.menuitem_av.value);
}

void menuitem_inc_tv(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_tv.value = tv_inc(*item->parm.menuitem_tv.value);
}

void menuitem_inc_bulb(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_tv.value = bulb_next(*item->parm.menuitem_tv.value);
}

void menuitem_inc_iso(const menuitem_t *item, const int repeating) {
	if (repeating || item->parm.menuitem_iso.full)
		*item->parm.menuitem_iso.value = MAX(*item->parm.menuitem_iso.value, iso_next(*item->parm.menuitem_iso.value));
	else
		*item->parm.menuitem_iso.value = iso_inc(*item->parm.menuitem_iso.value);
}

void menuitem_inc_int(const menuitem_t *item, const int repeating) {
	int small_step = item->parm.menuitem_int.small_step;
	int big_step   = item->parm.menuitem_int.big_step;

	if (item->parm.menuitem_int.base_log) {
		while (*item->parm.menuitem_int.value / item->parm.menuitem_int.base_log >= big_step) {
			SWAP(small_step, big_step);
			big_step *= item->parm.menuitem_int.base_log;
		}
	}

	int step = repeating ? big_step : small_step;

	*item->parm.menuitem_int.value += step;

	if (item->parm.menuitem_int.base_log)
		*item->parm.menuitem_int.value  = step * (*item->parm.menuitem_int.value / step);

	*item->parm.menuitem_int.value  = MIN(*item->parm.menuitem_int.value, item->parm.menuitem_int.max);
}

void menuitem_inc_flen(const menuitem_t *item, const int repeating) {
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

void menuitem_inc_enum(const menuitem_t *item, const int repeating) {
	if (*item->parm.menuitem_enum.value >= item->parm.menuitem_enum.list->size - 1) {
		if (item->parm.menuitem_enum.cycle || *item->parm.menuitem_enum.value > item->parm.menuitem_enum.list->size - 1)
			*item->parm.menuitem_enum.value = 0;
	} else
		(*item->parm.menuitem_enum.value)++;
}

void menuitem_inc_sub(const menuitem_t *item, const int repeating) {
	if (!repeating)
		menu_set_page(item->parm.menuitem_submenu.page);
}

void menuitem_dec_ec(const menuitem_t *item, const int repeating) {
	if (item->parm.menuitem_ec.zero_means_off && *item->parm.menuitem_ec.value < 0x05)
		*item->parm.menuitem_ec.value = item->parm.menuitem_ec.can_do_zero ? 0x00 : EV_STEP;
	else
		*item->parm.menuitem_ec.value = ec_dec(*item->parm.menuitem_ec.value, item->parm.menuitem_ec.extended);
}

void menuitem_dec_av(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_av.value = av_dec(*item->parm.menuitem_av.value);
}

void menuitem_dec_tv(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_tv.value = tv_dec(*item->parm.menuitem_tv.value);
}

void menuitem_dec_bulb(const menuitem_t *item, const int repeating) {
	*item->parm.menuitem_tv.value = bulb_prev(*item->parm.menuitem_tv.value);
}

void menuitem_dec_iso(const menuitem_t *item, const int repeating) {
	if (repeating || item->parm.menuitem_iso.full)
		*item->parm.menuitem_iso.value = iso_prev(*item->parm.menuitem_iso.value);
	else
		*item->parm.menuitem_iso.value = iso_dec(*item->parm.menuitem_iso.value);
}

void menuitem_dec_int(const menuitem_t *item, const int repeating) {
	int small_step = item->parm.menuitem_int.small_step;
	int big_step   = item->parm.menuitem_int.big_step;

	if (item->parm.menuitem_int.base_log) {
		while (*item->parm.menuitem_int.value / item->parm.menuitem_int.base_log > big_step) {
			SWAP(small_step, big_step);
			big_step *= item->parm.menuitem_int.base_log;
		}
	}

	int step = repeating ? big_step : small_step;

	*item->parm.menuitem_int.value -= step;

	if (item->parm.menuitem_int.base_log)
		*item->parm.menuitem_int.value  = step * (*item->parm.menuitem_int.value / step);

	*item->parm.menuitem_int.value  = MAX(*item->parm.menuitem_int.value, item->parm.menuitem_int.min);
}

void menuitem_dec_flen(const menuitem_t *item, const int repeating) {
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

void menuitem_dec_enum(const menuitem_t *item, const int repeating) {
	if (*item->parm.menuitem_enum.value <= 0) {
		if (item->parm.menuitem_enum.cycle || *item->parm.menuitem_enum.value < 0)
			*item->parm.menuitem_enum.value = item->parm.menuitem_enum.list->size - 1;
	} else
		(*item->parm.menuitem_enum.value)--;
}
