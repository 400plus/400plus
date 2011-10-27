#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "menu.h"

typedef struct {
	int  length;
	char **data;
} type_LIST;

typedef enum {
	MENUITEM_TYPE_EV,
	MENUITEM_TYPE_AV,
	MENUITEM_TYPE_TV,
	MENUITEM_TYPE_ISO,
	MENUITEM_TYPE_INT,
	MENUITEM_TYPE_ENUM,
	MENUITEM_TYPE_LAUNCH,
	MENUITEM_TYPE_SUBMENU,
	MENUITEM_TYPE_COUNT,
	MENUITEM_TYPE_FIRST = 0,
	MENUITEM_TYPE_LAST  = MENUITEM_TYPE_COUNT - 1
} type_MENUITEM_TYPE;

typedef void(*type_MENUITEM_TASK)(type_MENUITEM *item);

typedef struct {
	int  *value;
	int   can_do_zero;
	int   zero_means_off;
} type_MENUITEM_EV;

typedef struct {
	int  *value;
} type_MENUITEM_AV;

typedef struct {
	int  *value;
	int   bulb;
} type_MENUITEM_TV;

typedef struct {
	int  *value;
	int   full;
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
	type_MENUPAGE *page;
} type_MENUITEM_SUBMENU;

typedef union {
	type_MENUITEM_EV      menuitem_ev;
	type_MENUITEM_AV      menuitem_av;
	type_MENUITEM_TV      menuitem_tv;
	type_MENUITEM_ISO     menuitem_iso;
	type_MENUITEM_INT     menuitem_int;
	type_MENUITEM_ENUM    menuitem_enum;
	type_MENUITEM_SUBMENU menuitem_submenu;
} type_MENUITEM_PARM;

struct MENUITEM {
	char *name;
	int   readonly;
	type_MENUITEM_PARM  parm;
	type_MENUITEM_TASK  tasks[MENU_EVENT_COUNT];
	void (*display)(const type_MENUITEM *item, const char *buffer, const int length);
	void (*right)  (const type_MENUITEM *item, const int repeating);
	void (*left)   (const type_MENUITEM *item, const int repeating);
};

#define OPTIONLIST_DEC(NAME)      extern type_LIST _##NAME##_LIST_;
#define OPTIONLIST_REF(NAME)      (&_##NAME##_LIST_)
#define OPTIONLIST_DEF(NAME, ...) static char *_##NAME##_STRINGS_[]={__VA_ARGS__};  type_LIST _##NAME##_LIST_={length:LENGTH(_##NAME##_STRINGS_),data:_##NAME##_STRINGS_};

OPTIONLIST_DEC(bool)
OPTIONLIST_DEC(delay)
OPTIONLIST_DEC(flash)
OPTIONLIST_DEC(action)
OPTIONLIST_DEC(logfile)

