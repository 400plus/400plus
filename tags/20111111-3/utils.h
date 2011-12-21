#ifndef UTILS_H_
#define UTILS_H_

// it's slow
#undef FGETS_USE_SLOW

#include "types.h"

#define BEEP_LED_LENGTH  25
#define INTERCOM_WAIT     5
#define EVENT_WAIT        5
#define RELEASE_WAIT    100


extern int ev_sgn(int ev);
extern int ev_inc(int ev);
extern int ev_dec(int ev);
extern int ev_add(int ying, int yang);
extern int ev_sub(int ying, int yang);

extern int av_inc(int ev);
extern int av_dec(int ev);

extern int tv_next(int ev);
extern int tv_prev(int ev);
extern int tv_inc(int ev);
extern int tv_dec(int ev);
extern int tv_add(int ying, int yang);
extern int tv_sub(int ying, int yang);

extern int iso_roll(int iso);
extern int iso_next(int iso);
extern int iso_prev(int iso);
extern int iso_inc(int iso);
extern int iso_dec(int iso);

extern void ev_print(char *dest, int ev);
extern void av_print(char *dest, int ev);
extern void tv_print(char *dest, int ev);

extern void iso_print(char *dest, int code);

extern void beep();

extern void enter_factory_mode();
extern void exit_factory_mode();
extern void start_debug_mode();
extern void dump_log();
extern void print_info();

extern int  send_to_intercom(int message, int length, int parm);
extern int  shutter_release();
extern int  shutter_release_bulb(int time_ms);
extern int  press_button(int button);

extern int remote_on();
extern int remote_off();

extern int display_on();
extern int display_off();

extern void led_flash(int delay);

extern int strlen_utf8(const char *);

// convert string to upper case in-place
extern void stoupper(char *s);

#ifdef FGETS_USE_SLOW
// this version will read byte-by-byte ... it is slow
char * my_fgets_simple_but_slow(char *s, int n, int fd);
#define my_fgets_init() do { } while (0)
#define my_fgets my_fgets_simple_but_slow
#else
// WARNING: please read the comments in utils.c about this routine.
// though it is faster than reading byte-by-byte, it has a special init too.
char * my_fgets_faster(char *s, int n, int fd);
#define my_fgets_init() my_fgets_faster(NULL, 0, -1)
#define my_fgets my_fgets_faster
#endif

#endif /* UTILS_H_ */
