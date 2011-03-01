#include "main.h"
#include "utils.h"
#include "settings.h"

#include "menu.h"

type_SETTINGS menu_settings;

type_MENUITEM      current_item      = 0;
type_MENUITEM_EAEB current_item_eaeb = 0;

int eaeb_sub_menu = FALSE;

char menu_buffer[17];

char *wb_string[] = {"Auto", "Daylight", "Cloudy", "Tungsten", "Fluorescent", "Flash", "Custom", "Shade", "Color temp."};
char *tv_string[] = {"30", "15", "8", "4", "2", "1", "0.5", "1/4","1/8","1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000", "1/4000"} ;
char *dp_string[] = {"Disabled", "Change ISO", "Extended AEB", "Interval"};

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

void menu_swap() {
	switch(current_item) {
	case MENUITEM_AV_COMP:
		menu_settings.av_comp = ev_sgn(menu_settings.av_comp);
		break;
	case MENUITEM_FLASH_COMP:
		menu_settings.flash_comp = ev_sgn(menu_settings.flash_comp);
		break;
	case MENUITEM_WHITE_BALANCE:
		menu_settings.white_balance = (menu_settings.white_balance + 1) % 9;
		break;
	}

	menu_display();
}

void menu_up() {
	if (eaeb_sub_menu) {
		if (current_item_eaeb == MENUITEM_EAEB_LAST)
			current_item_eaeb = MENUITEM_EAEB_FIRST;
		else
			current_item_eaeb++;
	} else {
		if (current_item == MENUITEM_LAST)
			current_item = MENUITEM_FIRST;
		else
			current_item++;
	}

	menu_display();
}

void menu_down() {
	if (eaeb_sub_menu) {
		if (current_item_eaeb == MENUITEM_EAEB_FIRST)
			current_item_eaeb = MENUITEM_EAEB_LAST;
		else
			current_item_eaeb--;
	} else {
		if (current_item == MENUITEM_FIRST)
			current_item = MENUITEM_LAST;
		else
			current_item--;
	}

	menu_display();
}

void menu_right() {
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
			menu_settings.color_temp += 100;
			if (menu_settings.color_temp > 11000)
				menu_settings.color_temp = 11000;
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
	case MENUITEM_EAEB:
		if (eaeb_sub_menu) {
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
			}
		} else {
			eaeb_sub_menu = TRUE;
		}
		break;
	case MENUITEM_INTERVAL:
		menu_settings.interval_time = (menu_settings.interval_time < 100) ? (menu_settings.interval_time + 1) : 100;
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.ir_inst = TRUE;
		break;
	}

	menu_display();
}

void menu_left() {
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
			menu_settings.color_temp -= 100;
			if (menu_settings.color_temp < 1800)
				menu_settings.color_temp = 1800;
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
	case MENUITEM_EAEB:
		if (eaeb_sub_menu) {
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
			}
		} else {
			eaeb_sub_menu = TRUE;
		}
		break;
	case MENUITEM_INTERVAL:
		menu_settings.interval_time = (menu_settings.interval_time > 1) ? (menu_settings.interval_time - 1) : 1;
		break;
	case MENUITEM_REMOTE_DELAY:
		menu_settings.ir_inst = FALSE;
		break;
	}

	menu_display();
}

void menu_set() {
	switch (current_item) {
	case MENUITEM_EAEB:
	default:
		menu_save();
		break;
	}
}

void menu_esc() {
	switch (current_item) {
	case MENUITEM_EAEB:
		eaeb_sub_menu = FALSE;
		menu_display();
		break;
	}
}

void menu_save() {
	settings = menu_settings;

	settings_apply();
	settings_write();
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
		sprintf(menu_buffer, "AEB:             %s", menu_settings.aeb_ev ? ev_display : "Off");
		break;
	case MENUITEM_SAFETY_SHIFT:
		sprintf(menu_buffer, "Safety shift:  %s", menu_settings.safety_shift ? "On" : "Off");
		break;
	case MENUITEM_RELEASE_COUNT:
		sprintf(menu_buffer, "Release count: %u", FLAG_RELEASE_COUNT);
		break;
	case MENUITEM_ISO_VIEWFINDER:
		sprintf(menu_buffer, "Show ISO in viewfinder: %s", menu_settings.iso_in_viewfinder ? "On" : "Off");
		break;
	case MENUITEM_WHITE_BALANCE:
		if (menu_settings.white_balance == WB_MODE_COLORTEMP)
			sprintf(menu_buffer, "WB: color temp=%uK", menu_settings.color_temp);
		else
			sprintf(menu_buffer, "WB: %s", wb_string[menu_settings.white_balance]);
		break;
	case MENUITEM_EMIT_FLASH:
		sprintf(menu_buffer, "Flash:            %s", menu_settings.not_emit_flash ? "Off" : "On");
		break;
	case MENUITEM_AF_FLASH:
		sprintf(menu_buffer, "AF Assist Beam:       %s", menu_settings.not_af_flash ? "Off" : "On");
		break;
	case MENUITEM_DP_BUTTON:
		sprintf(menu_buffer, "DP Button:    %s", dp_string[menu_settings.dp_action]);
		break;
	case MENUITEM_EAEB:
		if (eaeb_sub_menu) {
			switch (current_item_eaeb) {
			case MENUITEM_EAEB_FRAMES:
				sprintf(menu_buffer, "Extended AEB: %u frames", menu_settings.eaeb_frames);
				break;
			case MENUITEM_EAEB_EV:
				ev_print(ev_display, menu_settings.eaeb_ev);
				sprintf(menu_buffer, "Extended AEB: %s", ev_display);
				break;
			case MENUITEM_EAEB_DELAY:
				sprintf(menu_buffer, "Extended AEB: %s Delay", menu_settings.eaeb_delay ? "2s" : "No");
				break;
			case MENUITEM_EAEB_M_MIN:
				sprintf(menu_buffer, "Extended AEB: M1 %s", tv_string[(menu_settings.eaeb_m_min - (0x10)) >> 3]);
				break;
			case MENUITEM_EAEB_M_MAX:
				sprintf(menu_buffer, "Extended AEB: M2 %s", tv_string[(menu_settings.eaeb_m_max - (0x10)) >> 3]);
				break;
			}
		} else {
			sprintf(menu_buffer, "Extended AEB...");
		}
		break;
	case MENUITEM_INTERVAL:
		sprintf(menu_buffer, "Interval time: %u", menu_settings.interval_time);
		break;
	case MENUITEM_REMOTE_DELAY:
		sprintf(menu_buffer, "IR Remote Release: %s", menu_settings.ir_inst ? "Instant" : "2sec.");
		break;
	}

	return menu_buffer;
}
