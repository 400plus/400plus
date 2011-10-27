#ifndef MENUPAGE_H_
#define MENUPAGE_H_

#include "menu.h"

typedef void(*type_MENUPAGE_TASK)(type_MENUPAGE *page);

struct MENUPAGE {
	char               *name;
	int                 sibilings;
	int                 length;
	type_MENUITEM      *items;
	type_MENUPAGE_TASK  tasks[MENU_EVENT_COUNT];
	int                 rename;
	int                *ordering;
	int                 highlight;
	int                 highlighted_item;
};

#endif /* MENU_H_ */
