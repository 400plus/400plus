#ifndef MENU_H_
#define MENU_H_

#define MENU_WIDTH  27
#define MENU_HEIGHT  5

#define AUTOREPEAT_DELAY_UNIT   50
#define AUTOREPEAT_DELAY_LONG   10
#define AUTOREPEAT_DELAY_SHORT   4

typedef enum {
	MENU_COLOR_RED              = 0x00,
	MENU_COLOR_BLUE             = 0x01,
	MENU_COLOR_YELLOW           = 0x02,
	MENU_COLOR_YELLOW_AND_WHITE = 0x06,
	MENU_COLOR_DARK_BLUE        = 0x09,
	//MENU_COLOR_SOMETHING_FOR_THE_HELP_SCREEN_MAY_BE = 0x0A, // cannot be used for menus
	MENU_COLOR_DARK_RED         = 0x0C,
	MENU_COLOR_YELLOW_AND_GREEN = 0x10, // nice
	MENU_COLOR_WHITE_ON_BLACK   = 0x12, // dark one
	MENU_COLOR_ORANGE           = 0x67,
} type_MENU_COLOR;

typedef struct MENU     type_MENU;
typedef struct MENUITEM type_MENUITEM;
typedef struct MENUPAGE type_MENUPAGE;

typedef enum {
	MENU_EVENT_MENU,
	MENU_EVENT_DISP,
	MENU_EVENT_JUMP,
	MENU_EVENT_PLAY,
	MENU_EVENT_TRASH,
	MENU_EVENT_SET,
	MENU_EVENT_PREV,
	MENU_EVENT_NEXT,
	MENU_EVENT_UP,
	MENU_EVENT_DOWN,
	MENU_EVENT_RIGHT,
	MENU_EVENT_LEFT,
	MENU_EVENT_DP,
	MENU_EVENT_AV,
	MENU_EVENT_OUT,
	MENU_EVENT_IN,
	MENU_EVENT_OPEN,
	MENU_EVENT_CHANGE,
	MENU_EVENT_CLOSE,
	MENU_EVENT_COUNT,
	MENU_EVENT_FIRST = 0,
	MENU_EVENT_LAST  = MENU_EVENT_COUNT - 1
} type_MENU_EVENT;

typedef void(*type_MENU_TASK)    (type_MENU     *menu);

struct MENU {
	type_MENU_COLOR   color;
	int               length;
	type_MENUPAGE   **pages;
	type_MENU_TASK    tasks[MENU_EVENT_COUNT];
	int              *ordering;
};

extern type_CAMERA_MODE menu_cameraMode;

extern void menu_create(type_MENU * menu);
extern void menu_set_page(type_MENUPAGE *page);
extern void menu_close();

extern void menu_event_menu();
extern void menu_event_disp();
extern void menu_event_jump();
extern void menu_event_play();
extern void menu_event_trash();
extern void menu_event_set();
extern void menu_event_prev();
extern void menu_event_next();
extern void menu_event_up();
extern void menu_event_down();
extern void menu_event_right();
extern void menu_event_left();
extern void menu_event_dp();
extern void menu_event_av();
extern void menu_event_out();
extern void menu_event_in();
extern void menu_event_open();
extern void menu_event_change();
extern void menu_event_close();

extern void menu_event(type_MENU_EVENT);

extern void menu_void();
extern void menu_return();

extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();

extern void menu_cycle();

extern void menu_drag_drop();

extern void menu_page_next();
extern void menu_page_prev();

#endif /* MENU_H_ */
