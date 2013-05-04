/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define AUTOISO_AUTO "AUTO"

extern void initialize_display();

extern void restore_display();
extern void display_refresh();
extern void display_overlay();

extern void display_countdown_dialog_create();
extern void display_countdown_dialog_destroy();
extern void display_countdown(int seconds);

extern void display_brightness();

extern void display_message_set(char *message, int timeout);

extern int  hack_TransferScreen(int r0, int r1, int r2, int r3, int a, int b, int c, int d);
extern int  hack_GUI_IDLEHandler(int unk0, int event, int unused, int unk1);
extern void *hack_invert_olc_screen(char *dst, char *src, int size);

#endif /* DISPLAY_H_ */
