#ifndef EXPOSURE_H_
#define EXPOSURE_H_

typedef   signed char ec_t;
typedef unsigned char ev_t;
typedef unsigned char av_t;
typedef unsigned char tv_t;
typedef unsigned char iso_t;

#define EV_CODE(val, sub)  (0010 * (val) + (sub))

#define EV_VAL(code)  ((code) / 0010)
#define EV_SUB(code)  ((code) - 0010 * EV_VAL(code))

#define EV_MINUS(code) (0400 - (code))
#define EV_TRUNC(code) EV_CODE(EV_VAL(code), 0)
#define EV_ROUND(code) EV_TRUNC(code + EV_CODE(0, 4))

#define EV_ZERO EV_CODE(0, 0)  //  0EV
#define EV_STEP EV_CODE(0, DPData.cf_explevel_inc_third ? 4 : 3) // 1/3 or 1/5

#define EC_ZERO    EV_CODE(  0, 0)  //   0EV
#define EC_MIN     EV_CODE( -6, 0)  //  +6EV
#define EC_MAX     EV_CODE( +6, 0)  //  -6EV
#define EC_MIN_EXT EV_CODE(-15, 0)  // -15EV
#define EC_MAX_EXT EV_CODE(+15, 0)  // +15EV

#define AV_MIN EV_CODE( 1, 0)  // f/1.0
#define AV_MAX EV_CODE(13, 0)  // f/64

#define TV_MIN EV_CODE( 2, 0)  // 30"
#define TV_SEC EV_CODE( 7, 0)  // 1s
#define TV_MAX EV_CODE(19, 0)  // 1/4000s

// We use a special "BULB" code to store large values for the EAEB script
#define TV_BULB(code) ((code) + 0100)               // From Tv values to BULB values
#define BULB_TV(code) ((code) - 0100)               // From BULB values to Tv values
#define BULB_MN(code) (1 << ((0110 - code) / 0010)) // From BULB values to minutes

#define BULB_MIN 0040  // 30'
#define BULB_MAX 0330  // 1/4000s
#define BULB_VAL 0120  // 30"

#define ISO_MIN EV_CODE( 9, 0)
#define ISO_MAX EV_CODE(13, 0)
#define ISO_EXT EV_CODE(13, 7)

#define ISO_100  EV_CODE( 9, 0)
#define ISO_200  EV_CODE(10, 0)
#define ISO_400  EV_CODE(11, 0)
#define ISO_800  EV_CODE(12, 0)
#define ISO_1600 EV_CODE(13, 0)

extern ev_t ev_time     (int s);
extern ev_t ev_normalize(ev_t ec);
extern ec_t ec_normalize(ec_t ec);

extern ec_t ec_inc(ec_t ev, int extended);
extern ec_t ec_dec(ec_t ev, int extended);
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

extern iso_t iso_next(iso_t iso);
extern iso_t iso_prev(iso_t iso);
extern iso_t iso_inc (iso_t iso);
extern iso_t iso_dec (iso_t iso);

extern void iso_print(char *dest, iso_t code);

#endif /* EXPOSURE_H_ */
