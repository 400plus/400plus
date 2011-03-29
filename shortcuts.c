#include "main.h"
#include "utils.h"
#include "tasks.h"
#include "scripts.h"
#include "display.h"
#include "firmware.h"

#include "shortcuts.h"

int  shortcuts_dialog = 0;

type_SHORTCUT shortcuts[5] = {
	{"^ Intermediate ISO   ", set_intermediate_iso},
	{"< Extended AEB",        script_extended_aeb},
	{"# Intervalometer",      script_interval},
	{"> Hand waving",         script_wave},
	{"v Self timer",          script_self_timer}
};

void shortcuts_create();
void shortcuts_display();
void shortcuts_launch(int id);

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
	char iso[8], buffer[64];

	for(i = 0; i < 5; i++) {
		if (i == 0) {
			iso_display(iso, cameraMode.ISO);
			sprintf(buffer, "%s [%s]", shortcuts[i].text, iso);
		} else {
			sprintf(buffer, "%s", shortcuts[i].text);
		}

		sub_FF837FA8(shortcuts_dialog, i + 1, buffer);
	}

	do_some_with_dialog(shortcuts_dialog);
}

void shortcuts_close() {
	pressButton_(BUTTON_DISP);
	SleepTask(100);

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

void shortcuts_launch(int id) {
	char iso[8], buffer[64];

	if (id != 0) {
		shortcuts_close();
	}

	shortcuts[id].launch();

	if (id == 0) {
		iso_display(iso, cameraMode.ISO);
		sprintf(buffer, "%s [%s]", shortcuts[id].text, iso);

		sub_FF837FA8(shortcuts_dialog, id + 1, buffer);
		do_some_with_dialog(shortcuts_dialog);
	}
}