#define MENUITEM_EV(_NAME_, _VALUE_, _CDZ_, _ZMO_, _ON_CHANGE_) { \
	name  : _NAME_, \
	parm  : { menuitem_ev : { \
		value          : _VALUE_, \
		can_do_zero    : _CDZ_, \
		zero_means_off : _ZMO_, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_ev, \
	right   : menuitem_right_ev, \
	left    : menuitem_left_ev, \
}

#define MENUITEM_AV(_NAME_, _VALUE_, _ON_CHANGE_) { \
	name  : _NAME_, \
	parm  : { menuitem_av : { \
			value : _VALUE_, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_av,  \
	right   : menuitem_right_av, \
	left    : menuitem_left_av, \
}

#define MENUITEM_TV(_NAME_, _VALUE_, _ON_CHANGE_) { \
	name  : _NAME_, \
	parm  : { menuitem_tv : { \
		value : _VALUE_, \
		bulb  : FALSE, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_tv,  \
	right   : menuitem_right_tv, \
	left    : menuitem_left_tv, \
}

#define MENUITEM_BULB(_NAME_, _VALUE_, _ON_CHANGE_) { \
	name  : _NAME_, \
	parm  : { menuitem_tv : { \
		value : _VALUE_, \
		bulb  : TRUE, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_tv,  \
	right   : menuitem_right_tv, \
	left    : menuitem_left_tv, \
}

#define MENUITEM_ISO(_NAME_, _VALUE_, _FULL_, _ON_CHANGE_)  { \
	name  : _NAME_, \
	parm  : { menuitem_iso : { \
		value : _VALUE_, \
		full  : _FULL_, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_iso,  \
	right   : menuitem_right_iso, \
	left    : menuitem_left_iso, \
}

#define MENUITEM_INT(_NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _ZMU_, _FORMAT_, _ON_CHANGE_) { \
	name     : _NAME_, \
	readonly : _RO_, \
	parm     : {menuitem_int : { \
		value                : _VALUE_, \
		min                  : _MIN_, \
		max                  : _MAX_, \
		small_step           : _SMALL_, \
		big_step             : _BIG_, \
		zero_means_unlimited : _ZMU_, \
		format               : _FORMAT_, \
	}}, \
	tasks    : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_int,  \
	right   : menuitem_right_int, \
	left    : menuitem_left_iso, \
}

#define MENUITEM_ENUM(_NAME_, _VALUE_, _CYCLE_, _TEXTS_, _ON_CHANGE_)  { \
	name  : _NAME_, \
	parm  : { menuitem_enum : { \
		value : _VALUE_, \
		cycle : _CYCLE_, \
		list  : _TEXTS_, \
	}}, \
	tasks : { \
		[MENU_EVENT_CHANGE] = _ON_CHANGE_, \
	}, \
	display : menuitem_display_enum,  \
	right   : menuitem_right_enum, \
	left    : menuitem_left_enum, \
}

#define MENUITEM_LAUNCH(_NAME_, _ACTION_)  { \
	name  : _NAME_, \
	tasks : { \
		[MENU_EVENT_SET] = _ACTION_, \
	}, \
	display : menuitem_display,  \
}

#define MENUITEM_SUBMENU(_NAME_, _PAGE_, _ACTION_) { \
	name  : _NAME_, \
	parm  : { menuitem_submenu : { \
		page : _PAGE_, \
	}}, \
	tasks : { \
		[MENU_EVENT_SET] = _ACTION_, \
	}, \
	display : menuitem_display_sub,  \
	right   : menuitem_right_sub, \
}

#define MENUITEM_EVCOMP(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE,  FALSE, _ON_CHANGE_)
#define MENUITEM_EVSEP( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE,  TRUE,  _ON_CHANGE_)
#define MENUITEM_EVEAEB(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EV(_NAME_, _VALUE_, FALSE, TRUE,  _ON_CHANGE_)

#define MENUITEM_BASEISO(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ISO(_NAME_, _VALUE_, FALSE, _ON_CHANGE_)
#define MENUITEM_FULLISO(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ISO(_NAME_, _VALUE_, TRUE , _ON_CHANGE_)

#define MENUITEM_BOOLEAN( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(bool),     _ON_CHANGE_)
#define MENUITEM_DELAY(   _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(delay),    _ON_CHANGE_)
#define MENUITEM_AFFLASH( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(flash),    _ON_CHANGE_)
#define MENUITEM_ACTION(  _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  OPTIONLIST_REF(action),   _ON_CHANGE_)
#define MENUITEM_LOGFILE( _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, OPTIONLIST_REF(logfile),  _ON_CHANGE_)

#define MENUITEM_CLRTEMP(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE, 1800, 11000, 100, 500, FALSE, "%5u", _ON_CHANGE_)
#define MENUITEM_TIMEOUT(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, FALSE, "%3u", _ON_CHANGE_)
#define MENUITEM_COUNTER(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, TRUE,  "%3u", _ON_CHANGE_)
#define MENUITEM_BRACKET(_NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    1,     9,   2,   2, FALSE, "%1u", _ON_CHANGE_)

#define MENUITEM_INFO(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, TRUE, 0, 0, 0, 0, FALSE, "%u", NULL)

#define MENUITEM_BREAK(_NAME_) MENUITEM_LAUNCH(_NAME_, NULL)

extern void menuitem_display      (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_ev   (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_av   (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_tv   (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_iso  (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_int  (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_enum (const type_MENUITEM *item, const char *buffer, const int length);
extern void menuitem_display_sub  (const type_MENUITEM *item, const char *buffer, const int length);

extern void menuitem_right_ev  (const type_MENUITEM *item, const int repeating);
extern void menuitem_right_av  (const type_MENUITEM *item, const int repeating);
extern void menuitem_right_tv  (const type_MENUITEM *item, const int repeating);
extern void menuitem_right_iso (const type_MENUITEM *item, const int repeating);
extern void menuitem_right_int (const type_MENUITEM *item, const int repeating);
extern void menuitem_right_enum(const type_MENUITEM *item, const int repeating);
extern void menuitem_right_sub (const type_MENUITEM *item, const int repeating);

extern void menuitem_left_ev  (const type_MENUITEM *item, const int repeating);
extern void menuitem_left_av  (const type_MENUITEM *item, const int repeating);
extern void menuitem_left_tv  (const type_MENUITEM *item, const int repeating);
extern void menuitem_left_iso (const type_MENUITEM *item, const int repeating);
extern void menuitem_left_int (const type_MENUITEM *item, const int repeating);
extern void menuitem_left_enum(const type_MENUITEM *item, const int repeating);

#endif /* MENUITEM_H_ */
