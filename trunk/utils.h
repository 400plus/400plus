/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef UTILS_H_
#define UTILS_H_

// it's slow
#undef FGETS_USE_SLOW

#include <sys/types.h>

typedef signed char ev_t;

#define BEEP_LED_LENGTH  25
#define INTERCOM_WAIT     5
#define EVENT_WAIT        5
#define RELEASE_WAIT    250

#define SHUTTER_LAG     125

extern ev_t ev_normalize(ev_t ev);

extern ev_t ev_inc(ev_t ev);
extern ev_t ev_dec(ev_t ev);
extern ev_t ev_add(ev_t ying, ev_t yang);
extern ev_t ev_sub(ev_t ying, ev_t yang);

extern char av_inc(char ev);
extern char av_dec(char ev);
extern char av_add(char ying, char yang);
extern char av_sub(char ying, char yang);

extern char tv_next(char ev);
extern char tv_prev(char ev);

extern char tv_inc(char ev);
extern char tv_dec(char ev);
extern char tv_add(char ying, char yang);
extern char tv_sub(char ying, char yang);

extern int iso_roll(int iso);
extern int iso_next(int iso);
extern int iso_prev(int iso);
extern int iso_inc(int iso);
extern int iso_dec(int iso);

extern void ev_print(char *dest, char ev);
extern void av_print(char *dest, int ev);
extern void tv_print(char *dest, int ev);

extern void iso_print(char *dest, int code);

extern void calculate_dof(int focal_length, int focus_distance, int av, char *min, char *max);

extern void beep();

extern void enter_factory_mode();
extern void exit_factory_mode();
extern void start_debug_mode();
extern void dump_log();
extern void dump_memory();
extern void dump_memory_after_5s();
extern void print_info();

extern int send_to_intercom(int message, int length, int parm);

extern void wait_for_camera();
extern void wait_for_capture();

extern int  shutter_release();
extern int  shutter_release_bulb(int time);

extern int  print_icu_info();
extern int  press_button(int button);

extern int remote_on();
extern int remote_off();

extern int display_on();
extern int display_off();

extern void led_flash(int delay);

extern int strlen_utf8(const char *);

// convert string to upper case in-place
extern void stoupper(char *s);

extern int timestamp();

char* strncpy0(char* dest, const char* src, size_t size);

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
