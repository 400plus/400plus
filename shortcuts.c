#include "main.h"
#include "utils.h"
#include "tasks.h"
#include "scripts.h"
#include "display.h"
#include "settings.h"
#include "firmware.h"

#include "shortcuts.h"

int shortcuts_dialog = 0;
int current_shortcut = 0;

char shortcuts_icons[] = {'^', '<', '#', '>', 'v'};

type_SHORTCUT shortcuts[] = {
	{"Intermediate ISO",   SHORTCUT_TYPE_ISO,    set_intermediate_iso,   &cameraMode.ISO},
	{"Extended AEB",       SHORTCUT_TYPE_STATIC, script_extended_aeb},
	{"Intervalometer",     SHORTCUT_TYPE_STATIC, script_interval},
	{"Hand waving",        SHORTCUT_TYPE_STATIC, script_wave},
	{"Self timer",         SHORTCUT_TYPE_STATIC, script_self_timer},
	{"Mirror lock-up",     SHORTCUT_TYPE_BOOL,   switch_CfMLU,           &cameraMode.CfMLU},
	{"Rear curtain flash", SHORTCUT_TYPE_BOOL,   switch_CfFlashSyncRear, &cameraMode.CfFlashSyncRear}
};

void shortcuts_create();
void shortcuts_display();
void shortcuts_display_line(int line);

void shortcuts_launch(int line);

void shortcuts_initialize() {
	beep();
	current_shortcut = 0;

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
		shortcuts_display_line(i);

	do_some_with_dialog(shortcuts_dialog);
}

void shortcuts_display_line(int line) {
	char iso[8], buffer[64];
	type_SHORTCUT shortcut = shortcuts[settings.shortcuts[line]];

	switch (shortcut.type) {
	case SHORTCUT_TYPE_STATIC:
		sprintf(buffer, "%c %s", shortcuts_icons[line], shortcut.text);
		break;
	case SHORTCUT_TYPE_BOOL:
		sprintf(buffer, "%c %-21s[%s]", shortcuts_icons[line], shortcut.text, *shortcut.data ? "yes" : " no");
		break;
	case SHORTCUT_TYPE_ISO:
		iso_display(iso, *shortcut.data);
		sprintf(buffer, "%c %-20s[%s]", shortcuts_icons[line], shortcut.text, iso);
		break;
	default:
		break;
	}

	sub_FF837FA8(shortcuts_dialog, line + 1, buffer);
}

void shortcuts_switch() {
	FLAG_GUI_MODE = (FLAG_GUI_MODE == GUI_MODE_SHORTCUTS) ? GUI_MODE_SCEDIT : GUI_MODE_SHORTCUTS;

	beep();
}

void shortcuts_close() {
	DeleteDialogBox(shortcuts_dialog);

	pressButton_(BUTTON_DISP);
	SleepTask(250);

	display_refresh();
}


void shortcuts_launch_0() {
	shortcuts_launch(0);
}

void shortcuts_launch_1() {
	shortcuts_launch(1);
}

void shortcuts_launch_2() {
	shortcuts_launch(2);
}

void shortcuts_launch_3() {
	shortcuts_launch(3);
}

void shortcuts_launch_4() {
	shortcuts_launch(4);
}

void shortcuts_launch(int line) {
	char iso[8], buffer[64];
	type_SHORTCUT shortcut = shortcuts[settings.shortcuts[line]];

	switch (shortcut.type) {
	case SHORTCUT_TYPE_STATIC:
		shortcuts_close();
		ENQUEUE_TASK(shortcut.launch);
		break;
	default:
		shortcut.launch();
		SleepTask(50);
		shortcuts_display_line(line);

		do_some_with_dialog(shortcuts_dialog);
		break;
	}
}

void shortcuts_up() {
	if (current_shortcut != 0)
		current_shortcut--;
}

void shortcuts_left() {
	if (settings.shortcuts[current_shortcut] > 0)
		settings.shortcuts[current_shortcut] --;
	else
		settings.shortcuts[current_shortcut] = LENGTH(shortcuts) - 1;

	shortcuts_display_line(current_shortcut);
	do_some_with_dialog(shortcuts_dialog);
}

void shortcuts_set() {
	settings_write();
	shortcuts_close();
}

void shortcuts_right() {
	if (settings.shortcuts[current_shortcut] < LENGTH(shortcuts) - 1)
		settings.shortcuts[current_shortcut] ++;
	else
		settings.shortcuts[current_shortcut] = 0;

	shortcuts_display_line(current_shortcut);
	do_some_with_dialog(shortcuts_dialog);
}

void shortcuts_down() {
	if (current_shortcut != 4)
		current_shortcut++;
}
