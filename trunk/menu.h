#ifndef MENU_H_
#define MENU_H_

#define AUTOREPEAT_DELAY_UNIT   50
#define AUTOREPEAT_DELAY_LONG   10
#define AUTOREPEAT_DELAY_SHORT   4

typedef struct {
	int  length;
	char **data;
} type_LIST;

typedef struct MENU     type_MENU;
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

typedef enum {
	MENU_EVENT_DP,
	MENU_EVENT_SET,
	MENU_EVENT_CHANGE,
	MENU_EVENT_CLOSE,
	MENU_EVENT_COUNT,
	MENU_EVENT_FIRST = 0,
	MENU_EVENT_LAST  = MENU_EVENT_COUNT - 1
} type_MENU_EVENT;

typedef void(*type_MENU_TASK)    (type_MENU *menu);
typedef void(*type_MENUITEM_TASK)(type_MENUITEM *item);

typedef struct {
	int  *value;
	int   zero_means_off;
} type_MENUITEM_EV;

typedef struct {
	int  *value;
} type_MENUITEM_ISO;

typedef struct {
	int   *value;
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
	int length;
	int current_item;
	type_MENUITEM *items;
} type_MENUITEM_SUBMENU;

typedef union {
	type_MENUITEM_EV      menuitem_ev;
	type_MENUITEM_ISO     menuitem_iso;
	type_MENUITEM_INT     menuitem_int;
	type_MENUITEM_ENUM    menuitem_enum;
	type_MENUITEM_SUBMENU menuitem_submenu;
} type_MENUITEM_PARM;

struct MENUITEM {
	char               *name;
	type_MENUITEM_TYPE  type;
	type_MENUITEM_PARM  parm;
	type_MENUITEM_TASK  tasks[MENU_EVENT_COUNT];
};

struct MENU {
	char            *name;
	int              length;
	type_MENUITEM   *items;
	type_MENU_TASK   tasks[MENU_EVENT_COUNT];
	int              rename;
	int              reorder;
	int             *ordering;
	int              highlight;
	int              highlighted_item;
};

#define OPTIONLIST_DEC(NAME)      extern type_LIST _##NAME##_LIST_;
#define OPTIONLIST_REF(NAME)      (&_##NAME##_LIST_)
#define OPTIONLIST_DEF(NAME, ...) static char *_##NAME##_STRINGS_[]={__VA_ARGS__};  type_LIST _##NAME##_LIST_={length:LENGTH(_##NAME##_STRINGS_),data:_##NAME##_STRINGS_};

OPTIONLIST_DEC(bool)
OPTIONLIST_DEC(delay)
OPTIONLIST_DEC(flash)
OPTIONLIST_DEC(action)
OPTIONLIST_DEC(shutter)

#define MENUITEM_EV(_NAME_, _VALUE_, _ZMO_, _ON_CHANGE_) \
	{name:_NAME_, type:MENUITEM_TYPE_EV, parm:{menuitem_ev:{value:_VALUE_, zero_means_off:_ZMO_}}, tasks:{[MENU_EVENT_CHANGE]=_ON_CHANGE_}}

#define MENUITEM_ISO(_NAME_, _VALUE_, _ON_CHANGE_) \
	{name:_NAME_, type:MENUITEM_TYPE_ISO, parm:{menuitem_iso:{value:_VALUE_}}, tasks:{[MENU_EVENT_CHANGE]=_ON_CHANGE_}}

#define MENUITEM_INT(_NAME_, _VALUE_, _MIN_, _MAX_, _SMALL_, _BIG_, _ZMU_, _FORMAT_, _ON_CHANGE_) \
	{name:_NAME_, type:MENUITEM_TYPE_INT, parm:{menuitem_int:{value:_VALUE_, min:_MIN_, max:_MAX_, small_step:_SMALL_, big_step:_BIG_, zero_means_unlimited:_ZMU_, format:_FORMAT_}}, tasks:{[MENU_EVENT_CHANGE]=_ON_CHANGE_}}

#define MENUITEM_ENUM(_NAME_, _VALUE_, _CYCLE_, _TEXTS_, _ON_CHANGE_) \
	{name:_NAME_, type:MENUITEM_TYPE_ENUM, parm:{menuitem_enum:{value:_VALUE_, cycle:_CYCLE_, list:_TEXTS_}}, tasks:{[MENU_EVENT_CHANGE]=_ON_CHANGE_}}

#define MENUITEM_LAUNCH(_NAME_, _ACTION_) \
	{name:_NAME_, type:MENUITEM_TYPE_LAUNCH, tasks:{[MENU_EVENT_SET]=_ACTION_}}

#define MENUITEM_SUBMENU(_NAME_, _ITEMS_) \
	{name:_NAME_, type:MENUITEM_TYPE_SUBMENU, parm:{menuitem_submenu:{length:LENGTH(_ITEMS_), items:_ITEMS_, current_item:0}}}

#define MENUITEM_EVCOMP(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EV(_NAME_, _VALUE_, FALSE, _ON_CHANGE_)
#define MENUITEM_EVSEP( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE,  _ON_CHANGE_)

#define MENUITEM_BOOLEAN(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(bool),    _ON_CHANGE_)
#define MENUITEM_DELAY(  _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(delay),   _ON_CHANGE_)
#define MENUITEM_AFFLASH(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(flash),   _ON_CHANGE_)
#define MENUITEM_ACTION( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(action),  _ON_CHANGE_)
#define MENUITEM_SHUTTER(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(shutter), _ON_CHANGE_)

#define MENUITEM_CLRTEMP(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_, 1800, 11000, 100, 500, FALSE, "%5u", _ON_CHANGE_)
#define MENUITEM_TIMEOUT(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_,    0,   250,   1,  10, FALSE, "%3u", _ON_CHANGE_)
#define MENUITEM_COUNTER(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_,    0,   250,   1,  10, TRUE,  "%3u", _ON_CHANGE_)
#define MENUITEM_BRACKET(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_,    1,     9,   2,   2, FALSE, "%1u", _ON_CHANGE_)

extern void menu_create(type_MENU * menu);
extern void menu_close();

extern void menu_event_dp();
extern void menu_event_set();
extern void menu_event_change();
extern void menu_event_close();
extern void menu_event(type_MENU_EVENT);

extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();

extern void menu_cycle();

extern void menu_set_changed();
extern int  menu_get_changed();

extern void menu_toggle_filenames();
extern void menu_rename();
extern void menu_drag_drop();

extern void menu_submenu_next();
extern void menu_submenu_prev();

#endif /* MENU_H_ */
