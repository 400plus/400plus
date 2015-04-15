#ifndef AF_PATTERNS_H_
#define AF_PATTERNS_H_

#define AF_PATTERN_NONE            0

#define AF_PATTERN_CENTER          AF_POINT_C
#define AF_PATTERN_SQUARE          AF_POINT_C | AF_POINT_TL | AF_POINT_TR | AF_POINT_BL | AF_POINT_BR

#define AF_PATTERN_TOP             AF_POINT_T
#define AF_PATTERN_TOPTRIANGLE     AF_POINT_T | AF_POINT_TL | AF_POINT_TR
#define AF_PATTERN_TOPDIAMOND      AF_POINT_T | AF_POINT_TL | AF_POINT_TR | AF_POINT_C
#define AF_PATTERN_TOPHALF         AF_POINT_T | AF_POINT_TL | AF_POINT_TR | AF_POINT_C | AF_POINT_L | AF_POINT_R

#define AF_PATTERN_BOTTOM          AF_POINT_B
#define AF_PATTERN_BOTTOMTRIANGLE  AF_POINT_B | AF_POINT_BL | AF_POINT_BR
#define AF_PATTERN_BOTTOMDIAMOND   AF_POINT_B | AF_POINT_BL | AF_POINT_BR | AF_POINT_C
#define AF_PATTERN_BOTTOMHALF      AF_POINT_B | AF_POINT_BL | AF_POINT_BR | AF_POINT_C | AF_POINT_L | AF_POINT_R

#define AF_PATTERN_TOPLEFT         AF_POINT_TL
#define AF_PATTERN_TOPRIGHT        AF_POINT_TR
#define AF_PATTERN_BOTTOMLEFT      AF_POINT_BL
#define AF_PATTERN_BOTTOMRIGHT     AF_POINT_BR

#define AF_PATTERN_LEFT            AF_POINT_L
#define AF_PATTERN_LEFTTRIANGLE    AF_POINT_L | AF_POINT_TL | AF_POINT_BL
#define AF_PATTERN_LEFTDIAMOND     AF_POINT_L | AF_POINT_TL | AF_POINT_BL | AF_POINT_C
#define AF_PATTERN_LEFTHALF        AF_POINT_L | AF_POINT_TL | AF_POINT_BL | AF_POINT_C | AF_POINT_T | AF_POINT_B

#define AF_PATTERN_RIGHT           AF_POINT_R
#define AF_PATTERN_RIGHTTRIANGLE   AF_POINT_R | AF_POINT_TR | AF_POINT_BR
#define AF_PATTERN_RIGHTDIAMOND    AF_POINT_R | AF_POINT_TR | AF_POINT_BR | AF_POINT_C
#define AF_PATTERN_RIGHTHALF       AF_POINT_R | AF_POINT_TR | AF_POINT_BR | AF_POINT_C | AF_POINT_T | AF_POINT_B

#define AF_PATTERN_HLINE           AF_POINT_C | AF_POINT_L | AF_POINT_R
#define AF_PATTERN_VLINE           AF_POINT_C | AF_POINT_T | AF_POINT_B

#define AF_PATTERN_ALL             AF_POINT_C | AF_POINT_T | AF_POINT_B | AF_POINT_TL | AF_POINT_TR | AF_POINT_BL | AF_POINT_BR | AF_POINT_L | AF_POINT_R

typedef struct {
	int pattern;
	int next_center;
	int next_top;
	int next_bottom;
	int next_left;
	int next_right;
} pattern_map_item_t;

typedef enum {
	DIRECTION_CENTER,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} direction_t;

extern void afp_enter (void);

extern void afp_center (void);
extern void afp_top    (void);
extern void afp_bottom (void);
extern void afp_left   (void);
extern void afp_right  (void);

#endif /* AF_PATTERNS_H_ */
