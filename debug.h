#ifndef DEBUG_H_
#define DEBUG_H_

#include "firmware.h"
#include "mainctrl.h"
#include "utils.h"

typedef enum {
	DEBUG_GENERIC    = 0x00, // +SFACT
	DEBUG_MAIN       = 0x01, // +MC +TEST
	DEBUG_STM_SSM    = 0x08, // +AvailShots +Lens +AVS
	DEBUG_SCP        = 0x09, // +SSMain
	DEBUG_SDV        = 0x0A, // develop?
	DEBUG_SRC        = 0x0B,
	DEBUG_RSS        = 0x10, // maybe ??
	DEBUG_GUI        = 0x18,
} canon_debug_class_t;

#ifdef ENABLE_DEBUG

#define debug_log(f, p...) printf_log(8, 8, "[400plus] %s[%d]: " f, __FILE__, __LINE__, ##p)

#define blink_cycles 1000000
#define blink_red()  do { int i; LEDRED  = LEDON; for (i=0;i<blink_cycles; i++); LEDRED  = LEDOFF; for (i=0;i<blink_cycles; i++); } while(0)
#define blink_blue() do { int i; LEDBLUE = LEDON; for (i=0;i<blink_cycles; i++); LEDBLUE = LEDOFF; for (i=0;i<blink_cycles; i++); } while(0)

const char * debug_mc_name(int event);
const char * debug_btn_name(int btn);
const char * debug_gui_name(int event);

void dump_dpr_data(void);

#else // ENABLE_DEBUG

#define debug_log(...)

#endif // ENABLE_DEBUG

extern void dump_log            (void);
extern void dump_memory         (void);
extern void dump_memory_after_5s(void);

extern void print_info(void);

#endif // DEBUG_H_
