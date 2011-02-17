#include "main.h"

#include "menu.h"

int option_number = 1;
int color_temp = 2200;
int i = 0;
int last_option = 13;
int av_comp_val;
int flash_exp_val;
int aeb_val;
int eaeb_sub_menu=0;

char buff[17];

int one = 0, two = 0;

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
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
}

void menu_up() {
	if (option_number == 1)
		option_number = last_option;
	else
		option_number -= 1;

	update = 1;
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
}

void menu_down() {
	if (option_number == last_option)
		option_number =1;
	else
		option_number += 1;

	update = 1;
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
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
		iso_in_viewfinder = 1;
		WriteSettings();
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
		if (dp_opt < 3) {
			dp_opt++;
			WriteSettings();
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
		interval_time = (interval_time < 101) ? (interval_time + 1) : (1);
		break;
	case 13:
		ir_inst = 1;
		RemoteInstantRelease(1);
		WriteSettings();
		break;
	}

	update = 0;
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
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
		iso_in_viewfinder = 0;
		WriteSettings();
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
		if (dp_opt > 0) {
			dp_opt--;
			WriteSettings();
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
		interval_time = (interval_time > 1) ? (interval_time - 1) : (100);
		break;
	case 13:
		ir_inst = 0;
		RemoteInstantRelease(2);
		WriteSettings();
		break;
	}

	update = 0;
	sub_FF837FA8(hInfoCreative, 0x11, menu_message());
	do_some_with_dialog(hInfoCreative);
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
				eaeb_frames = st_2;
				break;
			case 1:
				eaeb_ev = st_2;
				break;
			case 2:
				eaeb_delay = st_2;
				break;
			case 3:
				eaeb_m_min = st_2;
				break;
			case 4:
				eaeb_m_max = st_2;
				break;
			}

			WriteSettings();
		}

		eaeb_sub_menu ^= 1;
		break;
	case 12:
		 WriteSettings();
		 break;
	}
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
		sprintf(buff, "Av comp:         %c %u.%u", sign[i], one, two);
		return buff;
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
		sprintf(buff, "Flash exp comp:  %c %u.%u", sign[i], one, two);
		return buff;
	case 3:
		if (update)
			aeb_val = cameraMode.AEB;
		i = 0;
		HexToStr(aeb_val);
		sprintf(buff, "AEB:        +-%u.%u", one, two);
		return buff;
	case 4:
		if (cameraMode.CfSafetyShift == 0)
			return "Safety Shift:   Off";
		return "Safety Shift:   On";
	case 5:
		sprintf(buff, "Release Count: %u", FLAG_RELEASE_COUNT);
		return buff;
	case 6:
		if (iso_in_viewfinder)
			return "Show ISO in Viewfinder: On";
		return "Show ISO in Viewfinder: Off";
	case 7:
		if (update)
			color_temp = cameraMode.ColorTemp;
		sprintf(buff, "Color Temperature: %uK", color_temp);
		return buff;
	case 8:
		if (cameraMode.CfNotEmitFlash)
			return "Flash:            Off";
		return "Flash:            On";
	case 9:
		if (cameraMode.CfAfAssistBeam)
			return "AF Assist Beam:       Off";
		return "AF Assist Beam:       On";
	case 10:
		sprintf(buff, "DP Button:    %s", dp_button_string[dp_opt]);
		return buff;
	case 11:
		if (update)
			UpdateStVariables();

		if (st_1 == 1) {
			HexToStr(st_2);
			sprintf(buff, "Extended AEB: %u.%u %s", one, two, s_eaeb[st_1]);
			return buff;
		}

		if (st_1 == 2) {
			if (st_2)
				return "Extended AEB: 2sec. Delay";
			return "Extended AEB: No Delay";
		}

		if (st_1 == 3) {
			sprintf(buff, "Extended AEB: M1 %s", s_m_eaeb[(st_2 - (0x10)) >> 3]);
			return buff;
		}

		if (st_1 == 4) {
			sprintf(buff, "Extended AEB: M2 %s", s_m_eaeb[(st_2 - (0x10)) >>3]);
			return buff;
		}

		sprintf(buff, "Extended AEB: %u %s", st_2, s_eaeb[st_1]);
		return buff;
	case 12:
		sprintf(buff, "Interval time: %u", interval_time);
		return buff;
	case 13:
		sprintf(buff, "IR Remote Release: %s", (ir_inst == 1) ? ("Instant") : ("2sec."));
		return buff;
	}
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
		st_2=eaeb_frames;
		break;
	case 1:
		if (cameraMode.CfSettingSteps)
			eaeb_ev &= 0xFC;
		else {
			if ((eaeb_ev & 7) != 0 && (eaeb_ev & 3) == 0)
				eaeb_ev -= 1;
		}

		st_2=eaeb_ev;
		break;
	case 2:
		st_2=eaeb_delay;
		break;
	case 3:
		st_2=eaeb_m_min;
		break;
	case 4:
		st_2=eaeb_m_max;
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
