/**
 * $Revision$
 * $Date$
 * $Author$
 */

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

#include <vxworks.h>

#include "font.h"
#include "firmware.h"


extern int VramAddr; // MEM:0x00019638 (defined in camera.S)
// AF: I found 2 more addresses where the VRAM buffer can be found
// AF: they seems to be structs with the same structure:
// MEM:0x00019510 with offset 0x08 == MEM:0x00019518
// MEM:0x00019520 with offset 0x08 == MEM:0x00019528

#define vram_start (VramAddr)
//#define vram_start (0x212D7C) // AF
//#define vram_start (0x212D08) // Edu
#define vram_end   (vram_start + (360*240))
#define vram_size  (vram_end   - vram_start)

static inline int *bmp_vram(void) {
	int *x = (int*)vram_start;  //~ location of bmp buffer
	return x;
}

#define BMPPITCH 360

#define FONT_MASK               0x000F0000

#ifdef USE_FONT_SMALL
#define FONT_SMALL              0x00010000
#endif
#ifdef USE_FONT_MED
#define FONT_MED                0x00020000
#endif
#ifdef USE_FONT_LARGE
#define FONT_LARGE              0x00030000
#endif

#define FONT(font,fg,bg) ( 0   \
	| ((font) & FONT_MASK) \
	| ((bg) & 0xFF) << 8   \
	| ((fg) & 0xFF) << 0   \
)

#define FONT_BG(font) (((font) & 0xFF00) >> 8)
#define FONT_FG(font) (((font) & 0x00FF) >> 0)

static inline font_t * fontspec_font(unsigned fontspec) {
	switch( fontspec & FONT_MASK ) {
	default:
#ifdef USE_FONT_SMALL
	case FONT_SMALL:	return &font_small;
#endif
#ifdef USE_FONT_MED
	case FONT_MED:		return &font_med;
#endif
#ifdef USE_FONT_LARGE
	case FONT_LARGE:	return &font_large;
#endif
	}
}

static inline unsigned fontspec_fg(unsigned fontspec) {
	return (fontspec >> 0) & 0xFF;
}

static inline unsigned fontspec_bg(unsigned fontspec) {
	return (fontspec >> 8) & 0xFF;
}

static inline unsigned fontspec_height(unsigned fontspec) {
	return fontspec_font(fontspec)->height;
}

extern void bmp_printf (unsigned fontspec, unsigned  x, unsigned  y, const char *fmt, ...) __attribute__((format(printf,4,5)));
extern void bmp_hexdump(unsigned fontspec, unsigned  x, unsigned  y, const void *buf, int len);
extern void bmp_puts   (unsigned fontspec, unsigned *x, unsigned *y, const char *s);

#define bmp_printf_timed(time, font, x, y, f...) do { \
	bmp_printf(font, x, y, ##f);                  \
	signed int z = time;                          \
	while (z>0) {                                 \
		bmp_printf(font, x, y, ##f);          \
		SleepTask(20);                        \
		z -= 20;                              \
	}                                             \
	display_refresh();                            \
} while (0)

/** Fill the screen with a bitmap palette */
extern void bmp_draw_palette( void );

/** Some selected colors */
enum {
	COLOR_BLACK  = 0x00,
	COLOR_WHITE  = 0x11,
	COLOR_GRAY   = 0x33,
	COLOR_GREEN  = 0x55,
	COLOR_BLUE   = 0x66,
	COLOR_RED    = 0x77,
	COLOR_YELLOW = 0x88,
	COLOR_ORANGE = 0xCC,
};
