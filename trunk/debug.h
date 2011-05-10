#ifndef DEBUG_H_
#define DEBUG_H_

#include "firmware.h"

#ifdef ENABLE_DEBUG

#define debug_log(f, p...) printf_log(8, 8, "[400Plus] %s[%d]: " f, __FILE__, __LINE__, ##p)
#define debug_printf(f, p...) printf("\n[400Plus] %s[%d]: " f, __FILE__, __LINE__, ##p)
static inline char * gui_event_name(char * buf, gui_event_t event) {
	switch (event) {
	case GUI_GOT_TOP_OF_CONTROL:       sprintf(buf, "GUI_GOT_TOP_OF_CONTROL");       break;
	case GUI_INITIALIZE_CONTROLLER:    sprintf(buf, "GUI_INITIALIZE_CONTROLLER");    break;
	case GUI_BUTTON_RIGHT:             sprintf(buf, "GUI_BUTTON_RIGHT");             break;
	case GUI_BUTTON_LEFT:              sprintf(buf, "GUI_BUTTON_LEFT");              break;
	case GUI_BUTTON_UP:                sprintf(buf, "GUI_BUTTON_UP");                break;
	case GUI_BUTTON_DOWN:              sprintf(buf, "GUI_BUTTON_DOWN");              break;
	case GUI_BUTTON_MENU:              sprintf(buf, "GUI_BUTTON_MENU");              break;
	case GUI_BUTTON_JUMP:              sprintf(buf, "GUI_BUTTON_JUMP");              break;
	case GUI_BUTTON_SET:               sprintf(buf, "GUI_BUTTON_SET");               break;
	case GUI_BUTTON_ZOOM_IN_PRESS:     sprintf(buf, "GUI_BUTTON_ZOOM_IN_PRESS");     break;
	case GUI_BUTTON_ZOOM_IN_RELEASE:   sprintf(buf, "GUI_BUTTON_ZOOM_IN_RELEASE");   break;
	case GUI_BUTTON_ZOOM_OUT_PRESS:    sprintf(buf, "GUI_BUTTON_ZOOM_OUT_PRESS");    break;
	case GUI_BUTTON_ZOOM_OUT_RELEASE:  sprintf(buf, "GUI_BUTTON_ZOOM_OUT_RELEASE");  break;
	case GUI_BUTTON_DISP:              sprintf(buf, "GUI_BUTTON_DISP");              break;
	case GUI_BUTTON_DIAL_RIGHT:        sprintf(buf, "GUI_BUTTON_DIAL_RIGHT");        break;
	case GUI_BUTTON_DIAL_LEFT:         sprintf(buf, "GUI_BUTTON_DIAL_LEFT");         break;
	case GUI_BUTTON_PLAY:              sprintf(buf, "GUI_BUTTON_PLAY");              break;
	case GUI_BUTTON_TRASH:             sprintf(buf, "GUI_BUTTON_TRASH");             break;
	case GUI_BUTTON_DP:                sprintf(buf, "GUI_BUTTON_DP");                break;
	case GUI_BUTTON_DRIVE:             sprintf(buf, "GUI_BUTTON_DRIVE");             break;
	case GUI_UNKNOWN0:                 sprintf(buf, "GUI_UNKNOWN0");                 break;
	case GUI_BUTTON_CF_CARD:           sprintf(buf, "GUI_BUTTON_CF_CARD");           break;
	case GUI_UNKNOWN1:                 sprintf(buf, "GUI_UNKNOWN1");                 break;
	case GUI_UNKNOWN2:                 sprintf(buf, "GUI_UNKNOWN2");                 break;
	default:                           sprintf(buf, "0x%08X", event);                break;
	}
	return buf;
}

#else // ENABLE_DEBUG

#define debug_log(...)
#define debug_printf(...)
static inline char * __attribute__((unused)) gui_event_name(char * buf, gui_event_t event) {
	sprintf(buf, "0x%08X", event);
	return buf;
}
#endif

#endif // DEBUG_H_
