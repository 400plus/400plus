#include "main.h"
#include "menu.h"
#include "settings.h"
#include "presets.h"
#include "languages.h"
#include "firmware.h"

#include "menu_rename.h"

int   x, y, z;
int   caps;
type_DIALOG *dialog;

char *rename_filename;
char  rename_buffer[32];

type_TASK rename_callback;

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

// we need only the type here, there is no real menu structure
type_MENU menu_rename = {
	name        : LP_WORD(L_RENAME),
	type        : MENU_RENAME,
};


void rename_repeat(void (*repeateable)(int repeating));

void rename_repeateable_cycle(int repeating);
void rename_repeateable_right(int repeating);
void rename_repeateable_left (int repeating);

void rename_display();
void rename_refresh(int line);

void rename_destroy();

char *rename_message(int id);

void rename_prepare(char *filename, type_TASK callback) {
	printf("\nRENAME PREPARED\n");
	rename_filename = filename;
	rename_callback = callback;
}

void rename_create() {
	type_MENU *menu;

	printf("\nRENAME CREATING MENU\n");
	menu_create(&menu_rename); // create rename dialog
	SleepTask(200);
	printf("\nRENAME GETTING CURRENT\n");
	menu = menu_get_current();
	SleepTask(200);
	printf("\nRENAME CURRENT:%p\n", menu);
	dialog = menu->handle;
	SleepTask(200);

	printf("\nRENAME DISPLAY:%p\n", menu);
	rename_display();
	SleepTask(200);
}

void rename_display() {
	int i;

	for(i = 0; i < 5; i++)
		dialog_set_property_str(dialog, i + 1, rename_message(i));

	dialog_redraw(dialog);
}

void rename_refresh(int line) {
	dialog_set_property_str(dialog, line + 1, rename_message(line));
	dialog_redraw(dialog);
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

void rename_cycle() {
	rename_repeat(rename_repeateable_cycle);
}

void rename_action() {
	if (x < 4) {
		rename_filename[z] = letters[caps][x][y];

		if (z != 24)
			z++;

		rename_refresh(4);
	} else {
		presets_write();
		rename_destroy();
		rename_callback();
	}
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
	caps = !caps;
	rename_display();
}

void rename_destroy() {
	x = y = z = 0;
	caps = FALSE;
	menu_create_last();
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
