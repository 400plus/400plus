#include "main.h"
#include "settings.h"

#include "menu.h"

int option_number = 1;
int color_temp = 2200;
int i = 0;
int last_option = 13;
int av_comp_val = 0;
int flash_exp_val = 0;
int aeb_val = 0;
int eaeb_sub_menu = 0;
int st_1 = 0, st_2 = 0;

int one = 0, two = 0;

char menu_buffer[17];

void  menu_display();
char *menu_message();

int  GetValue(int temp, int button);
void UpdateStVariables();
void HexToStr(int hex);

void menu_swap() {
	switch(option_number) {
	case 1:
	case 2:
		i ^= 1;
		break;
	case 7:
		if      (color_temp < 2200) color_temp =  2200;
		else if (color_temp < 3200) color_temp =  3200;
		else if (color_temp < 4000) color_temp =  4000;
		else if (color_temp < 5200) color_temp =  5200;
		else if (color_temp < 6000) color_temp =  6000;
		else if (color_temp < 7000) color_temp =  7000;
		else                        color_temp = 11000;
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
		av_comp_val = GetValue(av_comp_val, 1);
		break;
	case 2:
		flash_exp_val = GetValue(flash_exp_val, 1);
		break;
	case 3:
		aeb_val = GetValue(aeb_val, 1);
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
		color_temp += 100;
		if (color_temp > 11000)
			color_temp = 11000;
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
				UpdateStVariables();
			}
		} else {
			switch (st_1) {
			case 0:
				if (st_2 < 9)
					st_2 += 2;
				break;
			case 1:
				if (st_2 < 0x18)
					st_2 = GetValue(st_2, 1);
				break;
			case 2:
				st_2 = 1;
				break;
			case 3:
			case 4:
				if (st_2 <= 0x90) //98 is maximum
					st_2+=8;
				break;
			}
		}
		break;
	case 12:
		settings.interval_time = (settings.interval_time < 100) ? (settings.interval_time + 1) : (100);
		break;
	case 13:
		settings.ir_inst = 1;
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
		av_comp_val = GetValue(av_comp_val, 0);
		break;
	case 2:
		flash_exp_val = GetValue(flash_exp_val, 0);
		break;
	case 3:
		aeb_val = GetValue(aeb_val, 0);
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
		color_temp -= 100;
		if (color_temp < 1800)
			color_temp = 1800;
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
				UpdateStVariables();
			}
		} else {
			switch (st_1) {
			case 0:
				if (st_2 > 3)
					st_2-=2;
				break;
			case 1:
				if (st_2 > 0x04)
					st_2=GetValue(st_2, 0);
				break;
			case 2:
				st_2 = 0;
				break;
			case 3:
			case 4:
				if(st_2 >= 0x18) //10 is minimum
					st_2-=8;
				break;
			}
		}
		break;
	case 12:
		settings.interval_time = (settings.interval_time > 1) ? (settings.interval_time - 1) : (1);
		break;
	case 13:
		settings.ir_inst = 0;
		RemoteInstantRelease(2);
		settings_write();
		break;
	}

	update = 0;
	menu_display();
}

