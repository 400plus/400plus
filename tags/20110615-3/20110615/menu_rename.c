#include "main.h"
#include "firmware.h"

#include "menu.h"

#include "menu_rename.h"

int   x, y, z;
int   caps;

type_DIALOG *handle = NULL;
type_MENU   *rename_parent;

char *rename_filename;
char  rename_buffer[32];

char letters[2][4][9] = {
	{
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
		{'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
		{'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0'},
		{'1', '2', '3', '4', '5', '6', '7', '8', '9'}
	},
	{
		{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'},
		{'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'},
		{'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '},
		{'!', '@', '#', '$', '%', '&', '-', ',', '.'}
	}
};

type_ACTION callbacks_rename[] = {
	{GUI_BUTTON_UP,             FALSE, FALSE, {rename_up}},
	{GUI_BUTTON_DOWN,           FALSE, FALSE, {rename_down}},
	{GUI_BUTTON_DISP,           FALSE, FALSE, {NULL}},
	{GUI_BUTTON_MENU,           FALSE, TRUE,  {rename_caps}},
	{GUI_BUTTON_JUMP,           FALSE, TRUE,  {rename_save}},
	{GUI_BUTTON_PLAY,           FALSE, TRUE,  {NULL}},
	{GUI_BUTTON_TRASH,          FALSE, TRUE,  {rename_clear}},
	{GUI_BUTTON_ZOOM_IN_PRESS,  FALSE, TRUE,  {rename_next}},
	{GUI_BUTTON_ZOOM_OUT_PRESS, FALSE, TRUE,  {rename_prev}},
	END_OF_LIST
};
void rename_initialize();
void rename_destroy();

int rename_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

void rename_event(type_MENU_EVENT event);

void rename_display();
void rename_refresh(int line);

void rename_repeat(void (*repeateable)(int repeating));

void rename_repeateable_cycle(int repeating);
void rename_repeateable_right(int repeating);
void rename_repeateable_left (int repeating);

char *rename_message(int id);

void rename_create(char *filename, type_MENU *parent) {
	rename_filename = filename;
	rename_parent   = parent;

	FLAG_GUI_MODE = GUIMODE_RENAME;

	rename_initialize();

	handle = dialog_create(22, rename_handler);
	dialog_set_property_str(handle, 8, "Rename");

	rename_display();
}

void rename_close() {
	rename_destroy();
}

void rename_initialize() {
	rename_destroy();

	handle = 0;
	x = y = z = 0;
	caps = FALSE;
}

void rename_destroy() {
	if (handle != NULL)
		DeleteDialogBox(handle);
}

int rename_handler(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code) {
	type_ACTION *action;

	// Loop over all the actions from this action chain
	for (action = callbacks_rename; ! IS_EOL(action); action++) {

		// Check whether this action corresponds to the event received
		if (action->button == event) {

			// Launch the defined task
			if (action->task[0])
				action->task[0]();

			// Decide how to respond to this button
			if (action->block)
				return FALSE;
			else
				goto pass_event;
		}
	}

pass_event:
	return InfoCreativeAppProc(dialog, r1, event, r3, r4, r5, r6, code);
}

void rename_event_close() {
	rename_event(MENU_EVENT_CLOSE);
}

void rename_event(type_MENU_EVENT event) {
}

void rename_display() {
	int i;

	for(i = 0; i < 5; i++)
		dialog_set_property_str(handle, i + 1, rename_message(i));

	dialog_redraw(handle);
}

void rename_refresh(int line) {
	dialog_set_property_str(handle, line + 1, rename_message(line));
	dialog_redraw(handle);
}

void rename_up() {
	if (x != 0) {
		x--;
		rename_display();
	}
}

void rename_down() {
	if (x != 4) {
		x++;
		rename_display();
	}
}

void rename_right() {
	rename_repeat(rename_repeateable_right);
}

void rename_left() {
	rename_repeat(rename_repeateable_left);
}

void rename_caps() {
	caps = !caps;
	rename_display();
}

void rename_cycle() {
	rename_repeat(rename_repeateable_cycle);
}

void rename_action() {
	if (x < 4) {
		rename_filename[z] = letters[caps][x][y];

		if (z != 24)
			z++;

		rename_refresh(4);
	}
}

void rename_save() {
	rename_close();

	menu_create(rename_parent);
	menu_event(MENU_EVENT_CHANGE);
}

void rename_clear() {
	int i;

	for (i = z; i < 25; i++)
		rename_filename[i] = ' ';

	rename_refresh(4);
}

void rename_next() {
	if (z != 24) {
		z++;
		rename_refresh(4);
	}
}

void rename_prev() {
	if (z != 0) {
		z--;
		rename_refresh(4);
	}
}

void rename_repeat(void(*repeateable)()){
	int delay;
	int button = status.button_down;

	SleepTask(50);

	repeateable(FALSE);
	delay = AUTOREPEAT_DELAY_LONG;

	do {
		SleepTask(AUTOREPEAT_DELAY_UNIT);

		if (--delay == 0) {
			repeateable(TRUE);
			delay = AUTOREPEAT_DELAY_SHORT;
		}
	} while (status.button_down && status.button_down == button);
}

void rename_repeateable_right(int repeating) {
	if (x < 4) {
		if (y == 8) {
			y = 0;
		} else {
			y++;
		}
	} else {
		rename_next();
	}

	rename_refresh(x);
}

void rename_repeateable_left(int repeating) {
	if (x < 4) {
		if (y == 0) {
			y = 8;
		} else {
			y--;
		}
	} else {
		rename_prev();
	}

	rename_refresh(x);
}

void rename_repeateable_cycle(int repeating) {
	if ('a' <= rename_filename[z] && rename_filename[z] <= 'z')
		rename_filename[z] += 'A' - 'a';
	else if ('A' <= rename_filename[z] && rename_filename[z] <= 'Z')
		rename_filename[z] += 'a' - 'A';

	rename_refresh(4);
}

char *rename_message(int id) {
	int i, j = 0;

	if (id < 4) {
		for (i = 0; i < 9; i++) {
			if (id == x && i == y) {
				rename_buffer[j++] = '[';
				rename_buffer[j++] = letters[caps][id][i];
				rename_buffer[j++] = ']';
			} else {
				rename_buffer[j++] = ' ';
				rename_buffer[j++] = letters[caps][id][i];
				rename_buffer[j++] = ' ';
			}
		}
	} else {
		for (i = 0; i < 25; i++) {
			if (i == z) {
				rename_buffer[j++] = '<';
				rename_buffer[j++] = rename_filename[i];
				rename_buffer[j++] = '>';
			} else {
				rename_buffer[j++] = rename_filename[i];
			}
		}
	}

	rename_buffer[j] = '\0';

	return rename_buffer;
}
