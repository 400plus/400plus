#include "main.h"
#include "utils.h"
#include "firmware.h"

#include "display.h"

void display_refresh_meteringmode();
void display_refresh_whitebalance();
void display_refresh_flashcomp();
void display_refresh_iso();
static int countdown_dialog = 0;

void restore_display() {
	SleepTask(100);

	if (cameraMode.ae < 6)
		display_refresh();
}

void display_refresh() {
	if (cameraMode.metering == METERING_MODE_SPOT)
		display_refresh_meteringmode();

	if (cameraMode.wb == WB_MODE_COLORTEMP)
		display_refresh_whitebalance();

	if (cameraMode.efcomp > 0x10 && cameraMode.efcomp < 0xF0)
		display_refresh_flashcomp();

	display_refresh_iso();

	dialog_redraw(MAIN_DIALOG);
}

void display_refresh_meteringmode() {
	dialog_set_property_int(MAIN_DIALOG, 0x0D, 0xF6);
}

void display_refresh_whitebalance() {
	dialog_set_property_int(MAIN_DIALOG, 0x0C, 0xCF);
}

void display_refresh_flashcomp() {
	int negative = FALSE, value;
	int flash_exp_comp = cameraMode.efcomp;

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

	dialog_set_property_int(MAIN_DIALOG, 0x0B, value);
}


void display_refresh_iso() {
	const char *text = "----";

	iso_display(text, cameraMode.iso);
	dialog_set_property_str(MAIN_DIALOG, 0x04, text);
}

void display_countdown_dialog_create() {
	if (countdown_dialog) // if dialog exists for some reason
		dialog_redraw(countdown_dialog);
	else
		countdown_dialog = DIALOG(79, InfoCreativeAppProc);
}

void display_countdown_dialog_destroy() {
	DeleteDialogBox(countdown_dialog);
	countdown_dialog = 0;
}

void display_countdown(int seconds) {
	char buffer[4];

	if (seconds)
		sprintf(buffer, "%u", seconds);
	else
		sprintf(buffer, "RUN");

	dialog_set_property_str(countdown_dialog, 1, buffer);
	dialog_redraw(countdown_dialog);
}
