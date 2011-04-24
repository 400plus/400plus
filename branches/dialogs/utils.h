#ifndef UTILS_H_
#define UTILS_H_

#define BEEP_LED_LENGTH 25
#define INTERCOM_WAIT    0
#define EVENT_WAIT       0

extern int ev_sgn(int ev);
extern int ev_inc(int ev);
extern int ev_dec(int ev);
extern int ev_add(int ying, int yang);
extern int ev_sub(int ying, int yang);

extern void ev_print(const char *dest, int ev);

extern int iso_roll(int iso);
extern int iso_next(int iso);
extern int iso_prev(int iso);
extern int iso_inc(int iso);
extern int iso_dec(int iso);

extern void iso_display(const char *buffer, int iso);

extern void beep();

extern void enter_factory_mode();
extern void exit_factory_mode();
extern void start_debug_mode();

extern int  send_to_intercom(int message, int length, int parm);
extern int  shutter_release();
extern int  print_icu_info();
extern int  press_button(int button);
extern void led_flash(int delay);

#endif /* UTILS_H_ */
