#ifndef MENUPAGE_H_
#define MENUPAGE_H_

#include "menu.h"

typedef struct {
	int         size;
	menuitem_t *data;
} list_item_t;

struct menupage_t {
	char        *name;
	list_item_t  items;
	menuaction_t actions[MENU_EVENT_COUNT];
	int          sibilings;
	int          show_id;
	int         *ordering;
	int          highlight;
	int          highlighted_item;
	int          current_line;
	int          current_posn;
};

extern void menupage_initialize(menupage_t *page);

extern void menupage_display(menu_t *menu);
extern void menupage_refresh(menu_t *menu);

extern void menupage_up   (menu_t *menu);
extern void menupage_down (menu_t *menu);

extern void menupage_pgup   (menu_t *menu);
extern void menupage_pgdown (menu_t *menu);

extern void menupage_drag_drop(menu_t *menu);

extern menuitem_t *get_current_item(menupage_t *page);
extern int         get_item_id     (menupage_t *page, int item_pos);

#endif /* MENU_H_ */
