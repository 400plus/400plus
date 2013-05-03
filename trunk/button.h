/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef BUTTON_H_
#define BUTTON_H_

typedef enum {
	BUTTON_NONE,
	BUTTON_DP,
	BUTTON_DISP,
	BUTTON_MENU,
	BUTTON_JUMP,
	BUTTON_PLAY,
	BUTTON_TRASH,
	BUTTON_WHEEL_LEFT,
	BUTTON_WHEEL_RIGHT,
	BUTTON_ZOOM_OUT,
	BUTTON_ZOOM_IN,
	BUTTON_AV,
	BUTTON_DRIVE,
	BUTTON_SET,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_RIGHT,
	BUTTON_LEFT,
	BUTTON_COUNT,
} button_t;

int button_handler(button_t button, int is_button_down);
void hack_send_jump_and_trash_buttons(int r0, int r1, int button);

#endif
