#ifndef UTILS_H_
#define UTILS_H_

#define BEEP_LED_LENGTH 25

extern int ev_sgn(int ev);
extern int ev_inc(int ev);
extern int ev_dec(int ev);
extern int ev_add(int ying, int yang);
extern int ev_sub(int ying, int yang);

extern void ev_print(const char *dest, int ev);

extern int iso_next(int iso);
extern int iso_inc(int iso);
extern int iso_dec(int iso);

extern void beep();

extern char *release_count();

#endif /* UTILS_H_ */
