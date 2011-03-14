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
type_MENUITEM_TIMER    current_item_timer    = MENUITEM_TIMER_FIRST;

char menu_buffer[64];

const char *tv_string[]   = {"30", "15", "8", "4", "2", "1", "0.5", "1/4","1/8","1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;
const char *dp_string[]   = {"Disabled", "Intm ISO", "Ext AEB", "Interval", "Wave", "Timer"};
const char *shot_string[] = {"One shot", "Ext. AEB", "Interval"};

void menu_repeat(void (*repeateable)(int repeating));

void menu_repeateable_cycle  (int repeating);
void menu_repeateable_up     (int repeating);
void menu_repeateable_down   (int repeating);
void menu_repeateable_right  (int repeating);
void menu_repeateable_left   (int repeating);

void  menu_save();
void  menu_display();
char *menu_message();

void menu_print_ev   (char *buffer, char *menu, int   parm);
void menu_print_int  (char *buffer, char *menu, int   parm, int len);
void menu_print_char (char *buffer, char *menu, char *parm);

void menu_initialize() {
	menu_settings = settings;

	menu_settings.av_comp        = cameraMode.AvComp;
	menu_settings.flash_comp     = cameraMode.FlashExComp;
	menu_settings.aeb_ev         = cameraMode.AEB;
	menu_settings.not_emit_flash = cameraMode.CfNotEmitFlash;
	menu_settings.not_af_flash   = cameraMode.CfAfAssistBeam;

	// We do NOT recover ColorTemp from cameraMode, because the camera fiddles with this value internally.
	//menu_settings.color_temp     = cameraMode.ColorTemp;
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

void menu_cycle() {
	menu_repeat(menu_repeateable_cycle);
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
		menu_settings.color_temp += repeating ? 500 : 100;
		menu_settings.color_temp  = MIN(menu_settings.color_temp, 11000);
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
			if (menu_settings.wave_action == SHOT_ACTION_LAST)
				menu_settings.wave_action = SHOT_ACTION_FIRST;
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
	case MENUITEM_TIMER:
		switch (current_item_timer) {
		case MENUITEM_TIMER_DELAY:
			menu_settings.self_timer += repeating ? 10 : 1;
			menu_settings.self_timer  = MIN(menu_settings.self_timer, 250);
			break;
		case MENUITEM_TIMER_ACTION:
			if (menu_settings.timer_action == SHOT_ACTION_LAST)
				menu_settings.timer_action = SHOT_ACTION_FIRST;
			else
				menu_settings.timer_action++;
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
		menu_settings.color_temp -= repeating ? 500 : 100;
		menu_settings.color_temp  = MAX (menu_settings.color_temp, 1800);
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
			if (menu_settings.wave_action == SHOT_ACTION_FIRST)
				menu_settings.wave_action = SHOT_ACTION_LAST;
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
	case MENUITEM_TIMER:
		switch (current_item_timer) {
		case MENUITEM_TIMER_DELAY:
			menu_settings.self_timer -= repeating ? 10 : 1;
			menu_settings.self_timer  = MAX(menu_settings.self_timer, 1);
			break;
		case MENUITEM_TIMER_ACTION:
			if (menu_settings.timer_action == SHOT_ACTION_FIRST)
				menu_settings.timer_action = SHOT_ACTION_LAST;
			else
				menu_settings.timer_action--;
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

void menu_repeateable_cycle(int repeating) {
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
	case MENUITEM_DP_BUTTON:
		if (menu_settings.dp_action == DP_ACTION_LAST)
			menu_settings.dp_action = DP_ACTION_FIRST;
		else
			menu_settings.dp_action++;
		break;
	case MENUITEM_WAVE:
		switch (current_item_wave) {
		case MENUITEM_WAVE_DELAY:
			menu_settings.wave_delay = ! menu_settings.wave_delay;
			break;
		case MENUITEM_WAVE_ACTION:
			if (menu_settings.wave_action == SHOT_ACTION_LAST)
				menu_settings.wave_action = SHOT_ACTION_FIRST;
			else
				menu_settings.wave_action++;
			break;
		default:
			break;
		}
		break;
		case MENUITEM_EAEB:
			switch (current_item_eaeb) {
			case MENUITEM_EAEB_DELAY:
				menu_settings.eaeb_delay = ! menu_settings.eaeb_delay;
				break;
			default:
				break;
			}
			break;
		case MENUITEM_INTERVAL:
			switch (current_item_interval) {
			case MENUITEM_INTERVAL_DELAY:
				menu_settings.interval_delay = ! menu_settings.interval_delay;
				break;
			case MENUITEM_INTERVAL_EAEB:
				menu_settings.interval_eaeb = ! menu_settings.interval_eaeb;
				break;
			default:
				break;
			}
			break;
		case MENUITEM_TIMER:
			switch (current_item_timer) {
			case MENUITEM_TIMER_ACTION:
				if (menu_settings.timer_action == SHOT_ACTION_LAST)
					menu_settings.timer_action = SHOT_ACTION_FIRST;
				else
					menu_settings.timer_action++;
				break;
			default:
				break;
			}
			break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.remote_delay = ! menu_settings.remote_delay;
		break;
	default:
		break;
	}

	menu_display();
}

void menu_submenu() {
	switch(current_item) {
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
	case MENUITEM_TIMER:
		if (current_item_timer == MENUITEM_TIMER_LAST)
			current_item_timer = MENUITEM_TIMER_FIRST;
		else
			current_item_timer++;
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.remote_delay = ! menu_settings.remote_delay;
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
	SleepTask(50);

	switch (current_item) {
	case MENUITEM_RELEASE_COUNT:
		menu_print_int(menu_buffer, "Release count", FLAG_RELEASE_COUNT, 8);
		break;
	case MENUITEM_AV_COMP:
		menu_print_ev(menu_buffer, "Av comp", menu_settings.av_comp);
		break;
	case MENUITEM_FLASH_COMP:
		menu_print_ev(menu_buffer, "Flash comp", menu_settings.flash_comp);
		break;
	case MENUITEM_AEB:
		if (menu_settings.aeb_ev)
			menu_print_ev(menu_buffer, "AEB", menu_settings.aeb_ev);
		else
			menu_print_char(menu_buffer, "AEB",  "off");
		break;
	case MENUITEM_SAFETY_SHIFT:
		menu_print_char(menu_buffer, "Safety shift", menu_settings.safety_shift ? "on" : "off");
		break;
	case MENUITEM_ISO_VIEWFINDER:
		menu_print_char(menu_buffer, "ISO in viewfinder", menu_settings.iso_in_viewfinder ? "on" : "off");
		break;
	case MENUITEM_WHITE_BALANCE:
		menu_print_int(menu_buffer, "Color Temp. (K)", menu_settings.color_temp, 5);
		break;
	case MENUITEM_EMIT_FLASH:
		menu_print_char(menu_buffer, "Flash", menu_settings.not_emit_flash ? "off" : "on");
		break;
	case MENUITEM_AF_FLASH:
		menu_print_char(menu_buffer, "AF assist beam", menu_settings.not_af_flash ? "off" : "on");
		break;
	case MENUITEM_DP_BUTTON:
		menu_print_char(menu_buffer, "DP Button", (char*)dp_string[menu_settings.dp_action]);
		break;
	case MENUITEM_WAVE:
		switch (current_item_wave) {
		case MENUITEM_WAVE_DELAY:
			menu_print_char(menu_buffer, "Wave>Delay", menu_settings.wave_delay ? "2s" : "no");
			break;
		case MENUITEM_WAVE_ACTION:
			menu_print_char(menu_buffer, "Wave>Action", (char*)shot_string[menu_settings.wave_action]);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_EAEB:
		switch (current_item_eaeb) {
		case MENUITEM_EAEB_FRAMES:
			menu_print_int(menu_buffer, "Ext. AEB>Frames", menu_settings.eaeb_frames, 3);
			break;
		case MENUITEM_EAEB_EV:
			menu_print_ev(menu_buffer, "Ext. AEB>Step (EV)", menu_settings.eaeb_ev);
			break;
		case MENUITEM_EAEB_DELAY:
			menu_print_char(menu_buffer, "Ext. AEB>Delay", menu_settings.eaeb_delay ? "2s" : "no");
			break;
		case MENUITEM_EAEB_M_MIN:
			menu_print_char(menu_buffer, "Ext. AEB>Manual [", (char*)tv_string[(menu_settings.eaeb_m_min - (0x10)) >> 3]);
			break;
		case MENUITEM_EAEB_M_MAX:
			menu_print_char(menu_buffer, "Ext. AEB>Manual ]", (char*)tv_string[(menu_settings.eaeb_m_max - (0x10)) >> 3]);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_INTERVAL:
		switch (current_item_interval) {
		case MENUITEM_INTERVAL_DELAY:
			menu_print_char(menu_buffer, "Interval>Delay", menu_settings.interval_delay ? "2s" : "no");
			break;
		case MENUITEM_INTERVAL_TIME:
			menu_print_int(menu_buffer, "Interval>Time (s)", menu_settings.interval_time, 3);
			break;
		case MENUITEM_INTERVAL_EAEB:
			menu_print_char(menu_buffer, "Interval>EAEB", menu_settings.interval_eaeb ? "yes" : "no");
			break;
		case MENUITEM_INTERVAL_SHOTS:
			if (menu_settings.interval_shots == 0)
				menu_print_char(menu_buffer, "Interval>Shots", "no limit");
			else
				menu_print_int(menu_buffer, "Interval>Shots", menu_settings.interval_shots, 3);
			break;
		default:
			break;
		}
		break;
	case MENUITEM_TIMER:
		switch (current_item_timer) {
		case MENUITEM_TIMER_DELAY:
			menu_print_int(menu_buffer, "Timer>Delay (s)", menu_settings.self_timer, 3);
			break;
		case MENUITEM_TIMER_ACTION:
			menu_print_char(menu_buffer, "Timer>Action", (char*)shot_string[menu_settings.timer_action]);
			break;
		default:
			break;
		}
		break;

		break;
	case MENUITEM_REMOTE_DELAY:
		menu_print_char(menu_buffer, "IR remote delay", menu_settings.remote_delay ? "no" : "2s");
		break;
	default:
		break;
	}

	return menu_buffer;
}

void menu_print_ev(char *buffer, char *menu, int parm) {
	char tmp[32];

	ev_print(tmp, parm);
	menu_print_char(buffer, menu, tmp);

}

void menu_print_int(char *buffer, char *menu, int parm, int len) {
	char tmp[32];

	sprintf(tmp, "%*u", len, parm);
	menu_print_char(buffer, menu, tmp);

}

void menu_print_char(char *buffer, char *menu, char *parm) {
	sprintf(buffer, "%-18s:%s", menu, parm);
}
