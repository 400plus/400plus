#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "menu.h"
#include "menuoptions.h"

typedef struct {
	int  *value;
	int   extended;
	int   can_do_zero;
	int   zero_means_off;
} menuitem_ec_t;

typedef struct {
	int  *value;
} menuitem_av_t;

typedef struct {
	int  *value;
	int   bulb;
} menuitem_tv_t;

typedef struct {
	int  *value;
	int   full;
} menuitem_iso_t;

typedef struct {
	int   *value;
	int    min;
	int    max;
	int    small_step;
	int    big_step;
	int    base_log;
	int    zero_means_unlimited;
	char  *format;
} menuitem_int_t;

typedef struct {
	int     *value;
	int      cycle;
	list_t  *list;
} menuitem_enum_t;

typedef struct {
	char *value;
} menuitem_info_t;

typedef struct {
	menupage_t *page;
} menuitem_submenu_t;

typedef union {
	menuitem_ec_t      menuitem_ec;
	menuitem_av_t      menuitem_av;
	menuitem_tv_t      menuitem_tv;
	menuitem_iso_t     menuitem_iso;
	menuitem_int_t     menuitem_int;
	menuitem_enum_t    menuitem_enum;
	menuitem_info_t    menuitem_info;
	menuitem_submenu_t menuitem_submenu;
} menuitem_parm_t;

typedef void (*itemaction_t)(const menuitem_t *item);

struct menuitem_t {
	int             id;
	char           *name;
	int             readonly;
	menuitem_parm_t parm;
	void (*display)(const menuitem_t *item, char *buffer, const int length);
	void (*inc)    (const menuitem_t *item, const int repeating);
	void (*dec)    (const menuitem_t *item, const int repeating);
	itemaction_t   action;
	itemaction_t   change;
};

#define MENUITEM_EC(_ID_, _NAME_, _VALUE_, _RO_, _EXT_, _CDZ_, _ZMO_, _CHANGE_) { \
	id       : _ID_, \
	name     : _NAME_, \
	readonly : _RO_, \
	parm     : { menuitem_ec : { \
		value          : _VALUE_, \
		extended       : _EXT_, \
		can_do_zero    : _CDZ_, \
		zero_means_off : _ZMO_, \
	}}, \
	display  : menuitem_display_ec, \
	inc      : menuitem_inc_ec, \
	dec      : menuitem_dec_ec, \
	change   : _CHANGE_ \
}

#define MENUITEM_AV(_ID_, _NAME_, _VALUE_, _CHANGE_) { \
	id      : _ID_, \
	name    : _NAME_, \
	parm    : { menuitem_av : { \
			value : _VALUE_, \
	}}, \
	display : menuitem_display_av, \
	inc     : menuitem_inc_av, \
	dec     : menuitem_dec_av, \
	change  : _CHANGE_ \
}

#define MENUITEM_TV(_ID_, _NAME_, _VALUE_, _CHANGE_) { \
	id      : _ID_, \
	name    : _NAME_, \
	parm    : { menuitem_tv : { \
		value : _VALUE_, \
	}}, \
	display : menuitem_display_tv, \
	inc     : menuitem_inc_tv, \
	dec     : menuitem_dec_tv, \
	change  : _CHANGE_ \
}

#define MENUITEM_BULB(_ID_, _NAME_, _VALUE_, _CHANGE_) { \
	id      : _ID_, \
	name    : _NAME_, \
	parm    : { menuitem_tv : { \
		value : _VALUE_, \
	}}, \
	display : menuitem_display_bulb,  \
	inc     : menuitem_inc_bulb, \
	dec     : menuitem_dec_bulb, \
	change  : _CHANGE_ \
}

#define MENUITEM_ISO(_ID_, _NAME_, _VALUE_, _FULL_, _CHANGE_)  { \
	id      : _ID_, \
	name    : _NAME_, \
	parm    : { menuitem_iso : { \
		value : _VALUE_, \
		full  : _FULL_, \
	}}, \
	display : menuitem_display_iso, \
	inc     : menuitem_inc_iso, \
	dec     : menuitem_dec_iso, \
	change  : _CHANGE_ \
}

