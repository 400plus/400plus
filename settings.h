#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x13

typedef enum {
	SHOT_ACTION_SHOT,
	SHOT_ACTION_EAEB,
	SHOT_ACTION_INTERVAL,
	SHOT_ACTION_COUNT,
	SHOT_ACTION_FIRST = 0,
	SHOT_ACTION_LAST  = SHOT_ACTION_COUNT - 1
} type_SHOT_ACTION;

typedef struct {
	int iso_in_viewfinder;
	int eaeb_frames;
	int eaeb_delay;
	int eaeb_ev;
	int eaeb_m_min;
	int eaeb_m_max;
	int interval_delay;
	int interval_time;
	int interval_eaeb;
	int interval_shots;
	int wave_delay;
    int wave_action;
    int wave_repeat;
    int wave_instant;
	int color_temp;
	int av_comp;
	int flash_comp;
	int aeb_ev;
	int safety_shift;
	int emit_flash;
	int af_flash;
	int remote_delay;
	int timer_timeout;
	int timer_action;
} type_SETTINGS;

extern type_SETTINGS settings;

extern void settings_read();
extern void settings_write();
extern void settings_apply();

#endif /* SETTINGS_H_ */
