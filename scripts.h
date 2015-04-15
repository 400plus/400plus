#ifndef SCRIPTS_H_
#define SCRIPTS_H_

// Time between tries while waiting for user
#define WAIT_USER_ACTION 100

// Feedback timing
#define FEEDBACK_LENGTH    25
#define FEEDBACK_INTERVAL 500

// Pooling time while delaying script
#define SCRIPT_DELAY_TIME 250

// Standard delay before starting (2s)
#define SCRIPT_DELAY_START 2 * TIME_RESOLUTION

// Minimum number of shots available on card
#define SCRIPT_MIN_SHOTS 3

// Bulb ramping limits
#define BRAMP_MAX_INTERVAL 18000
#define BRAMP_MAX_EXPOSURE 18000

#define BRAMP_MIN_INTERVAL   9
#define BRAMP_MIN_EXPOSURE 999

typedef enum {
	SCRIPT_NONE,
	SCRIPT_EXT_AEB,
	SCRIPT_ISO_AEB,
	SCRIPT_EFL_AEB,
	SCRIPT_APT_AEB,
	SCRIPT_INTERVAL,
	SCRIPT_BRAMP,
	SCRIPT_WAVE,
	SCRIPT_TIMER,
	SCRIPT_LONG_EXP,
	SCRIPT_COUNT,
	SCRIPT_FIRST = 0,
	SCRIPT_LAST  = SCRIPT_COUNT - 1
} script_t;

extern void script_ext_aeb   (void);
extern void script_efl_aeb   (void);
extern void script_apt_aeb   (void);
extern void script_iso_aeb   (void);
extern void script_interval  (void);
extern void script_bramp     (void);
extern void script_wave      (void);
extern void script_self_timer(void);
extern void script_long_exp  (void);

extern void script_restore(void);

#endif /* SCRIPTS_H_ */