#define MENUITEM_INT(_ID_, _NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _LOG_, _ZMU_, _FORMAT_, _CHANGE_, _ACTION_) { \
	id       : _ID_, \
	name     : _NAME_, \
	readonly : _RO_, \
	parm     : {menuitem_int : { \
		value                : _VALUE_, \
		min                  : _MIN_, \
		max                  : _MAX_, \
		small_step           : _SMALL_, \
		big_step             : _BIG_, \
		base_log             : _LOG_, \
		zero_means_unlimited : _ZMU_, \
		format               : _FORMAT_, \
	}}, \
	display : menuitem_display_int, \
	inc     : menuitem_inc_int, \
	dec     : menuitem_dec_int, \
	change  : _CHANGE_, \
	action  : _ACTION_ \
}

#define MENUITEM_TIME(_ID_, _NAME_, _VALUE_, _RO_, _MIN_, _MAX_, _SMALL_, _BIG_, _LOG_, _CHANGE_) { \
	id       : _ID_, \
	name     : _NAME_, \
	readonly : _RO_, \
	parm     : {menuitem_int : { \
		value                : _VALUE_, \
		min                  : _MIN_, \
		max                  : _MAX_, \
		small_step           : _SMALL_, \
		big_step             : _BIG_, \
		base_log             : _LOG_, \
	}}, \
	display : menuitem_display_time, \
	inc     : menuitem_inc_int, \
	dec     : menuitem_dec_int, \
	change  : _CHANGE_ \
}

#define MENUITEM_FLENGTH(_ID_, _NAME_, _VALUE_, _CHANGE_) { \
	id       : _ID_, \
	name     : _NAME_, \
	parm     : {menuitem_int : { \
		value                : _VALUE_, \
		format               : "%i", \
	}}, \
	display : menuitem_display_int, \
	inc     : menuitem_inc_flen, \
	dec     : menuitem_dec_flen, \
	change  : _CHANGE_ \
}

#define MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, _CYCLE_, _TEXTS_, _CHANGE_)  { \
	id    : _ID_, \
	name  : _NAME_, \
	parm  : { menuitem_enum : { \
		value : _VALUE_, \
		cycle : _CYCLE_, \
		list  : _TEXTS_, \
	}}, \
	display : menuitem_display_enum, \
	inc     : menuitem_inc_enum, \
	dec     : menuitem_dec_enum, \
	change  : _CHANGE_ \
}

#define MENUITEM_LAUNCH(_ID_, _NAME_, _ACTION_)  { \
	id      : _ID_, \
	name    : _NAME_, \
	display : menuitem_display,  \
	action  : _ACTION_, \
}

#define MENUITEM_SUBMENU(_ID_, _NAME_, _PAGE_, _ACTION_) { \
	id    : _ID_, \
	name  : _NAME_, \
	parm  : { menuitem_submenu : { \
		page : _PAGE_, \
	}}, \
	display : menuitem_display_sub, \
	inc     : menuitem_inc_sub, \
	action  : _ACTION_, \
}

#define MENUITEM_PAGE(_ID_, _NAME_) { \
	id      : _ID_, \
	name    : _NAME_, \
	display : menuitem_display, \
}

#define MENUITEM_INFO(_ID_, _NAME_, _VALUE_) { \
	id    : _ID_, \
	name  : _NAME_, \
	parm  : { menuitem_info : { \
		value : _VALUE_, \
	}}, \
	display : menuitem_display_info, \
}

#define MENUITEM_EVCOMP(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EC(_ID_, _NAME_, _VALUE_, FALSE, FALSE, TRUE,  FALSE, _ON_CHANGE_)
#define MENUITEM_EVSEP( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EC(_ID_, _NAME_, _VALUE_, FALSE, FALSE, TRUE,  TRUE,  _ON_CHANGE_)
#define MENUITEM_EVEAEB(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EC(_ID_, _NAME_, _VALUE_, FALSE, FALSE, FALSE, TRUE,  _ON_CHANGE_)
#define MENUITEM_EVINFO(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_EC(_ID_, _NAME_, _VALUE_, FALSE, TRUE,  TRUE,  FALSE, _ON_CHANGE_)

#define MENUITEM_BASEISO(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ISO(_ID_, _NAME_, _VALUE_, TRUE,  _ON_CHANGE_)
#define MENUITEM_FULLISO(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ISO(_ID_, _NAME_, _VALUE_, FALSE, _ON_CHANGE_)

