#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menuitem.h"

#include "menupage.h"

void menupage_display_line(type_MENUPAGE *page, const int line);

void menupage_display(type_MENUPAGE *page) {
	char buffer[LP_MAX_WORD];

	int i;

	int pad1, pad2, len  = strlen(page->name);

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

void menupage_refresh(type_MENUPAGE *page) {
	menupage_display_line(page, page->current_line);
	menu_redraw();
}

void menupage_display_line(type_MENUPAGE *page, const int line) {
	int  i = 0;
	char message[LP_MAX_WORD] = "";

	int item_id = line + page->current_posn - page->current_line;

	type_MENUITEM *item = get_item(page, item_id);

	if (item) {
		if (page->ordering && item_grabbed && get_item_id(item_id) == get_item_id(page->current_posn))
			message[i++] = '>';
		else if (page->highlight && page->highlighted_item == 1 + get_real_id(item_id))
			message[i++] = '*';
		else
			message[i++] = ' ';

		if (page->rename) {
			message[i++] = '1' + get_real_id(item_id);
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
	const int item_id = get_real_id(item_pos);

	return (item_id < page->length) ? &page->items[item_id] : NULL;
}

