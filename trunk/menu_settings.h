#ifndef MENU_SETTINGS_H_
#define MENU_SETTINGS_H_

#define MENUITEM_EVCOMP(_NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, FALSE)
#define MENUITEM_EVSEP( _NAME_, _VALUE_) MENUITEM_EV(_NAME_, _VALUE_, TRUE)

#define MENUITEM_BOOLEAN(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, bool_strings)
#define MENUITEM_DELAY(  _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, delay_strings)
#define MENUITEM_SCRACT( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  action_strings)
#define MENUITEM_SCRIPT( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, TRUE,  script_strings)
#define MENUITEM_SSPEED( _NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, sspeed_strings)

#define MENUITEM_RELEASE(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, TRUE,     0,     0,   0,   0, FALSE, "%6u")
#define MENUITEM_CLRTEMP(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE, 1800, 11000, 100, 500, FALSE, "%5u")
#define MENUITEM_TIMEOUT(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, FALSE, "%3u")
#define MENUITEM_COUNTER(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    0,   250,   1,  10, TRUE,  "%3u")
#define MENUITEM_BRACKET(_NAME_, _VALUE_) MENUITEM_INT(_NAME_, _VALUE_, FALSE,    1,     9,   2,   2, FALSE, "%1u")

extern void menu_settings_start();
extern void menu_settings_save();
extern void menu_settings_developer();

#endif /* MENU_SETTINGS_H_ */
