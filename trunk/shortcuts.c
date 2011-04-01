#include "main.h"
#include "utils.h"
#include "tasks.h"
#include "scripts.h"
#include "display.h"
#include "firmware.h"

#include "shortcuts.h"

int  shortcuts_dialog = 0;

type_SHORTCUT shortcuts[5] = {
	{"^ Intermediate ISO", SHORTCUT_TYPE_ISO,    set_intermediate_iso},
	{"< Extended AEB",     SHORTCUT_TYPE_STATIC, script_extended_aeb},
	{"# Intervalometer",   SHORTCUT_TYPE_STATIC, script_interval},
	{"> Hand waving",      SHORTCUT_TYPE_STATIC, script_wave},
	{"v Self timer",       SHORTCUT_TYPE_STATIC, script_self_timer}
};

void shortcuts_create();
void shortcuts_display();
void shortcuts_display_line(int line, type_SHORTCUT shortcut);

void shortcuts_launch(int line);

void shortcuts_initialize() {
	beep();

	pressButton_(BUTTON_MENU);
	SleepTask(100);

	shortcuts_create();
	shortcuts_display();
}

void shortcuts_create() {
	FLAG_GUI_MODE = GUI_MODE_SHORTCUTS;

	shortcuts_dialog = CreateDialogBox(0, 0, (int*)0xFF840AC4, 22);
	sub_FF837FA8(shortcuts_dialog, 8, "Shortcuts");
}

void shortcuts_display() {
	int i;

	for(i = 0; i < 5; i++)
		shortcuts_display_line(i, shortcuts[i]);

	do_some_with_dialog(shortcuts_dialog);
}

void shortcuts_display_line(int line, type_SHORTCUT shortcut) {
	char iso[8], buffer[64];

	switch (shortcut.type) {
	case SHORTCUT_TYPE_STATIC:
		sprintf(buffer, "%s", shortcut.text);
		break;
	case SHORTCUT_TYPE_ISO:
		iso_display(iso, cameraMode.ISO);
		sprintf(buffer, "%-22s[%s]", shortcut.text, iso);
		break;
	default:
		break;
	}

	sub_FF837FA8(shortcuts_dialog, line + 1, buffer);
}

void shortcuts_close() {
	DeleteDialogBox(shortcuts_dialog);

	pressButton_(BUTTON_DISP);
	SleepTask(250);

	display_refresh();
}


void shortcuts_up() {
	shortcuts_launch(0);
}

void shortcuts_left() {
	shortcuts_launch(1);
}

void shortcuts_set() {
	shortcuts_launch(2);
}

void shortcuts_right() {
	shortcuts_launch(3);
}

void shortcuts_down() {
	shortcuts_launch(4);
}

void shortcuts_launch(int line) {
	char iso[8], buffer[64];

	switch (shortcuts[line].type) {
	case SHORTCUT_TYPE_STATIC:
		shortcuts_close();
		ENQUEUE_TASK(shortcuts[line].launch);
		break;
	default:
		shortcuts[line].launch();
		shortcuts_display_line(line, shortcuts[line]);

		do_some_with_dialog(shortcuts_dialog);
		break;
	}
}
