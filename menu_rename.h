#ifndef MENU_RENAME_H_
#define MENU_RENAME_H_

extern void rename_create(char *filename, type_TASK callback);
extern void rename_close();

extern void rename_up();
extern void rename_down();
extern void rename_right();
extern void rename_left();

extern void rename_cycle();
extern void rename_action();
extern void rename_save();
extern void rename_clear();

extern void rename_next();
extern void rename_prev();

#endif /* MENU_RENAME_H_ */