void menu_save() {
	int flash_exp_val_temp, av_comp_val_temp;

	switch (option_number) {
	case 1:
		if (i)
			av_comp_val_temp = 0 - av_comp_val;
		else
			av_comp_val_temp = av_comp_val;

		SendToIntercom(0xA, 1, av_comp_val_temp);
		break;
	case 2:
		if(i)
			flash_exp_val_temp = 0 - flash_exp_val;
		else
			flash_exp_val_temp = flash_exp_val;

		SendToIntercom(0x03, 1, flash_exp_val_temp);
		break;
	case 3:
		SendToIntercom(0xd, 1, aeb_val);
		break;
	case 7:
		SendToIntercom(0x10, 2, color_temp);

		if (cameraMode.WB != 0x08)
			SendToIntercom(0x5, 1, 0x08);

		break;
	case 11:
		if(eaeb_sub_menu) {
			switch (st_1) {
			case 0:
				settings.eaeb_frames = st_2;
				break;
			case 1:
				settings.eaeb_ev = st_2;
				break;
			case 2:
				settings.eaeb_delay = st_2;
				break;
			case 3:
				settings.eaeb_m_min = st_2;
				break;
			case 4:
				settings.eaeb_m_max = st_2;
				break;
			}

			settings_write();
		}

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

	switch (option_number) {
	case 1:
		if (update) {
			av_comp_val = cameraMode.AvComp;

			if (av_comp_val > 0x30) {
				av_comp_val = 0x100 - av_comp_val;
				i = 1;
			} else
				i = 0;
		}

		HexToStr(av_comp_val);
		sprintf(menu_buffer, "Av comp:         %c %u.%u", sign[i], one, two);
		break;
	case 2:
		if (update) {
			flash_exp_val = cameraMode.FlashExComp;
			if (flash_exp_val > 0x30) {
				flash_exp_val = 0x100 - flash_exp_val;
				i = 1;
			} else
				i = 0;
		}

		HexToStr(flash_exp_val);
		sprintf(menu_buffer, "Flash exp comp:  %c %u.%u", sign[i], one, two);
		break;
	case 3:
		if (update)
			aeb_val = cameraMode.AEB;

		i = 0;

		HexToStr(aeb_val);
		sprintf(menu_buffer, "AEB:        +-%u.%u", one, two);
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
			color_temp = cameraMode.ColorTemp;

		sprintf(menu_buffer, "Color Temperature: %uK", color_temp);
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
		if (update)
			UpdateStVariables();

		switch (st_1) {
		case 1:
			HexToStr(st_2);
			sprintf(menu_buffer, "Extended AEB: %u.%u %s", one, two, s_eaeb[st_1]);
			break;
		case 2:
			sprintf(menu_buffer, "Extended AEB: %s Delay", st_2 ? "2s" : "No");
			break;
		case 3:
			sprintf(menu_buffer, "Extended AEB: M1 %s", s_m_eaeb[(st_2 - (0x10)) >> 3]);
			break;
		case 4:
			sprintf(menu_buffer, "Extended AEB: M2 %s", s_m_eaeb[(st_2 - (0x10)) >> 3]);
			break;
		default:
			sprintf(menu_buffer, "Extended AEB: %u %s", st_2, s_eaeb[st_1]);
			break;
		}

		break;
	case 12:
		sprintf(menu_buffer, "Interval time: %u", settings.interval_time);
		break;
	case 13:
		sprintf(menu_buffer, "IR Remote Release: %s", (settings.ir_inst == 1) ? ("Instant") : ("2sec."));
		break;
	}

	return menu_buffer;
}

int GetValue(int temp, int button) {
	if (temp == 0 && button == 0 && option_number != 3 && option_number != 11)
		i=1;

	if (i)
		button ^= 1;

	switch (button) {
	case 0:
		if (cameraMode.CfSettingSteps == 1) {
			if ((temp & 3) != 0){
				temp &= 0xFC;
				break;
			}

			temp -= 4;
			break;
		} else {
			if ((temp & 7) != 0 && (temp & 3) == 0) {
				temp -= 1;
				break;
			}

			if ((temp & 5) == 5)
				temp -= 2;
			else
				temp -= 3;
		}

		if (temp < 0)
			temp=0;

		break;
	case 1:
		if (cameraMode.CfSettingSteps == 1) {
			temp = (temp & 0xFC) + 4;
			break;
		} else {
			if ((temp & 7) != 0 && (temp & 3) == 0) {
				temp += 1;
				break;
			}

			if ((temp &3 ) == 3)
				temp += 2;
			else
				temp += 3;
		}

		if (temp > 0x30)
			temp = 0x30;

		break;
	}

	if (temp == 0 && i == 1)
		i = 0;

	return temp;
}

void UpdateStVariables() {
	switch (st_1)	{
	case 0:
		st_2 = settings.eaeb_frames;
		break;
	case 1:
		if (cameraMode.CfSettingSteps)
			settings.eaeb_ev &= 0xFC;
		else {
			if ((settings.eaeb_ev & 7) != 0 && (settings.eaeb_ev & 3) == 0)
				settings.eaeb_ev -= 1;
		}

		st_2 = settings.eaeb_ev;
		break;
	case 2:
		st_2 = settings.eaeb_delay;
		break;
	case 3:
		st_2 = settings.eaeb_m_min;
		break;
	case 4:
		st_2 = settings.eaeb_m_max;
		break;
	}
}

void HexToStr(int hex) {
	one = 0;
	two = 0;

	switch (hex & 0xf0) {
	case 0x10:
		one = 2;
		break;
	case 0x20:
		one = 4;
		break;
	case 0x30:
		one = 6;
		break;
	}

	if((hex & 0x08) == 8)
		one++;

	switch(hex & 0x07) {
		case 3:
			two = 3;
			break;
		case 4:
			two = 5;
			break;
		case 5:
			two = 7;
			break;
	}
}
