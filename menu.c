#include "main.h"
#include "utils.h"
#include "settings.h"

#include "menu.h"

int option_number = 1;
int last_option = 13;
int eaeb_sub_menu = 0;
int st_1 = 0;

char menu_buffer[17];

void  menu_display();
char *menu_message();

void menu_swap() {
	switch(option_number) {
	case 1:
		settings.av_comp = ev_sgn(settings.av_comp);
		break;
	case 2:
		settings.flash_comp = ev_sgn(settings.flash_comp);
		break;
	case 7:
		if      (settings.color_temp < 2200) settings.color_temp =  2200;
		else if (settings.color_temp < 3200) settings.color_temp =  3200;
		else if (settings.color_temp < 4000) settings.color_temp =  4000;
		else if (settings.color_temp < 5200) settings.color_temp =  5200;
		else if (settings.color_temp < 6000) settings.color_temp =  6000;
		else if (settings.color_temp < 7000) settings.color_temp =  7000;
		else                                 settings.color_temp = 11000;
		break;
	}

	update = 0;
	menu_display();
}

void menu_up() {
	if (option_number == 1)
		option_number = last_option;
	else
		option_number -= 1;

	update = 1;
	menu_display();
}

void menu_down() {
	if (option_number == last_option)
		option_number =1;
	else
		option_number += 1;

	update = 1;
	menu_display();
}

void menu_right() {
	switch(option_number) {
	case 1:
		settings.av_comp = ev_inc(settings.av_comp);
		break;
	case 2:
		settings.flash_comp = ev_inc(settings.flash_comp);
		break;
	case 3:
		settings.aeb_ev = ev_inc(settings.aeb_ev);
		break;
	case 4:
		if (cameraMode.CfSafetyShift == 0)
			SendToIntercom(0x39, 1, 1);
		break;
	case 6:
		settings.iso_in_viewfinder = 1;
		settings_write();
		break;
	case 7:
		settings.color_temp += 100;
		if (settings.color_temp > 11000)
			settings.color_temp = 11000;
		break;
	case 8:
		SendToIntercom(0x30, 1, 0);
		break;
	case 9:
		SendToIntercom(0x2E, 1, 0);
		break;
	case 10:
		if (settings.dp_opt < 3) {
			settings.dp_opt++;
			settings_write();
		}
		break;
	case 11:
		if (eaeb_sub_menu == 0) {
			if(st_1 < 4) {
				st_1++;
			}
		} else {
			switch (st_1) {
			case 0:
				if (settings.eaeb_frames < 9)
					settings.eaeb_frames += 2;
				break;
			case 1:
				settings.eaeb_ev = ev_inc(settings.eaeb_ev);
				break;
			case 2:
				settings.eaeb_delay = TRUE;
				break;
			case 3:
				if (settings.eaeb_m_min <= 0x90) //98 is maximum
					settings.eaeb_m_min += 8;
				break;
			case 4:
				if (settings.eaeb_m_max <= 0x90) //98 is maximum
					settings.eaeb_m_max += 8;
				break;
			}
		}
		break;
	case 12:
		settings.interval_time = (settings.interval_time < 100) ? (settings.interval_time + 1) : (100);
		break;
	case 13:
		settings.ir_inst = TRUE;
		RemoteInstantRelease(1);
		settings_write();
		break;
	}

	update = 0;
	menu_display();
}

void menu_left() {
	switch (option_number) {
	case 1:
		settings.av_comp = ev_dec(settings.av_comp);
		break;
	case 2:
		settings.flash_comp = ev_dec(settings.flash_comp);
		break;
	case 3:
		if (settings.aeb_ev > 0x04)
			settings.aeb_ev = ev_dec(settings.aeb_ev);
		else
			settings.aeb_ev = 0x00;
		break;
	case 4:
		if (cameraMode.CfSafetyShift == 1)
			SendToIntercom(0x39, 1, 0);
		break;
	case 6:
		settings.iso_in_viewfinder = 0;
		settings_write();
		break;
	case 7:
		settings.color_temp -= 100;
		if (settings.color_temp < 1800)
			settings.color_temp = 1800;
		break;
	case 8:
		SendToIntercom(0x30, 1, 1);
		break;
	case 9:
		SendToIntercom(0x2E, 1, 1);
		break;
	case 10:
		if (settings.dp_opt > 0) {
			settings.dp_opt--;
			settings_write();
		}
		break;
	case 11:
		if (eaeb_sub_menu == 0) {
			if(st_1 > 0) {
				st_1--;
			}
		} else {
			switch (st_1) {
			case 0:
				if (settings.eaeb_frames > 3)
					settings.eaeb_frames -= 2;
				break;
			case 1:
				if (settings.eaeb_ev > 0x04)
					settings.eaeb_ev = ev_dec(settings.eaeb_ev);
				break;
			case 2:
				settings.eaeb_delay = FALSE;
				break;
			case 3:
				if(settings.eaeb_m_min >= 0x18) //10 is minimum
					settings.eaeb_m_min -= 8;
				break;
			case 4:
				if(settings.eaeb_m_max >= 0x18) //10 is minimum
					settings.eaeb_m_max -= 8;
				break;
			}
		}
		break;
	case 12:
		settings.interval_time = (settings.interval_time > 1) ? (settings.interval_time - 1) : (1);
		break;
	case 13:
		settings.ir_inst = FALSE;
		RemoteInstantRelease(2);
		settings_write();
		break;
	}

	update = 0;
	menu_display();
}

