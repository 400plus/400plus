#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menuitem.h"

#include "menupage.h"

int item_grabbed;

void menupage_display_line(type_MENUPAGE *page, const int line);

int get_item_id(type_MENUPAGE *page, int item_pos);
int get_real_id(type_MENUPAGE *page, int item_pos);

void menupage_initialize(type_MENUPAGE *page) {
	item_grabbed = FALSE;
}

void menupage_display(type_MENU *menu) {
	int i;
	char buffer[LP_MAX_WORD];

	type_MENUPAGE *page = menu->current_page;

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

	menu_event_open();

	for(i = 0; i < MENU_HEIGHT; i++)
		menupage_display_line(page, i);

	menu_highlight(page->current_line);
}

void menupage_up(type_MENU *menu) {
	int display = FALSE;
	type_MENUPAGE *page = menu->current_page;

	if (page->length > MENU_HEIGHT || page->current_posn > 0) {
		page->current_posn--;

		if (item_grabbed) {
			INT_SWAP(page->ordering[get_item_id(page, page->current_posn)], page->ordering[get_item_id(page, page->current_posn + 1)]);
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

void menupage_down(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	const int height = MIN(MENU_HEIGHT, page->length) - 1;
	int display = FALSE;

	if (page->length > MENU_HEIGHT || page->current_posn < height) {
		page->current_posn++;

		if (item_grabbed) {
			INT_SWAP(page->ordering[get_item_id(page, page->current_posn)], page->ordering[get_item_id(page, page->current_posn - 1)]);
			display = TRUE;
		}
	}

	if (page->current_line < height) {
		page->current_line++;
		menu_highlight(page->current_line);
	} else {
		display = TRUE;
	}

	if (display)
		menu_event_display();
}

void menupage_drag_drop(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	if (page->ordering) {
		item_grabbed = ! item_grabbed;
		menu_event_change();
		menu_event_refresh();
	}
}

void menupage_refresh(type_MENU *menu) {
	type_MENUPAGE *page = menu->current_page;

	menupage_display_line(page, page->current_line);
	menu_redraw();
}

void menupage_display_line(type_MENUPAGE *page, const int line) {
	int  i = 0;
	char message[LP_MAX_WORD] = "";

	int item_id = line + page->current_posn - page->current_line;

	type_MENUITEM *item = get_item(page, item_id);

	if (item) {
		if (page->ordering && item_grabbed && get_item_id(page, item_id) == get_item_id(page, page->current_posn))
			message[i++] = '>';
		else if (page->highlight && page->highlighted_item == 1 + get_real_id(page, item_id))
			message[i++] = '*';
		else
			message[i++] = ' ';

		if (page->rename) {
			message[i++] = '1' + get_real_id(page, item_id);
			message[i++] = ' ';
		}

		if (item->tasks[MENU_EVENT_SET])
			message[i++] = '!';

		if (item->display)
			item->display(item, &message[i], MENU_WIDTH - i);
	}

	menu_set_text(line, message);
}

type_MENUITEM *get_current_item(type_MENUPAGE *page) {
	return get_item(page, page->current_posn);
}

type_MENUITEM *get_item(type_MENUPAGE *page, int item_pos) {
	const int item_id = get_real_id(page, item_pos);

	return (item_id < page->length) ? &page->items[item_id] : NULL;
}

int get_real_id(type_MENUPAGE *page, int item_pos) {
	if (page->ordering)
		return page->ordering[get_item_id(page, item_pos)];
	else
		return get_item_id(page, item_pos);
}

int get_item_id(type_MENUPAGE *page, int item_pos) {
	const int max_pos = MAX(page->length, MENU_HEIGHT);
	const int item_id = item_pos - max_pos * (item_pos / max_pos);

	return (item_id < 0) ? (item_id + max_pos) : item_id;
}
