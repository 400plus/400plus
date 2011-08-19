#include "main.h"

#include "languages.h"
#include "menu.h"
#include "menu_settings.h"
#include "utils.h"
#include "settings.h"

#include "menu_developer.h"

#undef TEST_DIALOGS
//#define TEST_DIALOGS
// enable dialogs testing from here...
// when enter the dialogs test mode
// DISPLAY -> next dialog
// MENU -> exit test mode
// JUMP -> change color palette (some dialogs are seen in special palettes)

#ifdef TEST_DIALOGS
#include "firmware.h"
#include "debug.h"
static void test_dialog_create();
#endif

type_MENUITEM menu_developer_items[] = {
#ifdef TEST_DIALOGS
	MENUITEM_LAUNCH(LP_WORD(L_TEST_DIALOGS),       test_dialog_create),
#endif
	MENUITEM_LAUNCH(LP_WORD(L_DUMP_LOG_TO_FILE),   dump_log),
	MENUITEM_LAUNCH(LP_WORD(L_ENTER_FACTORY_MODE), enter_factory_mode),
	MENUITEM_LAUNCH(LP_WORD(L_EXIT_FACTORY_MODE),  exit_factory_mode),
	MENUITEM_BOOLEAN(LP_WORD(L_DEBUG_ON_POWERON),  &settings.debug_on_poweron, NULL),
	MENUITEM_LOGFILE(LP_WORD(L_LOGFILE),           &settings.logfile_mode, NULL),
	MENUITEM_BREAK("")
};

type_MENU menu_developer = {
	name        : LP_WORD(L_DEVELOPER),
	length      : LENGTH(menu_developer_items),
	items       : menu_developer_items,
	reorder     : FALSE,
	tasks       : {
		[MENU_EVENT_DP] = menu_settings_start,
		[MENU_EVENT_CHANGE] = menu_set_changed,
		[MENU_EVENT_CLOSE] = menu_settings_save,
	}
};

void menu_developer_start() {
	beep();
	menu_create(&menu_developer);
}

#ifdef TEST_DIALOGS
extern void *menu_handler;
static int template = 1;
static int curr_palette = 0;

static int test_dialog_btn_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code) {
	switch (event) {
	case GUI_BUTTON_DISP:
		if (template>=110) {
			DeleteDialogBox(menu_handler);
			menu_handler = NULL;
			FLAG_GUI_MODE = GUIMODE_400PLUS;
		}
		template++;
		curr_palette = 0;
		debug_log("incrementing template to [%d]", template);
		test_dialog_create();
		return 0; // block
	case GUI_BUTTON_MENU:
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
		FLAG_GUI_MODE = GUIMODE_400PLUS;
		return 0;
	case GUI_BUTTON_JUMP:
		curr_palette++;
		debug_log("palette for dialog [%d] to [%d]", template, curr_palette);
		test_dialog_create();
		return 0;
	default:
		debug_log("btn: [%d] pressed.", event);
		break;
	}
	return InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
}

static void test_dialog_create() {
	debug_log("Creating dialog [%d]", template);
	FLAG_GUI_MODE = 0x30;

	if (menu_handler != NULL) {
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
	}

	menu_handler = dialog_create(template, test_dialog_btn_handler);

	int i;
	for (i = 0; i<255; i++) {
		char s[30];
		sprintf(s, "[%d,%d]",template,i);
		dialog_set_property_str(menu_handler, i, s);
	}

	PaletteChange(curr_palette);

	dialog_redraw(menu_handler);
}
#endif

#if 0

Info  Dialogs:
	4  - [error] 2 lines in center and 1 special in bottom, with X icon on top
	83 - [error] 1 title, red screen
	21 - [warning] 1 line in center and 2 special in bottom, with ! icon on top
	23 - 1 title, 2 lines in center, and 2 special places for buttons at bottom
	24 - 1 title, 3 lines in center, and 1 special places for buttons at bottom
	28 - 2 sections (left and right) with 6 lines each and title
	34 - 1 line in center and one line as description of SET btn, there is an icon of MENU btn for back.
	37,40 - 1 title, 1 line, 2 btns with text
	45 - 1 title, 5 lines info, 2 btns at bottom
	52 - 1 title, 3 lines info, 1 btn at bottm
	53 - 1 title, 2 lines info, 2 btns at bottom
	71 - 1 title, 2 lines info, 2 btns at bottom
	95 - 1 line, 2 btns at bottm
	105- 1 line in center with key icon on top-left and menu icon(back) on bottom-right

OSD   Dialogs:
	5  - [help] 1 line at the bottom
	64 - [help] 2 lines in center
	98 - [help] 1 line in center
	101- [help] 1 line in center
	6  - 5 lines with 10 chars in upper-right corner, icons infront of each line
	13 - ! 2 btns with text ~15 chars in bottom right corner
	14 - 2 parts with 2 lines each at the top half of the screen

Menu  Dialogs:
	8,9,10 - 1 title, 3 tabs, 5 lines, MENU and SET btns at bottom with text
	22 - the current menu, with 5 lines and 1 title on top
	25 - 5 lines and 1 title on top, lines are with 2 sections
	26 - 4 lines, 1 title on top and 2 special at the bottom, lines are with 2 sections
	42 - 1 title, 3 lines
	54 - ! 1 title, 3 sections with 6 btns, can be used for shortcuts
	69 - ! 1 title, 2 sections (left,right) with 3 lines for menus
	70 - ! 1 title, 2 sections (left,right) with 4 lines for menus
	86 - * with special palette, 1 title, 2 sections with 4 lines

Special Dialogs:
	33 - the sensor clean-up (full screen) animation with 1 line at the bottom
	38 - 1 line OSD with progress bar
	79 - the bulb counter screen, with 1 line at bottom (large font)
	102 - pause icon on top left
	103 - menu icon (back) on bottom right
	104 - key icon with SET text on top left
	99 - key with SET text on top left with 1 line under, and one text in upper-right



#endif

