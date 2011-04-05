#ifndef MENU_H_
#define MENU_H_

#define AUTOREPEAT_DELAY_UNIT   50
#define AUTOREPEAT_DELAY_LONG   10
#define AUTOREPEAT_DELAY_SHORT   4

typedef struct MENUITEM type_MENUITEM;

typedef enum {
	MENUITEM_TYPE_EV,
	MENUITEM_TYPE_INT,
	MENUITEM_TYPE_ENUM,
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
	int length;
	int current_item;
	type_MENUITEM *items;
} type_MENUITEM_SUBMENU;

struct MENUITEM {
	char               *name;
	type_MENUITEM_TYPE  type;
	union {
		type_MENUITEM_EV      menuitem_ev;
		type_MENUITEM_INT     menuitem_int;
		type_MENUITEM_ENUM    menuitem_enum;
		type_MENUITEM_SUBMENU menuitem_submenu;
	};
};

#define MENUITEM_EV(_NAME_, _VALUE_, _ZMO_) \
	{name:_NAME_, type:MENUITEM_TYPE_EV, {menuitem_ev:{value:_VALUE_, zero_means_off:_ZMO_}}}

#define MENUITEM_INT(_NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _ZMU_, _FORMAT_) \
	{name:_NAME_, type:MENUITEM_TYPE_INT, {menuitem_int:{value:_VALUE_, readonly:_RO_, min:_MIN_, max:_MAX_, small_step:_SMALL_, big_step:_BIG_, zero_means_unlimited:_ZMU_, format:_FORMAT_}}}

#define MENUITEM_ENUM(_NAME_, _VALUE_, _CYCLE_, _TEXTS_) \
	{name:_NAME_, type:MENUITEM_TYPE_ENUM, {menuitem_enum:{value:_VALUE_, cycle:_CYCLE_, count:LENGTH(_TEXTS_), texts:_TEXTS_}}}

#define MENUITEM_SUBMENU(_NAME_, _ITEMS_) \
	{name:_NAME_, type:MENUITEM_TYPE_SUBMENU, {menuitem_submenu:{length:LENGTH(_ITEMS_), items:_ITEMS_, current_item:0}}}

#define MENUITEM_EVCOMP(_NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, FALSE)
#define MENUITEM_EVSEP( _NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE)

#define MENUITEM_BOOLEAN(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, bool_strings)
#define MENUITEM_DELAY(  _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, delay_strings)
#define MENUITEM_ACTION( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  action_strings)
#define MENUITEM_SCRIPT( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  script_strings)
#define MENUITEM_SSPEED( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, sspeed_strings)

#define MENUITEM_RELEASE(  _NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, TRUE,     0,     0,   0,   0, FALSE, "%6u")
#define MENUITEM_COLORTEMP(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE, 1800, 11000, 100, 500, FALSE, "%5u")
#define MENUITEM_TIMEOUT(  _NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, FALSE, "%3u")
#define MENUITEM_COUNTER(  _NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, TRUE,  "%3u")
#define MENUITEM_BRACKET(  _NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    1,     9,   2,   2, FALSE, "%1u")

extern void menu_initialize();

extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();

extern void menu_cycle();
extern void menu_submenu();

extern void menu_save();

extern char *menu_message();

#endif /* MENU_H_ */
