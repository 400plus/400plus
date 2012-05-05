/*##################################################################################
 #                                                                                 #
 #                          _____     _       _                                    #
 #                         |  ___|   | |     | |                                   #
 #                         |___ \  __| |_ __ | |_   _ ___                          #
 #                             \ \/ _` | '_ \| | | | / __|                         #
 #                         /\__/ / (_| | |_) | | |_| \__ \                         #
 #                         \____/ \__,_| .__/|_|\__,_|___/                         #
 #                                     | |                                         #
 #                                     |_|                                         #
 #                                                                                 #
 #################################################################################*/

#include "bmp.h"
#include "debug.h"
#include <stdarg.h>


static void _draw_char(unsigned fontspec, uint8_t * bmp_vram_row, char c) {
	//~ if (!bmp_enabled) return;
	unsigned i,j;
	const struct font * const font = fontspec_font( fontspec );

	uint32_t        fg_color        = fontspec_fg( fontspec ) << 24;
	uint32_t        bg_color        = fontspec_bg( fontspec ) << 24;

	// Special case -- fg=bg=0 => white on black
	if( fg_color == 0 && bg_color == 0 ) {
		fg_color = COLOR_WHITE << 24;
		bg_color = COLOR_BLACK << 24;
	}

	const uint32_t  pitch           = BMPPITCH / 4;
	uint32_t *      front_row       = (uint32_t *) bmp_vram_row;

	//uint32_t flags = cli();
	for( i=0 ; i<font->height ; i++ ) {
		// Start this scanline
		uint32_t * row = front_row;

		// move to the next scanline
		front_row += pitch;

		uint32_t pixels = font->bitmap[ c + (i << 7) ];
		uint8_t pixel;

		for( j=0 ; j<font->width/4 ; j++ ) {
			uint32_t bmp_pixels = 0;
			for( pixel=0 ; pixel<4 ; pixel++, pixels <<=1 ) {
				bmp_pixels >>= 8;
				bmp_pixels |= (pixels & 0x80000000) ? fg_color : bg_color;
			}

			if ( (int)row < vram_end && (int)row >= vram_start ) {
				*(row++) = bmp_pixels;
			} else {
				debug_log("VRAM: draw outside vram region (0x%08X)", row);
				return;
			}

			// handle characters wider than 32 bits
			if( j == 28/4 )
				pixels = font->bitmap[ c + ((i+128) << 7) ];
		}
	}

	//sei( flags );
}






void bmp_puts(unsigned fontspec, unsigned * x, unsigned * y, const char * s) {
	const uint32_t pitch = BMPPITCH;
	int * vram = bmp_vram();
	if( !vram || ((int)vram & 1) == 1 )
		return;
	const unsigned initial_x = *x;
	uint8_t * first_row = (uint8_t*) ((int)vram + ((*y) * pitch) + (*x));
	uint8_t * row = first_row;

	char c;

	const struct font * const font = fontspec_font( fontspec );

	while( (c = *s++) ) {
		if( c == '\n' ) {
			row = first_row += pitch * font->height;
			(*y) += font->height;
			(*x) = initial_x;
			continue;
		}

		_draw_char( fontspec, row, c );
		row += font->width;
		(*x) += font->width;
	}

}





void bmp_printf(unsigned fontspec, unsigned x, unsigned y, const char * fmt, ...) {
	va_list                 ap;
	char                    buf[ 256 ];

	va_start( ap, fmt );
	vsnprintf( buf, sizeof(buf), fmt, ap );
	va_end( ap );

	bmp_puts( fontspec, &x, &y, buf );
}

// Andrew:
// bmp_hexdump(FONT_SMALL, 0, y_offset, 0xlocation_to_dump, 16*[# of lines to show on screen]);
// always keep x offset as 0 because it fills the whole screen as is :P
//
//~ Scaled in half from ML version. always have len as a multiple of 16. General
//~ use is 16 * num of lines desired printed.
void bmp_hexdump(unsigned fontspec, unsigned x, unsigned y, const void * buf, int len) {
	if( len == 0 )
		return;

	// Round up
	len = (len + 15) & ~15;

	const uint32_t *    d = (uint32_t*) buf;

	do {
		bmp_printf(fontspec, x, y,
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
void bmp_draw_palette( void ) {
	uint32_t x, y, msb, lsb;
	const uint32_t height = 15;
	const uint32_t width = 22;

	for( msb=0 ; msb<16; msb++ ) {
		for( y=0 ; y<height; y++ ) {
			int * const row = (int*) (int)bmp_vram() + (y + height*msb) * BMPPITCH;

			for( lsb=0 ; lsb<16 ; lsb++ ) {
				for( x=0 ; x<width ; x++ )
					row[x+width*lsb] = (msb << 4) | lsb;
			}
		}
	}

	static int written;
	if( !written )
		//dispcheck();
		written = 1;
	SleepTask(2000);
}

