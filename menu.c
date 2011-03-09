#include "main.h"
#include "utils.h"
#include "settings.h"
#include "firmware.h"

#include "menu.h"

type_SETTINGS menu_settings;

type_MENUITEM          current_item          = MENUITEM_FIRST;
type_MENUITEM_WAVE     current_item_wave     = MENUITEM_WAVE_FIRST;
type_MENUITEM_EAEB     current_item_eaeb     = MENUITEM_EAEB_FIRST;
type_MENUITEM_INTERVAL current_item_interval = MENUITEM_INTERVAL_FIRST;

char menu_buffer[17];

const char *wb_string[]   = {"Auto", "Daylight", "Cloudy", "Tungsten", "Fluorescent", "Flash", "Custom", "Shade", "Color temp."};
const char *tv_string[]   = {"30", "15", "8", "4", "2", "1", "0.5", "1/4","1/8","1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;
const char *dp_string[]   = {"Disabled", "Change ISO", "Extended AEB", "Interval", "Wave"};
const char *wave_string[] = {"One shot", "Extended AEB", "Interval"};

void menu_repeat(void (*repeateable)(int repeating));

void menu_repeateable_toggle (int repeating);
void menu_repeateable_cycle  (int repeating);
void menu_repeateable_up     (int repeating);
void menu_repeateable_down   (int repeating);
void menu_repeateable_right  (int repeating);
void menu_repeateable_left   (int repeating);

void  menu_save();
void  menu_display();
char *menu_message();

void menu_initialize() {
	menu_settings = settings;

	menu_settings.av_comp        = cameraMode.AvComp;
	menu_settings.flash_comp     = cameraMode.FlashExComp;
	menu_settings.aeb_ev         = cameraMode.AEB;
	menu_settings.not_emit_flash = cameraMode.CfNotEmitFlash;
	menu_settings.not_af_flash   = cameraMode.CfAfAssistBeam;
	menu_settings.white_balance  = cameraMode.WB;

	// We do NOT recover ColorTemp from cameraMode, because the camera fiddles with this value internally.
	//menu_settings.color_temp     = cameraMode.ColorTemp;
}

void menu_toggle() {
	menu_repeat(menu_repeateable_toggle);
}

void menu_cycle() {
	menu_repeat(menu_repeateable_cycle);
}

void menu_up() {
	menu_repeat(menu_repeateable_up);
}

void menu_down() {
	menu_repeat(menu_repeateable_down);
}

void menu_right() {
	menu_repeat(menu_repeateable_right);
}

void menu_left() {
	menu_repeat(menu_repeateable_left);
}

void menu_repeat(void(*repeateable)()){
	int delay;
	int button = status.button_down;

	SleepTask(50);

	repeateable(FALSE);
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			repeateable(TRUE);
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void menu_repeateable_toggle(int repeating) {
	switch(current_item) {
	case MENUITEM_AV_COMP:
		menu_settings.av_comp = ev_sgn(menu_settings.av_comp);
		break;
	case MENUITEM_FLASH_COMP:
		menu_settings.flash_comp = ev_sgn(menu_settings.flash_comp);
		break;
	case MENUITEM_SAFETY_SHIFT:
		menu_settings.safety_shift = ! menu_settings.safety_shift;
		break;
	case MENUITEM_ISO_VIEWFINDER:
		menu_settings.iso_in_viewfinder = ! menu_settings.iso_in_viewfinder;
		break;
	case MENUITEM_EMIT_FLASH:
		menu_settings.not_emit_flash = ! menu_settings.not_emit_flash;
		break;
	case MENUITEM_AF_FLASH:
		menu_settings.not_af_flash = ! menu_settings.not_af_flash;
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.remote_delay = ! menu_settings.remote_delay;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_repeateable_cycle(int repeating) {
	switch(current_item) {
	case MENUITEM_WHITE_BALANCE:
		menu_settings.white_balance = (menu_settings.white_balance + 1) % 9;
		break;
	case MENUITEM_WAVE:
		if (current_item_wave == MENUITEM_WAVE_LAST)
			current_item_wave = MENUITEM_WAVE_FIRST;
		else
			current_item_wave++;
		break;
	case MENUITEM_EAEB:
		if (current_item_eaeb == MENUITEM_EAEB_LAST)
			current_item_eaeb = MENUITEM_EAEB_FIRST;
		else
			current_item_eaeb++;
		break;
	case MENUITEM_INTERVAL:
		if (current_item_interval == MENUITEM_INTERVAL_LAST)
			current_item_interval = MENUITEM_INTERVAL_FIRST;
		else
			current_item_interval++;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_repeateable_up(int repeating) {
	if (current_item == MENUITEM_LAST)
		current_item = MENUITEM_FIRST;
	else
		current_item++;

	menu_display();
}

void menu_repeateable_down(int repeating) {
	if (current_item == MENUITEM_FIRST)
		current_item = MENUITEM_LAST;
	else
		current_item--;

	menu_display();
}

void menu_repeateable_right(int repeating) {
	switch(current_item) {
	case MENUITEM_AV_COMP:
		menu_settings.av_comp = ev_inc(menu_settings.av_comp);
		break;
	case MENUITEM_FLASH_COMP:
		menu_settings.flash_comp = ev_inc(menu_settings.flash_comp);
		break;
	case MENUITEM_AEB:
		menu_settings.aeb_ev = ev_inc(menu_settings.aeb_ev);
		break;
	case MENUITEM_SAFETY_SHIFT:
		menu_settings.safety_shift = TRUE;
		break;
	case MENUITEM_ISO_VIEWFINDER:
		menu_settings.iso_in_viewfinder = TRUE;
		break;
	case MENUITEM_WHITE_BALANCE:
		if (menu_settings.white_balance == WB_MODE_COLORTEMP) {
			menu_settings.color_temp += repeating ? 500 : 100;
			menu_settings.color_temp  = MIN(menu_settings.color_temp, 11000);
		}
		break;
	case MENUITEM_EMIT_FLASH:
		menu_settings.not_emit_flash = FALSE;
		break;
	case MENUITEM_AF_FLASH:
		menu_settings.not_af_flash = FALSE;
		break;
	case MENUITEM_DP_BUTTON:
		if (menu_settings.dp_action == DP_ACTION_LAST)
			menu_settings.dp_action = DP_ACTION_FIRST;
		else
			menu_settings.dp_action++;
		break;
	case MENUITEM_WAVE:
		switch (current_item_wave) {
		case MENUITEM_WAVE_DELAY:
			menu_settings.wave_delay = TRUE;
			break;
		case MENUITEM_WAVE_ACTION:
			if (menu_settings.wave_action == WAVE_ACTION_LAST)
				menu_settings.wave_action = WAVE_ACTION_FIRST;
			else
				menu_settings.wave_action++;
			break;
		default:
			break;
		}
		break;
	case MENUITEM_EAEB:
		switch (current_item_eaeb) {
		case MENUITEM_EAEB_FRAMES:
			if (menu_settings.eaeb_frames < 9)
				menu_settings.eaeb_frames += 2;
			break;
		case MENUITEM_EAEB_EV:
			menu_settings.eaeb_ev = ev_inc(menu_settings.eaeb_ev);
			break;
		case MENUITEM_EAEB_DELAY:
			menu_settings.eaeb_delay = TRUE;
			break;
		case MENUITEM_EAEB_M_MIN:
			if (menu_settings.eaeb_m_min <= 0x90) //98 is maximum
				menu_settings.eaeb_m_min += 8;
			break;
		case MENUITEM_EAEB_M_MAX:
			if (menu_settings.eaeb_m_max <= 0x90) //98 is maximum
				menu_settings.eaeb_m_max += 8;
			break;
		default:
			break;
		}
		break;
	case MENUITEM_INTERVAL:
		switch (current_item_interval) {
		case MENUITEM_INTERVAL_DELAY:
			menu_settings.interval_delay = TRUE;
			break;
		case MENUITEM_INTERVAL_TIME:
			menu_settings.interval_time += repeating ? 10 : 1;
			menu_settings.interval_time  = MIN(menu_settings.interval_time, 250);
			break;
		case MENUITEM_INTERVAL_EAEB:
			menu_settings.interval_eaeb = TRUE;
			break;
		case MENUITEM_INTERVAL_SHOTS:
			menu_settings.interval_shots += repeating ? 10 : 1;
			menu_settings.interval_shots  = MIN(menu_settings.interval_shots, 250);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.remote_delay = TRUE;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_repeateable_left(int repeating) {
	switch (current_item) {
	case MENUITEM_AV_COMP:
		menu_settings.av_comp = ev_dec(menu_settings.av_comp);
		break;
	case MENUITEM_FLASH_COMP:
		menu_settings.flash_comp = ev_dec(menu_settings.flash_comp);
		break;
	case MENUITEM_AEB:
		if (menu_settings.aeb_ev > 0x04)
			menu_settings.aeb_ev = ev_dec(menu_settings.aeb_ev);
		else
			menu_settings.aeb_ev = 0x00;
		break;
	case MENUITEM_SAFETY_SHIFT:
		menu_settings.safety_shift = FALSE;
	case MENUITEM_ISO_VIEWFINDER:
		menu_settings.iso_in_viewfinder = FALSE;
		break;
	case MENUITEM_WHITE_BALANCE:
		if (menu_settings.white_balance == WB_MODE_COLORTEMP) {
			menu_settings.color_temp -= repeating ? 500 : 100;
			menu_settings.color_temp  = MAX (menu_settings.color_temp, 1800);
		}
		break;
	case MENUITEM_EMIT_FLASH:
		menu_settings.not_emit_flash = TRUE;
		break;
	case MENUITEM_AF_FLASH:
		menu_settings.not_af_flash = TRUE;
		break;
	case MENUITEM_DP_BUTTON:
		if (menu_settings.dp_action == DP_ACTION_FIRST)
			menu_settings.dp_action = DP_ACTION_LAST;
		else
			menu_settings.dp_action--;
		break;
	case MENUITEM_WAVE:
		switch (current_item_wave) {
		case MENUITEM_WAVE_DELAY:
			menu_settings.wave_delay = FALSE;
			break;
		case MENUITEM_WAVE_ACTION:
			if (menu_settings.wave_action == WAVE_ACTION_FIRST)
				menu_settings.wave_action = WAVE_ACTION_LAST;
			else
				menu_settings.wave_action--;
			break;
		default:
			break;
		}
		break;
	case MENUITEM_EAEB:
		switch (current_item_eaeb) {
		case MENUITEM_EAEB_FRAMES:
			if (menu_settings.eaeb_frames > 3)
				menu_settings.eaeb_frames -= 2;
			break;
		case MENUITEM_EAEB_EV:
			if (menu_settings.eaeb_ev > 0x04)
				menu_settings.eaeb_ev = ev_dec(menu_settings.eaeb_ev);
			break;
		case MENUITEM_EAEB_DELAY:
			menu_settings.eaeb_delay = FALSE;
			break;
		case MENUITEM_EAEB_M_MIN:
			if(menu_settings.eaeb_m_min >= 0x18) //10 is minimum
				menu_settings.eaeb_m_min -= 8;
			break;
		case MENUITEM_EAEB_M_MAX:
			if(menu_settings.eaeb_m_max >= 0x18) //10 is minimum
				menu_settings.eaeb_m_max -= 8;
			break;
		default:
			break;
		}
		break;
	case MENUITEM_INTERVAL:
		switch (current_item_interval) {
		case MENUITEM_INTERVAL_DELAY:
			menu_settings.interval_delay = FALSE;
			break;
		case MENUITEM_INTERVAL_TIME:
			menu_settings.interval_time -= repeating ? 10 : 1;
			menu_settings.interval_time  = MAX(menu_settings.interval_time, 1);
			break;
		case MENUITEM_INTERVAL_EAEB:
			menu_settings.interval_eaeb = FALSE;
			break;
		case MENUITEM_INTERVAL_SHOTS:
			menu_settings.interval_shots -= repeating ? 10 : 1;
			menu_settings.interval_shots  = MAX(menu_settings.interval_shots, 1);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.remote_delay = FALSE;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();

	beep();
}

void menu_display() {
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
}

char *menu_message() {
	char ev_display[] = "      ";

	SleepTask(50);

	switch (current_item) {
	case MENUITEM_AV_COMP:
		ev_print(ev_display, menu_settings.av_comp);
		sprintf(menu_buffer, "Av comp:         %s", ev_display);
		break;
	case MENUITEM_FLASH_COMP:
		ev_print(ev_display, menu_settings.flash_comp);
		sprintf(menu_buffer, "Flash comp:      %s", ev_display);
		break;
	case MENUITEM_AEB:
		ev_print(ev_display, menu_settings.aeb_ev);
		sprintf(menu_buffer, "AEB:             %s", menu_settings.aeb_ev ? ev_display : "off");
		break;
	case MENUITEM_SAFETY_SHIFT:
		sprintf(menu_buffer, "Safety shift:  %s", menu_settings.safety_shift ? "on" : "off");
		break;
	case MENUITEM_RELEASE_COUNT:
		sprintf(menu_buffer, "Release count: %u", FLAG_RELEASE_COUNT);
		break;
	case MENUITEM_ISO_VIEWFINDER:
		sprintf(menu_buffer, "Show ISO in viewfinder: %s", menu_settings.iso_in_viewfinder ? "on" : "off");
		break;
	case MENUITEM_WHITE_BALANCE:
		if (menu_settings.white_balance == WB_MODE_COLORTEMP)
			sprintf(menu_buffer, "WB:: color temp=%uK", menu_settings.color_temp);
		else
			sprintf(menu_buffer, "WB:: %s", wb_string[menu_settings.white_balance]);
		break;
	case MENUITEM_EMIT_FLASH:
		sprintf(menu_buffer, "Flash:            %s", menu_settings.not_emit_flash ? "off" : "on");
		break;
	case MENUITEM_AF_FLASH:
		sprintf(menu_buffer, "AF Assist Beam:       %s", menu_settings.not_af_flash ? "off" : "on");
		break;
	case MENUITEM_DP_BUTTON:
		sprintf(menu_buffer, "DP Button:    %s", dp_string[menu_settings.dp_action]);
		break;
	case MENUITEM_WAVE:
		switch (current_item_wave) {
		case MENUITEM_WAVE_DELAY:
			sprintf(menu_buffer, "Wave:: %s delay", menu_settings.wave_delay ? "2s" : "no");
			break;
		case MENUITEM_WAVE_ACTION:
			sprintf(menu_buffer, "Wave:: %s", wave_string[menu_settings.wave_action]);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_EAEB:
		switch (current_item_eaeb) {
		case MENUITEM_EAEB_FRAMES:
			sprintf(menu_buffer, "Extended AEB:: %u frames", menu_settings.eaeb_frames);
			break;
		case MENUITEM_EAEB_EV:
			ev_print(ev_display, menu_settings.eaeb_ev);
			sprintf(menu_buffer, "Extended AEB:: %s", ev_display);
			break;
		case MENUITEM_EAEB_DELAY:
			sprintf(menu_buffer, "Extended AEB:: %s delay", menu_settings.eaeb_delay ? "2s" : "no");
			break;
		case MENUITEM_EAEB_M_MIN:
			sprintf(menu_buffer, "Extended AEB:: M1 %s", tv_string[(menu_settings.eaeb_m_min - (0x10)) >> 3]);
			break;
		case MENUITEM_EAEB_M_MAX:
			sprintf(menu_buffer, "Extended AEB:: M2 %s", tv_string[(menu_settings.eaeb_m_max - (0x10)) >> 3]);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_INTERVAL:
		switch (current_item_interval) {
		case MENUITEM_INTERVAL_DELAY:
			sprintf(menu_buffer, "Interval:: %s delay", menu_settings.interval_delay ? "2s" : "no");
			break;
		case MENUITEM_INTERVAL_TIME:
			sprintf(menu_buffer, "Interval:: %us time", menu_settings.interval_time);
			break;
		case MENUITEM_INTERVAL_EAEB:
			sprintf(menu_buffer, "Interval:: EAEB %s", menu_settings.interval_eaeb ? "yes" : "no");
			break;
		case MENUITEM_INTERVAL_SHOTS:
			if (menu_settings.interval_shots == 0)
				sprintf(menu_buffer, "Interval:: unlimited");
			else
				sprintf(menu_buffer, "Interval:: %u shots", menu_settings.interval_shots);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_REMOTE_DELAY:
		sprintf(menu_buffer, "IR Remote Release: %s", menu_settings.remote_delay ? "instant" : "2sec.");
		break;
	default:
		break;
	}

	return menu_buffer;
}
