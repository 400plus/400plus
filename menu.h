#ifndef MENU_H_
#define MENU_H_

#define AUTOREPEAT_DELAY_UNIT   50
#define AUTOREPEAT_DELAY_LONG   10
#define AUTOREPEAT_DELAY_SHORT   4

typedef struct MENUITEM type_MENUITEM;

typedef enum {
	MENUITEM_TYPE_EV,
	MENUITEM_TYPE_ISO,
	MENUITEM_TYPE_INT,
	MENUITEM_TYPE_ENUM,
	MENUITEM_TYPE_ACTION,
	MENUITEM_TYPE_SUBMENU,
	MENUITEM_TYPE_COUNT,
	MENUITEM_TYPE_FIRST = 0,
	MENUITEM_TYPE_LAST  = MENUITEM_TYPE_COUNT - 1
} type_MENUITEM_TYPE;

typedef struct {
	int  *value;
	int   zero_means_off;
} type_MENUITEM_EV;

typedef struct {
	int  *value;
} type_MENUITEM_ISO;

typedef struct {
	int   *value;
	int    readonly;
	int    min;
	int    max;
	int    small_step;
	int    big_step;
	int    zero_means_unlimited;
  char  *format;
} type_MENUITEM_INT;

typedef struct {
	int   *value;
	int    cycle;
	int    count;
	char **texts;
} type_MENUITEM_ENUM;

typedef struct {
	type_TASK action;
} type_MENUITEM_ACTION;

typedef struct {
	int length;
	int current_item;
	type_MENUITEM *items;
} type_MENUITEM_SUBMENU;

struct MENUITEM {
	char               *name;
	type_MENUITEM_TYPE  type;
	union {
		type_MENUITEM_EV      menuitem_ev;
		type_MENUITEM_ISO     menuitem_iso;
		type_MENUITEM_INT     menuitem_int;
		type_MENUITEM_ENUM    menuitem_enum;
		type_MENUITEM_ACTION  menuitem_action;
		type_MENUITEM_SUBMENU menuitem_submenu;
	};
};

typedef struct {
	char *name;
	int   length;
	type_MENUITEM *items;
	type_TASK      action;
} type_MENU;

#define MENUITEM_EV(_NAME_, _VALUE_, _ZMO_) \
	{name:_NAME_, type:MENUITEM_TYPE_EV, {menuitem_ev:{value:_VALUE_, zero_means_off:_ZMO_}}}

#define MENUITEM_ISO(_NAME_, _VALUE_) \
	{name:_NAME_, type:MENUITEM_TYPE_ISO, {menuitem_iso:{value:_VALUE_}}}

#define MENUITEM_INT(_NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _ZMU_, _FORMAT_) \
	{name:_NAME_, type:MENUITEM_TYPE_INT, {menuitem_int:{value:_VALUE_, readonly:_RO_, min:_MIN_, max:_MAX_, small_step:_SMALL_, big_step:_BIG_, zero_means_unlimited:_ZMU_, format:_FORMAT_}}}

#define MENUITEM_ENUM(_NAME_, _VALUE_, _CYCLE_, _TEXTS_) \
	{name:_NAME_, type:MENUITEM_TYPE_ENUM, {menuitem_enum:{value:_VALUE_, cycle:_CYCLE_, count:LENGTH(_TEXTS_), texts:_TEXTS_}}}

#define MENUITEM_ACTION(_NAME_, _ACTION_) \
	{name:_NAME_, type:MENUITEM_TYPE_ACTION, {menuitem_action:{action:_ACTION_}}}

#define MENUITEM_SUBMENU(_NAME_, _ITEMS_) \
	{name:_NAME_, type:MENUITEM_TYPE_SUBMENU, {menuitem_submenu:{length:LENGTH(_ITEMS_), items:_ITEMS_, current_item:0}}}

extern void menu_create(type_MENU menu);
extern void menu_close();

extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();

extern void menu_cycle();
extern void menu_action();
extern void menu_submenu();

#endif /* MENU_H_ */
