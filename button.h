/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

typedef enum {
	BUTTON_DP,
	BUTTON_DISP,
	BUTTON_MENU,
	BUTTON_JUMP,
	BUTTON_PLAY,
	BUTTON_TRASH,
	BUTTON_DIAL_LEFT,
	BUTTON_DIAL_RIGHT,
	BUTTON_ZOOM_OUT,
	BUTTON_ZOOM_IN,
	BUTTON_AV,
	BUTTON_DRIVE,
	BUTTON_SET,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_RIGHT,
	BUTTON_LEFT
} type_BUTTON;

int button_handler(type_BUTTON button);

#endif