/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef EXPOSURE_H_
#define EXPOSURE_H_

typedef   signed char ec_t;
typedef unsigned char ev_t;
typedef unsigned char av_t;
typedef unsigned char tv_t;

#define EV_CODE(val, sub)  (0010 * (val) + (sub))

#define EV_VAL(code)  ((code) / 0010)
#define EV_SUB(code)  ((code) - 0010 * EV_VAL(code))

extern ec_t ec_normalize(ec_t ec);

extern ec_t ec_inc(ec_t ev);
extern ec_t ec_dec(ec_t ev);
extern ec_t ec_add(ec_t ying, ec_t yang);
extern ec_t ec_sub(ec_t ying, ec_t yang);

extern void ec_print(char *dest, ec_t ec);

extern av_t av_add(av_t ying, av_t yang);
extern av_t av_sub(av_t ying, av_t yang);
extern av_t av_inc(av_t av);
extern av_t av_dec(av_t av);

extern void av_print(char *dest, av_t av);

extern tv_t tv_add(tv_t ying, tv_t yang);
extern tv_t tv_sub(tv_t ying, tv_t yang);
extern tv_t tv_inc(tv_t tv);
extern tv_t tv_dec(tv_t tv);

extern tv_t bulb_next(tv_t tv);
extern tv_t bulb_prev(tv_t tv);

extern void tv_print  (char *dest, tv_t tv);
extern void bulb_print(char *dest, tv_t tv);

extern int iso_roll(int iso);
extern int iso_next(int iso);
extern int iso_prev(int iso);
extern int iso_inc(int iso);
extern int iso_dec(int iso);

extern void iso_print(char *dest, int code);

#endif /* EXPOSURE_H_ */
