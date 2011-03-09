#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x0D

typedef enum {
	DP_ACTION_DISABLED,
	DP_ACTION_INTERMEDIATE_ISO,
	DP_ACTION_EXTENDED_AEB,
	DP_ACTION_INTERVAL,
	DP_ACTION_WAVE,
	DP_ACTION_COUNT,
	DP_ACTION_FIRST = 0,
	DP_ACTION_LAST  = DP_ACTION_COUNT - 1
} type_DP_ACTION;

typedef enum {
	WAVE_ACTION_SHOT,
	WAVE_ACTION_EAEB,
	WAVE_ACTION_INTERVAL,
	WAVE_ACTION_COUNT,
	WAVE_ACTION_FIRST = 0,
	WAVE_ACTION_LAST  = WAVE_ACTION_COUNT - 1
} type_WAVE_ACTION;

typedef struct {
	int iso_in_viewfinder;
	int dp_action;
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
	int white_balance;
	int color_temp;
	int av_comp;
	int flash_comp;
	int aeb_ev;
	int safety_shift;
	int not_emit_flash;
	int not_af_flash;
	int remote_delay;
} type_SETTINGS;

extern type_SETTINGS settings;

extern void settings_read();
extern void settings_write();
extern void settings_apply();

#endif /* SETTINGS_H_ */
