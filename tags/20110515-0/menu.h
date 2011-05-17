#ifndef MENU_H_
#define MENU_H_

#define AUTOREPEAT_DELAY_UNIT   50
#define AUTOREPEAT_DELAY_LONG   10
#define AUTOREPEAT_DELAY_SHORT   4

typedef struct {
	int  length;
	char **data;
} type_LIST;

typedef struct MENUITEM type_MENUITEM;

typedef enum {
	MENUITEM_TYPE_EV,
	MENUITEM_TYPE_ISO,
	MENUITEM_TYPE_INT,
	MENUITEM_TYPE_ENUM,
	MENUITEM_TYPE_LAUNCH,
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
	int       *value;
	int        cycle;
	type_LIST *list;
} type_MENUITEM_ENUM;

typedef struct {
	int       close;
	type_TASK action;
} type_MENUITEM_LAUNCH;

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
		type_MENUITEM_LAUNCH  menuitem_launch;
		type_MENUITEM_SUBMENU menuitem_submenu;
	};
};

typedef struct {
	char            *name;
	int              length;
	type_MENUITEM   *items;
	type_TASK        action;
	type_TASK        dp_action;
	int              rename;
	type_TASK        callback;
	int              reorder;
	int             *ordering;
	void            *handle;       // dialog handle returned from CreateDialogBox()
	int              current_line;
	int              current_item;
	int              item_grabbed; // for menu reordering
} type_MENU;

#define OPTIONLIST_DEC(NAME)      extern type_LIST _##NAME##_LIST_;
#define OPTIONLIST_REF(NAME)      (&_##NAME##_LIST_)
#define OPTIONLIST_DEF(NAME, ...) static char *_##NAME##_STRINGS_[]={__VA_ARGS__};  type_LIST _##NAME##_LIST_={length:LENGTH(_##NAME##_STRINGS_),data:_##NAME##_STRINGS_};

OPTIONLIST_DEC(bool)
OPTIONLIST_DEC(delay)
OPTIONLIST_DEC(flash)
OPTIONLIST_DEC(action)
OPTIONLIST_DEC(shutter)

#define MENUITEM_EV(_NAME_, _VALUE_, _ZMO_) \
	{name:_NAME_, type:MENUITEM_TYPE_EV, {menuitem_ev:{value:_VALUE_, zero_means_off:_ZMO_}}}

#define MENUITEM_ISO(_NAME_, _VALUE_) \
	{name:_NAME_, type:MENUITEM_TYPE_ISO, {menuitem_iso:{value:_VALUE_}}}

#define MENUITEM_INT(_NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _ZMU_, _FORMAT_) \
	{name:_NAME_, type:MENUITEM_TYPE_INT, {menuitem_int:{value:_VALUE_, readonly:_RO_, min:_MIN_, max:_MAX_, small_step:_SMALL_, big_step:_BIG_, zero_means_unlimited:_ZMU_, format:_FORMAT_}}}

#define MENUITEM_ENUM(_NAME_, _VALUE_, _CYCLE_, _TEXTS_) \
	{name:_NAME_, type:MENUITEM_TYPE_ENUM, {menuitem_enum:{value:_VALUE_, cycle:_CYCLE_, list:_TEXTS_}}}

#define MENUITEM_LAUNCH(_NAME_, _CLOSE_, _ACTION_) \
	{name:_NAME_, type:MENUITEM_TYPE_LAUNCH, {menuitem_launch:{close:_CLOSE_, action:_ACTION_}}}

#define MENUITEM_SUBMENU(_NAME_, _ITEMS_) \
	{name:_NAME_, type:MENUITEM_TYPE_SUBMENU, {menuitem_submenu:{length:LENGTH(_ITEMS_), items:_ITEMS_, current_item:0}}}

#define MENUITEM_EVCOMP(_NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, FALSE)
#define MENUITEM_EVSEP( _NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE)

#define MENUITEM_BOOLEAN(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(bool))
#define MENUITEM_DELAY(  _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(delay))
#define MENUITEM_AFFLASH(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(flash))
#define MENUITEM_ACTION( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(action))
#define MENUITEM_SHUTTER(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(shutter))

#define MENUITEM_RELEASE(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, TRUE,     0,     0,   0,   0, FALSE, "%6u")
#define MENUITEM_CLRTEMP(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE, 1800, 11000, 100, 500, FALSE, "%5u")
#define MENUITEM_TIMEOUT(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, FALSE, "%3u")
#define MENUITEM_COUNTER(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, TRUE,  "%3u")
#define MENUITEM_BRACKET(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    1,     9,   2,   2, FALSE, "%1u")

#define MENUITEM_SCRIPT(_NAME_, _VALUE_) MENUITEM_LAUNCH(_NAME_, TRUE,  _VALUE_)
#define MENUITEM_TASK(  _NAME_, _VALUE_) MENUITEM_LAUNCH(_NAME_, FALSE, _VALUE_)

extern void menu_create(type_MENU * menu);
extern void menu_close();

extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();

extern void menu_action();
extern void menu_dp_action();
extern void menu_cycle();

extern void menu_drag_drop();

extern void menu_submenu_next();
extern void menu_submenu_prev();

#endif /* MENU_H_ */