#define MENUITEM_BOOLEAN(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_bool,         _ON_CHANGE_)
#define MENUITEM_AFFLASH(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_flash,        _ON_CHANGE_)
#define MENUITEM_ACTION( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_action,       _ON_CHANGE_)
#define MENUITEM_LOGFILE(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_logfile,      _ON_CHANGE_)
#define MENUITEM_BTNACTN(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_btnactn,      _ON_CHANGE_)
#define MENUITEM_EAEBDIR(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_direction,    _ON_CHANGE_)
#define MENUITEM_LANG(   _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_languages,    _ON_CHANGE_)
#define MENUITEM_VFORMAT(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_vformat,      _ON_CHANGE_)
#define MENUITEM_SCRIND( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_scrind,       _ON_CHANGE_)
#define MENUITEM_SCRLCD( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_scrlcd,       _ON_CHANGE_)
#define MENUITEM_WEIGTH( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_qexp_weight,  _ON_CHANGE_)
#define MENUITEM_DIG_ISO(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_digiso_steps, _ON_CHANGE_)
#define MENUITEM_OLC_INV(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_ENUM(_ID_, _NAME_, _VALUE_, TRUE, &menuoptions_olcinv_steps, _ON_CHANGE_)

#define MENUITEM_CLRTEMP(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE, 1800, 11000, 100, 500,  0, FALSE, "%5u", _ON_CHANGE_, NULL)
#define MENUITEM_COUNTER(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE,    0,  9000,   1,  10, 10, TRUE,  "%4u", _ON_CHANGE_, NULL)
#define MENUITEM_BRACKET(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE,    3,     9,   2,   2,  0, FALSE, "%1u", _ON_CHANGE_, NULL)
#define MENUITEM_FDIST(  _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE,    1,  1000,   1,  10,  0, FALSE, "%4u", _ON_CHANGE_, NULL)
#define MENUITEM_BRSHOTS(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE,    0,  9000,   1,  10, 10, FALSE, "%4u", _ON_CHANGE_, NULL)

#define MENUITEM_NAMEDCT(_ID_, _NAME_, _VALUE_, _ACTION_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, FALSE, 1800, 11000,  25, 100,  0, FALSE, "%5u", NULL, _ACTION_)

#define MENUITEM_PARAM(_ID_, _NAME_, _VALUE_) MENUITEM_INT(_ID_, _NAME_, _VALUE_, TRUE, 0, 0, 0, 0, 0, FALSE, "%u", NULL, NULL)

#define MENUITEM_TIMEOUT(_ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_TIME(_ID_, _NAME_, _VALUE_, FALSE,    1, 18000,   1,  10, 60, _ON_CHANGE_)
#define MENUITEM_BRTIME( _ID_, _NAME_, _VALUE_, _ON_CHANGE_) MENUITEM_TIME(_ID_, _NAME_, _VALUE_, FALSE,    0, 18000,   1,  10, 60, _ON_CHANGE_)
#define MENUITEM_INFTIME(_ID_, _NAME_, _VALUE_)              MENUITEM_TIME(_ID_, _NAME_, _VALUE_, TRUE,     1, 18000,   1,  10, 60, NULL)

extern void menuitem_display      (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_ec   (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_av   (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_tv   (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_bulb (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_iso  (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_int  (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_time (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_enum (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_info (const menuitem_t *item, char *buffer, const int length);
extern void menuitem_display_sub  (const menuitem_t *item, char *buffer, const int length);

extern void menuitem_inc_ec   (const menuitem_t *item, const int repeating);
extern void menuitem_inc_av   (const menuitem_t *item, const int repeating);
extern void menuitem_inc_tv   (const menuitem_t *item, const int repeating);
extern void menuitem_inc_bulb (const menuitem_t *item, const int repeating);
extern void menuitem_inc_iso  (const menuitem_t *item, const int repeating);
extern void menuitem_inc_int  (const menuitem_t *item, const int repeating);
extern void menuitem_inc_flen (const menuitem_t *item, const int repeating);
extern void menuitem_inc_enum (const menuitem_t *item, const int repeating);
extern void menuitem_inc_sub  (const menuitem_t *item, const int repeating);

extern void menuitem_dec_ec   (const menuitem_t *item, const int repeating);
extern void menuitem_dec_av   (const menuitem_t *item, const int repeating);
extern void menuitem_dec_tv   (const menuitem_t *item, const int repeating);
extern void menuitem_dec_bulb (const menuitem_t *item, const int repeating);
extern void menuitem_dec_iso  (const menuitem_t *item, const int repeating);
extern void menuitem_dec_int  (const menuitem_t *item, const int repeating);
extern void menuitem_dec_flen (const menuitem_t *item, const int repeating);
extern void menuitem_dec_enum (const menuitem_t *item, const int repeating);

#endif /* MENUITEM_H_ */
