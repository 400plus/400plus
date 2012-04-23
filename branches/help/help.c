#include "main.h"
#include "firmware.h"

#include "debug.h"

#include "help.h"
#include "settings.h"
#include "utils.h"
#include "ini.h"

static char * found_help = NULL;

static int help_finder(void* user, int lineno, const char* section, const char* name, const char* value) {
	// check if it's our key
	if (!strncmp((char *)user, name, LP_MAX_WORD-1)) {
		int vlen = strlen(value);

		if (found_help) {
			free(found_help);
			found_help = NULL;
		}

		found_help = (char *)malloc(vlen+2);
		if (!found_help) {
			debug_log("Cannot allocate memory for help string");
			return 0; // break the scanning
		}

		strncpy0(found_help, value, vlen+1);
		debug_log("found help [%s]", found_help);
		return 0; // break the scanning
	}

	return 1; // return non-zero == continue file scanning
}

char * help_get_str(char * key) {
	static char lang[LP_MAX_WORD];

	if (settings.language != 0) {
		strncpy0(lang, languages_found[settings.language], LP_MAX_WORD);
	} else {
		GetLanguageStr(cameraMode->language, lang);
	}
	//debug_log("looking for help: [%s] <%s>", lang, key);

	int res;
	stoupper(lang); // convert to upper case
	res = ini_parse("A:/help.ini", lang, help_finder, NULL, (void*)key);
	if (res == 0) {
		debug_log("HELP: [%s] <%s> not found", lang, key);
	} else if (res > 0) {
		if (found_help) {
			//debug_log("HELP: [%s] <%s> on line %d", lang, key, res);
			//debug_log("[%s]", found_help);
			return found_help; // success
		} else {
			debug_log("HELP: error on line %d", res);
		}
	} else {
		debug_log("HELP: help.ini not found");
	}

	return NULL; // problem
}

static void *help_dlg_handler;
static int current_help_line = 0;
static char * current_help_str = 0;
static char help_line_1[25], help_line_2[25];
static int help_max_lines = 0;
#define HELP_LINE_LEN 23 // can be 24 but touches the borders
static char end_line[] = "-------[ END ]-------";

void help_dlg_destroy() {
	if (help_dlg_handler != NULL) {
		GUI_Lock();
		GUI_PalleteInit();

		DeleteDialogBox(help_dlg_handler);
		help_dlg_handler = NULL;
		FLAG_GUI_MODE = GUIMODE_400PLUS;

		GUI_UnLock();
		GUI_PalleteUnInit();
	}
}

int help_dlg_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {
	debug_log("HELP:_IC_ [%s][guimode:%02X]", debug_ic_name(event), FLAG_GUI_MODE);
	debug_log("HELP:_MC_ [%s][guimode:%02X]", debug_mc_name(event), FLAG_GUI_MODE);
	debug_log("HELP:_BTN_ [%s][guimode:%02X]", debug_btn_name(event), FLAG_GUI_MODE);
	debug_log("HELP:_GUI_ [%s][guimode:%02X]", debug_gui_name(event), FLAG_GUI_MODE);
	switch (event) {
	case GUI_BUTTON_UP:
		debug_log("HELP[UP]: %d", current_help_line);
		current_help_line--;
		if (current_help_line < 1) current_help_line = 1;

		if (get_splitted_line(help_line_1, current_help_str, HELP_LINE_LEN, current_help_line)) {
			dialog_set_property_str(help_dlg_handler, 1, help_line_1);
		} else {
			dialog_set_property_str(help_dlg_handler, 1, "ERR");
		}

		if (current_help_line >= help_max_lines ||
		    !get_splitted_line(help_line_2, current_help_str, HELP_LINE_LEN, current_help_line+1)) {
			dialog_set_property_str(help_dlg_handler, 2, end_line);
		} else {
			dialog_set_property_str(help_dlg_handler, 2, help_line_2);
		}

		dialog_redraw(help_dlg_handler);
		return 0; // block

	case GUI_BUTTON_DOWN:
		debug_log("HELP[DOWN]: %d", current_help_line);
		if (current_help_line < help_max_lines) current_help_line++;
		if (get_splitted_line(help_line_1, current_help_str, HELP_LINE_LEN, current_help_line)) {
			dialog_set_property_str(help_dlg_handler, 1, help_line_1);
			if (get_splitted_line(help_line_2, current_help_str, HELP_LINE_LEN, current_help_line+1)) {
				dialog_set_property_str(help_dlg_handler, 2, help_line_2);
			} else {
				dialog_set_property_str(help_dlg_handler, 2, end_line);
				//if (!help_line_end) current_help_line--;
			}
		} else {
			dialog_set_property_str(help_dlg_handler, 1, "ERR");
			//current_help_line--;
		}
		dialog_redraw(help_dlg_handler);
		return 0; // block

	case GUI_BUTTON_SET:
	case GUI_BUTTON_DP:
		help_dlg_destroy();
		return 0; // block
/*
	case GUI_BUTTON_RIGHT:
	case GUI_BUTTON_LEFT:
	case GUI_BUTTON_MENU:
	case GUI_BUTTON_JUMP:
	case GUI_BUTTON_ZOOM_IN_PRESS:
	case GUI_BUTTON_ZOOM_OUT_PRESS:
	case GUI_BUTTON_DISP:
	case GUI_BUTTON_DIAL_RIGHT:
	case GUI_BUTTON_DIAL_LEFT:
	case GUI_BUTTON_PLAY:
	case GUI_BUTTON_TRASH:
		return 0; // just block

	case GUI_BUTTON_ZOOM_IN_RELEASE:
	case GUI_BUTTON_ZOOM_OUT_RELEASE:
	case GUI_TERMINATE_WINSYS:
		help_dlg_destroy();

	default:
		// pass the other events
		return InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
*/
	default:
		return 0;
	}
}

void help_dlg_create(char * str) {
	beep();

	help_dlg_destroy();

	//FLAG_GUI_MODE = 0x2D;
	FLAG_GUI_MODE = GUIMODE_HELP;

	GUI_Lock();
	GUI_PalleteInit();

	help_dlg_handler = dialog_create(64, help_dlg_event_handler);

	PalettePush();

	current_help_str = str;

	help_max_lines = get_splitted_line(help_line_1, str, HELP_LINE_LEN, 0);

	if (get_splitted_line(help_line_1, str, HELP_LINE_LEN, 1))
		dialog_set_property_str(help_dlg_handler, 1, help_line_1);

	if (get_splitted_line(help_line_2, str, HELP_LINE_LEN, 2)) {
		dialog_set_property_str(help_dlg_handler, 2, help_line_2);
	} else {
		dialog_set_property_str(help_dlg_handler, 2, end_line);
	}

	current_help_line = 1;

	dialog_set_property_str(help_dlg_handler, 4, "");

	dialog_redraw(help_dlg_handler);

	GUI_UnLock();
	GUI_PalleteUnInit();

}



