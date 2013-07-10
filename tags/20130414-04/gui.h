/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef GUI_H_
#define GUI_H_

typedef enum {
	WIDGET_BINARY_BITMAP  = 1,
	WIDGET_BUTTON         = 2,
	WIDGET_COUNTER        = 3,
	WIDGET_FOCUS_MARK     = 4,
	WIDGET_HISTOGRAM      = 5,
	WIDGET_LIST_SELECT    = 8,
	WIDGET_MENU_TAB       = 9,
	WIDGET_NAVIGATE_ICON  = 10,
	WIDGET_POPUP_AEB      = 11,
	WIDGET_POPUP_MENU     = 13,
	WIDGET_PROGRESS_BAR   = 14,
	WIDGET_RECTANGLE      = 15,
	WIDGET_SCROLL_BAR     = 16,
	WIDGET_SLIDER         = 17,
	WIDGET_TEXT           = 19,
	WIDGET_LIST_VIEW      = 20,
	WIDGET_POPUP_SLIDER   = 22,
	WIDGET_ANIMATION_BMP  = 23,
	WIDGET_ARCH_RECT      = 27,
	WIDGET_PALETTE_BITMAP = 28,
} widget_init_t;

#endif // GUI_H_
