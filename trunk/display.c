/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <camera.h>

#include "main.h"

#include "bmp.h"
#include "cmodes.h"
#include "exposure.h"
#include "settings.h"
#include "utils.h"

#include "display.h"

char display_message[LP_MAX_WORD];
int  message_timeout;

void display_refresh_meteringmode();
void display_refresh_whitebalance();
void display_refresh_flashcomp();
void display_refresh_iso();

void initialize_display() {
	if (!status.script_running)
		enqueue_action(restore_display);
}

void restore_display() {
	SleepTask(100);

	if (FLAG_GUI_MODE == GUIMODE_OLC && AE_IS_CREATIVE(DPData.ae))
		display_refresh();
}

void display_refresh() {
	if (DPData.metering == METERING_MODE_SPOT)
		display_refresh_meteringmode();

	if (DPData.wb == WB_MODE_COLORTEMP)
		display_refresh_whitebalance();

	if (DPData.efcomp > 0x10 && DPData.efcomp < 0xF0)
		display_refresh_flashcomp();

	display_refresh_iso();

	dialog_redraw(hMainDialog);

	enqueue_action(display_overlay);
}

void display_refresh_meteringmode() {
	dialog_set_property_int(hMainDialog, 0x0D, 0xF6);
}

void display_refresh_whitebalance() {
	dialog_set_property_int(hMainDialog, 0x0C, 0xCF);
}

void display_refresh_flashcomp() {
	int negative = false, value = 0;
	int flash_exp_comp = DPData.efcomp;

	if (flash_exp_comp > 0x30) {
		flash_exp_comp = 0x100 - flash_exp_comp;
		negative = true;
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

	dialog_set_property_int(hMainDialog, 0x0B, value);
}


void display_refresh_iso() {
	char tmp[32] = "AUTO";

	switch (DPData.ae) {
	case AE_MODE_P:
	case AE_MODE_TV:
	case AE_MODE_AV:
	case AE_MODE_M:
		if (!settings.autoiso_enable || status.measuring)
	default:
			iso_print(tmp, DPData.iso);
	break;
	}

	dialog_set_property_str(hMainDialog, 0x04, tmp);
}

#if false

static dialog_t *countdown_dialog = NULL;

void display_countdown_dialog_create() {
	if (countdown_dialog) // if dialog exists for some reason
		dialog_redraw(countdown_dialog);
	else
		countdown_dialog = dialog_create(79, InfoCreativeAppProc);
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

#endif

void display_brightness() {
	if (settings.button_disp)
		switch (FLAG_GUI_MODE) {
		case GUIMODE_OFF:
			send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1);
			press_button(IC_BUTTON_DISP);
			break;

		case GUIMODE_OLC:
			if (DPData.lcd_brightness < 7)
				send_to_intercom(IC_SET_LCD_BRIGHTNESS, 1 + DPData.lcd_brightness);
			else
				press_button(IC_BUTTON_DISP);
			break;

		default:
			press_button(IC_BUTTON_DISP);
			break;
		}
	else
		press_button(IC_BUTTON_DISP);
}

void display_overlay() {
	int i;

	for (i = 0; i < OVERLAY_RETRY; i++)
		if (FLAG_GUI_MODE == GUIMODE_OLC && AE_IS_CREATIVE(DPData.ae)) {
			int current_cmode = get_current_cmode();

			if (status.cmode_active && current_cmode != CMODE_NONE)
				bmp_printf(FONT(FONT_SMALL, COLOR_BLACK, COLOR_WHITE),  16,  96, "%s", cmodes_config.names[current_cmode]);

			if (status.fexp)
				bmp_printf(FONT(FONT_SMALL, COLOR_BLACK, COLOR_WHITE), 138,  32, "#");

			if (DPData.wb == WB_MODE_COLORTEMP)
				bmp_printf(FONT(FONT_SMALL, COLOR_BLACK, COLOR_WHITE),  50, 134, "%d", DPData.color_temp);

			if (*display_message) {
				if(timestamp() < message_timeout)
					bmp_printf(FONT(FONT_SMALL, COLOR_WHITE, COLOR_BLACK),  16, 228, display_message);
				else
					*display_message = '\0';
			}

			SleepTask(OVERLAY_DELAY);
		}
}

void display_message_set(char *message, int timeout) {
	strncpy(display_message, message, LP_MAX_WORD);
	message_timeout = timestamp() + timeout;

	restore_display();
}
