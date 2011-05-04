#include "main.h"
#include "menu.h"
#include "settings.h"
#include "presets.h"
#include "firmware.h"

#include "menu_rename.h"

int   x, y, z;
int   caps;
type_MENU *menu;

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

void rename_repeat(void (*repeateable)(int repeating));

void rename_repeateable_cycle(int repeating);
void rename_repeateable_right(int repeating);
void rename_repeateable_left (int repeating);

void rename_display();
void rename_refresh(int line);

void rename_destroy();

char *rename_message(int id);

void rename_create(type_MENU *m, char *filename, type_TASK callback) {
	printf("\nrename_create()\n");
	rename_filename = filename;
	rename_callback = callback;

	menu = m;
	menu->in_rename = 1;
	dialog_set_property_str(menu->handle, 8, "Rename");
	rename_display();
}

void rename_display() {
	printf("\nrename_display()\n");
	int i;

	for(i = 0; i < 5; i++)
		dialog_set_property_str(menu->handle, i + 1, rename_message(i));

	dialog_redraw(menu->handle);
}

void rename_refresh(int line) {
	dialog_set_property_str(menu->handle, line + 1, rename_message(line));
	dialog_redraw(menu->handle);
}

void rename_up() {
	printf("\nrename_up()\n");
	if (x != 0) {
		x--;
		rename_display();
	}
}

void rename_down() {
	printf("\nrename_down()\n");
	if (x != 4) {
		x++;
		rename_display();
	}
}

void rename_right() {
	printf("\nrename_right()\n");
	rename_repeat(rename_repeateable_right);
}

void rename_left() {
	printf("\nrename_left()\n");
	rename_repeat(rename_repeateable_left);
}

void rename_cycle() {
	printf("\nrename_cycle()\n");
	rename_repeat(rename_repeateable_cycle);
}

void rename_action() {
	printf("\nrename_action()\n");
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

	printf("\nrename_clear()\n");
	for (i = z; i < 25; i++)
		rename_filename[i] = ' ';

	rename_refresh(4);
}

void rename_next() {
	printf("\nrename_next()\n");
	if (z != 24) {
		z++;
		rename_refresh(4);
	}
}

void rename_prev() {
	printf("\nrename_prev()\n");
	if (z != 0) {
		z--;
		rename_refresh(4);
	}
}

void rename_repeat(void(*repeateable)()){
	int delay;
	int button = status.button_down;

	printf("\nrename_repeat()\n");
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
	printf("\nrename_destroy()\n");
	menu->in_rename = 0;
	menu = 0;
	x = y = z = 0;
	caps = FALSE;
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
