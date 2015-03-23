/**
 * $Revision$
 * $Date$
 * $Author$
 */

// Thanks to Coutts for porthing this.

#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "firmware.h"
#include "bmp.h"
#include "debug.h"
#include "cmodes.h"

uint8_t *VramAddrOverride;

static void _draw_char(uint8_t *vram_address, unsigned fontspec, uint8_t *bmp_vram_row, char c) {
	//~ if (!bmp_enabled) return;
	unsigned i,j;
	const font_t * const font = fontspec_font( fontspec );

	uint32_t        fg_color        = fontspec_fg( fontspec ) << 24;
	uint32_t        bg_color        = fontspec_bg( fontspec ) << 24;

	// Special case -- fg=bg=0 => white on black
	if( fg_color == 0 && bg_color == 0 ) {
		fg_color = COLOR_WHITE << 24;
		bg_color = COLOR_BLACK << 24;
	}

	// Protect us from unprintable characters
	if (c < 32 || c > 126)
		c = '?';

	const uint32_t  pitch      = BMPPITCH / 4;
	uint32_t *      front_row  = (uint32_t *) bmp_vram_row;

	//uint32_t flags = cli();
	for( i=0 ; i<font->height ; i++ ) {
		// Start this scanline
		uint32_t * row = front_row;

		// move to the next scanline
		front_row += pitch;

		uint16_t pixels = font->bitmap[ c + (i << 7) ];
		uint8_t pixel;

		for( j=0 ; j<font->width/4 ; j++ ) {
			uint32_t bmp_pixels = 0;
			for( pixel=0 ; pixel<4 ; pixel++, pixels <<=1 ) {
				bmp_pixels >>= 8;
				bmp_pixels |= (pixels & 0x8000) ? fg_color : bg_color;
			}

			if ((void *)row >= (void *)vram_address && (void *)row < (void *)(vram_address + VramSize)) {
				*(row++) = bmp_pixels;
			} else {
				debug_log("VRAM: draw outside vram region (0x%08X)", row);
				return;
			}
		}
	}

	//sei( flags );
}

void bmp_puts(uint8_t *vram_address, unsigned fontspec, unsigned * x, unsigned * y, const char * s) {
	const uint32_t pitch = BMPPITCH;

	if( !vram_address || ((int)vram_address & 1) == 1 )
		return;

	const unsigned initial_x = *x;
	uint8_t * first_row = (uint8_t*) ((int)vram_address + ((*y) * pitch) + (*x));
	uint8_t * row = first_row;

	char c;

	const font_t * const font = fontspec_font( fontspec );

	while( (c = *s++) ) {
		if( c == '\n' ) {
			row = first_row += pitch * font->height;
			(*y) += font->height;
			(*x) = initial_x;
			continue;
		}

		_draw_char(vram_address, fontspec, row, c );
		row += font->width;
		(*x) += font->width;
	}

}

void bmp_printf(uint8_t *vram_address, unsigned fontspec, unsigned x, unsigned y, const char * fmt, ...) {
	va_list                 ap;
	char                    buf[ 256 ];

	va_start( ap, fmt );
	vsnprintf( buf, sizeof(buf), fmt, ap );
	va_end( ap );

	bmp_puts(vram_address, fontspec, &x, &y, buf);
}

// Andrew:
// bmp_hexdump(FONT_SMALL, 0, y_offset, 0xlocation_to_dump, 16*[# of lines to show on screen]);
// always keep x offset as 0 because it fills the whole screen as is :P
//
//~ Scaled in half from ML version. always have len as a multiple of 16. General
//~ use is 16 * num of lines desired printed.
void bmp_hexdump(uint8_t *vram_address, unsigned fontspec, unsigned x, unsigned y, const void * buf, int len) {
	if( len == 0 )
		return;

	// Round up
	len = (len + 15) & ~15;

	const uint32_t *    d = (uint32_t*) buf;

	do {
		bmp_printf(vram_address,fontspec, x, y,
				"%08x: %08x %08x %08x %08x",
				(unsigned) d,
				len >  0 ? MEM(d+0) : 0,
				len >  4 ? MEM(d+1) : 0,
				len >  8 ? MEM(d+2) : 0,
				len > 12 ? MEM(d+3) : 0
		);

		y += fontspec_height( fontspec );
		d += 4;
		len -= 16;
	} while(len > 0);
}

/** Draw a picture of the BMP color palette. */
void bmp_draw_palette(uint8_t *vram_address) {
	uint32_t x, y;

	for (x = 0; x < 16 * 8; x++)
		for (y = 0; y < 16 * 8; y++)
			vram_address[x + y * 360] = (x / 8) | ((y / 8) << 4);
}

