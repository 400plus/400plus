#include <vxworks.h>
#include <string.h>

#include "macros.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "menu_main.h"
#include "utils.h"

#include "menu_rename.h"

const char letters[2][4][9] = {
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

char *rename_filename;
int   x, y, z;
int   caps;

void rename_display_up  (const menuitem_t *item, char *buffer, const int length);
void rename_display_down(const menuitem_t *item, char *buffer, const int length);

void rename_up  (menu_t *menu);
void rename_down(menu_t *menu);

void rename_right  (const menuitem_t *item, const int repeating);
void rename_left   (const menuitem_t *item, const int repeating);

void rename_prev(menu_t *menu);
void rename_next(menu_t *menu);

void rename_action(const menuitem_t *item);

void rename_caps  (menu_t *menu);
void rename_toggle(menu_t *menu);
void rename_clear (menu_t *menu);
void rename_return(menu_t *menu);
void rename_close (menu_t *menu);
void rename_save  (menu_t *menu);

void rename_display(menu_t *menu);
void rename_refresh(menu_t *menu);
void rename_display_line(menupage_t *page, const int line);

menuitem_t menupage_rename_items[] = {
	{
		id      : 0,
		display : rename_display_up,
		inc     : rename_right,
		dec     : rename_left,
		action  : rename_action,
	},
	{
		id      : 1,
		display : rename_display_up,
		inc     : rename_right,
		dec     : rename_left,
		action  : rename_action,
	},
	{
		id      : 2,
		display : rename_display_up,
		inc     : rename_right,
		dec     : rename_left,
		action  : rename_action,
	},
	{
		id      : 3,
		display : rename_display_up,
		inc     : rename_right,
		dec     : rename_left,
		action  : rename_action,
	},
	{
		display : rename_display_down,
	}
};

menupage_t menupage_rename = {
	name      : LP_WORD(L_P_RENAME),
	items     : LIST(menupage_rename_items),
	actions   : {
		[MENU_EVENT_UP]      = rename_up,
		[MENU_EVENT_DOWN]    = rename_down,
		[MENU_EVENT_OUT]     = rename_prev,
		[MENU_EVENT_IN]      = rename_next,
		[MENU_EVENT_DISP]    = rename_caps,
		[MENU_EVENT_JUMP]    = rename_toggle,
		[MENU_EVENT_TRASH]   = rename_clear,
		[MENU_EVENT_AV]      = rename_return,
		[MENU_EVENT_DISPLAY] = rename_display,
		[MENU_EVENT_REFRESH] = rename_refresh,
		[MENU_EVENT_SAVE]    = rename_close,
	},
};


void rename_create(char *filename) {
	rename_filename = filename;

	x = y = z = 0;

	menupage_rename.current_line = x;
	menupage_rename.current_posn = x;

	caps = FALSE;

	menu_set_page(&menupage_rename);
	menu_highlight(x);
}

void rename_display_up(const menuitem_t *item, char *buffer, const int length) {
	int i, j = 0;
	int id = item->id;

	for (i = 0; i < 9; i++) {
		if (id == x && i == y) {
			buffer[j++] = '[';
			buffer[j++] = letters[caps][id][i];
			buffer[j++] = ']';
		} else {
			buffer[j++] = ' ';
			buffer[j++] = letters[caps][id][i];
			buffer[j++] = ' ';
		}
	}

	buffer[j] = '\0';
}

void rename_display_down(const menuitem_t *item, char *buffer, const int length) {
	int i, j = 0;

	for (i = 0; i < 25; i++) {
		if (i == z) {
			buffer[j++] = '<';
			buffer[j++] = rename_filename[i];
			buffer[j++] = '>';
		} else {
			buffer[j++] = rename_filename[i];
		}
	}

	buffer[j] = '\0';
}

void rename_up(menu_t *menu) {
	if (x > 0) {
		x--;
		menupage_rename.current_line = x;
		menupage_rename.current_posn = x;

		menu_highlight(x);
		rename_display(menu);
	}
}

void rename_down(menu_t *menu) {
	if (x < MENU_HEIGHT - 2) {
		x++;
		menupage_rename.current_line = x;
		menupage_rename.current_posn = x;

		menu_highlight(x);
		rename_display(menu);
	}
}

void rename_right(const menuitem_t *item, const int repeating) {
	if (y == 8) {
		y = 0;
	} else {
		y++;
	}

	menu_event_refresh();
}

void rename_left(const menuitem_t *item, const int repeating) {
	if (y == 0) {
		y = 8;
	} else {
		y--;
	}

	menu_event_refresh();
}

void rename_prev(menu_t *menu) {
	if (z != 0) {
		z--;
		rename_display_line(&menupage_rename, 4);
		menu_redraw();
	}
}

void rename_next(menu_t *menu) {
	if (z != 24) {
		z++;

		if (rename_filename[z] == '\0') {
			rename_filename[z]   = ' ';
			rename_filename[z+1] = '\0';
		}

		rename_display_line(&menupage_rename, 4);
		menu_redraw();
	}
}

void rename_action(const menuitem_t *item) {
	rename_filename[z] = letters[caps][x][y];
	menu_event_in();
}

void rename_caps(menu_t *menu) {
	caps = !caps;
	rename_display(menu);
}

void rename_toggle(menu_t *menu) {
	menupage_t *page = menu->current_page;

	if ('a' <= rename_filename[z] && rename_filename[z] <= 'z')
		rename_filename[z] += 'A' - 'a';
	else if ('A' <= rename_filename[z] && rename_filename[z] <= 'Z')
		rename_filename[z] += 'a' - 'A';

	rename_display_line(page, 4);
	menu_redraw();
}

void rename_clear(menu_t *menu) {
	int i;

	menupage_t *page = menu->current_page;

	for (i = z; i < 25; i++)
		rename_filename[i] = ' ';

	rename_display_line(page, 4);
	menu_redraw();
}

void rename_return(menu_t *menu) {
	rename_save(menu);
	menu_return(menu);
}

void rename_close(menu_t *menu) {
	rename_save(menu);
	menu_main_save(menu);
}

void rename_save(menu_t *menu) {
	int i;

	for(i = strlen(rename_filename) - 1; rename_filename[i] == ' '; i--)
		rename_filename[i] = '\0';

	menu->changed = TRUE;
}

void rename_display(menu_t *menu) {
	int i;

	menupage_t *page = menu->current_page;

	for(i = 0; i < MENU_HEIGHT; i++)
		rename_display_line(page, i);

	menu_redraw();
}

void rename_refresh(menu_t *menu) {
	menupage_t *page = menu->current_page;

	rename_display_line(page, x);
	menu_redraw();
}

void rename_display_line(menupage_t *page, const int line) {
	char message[LP_MAX_WORD] = "";

	menuitem_t *item = &page->items.data[line];

	if (item && item->display)
		item->display(item, message, 0);

	menu_set_text(line, message);
}
