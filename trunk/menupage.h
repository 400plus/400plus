#ifndef MENUPAGE_H_
#define MENUPAGE_H_

#include "menu.h"

struct MENUPAGE {
	char               *name;
	int                 sibilings;
	int                 length;
	type_MENUITEM      *items;
	type_MENU_TASK      tasks[MENU_EVENT_COUNT];
	int                 rename;
	int                *ordering;
	int                 highlight;
	int                 highlighted_item;
	int                 current_line;
	int                 current_posn;
	void (*display)(type_MENUPAGE *page);
	void (*refresh)(type_MENUPAGE *page);
};

extern void menupage_display(type_MENUPAGE *page);
extern void menupage_refresh(type_MENUPAGE *page);

type_MENUITEM *get_current_item(type_MENUPAGE *page);
type_MENUITEM *get_item        (type_MENUPAGE *page, int item_id);

#endif /* MENU_H_ */
