#ifndef MENU_H_
#define MENU_H_

#define hInfoCreative         (*(int*)(0x0000213C))

extern void menu_swap();
extern void menu_up();
extern void menu_down();
extern void menu_right();
extern void menu_left();
extern void menu_save();

extern char *menu_message();

#endif /* MENU_H_ */
