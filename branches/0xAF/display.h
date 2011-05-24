#ifndef DISPLAY_H_
#define DISPLAY_H_

extern void restore_display();
extern void display_refresh();

extern void display_countdown_dialog_create();
extern void display_countdown_dialog_destroy();
extern void display_countdown(int seconds);

#endif /* DISPLAY_H_ */
