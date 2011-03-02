#include "main.h"
#include "firmware.h"

#include "display.h"

// Translation from ISO codes to text displayed
const char iso_text[][5] = {" 100", " 125", " 160", " 200", " 250", " 320", " 400", " 500", " 640", " 800", "1000", "1250", "1600", "2000", "2500", "3200"};
const int  iso_code[]    = {  0x48,   0x4C,   0x4E,   0x50,   0x53,   0x56,   0x58,   0x5C,   0x5D,   0x60,   0x64,   0x66,   0x68,   0x6C,   0x6D,   0x6F};

void display_refresh_meteringmode();
void display_refresh_whitebalance();
void display_refresh_flashcomp();
void display_refresh_iso();

void restore_display() {
	SleepTask(100);

	if (cameraMode.AEMode < 6)
		display_refresh();
}

void display_refresh() {
	if (cameraMode.MeteringMode == METERING_MODE_SPOT)
		display_refresh_meteringmode();

	if (cameraMode.WB == WB_MODE_COLORTEMP)
		display_refresh_whitebalance();

	if (cameraMode.FlashExComp > 0x10 && cameraMode.FlashExComp < 0xF0)
		display_refresh_flashcomp();

	display_refresh_iso();

	do_some_with_dialog(*(int*)(0x47F0));
}

void display_refresh_meteringmode() {
	sub_FF8382DC(*(int*)(0x47F0), 0x0D, 0xF6);
}

void display_refresh_whitebalance() {
	sub_FF8382DC(*(int*)(0x47F0), 0x0C, 0xCF);
}

void display_refresh_flashcomp() {
	int negative = FALSE, value;
	int flash_exp_comp = cameraMode.FlashExComp;

	if (flash_exp_comp > 0x30) {
		flash_exp_comp = 0x100 - flash_exp_comp;
		negative = TRUE;
	}

	switch (flash_exp_comp)	{
	case 0x13: value =  1; break;
	case 0x14: value =  0; break;
	case 0x15: value =  2; break;
	case 0x18: value =  3; break;
	case 0x1B: value =  5; break;
	case 0x1C: value =  4; break;
	case 0x1D: value =  6; break;
	case 0x20: value =  7; break;
	case 0x23: value =  9; break;
	case 0x24: value =  8; break;
	case 0x25: value = 10; break;
	case 0x28: value = 11; break;
	case 0x2B: value = 13; break;
	case 0x2C: value = 12; break;
	case 0x2D: value = 14; break;
	case 0x30: value = 15; break;
	}

	value += negative ? 130 : 154;

	sub_FF8382DC(*(int*)(0x47F0), 0x0B, value);
}


void display_refresh_iso() {
	int i;
	const char *text = "----";

	for (i = 0; i < LENGTH(iso_code); i++) {
		if (iso_code[i] == cameraMode.ISO) {
			text = iso_text[i];
			break;
		}
	}

	sub_FF837FA8(*(int*)(0x47F0), 0x04, text);
}
