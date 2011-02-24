#ifndef MENU_H_
#define MENU_H_

#define hInfoCreative (*(int*)(0x0000213C))

typedef enum {
	MENUITEM_AV_COMP,
	MENUITEM_FLASH_COMP,
	MENUITEM_AEB,
	MENUITEM_SAFETY_SHIFT,
	MENUITEM_RELEASE_COUNT,
	MENUITEM_ISO_VIEWFINDER,
	MENUITEM_COLOR_TEMP,
	MENUITEM_EMIT_FLASH,
	MENUITEM_AF_FLASH,
	MENUITEM_DP_BUTTON,
	MENUITEM_EAEB,
	MENUITEM_INTERVAL,
	MENUITEM_REMOTE_DELAY,
	MENUITEM_COUNT,
	MENUITEM_LAST = MENUITEM_COUNT - 1
} type_MENUITEM;

typedef enum {
	MENUITEM_EAEB_FRAMES,
	MENUITEM_EAEB_EV,
	MENUITEM_EAEB_DELAY,
	MENUITEM_EAEB_M_MIN,
	MENUITEM_EAEB_M_MAX,
	MENUITEM_EAEB_COUNT,
	MENUITEM_EAEB_LAST = MENUITEM_EAEB_COUNT - 1
} type_MENUITEM_EAEB;

extern void menu_swap();
extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();
extern void menu_save();

extern char *menu_message();

#endif /* MENU_H_ */
