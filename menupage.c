#include <vxworks.h>
#include <stdio.h>

#include "firmware.h"

#include "macros.h"
#include "languages.h"
#include "menu.h"
#include "menuitem.h"
#include "settings.h"
#include "utils.h"

#include "menupage.h"

int item_grabbed;

void menupage_display_line(menupage_t *page, const int line);

int get_item_id(menupage_t *page, int item_pos);
int get_real_id(menupage_t *page, int item_pos);

menuitem_t *get_item(menupage_t *page, int item_id);

void menupage_initialize(menupage_t *page) {
	// Correct position if menu has shrunk since last time
	int offset = page->current_line - (page->items.size - 1);

	if (offset > 0) {
		page->current_posn -= offset;
		page->current_line -= offset;
	}

	// Release item if was grabbed last time we left menu
	item_grabbed = FALSE;
}

void menupage_display(menu_t *menu) {
	int i;
	char buffer[LP_MAX_WORD];

	menupage_t *page = menu->current_page;

	int pad1, pad2, len  = strlen_utf8(page->name);

	if (page->sibilings) {
		pad1 = (    MENU_WIDTH - 2 - len) / 2;
		pad2 = (1 + MENU_WIDTH - 4 - len) / 2;
		sprintf(buffer, "<<%*s%s%*s>>", pad1, "", page->name, pad2, "");
	} else {
		pad1 = (    MENU_WIDTH - 0 - len) / 2;
		pad2 = (1 + MENU_WIDTH - 2 - len) / 2;
		sprintf(buffer, "%*s%s%*s", pad1, "", page->name, pad2, "");
	}

	menu_set_text(7, buffer);

	for(i = 0; i < MENU_HEIGHT; i++)
		menupage_display_line(page, i);

	menu_highlight(page->current_line);
}

void menupage_up(menu_t *menu) {
	int display = FALSE;
	menupage_t *page = menu->current_page;

	if ((page->items.size > MENU_HEIGHT && settings.menu_wrap) || page->current_posn > 0) {
		page->current_posn--;

		if (item_grabbed) {
			SWAP(page->ordering[get_item_id(page, page->current_posn)], page->ordering[get_item_id(page, page->current_posn + 1)]);
			display = TRUE;
		}
	}

	if (page->current_line > 0) {
		page->current_line--;
		menu_highlight(page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_event_display();
}

void menupage_down(menu_t *menu) {
	int display = FALSE;
	menupage_t *page = menu->current_page;

	if ((page->items.size > MENU_HEIGHT && settings.menu_wrap) || page->current_posn < page->items.size - 1) {
		page->current_posn++;

		if (item_grabbed) {
			SWAP(page->ordering[get_item_id(page, page->current_posn)], page->ordering[get_item_id(page, page->current_posn - 1)]);
			display = TRUE;
		}
	}

	if (page->current_line < MIN(MENU_HEIGHT, page->items.size) - 1) {
		page->current_line++;
		menu_highlight(page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_event_display();
}

void menupage_pgup(menu_t *menu) {
	int display = FALSE;
	menupage_t *page = menu->current_page;

	if (item_grabbed)
		return;

	page->current_posn -= MENU_HEIGHT - 1;

	if (! (page->items.size > MENU_HEIGHT && settings.menu_wrap))
		page->current_posn = MAX(page->current_posn, 0);

	if (page->current_line > 0) {
		page->current_line = 0;
		menu_highlight(page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_event_display();
}

void menupage_pgdown(menu_t *menu) {
	int display = FALSE;
	menupage_t *page = menu->current_page;

	if (item_grabbed)
		return;

	page->current_posn += MENU_HEIGHT - 1;

	if (! (page->items.size > MENU_HEIGHT && settings.menu_wrap)) {
		page->current_posn = MIN(page->current_posn, page->items.size - 1);
	}

	if (page->current_line < MIN(MENU_HEIGHT, page->items.size) - 1) {
		page->current_line = MIN(MENU_HEIGHT, page->items.size) - 1;
		menu_highlight(page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_event_display();
}

void menupage_drag_drop(menu_t *menu) {
	menupage_t *page = menu->current_page;

	if (page->ordering) {
		item_grabbed  = ! item_grabbed;
		menu->changed = TRUE;
		menu_event_refresh();
	}
}

void menupage_refresh(menu_t *menu) {
	menupage_t *page = menu->current_page;

	menupage_display_line(page, page->current_line);
	menu_redraw();
}

void menupage_display_line(menupage_t *page, const int line) {
	int  i = 0;
	char message[LP_MAX_WORD] = "";

	int item_id = line + page->current_posn - page->current_line;

	menuitem_t *item = get_item(page, item_id);

	if (item) {
		if (page->ordering && item_grabbed && get_item_id(page, item_id) == get_item_id(page, page->current_posn))
			message[i++] = '>';
		else if (page->highlight && page->highlighted_item == get_real_id(page, item_id))
			message[i++] = '*';
		else
			message[i++] = ' ';

		if (page->show_id) {
			sprintf(message + i, "%X:", item->id);
			i += 2;
		}

		if (item->action)
			message[i++] = '!';

		if (item->display)
			item->display(item, &message[i], MENU_WIDTH - i);
	}

	menu_set_text(line, message);
}

menuitem_t *get_current_item(menupage_t *page) {
	return get_item(page, page->current_posn);
}

menuitem_t *get_item(menupage_t *page, int item_pos) {
	const int item_id = get_real_id(page, item_pos);

	return (item_id < page->items.size) ? &page->items.data[item_id] : NULL;
}

int get_real_id(menupage_t *page, int item_pos) {
	if (page->ordering)
		return page->ordering[get_item_id(page, item_pos)];
	else
		return get_item_id(page, item_pos);
}

int get_item_id(menupage_t *page, int item_pos) {
	const int max_pos = MAX(page->items.size, MENU_HEIGHT);
	const int item_id = item_pos - max_pos * (item_pos / max_pos);

	return (item_id < 0) ? (item_id + max_pos) : item_id;
}
