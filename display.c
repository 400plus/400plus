#include <vxworks.h>
#include <string.h>

#include "main.h"
#include "firmware.h"
#include "firmware/camera.h"

#include "bmp.h"
#include "cmodes.h"
#include "exposure.h"
#include "settings.h"
#include "utils.h"
#include "debug.h"

#include "display.h"

char display_message[LP_MAX_WORD];
int  message_timeout;

int get_efcomp_data(int efcomp);

void display_refresh(void) {
	dialog_redraw(hMainDialog);
}

void hack_item_set_label_int(dialog_t *dialog, const int type, const void *data, const int length, const int item)
{
	int data_meteringmode_spot  = 0xF6;
	int data_whitebalance_ctemp = 0xCF;
	int data_efcomp;

	const int *my_data = data;

	if (dialog == hMainDialog) {
		switch (item) {
		case 0x0B: // flash exposure compensation
			if (DPData.efcomp > 0x10 && DPData.efcomp < 0xF0) {
				data_efcomp = get_efcomp_data(DPData.efcomp);
				my_data = &data_efcomp;
			}
		break;
		case 0x0C: // white balance
			if (DPData.wb == WB_MODE_COLORTEMP)
				my_data = &data_whitebalance_ctemp;
		break;
		case 0x0D: // metering mode
			if (DPData.metering == METERING_MODE_SPOT)
				my_data = &data_meteringmode_spot;
		break;
		}
	}

	item_set_label_internal(dialog, type, my_data, length, item);
}

void hack_item_set_label_str(dialog_t *dialog, const int type, const void *data, const int length, const int item)
{
	char label[32] = "";
	const char *my_data = data;

	if (dialog == hMainDialog) {
		switch (item) {
		case 0x04: // ISO
			iso_print(label, DPData.iso);
			my_data = label;
		break;
		}
	}

	item_set_label_internal(dialog, type, my_data, length, item);
}

#if FALSE

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

void display_overlay(uint8_t *vram_address) {
	char buffer[LP_MAX_WORD];

	if (FLAG_GUI_MODE == GUIMODE_OLC && AE_IS_CREATIVE(DPData.ae)) {
		if (FLAG_DISPLAY_ON) {
			int current_cmode = get_current_cmode();

			if (status.msm_active)
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY),  35,  96, "[***]");
			else if (status.cmode_active && current_cmode != CMODE_NONE)
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY),  16,  96, "%s", cmodes_config.names[current_cmode]);

			if (status.fexp && DPData.tv_val != TV_VAL_BULB)
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY), 138,  32, "#");

			if (settings.autoiso_enable && (DPData.ae != AE_MODE_M || DPData.tv_val != TV_VAL_BULB))
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY), 237,  14, "%s", AUTOISO_AUTO);

			if (DPData.wb == WB_MODE_COLORTEMP)
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY),  50, 138, "%d", DPData.color_temp);

			if (DPData.ae_bkt) {
				ec_print(buffer, DPData.ae_bkt);
				bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY), 224,  96, "%s", buffer);
			}

#ifdef RELEASE
			bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_BLUE), 148, 0, LP_WORD(L_P_400PLUS));
#else
			bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_BLACK, COLOR_RED ),  20, 0, LP_WORD(L_A_WARNING));
#endif

			if (*display_message) {
				if(timestamp() < message_timeout)
					bmp_printf(vram_address, FONT(FONT_SMALL, COLOR_WHITE, COLOR_BLACK),  16, 228, display_message);
				else
					*display_message = '\0';
			}
		}

	}
}

void display_message_set(char *message, int timeout) {
	strncpy(display_message, message, LP_MAX_WORD);
	message_timeout = timestamp() + timeout;

	display_refresh();
}

int hack_TransferScreen(int r0, int r1, int r2, int r3) {
	debug_log("0x%08X, 0x%08X, 0x%08X, 0x%08X", r0, r1, r2, r3);

	return TransferNormalScreen(r0, r1, r2, r3);
}

int hack_FF92E704 (int r0, int r1, int r2, int r3) {
	debug_log("0x%08X, 0x%08X, 0x%08X, 0x%08X", r0, r1, r2, r3);

	return sub_FF92E704(r0, r1, r2, r3);
}

int hack_FF92E4C4 (int r0, int r1, int r2, int r3) {
	debug_log("0x%08X, 0x%08X, 0x%08X, 0x%08X", r0, r1, r2, r3);

	display_overlay((uint8_t*)(r3 + 0x78));
	return sub_FF92E4C4(r0, r1, r2, r3);
}

#ifdef ENABLE_DEBUG
int hack_GUI_IDLEHandler(int unk0, int event, int unused, int unk1) {
	debug_log("0x%08X, %s, 0x%08X, 0x%08X", unk0, debug_gui_name(event), unused, unk1);

	return GUI_IDLEHandler(unk0, event, unused, unk1);
}
#endif

int olc_colors_map[] = {
	[ 0] = 0,
	[ 1] = 0x1B, // 27  Blk on Gry
	[ 2] = 0xE5, // 229 Blk on Yel
	[ 3] = 0x70, // Grn on Gry
	[ 4] = 0xC1, // 193 Blu on Gry
	[ 5] = 0x24, // 36  Blu on Blk
	[ 6] = 0xF1, // 241 Blu on Yel
	[ 7] = 0x11, // Cya on Gry
	[ 8] = 0x44, // 68  Yel on Blk
	[ 9] = 0x42, // 66  Org on Blk
	[10] = 0x7C, // 124 Yel on Grn
	[11] = 0x84, // 132 Yel on Blu
	[12] = 0x86, // 134 Yel on Blu
	[13] = 0x88, // 136 Yel on Blu
	[14] = 0x87, // 135 Yel on Cya
	[15] = 0x49, // 73  Yel on Red
	[16] = 0x89, // 137 Yel on Pur
	[17] = 0x35, // 53  Red on Gry
	[18] = 0x34, // 52  Red on Gry
	[19] = 0x72, // 114 Red on Gry
	[20] = 0x39, // 57  Red on Pnk
	[21] = 0x3A, // 58  Red on Yel
	[22] = 0x92, // 146 Red on Blk
	[23] = 0x22, // 34  Pur on Blk
	[24] = 0x76, // 118 Wht on Grn
	[25] = 0x5F, // 95  Gry on Gry
	[26] = 0x99, // 153 Gry on Red
	[27] = 0x9C, // 156 Gry on Red
	[28] = 0xFF, // 255 Gry on Blu
	[29] = 0x8C, // 140 Wht on Blu
	[30] = 0x78, // 120 Wht on Cya
	[31] = 0xBE, // 190 Gry on Yel
	[32] = 0xDE, // 222 Gry on Yel
	[33] = 0xFE, // 254 Gry on Yel
};

void *hack_invert_olc_screen(char *dst, char *src, int size) {
	if ( settings.invert_olc && (FLAG_GUI_MODE == GUIMODE_OLC || FLAG_GUI_MODE == GUIMODE_ACTIVESWEEP_OLC)) {
		while (size--) {
			*dst++ = olc_colors_map[settings.invert_olc] - (*src++);
		}
		return dst;
	}

	return memcpy(dst, src, size);
}

int get_efcomp_data(int efcomp) {
	int negative = FALSE, value = 0;

	if (efcomp > 0x30) {
		efcomp = 0x100 - efcomp;
		negative = TRUE;
	}

	switch (efcomp)	{
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

	return value + (negative ? 130 : 154);
}
