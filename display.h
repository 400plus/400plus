/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define OVERLAY_RETRY  2
#define OVERLAY_DELAY 10

extern void initialize_display();

extern void restore_display();
extern void display_refresh();
extern void display_overlay();

extern void display_countdown_dialog_create();
extern void display_countdown_dialog_destroy();
extern void display_countdown(int seconds);

extern void display_brightness();

extern void display_message_set(char *message, int timeout);

#endif /* DISPLAY_H_ */
