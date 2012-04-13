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

		found_help = (char *)malloc(vlen+1);
		if (!found_help) {
			debug_log("Cannot allocate memory for help string");
			return 0; // break the scanning
		}

		strncpy(found_help, value, vlen);
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

void *help_dlg_handler;

void help_dlg_destroy() {
	if (help_dlg_handler != NULL) {
		//PalettePop();
		DeleteDialogBox(help_dlg_handler);
		help_dlg_handler = NULL;
		FLAG_GUI_MODE = GUIMODE_400PLUS;
		//GUI_ClearImage();
	}
}

int help_dlg_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {

	debug_log("_H-BTN_ [%s][guimode:%08X]", debug_btn_name(event), FLAG_GUI_MODE);

	switch (event) {
	case GUI_BUTTON_UP:
		debug_log("HELP: UP");
		return 0; // block
	case GUI_BUTTON_DOWN:
		debug_log("HELP: DOWN");
		return 0;
	case GUI_BUTTON_SET:
	case GUI_BUTTON_DP:
		help_dlg_destroy();
		return 0;

	case GUI_BUTTON_RIGHT:
	case GUI_BUTTON_LEFT:
	case GUI_BUTTON_MENU:
	case GUI_BUTTON_JUMP:
	case GUI_BUTTON_ZOOM_IN_PRESS:
	case GUI_BUTTON_ZOOM_IN_RELEASE:
	case GUI_BUTTON_ZOOM_OUT_PRESS:
	case GUI_BUTTON_ZOOM_OUT_RELEASE:
	case GUI_BUTTON_DISP:
	case GUI_BUTTON_DIAL_RIGHT:
	case GUI_BUTTON_DIAL_LEFT:
	case GUI_BUTTON_PLAY:
	case GUI_BUTTON_TRASH:
		return 0; // just block

	default:
		// pass the other events
		return InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
	}
}

void help_dlg_create(char * str) {
	beep();

	//FLAG_GUI_MODE = 0x2D;
	FLAG_GUI_MODE = 0x30;

	//GUI_Lock();
	//GUI_PalleteInit();

	help_dlg_handler = dialog_create(64, help_dlg_event_handler);
	//*(int*)((int)(menu_handler+0x58)) = (int)my_central_handler;
	//*(int*)((int)(menu_handler+0x7C)) = (int)menu_event_handler;

	PalettePush();
	//PaletteChange(current_menu->color);

	//menu_event_display();

	//GUI_UnLock();
	//GUI_PalleteUnInit();

	dialog_set_property_str(help_dlg_handler, 1, str); // 24 chars max
	dialog_set_property_str(help_dlg_handler, 2, "123456789012345678901234");

	dialog_redraw(help_dlg_handler);

}

void help_dlg_close() {
	GUI_Lock();
	GUI_PalleteInit();

	DeleteDialogBox(help_dlg_handler);
	help_dlg_handler = NULL;

	GUI_UnLock();
	GUI_PalleteUnInit();
}


