#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_

typedef void(*type_LAUNCH)();

typedef enum {
	SHORTCUT_TYPE_STATIC,
	SHORTCUT_TYPE_BOOL,
	SHORTCUT_TYPE_ISO,
	SHORTCUT_TYPE_COUNT,
	SHORTCUT_TYPE_FIRST = 0,
	SHORTCUT_TYPE_LAST  = SHORTCUT_TYPE_COUNT - 1
} type_SHORTCUT_TYPE;

typedef struct {
	char               *text;
	type_SHORTCUT_TYPE  type;
	type_LAUNCH         launch;
	int                *data;
} type_SHORTCUT;

extern void shortcuts_initialize();
extern void shortcuts_close();

extern void shortcuts_config_start();
extern void shortcuts_config_end();

extern void shortcuts_launch_0();
extern void shortcuts_launch_1();
extern void shortcuts_launch_2();
extern void shortcuts_launch_3();
extern void shortcuts_launch_4();

extern void shortcuts_up();
extern void shortcuts_left();
extern void shortcuts_set();
extern void shortcuts_right();
extern void shortcuts_down();

#endif /* SHORTCUTS_H_ */