void menu_save() {
	switch (option_number) {
	case 1:
		SendToIntercom(0xA, 1, settings.av_comp);
		break;
	case 2:
		SendToIntercom(0x03, 1, settings.flash_comp);
		break;
	case 3:
		SendToIntercom(0xd, 1, settings.aeb_ev);
		break;
	case 7:
		SendToIntercom(0x10, 2, settings.color_temp);

		if (cameraMode.WB != 0x08)
			SendToIntercom(0x5, 1, 0x08);

		break;
	case 11:
		settings_write();
		eaeb_sub_menu ^= 1;
		break;
	case 12:
		 settings_write();
		 break;
	}
}

void menu_display() {
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
}

char *menu_message() {
	SleepTask(40);
	char sign[2] = {'+', '-'};
	char ev_display[] = "      ";

	switch (option_number) {
	case 1:
		if (update)
			settings.av_comp = cameraMode.AvComp;

		ev_print(ev_display, settings.av_comp);
		sprintf(menu_buffer, "Av comp:         %s", ev_display);
		break;
	case 2:
		if (update)
			settings.flash_comp = cameraMode.FlashExComp;

		ev_print(ev_display, settings.flash_comp);
		sprintf(menu_buffer, "Flash exp comp:  %s", ev_display);
		break;
	case 3:
		if (update)
			settings.aeb_ev = cameraMode.AEB;

		ev_print(ev_display, settings.aeb_ev);
		sprintf(menu_buffer, "AEB:             %s", settings.aeb_ev ? ev_display : "Off");
		break;
	case 4:
		sprintf(menu_buffer, "Safety Shift:  %s", cameraMode.CfSafetyShift ? "On" : "Off");
		break;
	case 5:
		sprintf(menu_buffer, "Release Count: %u", FLAG_RELEASE_COUNT);
		break;
	case 6:
		sprintf(menu_buffer, "Show ISO in Viewfinder: %s", settings.iso_in_viewfinder ? "On" : "Off");
		break;
	case 7:
		if (update)
			settings.color_temp = cameraMode.ColorTemp;

		sprintf(menu_buffer, "Color Temperature: %uK", settings.color_temp);
		break;
	case 8:
		sprintf(menu_buffer, "Flash:            %s", cameraMode.CfNotEmitFlash ? "Off" : "On");
		break;
	case 9:
		sprintf(menu_buffer, "AF Assist Beam:       %s", cameraMode.CfAfAssistBeam ? "Off" : "On");
		break;
	case 10:
		sprintf(menu_buffer, "DP Button:    %s", dp_button_string[settings.dp_opt]);
		break;
	case 11:
		switch (st_1) {
		case 0:
			sprintf(menu_buffer, "Extended AEB: %u frames", settings.eaeb_frames);
			break;
		case 1:
			ev_print(ev_display, settings.eaeb_ev);
			sprintf(menu_buffer, "Extended AEB: %s", ev_display);
			break;
		case 2:
			sprintf(menu_buffer, "Extended AEB: %s Delay", settings.eaeb_delay ? "2s" : "No");
			break;
		case 3:
			sprintf(menu_buffer, "Extended AEB: M1 %s", s_m_eaeb[(settings.eaeb_m_min - (0x10)) >> 3]);
			break;
		case 4:
			sprintf(menu_buffer, "Extended AEB: M2 %s", s_m_eaeb[(settings.eaeb_m_max - (0x10)) >> 3]);
			break;
		}
		break;
	case 12:
		sprintf(menu_buffer, "Interval time: %u", settings.interval_time);
		break;
	case 13:
		sprintf(menu_buffer, "IR Remote Release: %s", settings.ir_inst ? "Instant" : "2sec.");
		break;
	}

	return menu_buffer;
}
