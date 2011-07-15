#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x1C

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
	int eaeb_tv_min;
	int eaeb_tv_max;
	int interval_delay;
	int interval_time;
	int interval_eaeb;
	int interval_shots;
	int wave_delay;
	int wave_action;
	int wave_repeat;
	int wave_instant;
	int remote_delay;
	int timer_timeout;
	int timer_action;
	int shortcuts_order[10];
	int shortcuts_menu;
	int dim_lcd_down;
	int keep_power_on;
} type_SETTINGS;

extern type_SETTINGS settings;

extern int  settings_read();
extern void settings_write();
extern void settings_apply();

#endif /* SETTINGS_H_ */
