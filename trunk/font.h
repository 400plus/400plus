/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef _font_h_
#define _font_h_

#include <stdint.h>

struct font
{
	unsigned        width;
	unsigned        height;
	uint16_t        bitmap[];
};

#ifdef USE_FONT_SMALL
extern struct font font_small;
#endif
#ifdef USE_FONT_MED
extern struct font font_med;
#endif
#ifdef USE_FONT_LARGE
extern struct font font_large;
#endif

#endif