void ppm_vram_screenshot(uint8_t *vram_address) {
    char filename[20] = "A:/SCREENSHOT.BMP";

    lcd_printf(0,0,"Vram size : %d",VramSize);

    // Getting the current date
    time_t t;
    struct tm tm;
    time(&t);
    localtime_r(&t, &tm);

    // Renaming the screenshot file according to the current date
    sprintf(filename, "A:/%02d%02d%02d%02d.BMP", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Opening the file
    int file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644);

    if (file == -1) {
		debug_log("ERROR: can't open file for writing (%s)", filename);
		beep();
		beep();
	} else {
		unsigned char bmpfileheader[14] = {'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
		unsigned char bmpinfoheader[40] = {40,0,0,0,0,0,0,0,0,0,0,0,1,0,24,0};

		int height = 240;
		int width = 360;
		int filesize = 54 + height*width*3;

		bmpfileheader[2]  = (unsigned char)(filesize);
		bmpfileheader[3]  = (unsigned char)(filesize >> 8);
		bmpfileheader[4]  = (unsigned char)(filesize >> 16);
		bmpfileheader[5]  = (unsigned char)(filesize >> 24);

		bmpinfoheader[4]  = (unsigned char)(width);
		bmpinfoheader[5]  = (unsigned char)(width >> 8);
		bmpinfoheader[6]  = (unsigned char)(width >> 16);
		bmpinfoheader[7]  = (unsigned char)(width >> 24);
		bmpinfoheader[8]  = (unsigned char)(height);
		bmpinfoheader[9]  = (unsigned char)(height >> 8);
		bmpinfoheader[10] = (unsigned char)(height >> 16);
		bmpinfoheader[11] = (unsigned char)(height >> 24);

		FIO_WriteFile(file,bmpfileheader,14);
		FIO_WriteFile(file,bmpinfoheader,40);

		// Saving current power state
		int power_off_state = DPData.auto_power_off;

		// Disabling auto power off
		send_to_intercom(IC_SET_AUTO_POWER_OFF, false);

		int x,y;
		for (y = height; y; --y) {
			char line[1080];

			for (x = 0; x < width; ++x) {
				char current_pixel = vram_address[x+y*360];
				switch (current_pixel) {
					case 0x11: // lighter gray
						line[x*3] = 0xE0;
						line[x*3+1] = 0xE0;
						line[x*3+2] = 0xE0;
						break;
					case 0x22: // dark gray almost black
						line[x*3] = 0x26;
						line[x*3+1] = 0x26;
						line[x*3+2] = 0x26;
						break;
					case 0x33: // light gray
						line[x*3] = 0xCC;
						line[x*3+1] = 0xCC;
						line[x*3+2] = 0xCC;
						break;
					case 0x44: // light grey background of menu
						line[x*3] = 0x7D;
						line[x*3+1] = 0x7D;
						line[x*3+2] = 0x7D;
						break;
					case 0x55: // light green / lime green
						line[x*3] = 0x00;
						line[x*3+1] = 0xFF;
						line[x*3+2] = 0x8C;
						break;
					case 0x66: // red
						line[x*3] = 0x00;
						line[x*3+1] = 0x00;
						line[x*3+2] = 0xFF;
						break;
					case 0x77: // brown red / maroon
						line[x*3] = 0x13;
						line[x*3+1] = 0x29;
						line[x*3+2] = 0x61;
						break;
					case 0x88: // light blue
						line[x*3] = 0xFF;
						line[x*3+1] = 0xE5;
						line[x*3+2] = 0x00;
						break;
					case 0x99: // light gray
						line[x*3] = 0xCC;
						line[x*3+1] = 0xCC;
						line[x*3+2] = 0xCC;
						break;
					case 0xAA: // darker gray
						line[x*3] = 0x40;
						line[x*3+1] = 0x40;
						line[x*3+2] = 0x40;
						break;
					case 0xBB: // brown red / maroon
						line[x*3] = 0x13;
						line[x*3+1] = 0x29;
						line[x*3+2] = 0x61;
						break;
					case 0xCC: // light blue
						line[x*3] = 0xFF;
						line[x*3+1] = 0xE5;
						line[x*3+2] = 0x00;
						break;
					case 0xDD: // light orange / pale yellow
						line[x*3] = 0x00;
						line[x*3+1] = 0x00;
						line[x*3+2] = 0xFF;
						break;
					case 0xEE: // orange
						line[x*3] = 0x00;
						line[x*3+1] = 0x00;
						line[x*3+2] = 0xFF;
						break;
					case 0xFF: // white
						line[x*3] = 0xFF;
						line[x*3+1] = 0xFF;
						line[x*3+2] = 0xFF;
						break;
				}
			}

			FIO_WriteFile(file,line,width*3);
		}

		FIO_CloseFile(file);

		// Putting back the older power state
		send_to_intercom(IC_SET_AUTO_POWER_OFF, power_off_state);

		beep();
	}
}