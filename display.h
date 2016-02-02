#ifndef DISPLAY_H_
#define DISPLAY_H_

#define AUTOISO_AUTO "AUTO"

#include <vxworks.h>
#include <stdint.h>

#include "firmware/gui.h"

#include "firmware.h"

extern void display_refresh(void);
extern void display_overlay(uint8_t *vram_address);

extern void display_countdown_dialog_create (void);
extern void display_countdown_dialog_destroy(void);
extern void display_countdown               (int seconds);

extern void display_message_set(char *message, int timeout);

extern int  hack_TransferScreen(int r0, int r1, int r2, int r3);
extern int  hack_GUI_IDLEHandler(int unk0, int event, int unused, int unk1);
extern void *hack_invert_olc_screen(char *dst, char *src, int size);

extern void hack_item_set_label_int(dialog_t *dialog, const int type, const void *data, const int length, const int item);
extern void hack_item_set_label_str(dialog_t *dialog, const int type, const void *data, const int length, const int item);

extern int hack_FF92E704 (int r0, int r1, int r2, int r3);
extern int hack_FF92E4C4 (int r0, int r1, int r2, int r3);

#endif /* DISPLAY_H_ */
