/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef _font_h_
#define _font_h_

struct font
{
    unsigned        width;
    unsigned        height;
    unsigned        bitmap[];
};


extern struct font font_small;
extern struct font font_med;
extern struct font font_large;
extern struct font font_huge;

#endif