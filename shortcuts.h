#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_

typedef void(*type_LAUNCH)();

typedef struct {
	char        *text;
	type_LAUNCH  launch;
} type_SHORTCUT;

extern type_SHORTCUT shortcuts[5];

extern void shortcuts_initialize();
extern void shortcuts_close();

extern void shortcuts_up();
extern void shortcuts_left();
extern void shortcuts_set();
extern void shortcuts_right();
extern void shortcuts_down();

#endif /* SHORTCUTS_H_ */
