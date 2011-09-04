#ifndef DEBUG_H_
#define DEBUG_H_

#include "firmware.h"
#include "mainctrl.h"

#ifdef ENABLE_DEBUG

#define debug_log(f, p...) printf_log(8, 8, "[400Plus] %s[%d]: " f, __FILE__, __LINE__, ##p)
#define debug_printf(f, p...) printf("\n[400Plus] %s[%d]: " f, __FILE__, __LINE__, ##p)
#if 0
static inline char * mc_btn_name(char * buf, int event) {
	switch (event) {
	case MC_BUTTON_MENU:		sprintf(buf, "MC_BUTTON_MENU");			break;
	case MC_BUTTON_DISP:		sprintf(buf, "MC_BUTTON_DISP");			break;
	case MC_BUTTON_JUMP:		sprintf(buf, "MC_BUTTON_JUMP");			break;
	case MC_BUTTON_PLAY:		sprintf(buf, "MC_BUTTON_PLAY");			break;
	case MC_BUTTON_TRASH:		sprintf(buf, "MC_BUTTON_TRASH");		break;
	case MC_BUTTON_SET:		sprintf(buf, "MC_BUTTON_SET");			break;
	case MC_DIALOG1:		sprintf(buf, "MC_DIALOG1");			break;
	case MC_DIALOG2:		sprintf(buf, "MC_DIALOG2");			break;
	case MC_BUTTON_DIAL:		sprintf(buf, "MC_BUTTON_DIAL");			break;
	case MC_BUTTON_DIAL_LEFT:	sprintf(buf, "MC_BUTTON_DIAL_LEFT");		break;
	case MC_BUTTON_DIAL_RIGHT:	sprintf(buf, "MC_BUTTON_DIAL_RIGHT");		break;
	case MC_BUTTON_CARD_DOOR_OPEN:	sprintf(buf, "MC_BUTTON_CARD_DOOR");		break;
	case MC_BUTTON_UNK1:		sprintf(buf, "MC_BUTTON_UNK1");			break;
	case MC_BUTTON_POWER:		sprintf(buf, "MC_BUTTON_POWER");		break;
	case MC_BUTTON_BATTERY_DOOR_OPEN:sprintf(buf, "MC_BUTTON_BATTERY_DOOR");		break;
	case MC_BUTTON_UP:		sprintf(buf, "MC_BUTTON_UP");			break;
	case MC_BUTTON_DOWN:		sprintf(buf, "MC_BUTTON_DOWN");			break;
	case MC_BUTTON_RIGHT:		sprintf(buf, "MC_BUTTON_RIGHT");		break;
	case MC_BUTTON_LEFT:		sprintf(buf, "MC_BUTTON_LEFT");			break;
	case MC_BUTTON_HALF_SHUTTER:	sprintf(buf, "MC_BUTTON_HALF_SHUTTER");		break;
	case MC_BUTTON_FULL_SHUTTER:	sprintf(buf, "MC_BUTTON_FULL_SHUTTER");		break;
	case MC_BUTTON_DP:		sprintf(buf, "MC_BUTTON_DP");			break;
	case MC_AFPDLGON:		sprintf(buf, "MC_AFPDLGON");			break;
	case MC_BUTTON_DRIVE:		sprintf(buf, "MC_BUTTON_DRIVE");		break;
	case MC_BUTTON_CARD_DOOR_CLOSE:	sprintf(buf, "MC_BUTTON_CF_DOOR_CLOSE");	break;
	case MC_BUTTON_UNK2:		sprintf(buf, "MC_BUTTON_UNK2");			break;
	default:			sprintf(buf, "0x%08X", event);			break;
	}
	return buf;
}
#else
static inline char * __attribute__((unused)) mc_btn_name(char * buf, int event) {
	sprintf(buf, "0x%08X", event);
	return buf;
}
#endif

#define LEDRED (*((int*)0xC02200A0))
#define LEDBLUE (*((int*)0xC0220000))
#define LEDON   0x46
#define LEDOFF  0x44

#define blink_cycles 1000000
#define blink_red() do { int i; LEDRED=LEDON; for (i=0;i<blink_cycles; i++); LEDRED=LEDOFF; for (i=0;i<blink_cycles; i++); } while (0)
#define blink_blue() do { int i; LEDBLUE=LEDON; for (i=0;i<blink_cycles; i++); LEDBLUE=LEDOFF; for (i=0;i<blink_cycles; i++); } while(0)

#else // ENABLE_DEBUG

#define debug_log(...)
#define debug_printf(...)
static inline char * __attribute__((unused)) mc_btn_name(char * buf, int event) {
	sprintf(buf, "0x%08X", event);
	return buf;
}
#endif


#endif // DEBUG_H_
