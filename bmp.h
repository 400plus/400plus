// Thanks to Coutts for porthing this.

#if FALSE  // Temporarily disable until we make it stable

#include "font.h"
#include "firmware.h"

#include <vxworks.h>

#define VramSize (360*240)

#define VramInstance_address *(int*)0x00005190

extern uint8_t *VramAddress; // MEM:0x00019638 (defined in camera.S)
// AF: I found 2 more addresses where the VRAM buffer can be found
// AF: they seems to be structs with the same structure:
// MEM:0x00019510 with offset 0x08 == MEM:0x00019518
// MEM:0x00019520 with offset 0x08 == MEM:0x00019528

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

// max x: 45
// max y: 20
#define lcd_printf(x, y, f...) bmp_printf(VramAddress, FONT(FONT_SMALL, COLOR_BLACK, COLOR_GRAY), x*8, y*12, ##f);
extern void bmp_printf (uint8_t *vram_address, unsigned fontspec, unsigned  x, unsigned  y, const char *fmt, ...) __attribute__((format(printf, 5, 6)));
extern void bmp_hexdump(uint8_t *vram_address, unsigned fontspec, unsigned  x, unsigned  y, const void *buf, int len);
extern void bmp_puts   (uint8_t *vram_address, unsigned fontspec, unsigned *x, unsigned *y, const char *s);

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
extern void bmp_draw_palette(uint8_t *vram_address);

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

#endif
