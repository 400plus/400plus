// to enable specific functionality compile with the following flags:
// -DBREAK_CAMERA   - enable "factory mode" menus
// -DTEST_DIALOGS   - enable dialogs testing menu
// -DMEM_DUMP       - enable memory dump menu

// dialogs testing navigation:
// DISPLAY -> next dialog
// MENU -> exit test mode
// JUMP -> change color palette (some dialogs are seen in special palettes)

#include <vxworks.h>
#include <stdio.h>

#include "firmware/gui.h"

#include "macros.h"

#include "debug.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_settings.h"
#include "utils.h"
#include "settings.h"
#include "memspy.h"

#include "menu_developer.h"

extern void *menu_handler;
static int   template     = 1;
static int   curr_palette = 0;

static void test_dialog_create(void);

void menupage_developer_dump_log  (const menuitem_t *menuitem);
void menupage_developer_print_info(const menuitem_t *menuitem);

	menuitem_t menu_developer_items[] = {
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_DUMP,          LP_WORD(L_I_DUMP_LOG_TO_FILE),    menupage_developer_dump_log),
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_PRINT,         LP_WORD(L_I_PRINT_INFO),          menupage_developer_print_info),
	MENUITEM_BOOLEAN(MENUPAGE_DEVEL_DEBUG,         LP_WORD(L_I_DEBUG_ON_POWERON),   &settings.debug_on_poweron, NULL),
	MENUITEM_LOGFILE(MENUPAGE_DEVEL_MODE,          LP_WORD(L_I_LOGFILE_MODE),       &settings.logfile_mode,     NULL),
#ifdef MEM_DUMP
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_MEMORY,        LP_WORD(L_I_DUMP_MEMORY),         dump_memory_after_5s),
#endif
#ifdef MEMSPY
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_MEMSPYENABLE,  LP_WORD(L_I_MEMSPY_ENABLE),       memspy_enable),
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_MEMSPYDISABLE, LP_WORD(L_I_MEMSPY_DISABLE),      memspy_disable),
#endif
#ifdef BREAK_CAMERA
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_ENTERFACTMODE, LP_WORD(L_I_ENTER_FACTORY_MODE),  enter_factory_mode),
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_EXITFACTMODE,  LP_WORD(L_I_EXIT_FACTORY_MODE),   exit_factory_mode),
#endif
#ifdef TEST_DIALOGS
	MENUITEM_LAUNCH( MENUPAGE_DEVEL_TEST,          LP_WORD(L_I_TEST_DIALOGS),        test_dialog_create),
#endif
};

menupage_t menupage_developer = {
	name      : LP_WORD(L_P_DEVELOPERS),
	items     : LIST(menu_developer_items),
	ordering  : menu_order.developer,
	actions  : {
		[MENU_EVENT_AV] = menu_return,
	}
};

void menupage_developer_start(menu_t *menu) {
	if (settings.developers_menu) {
		menu_set_page(&menupage_developer);
	}
}

void menupage_developer_dump_log(const menuitem_t *menuitem) {
	dump_log();
}

void menupage_developer_print_info(const menuitem_t *menuitem) {
	print_info();
}

static int test_dialog_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code) {
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

	return dialog_event_handler(dialog, r1, event, r3, r4, r5, r6, code);
}

static void test_dialog_create(void) {
	debug_log("Creating dialog [%d]", template);
	FLAG_GUI_MODE = 0x30;

	if (menu_handler != NULL) {
		DeleteDialogBox(menu_handler);
		menu_handler = NULL;
	}

	menu_handler = dialog_create(template, test_dialog_event_handler);

	int i;
	for (i = 0; i<255; i++) {
		char s[30];
		sprintf(s, "[%d,%d]",template,i);
		dialog_set_property_str(menu_handler, i, s);
	}

	GUI_PaletteChange(curr_palette);

	dialog_redraw(menu_handler);
}


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

0xAF:
	eventproc_DispWarningDlg() shows nice OSD for helps -> reverse
	eventproc_DispWarningDlgLarge() - bigger one

#endif

