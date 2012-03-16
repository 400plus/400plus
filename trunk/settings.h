#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x32

typedef enum {
	SHOT_ACTION_SHOT,
	SHOT_ACTION_EXT_AEB,
	SHOT_ACTION_EFL_AEB,
	SHOT_ACTION_ISO_AEB,
	SHOT_ACTION_COUNT,
	SHOT_ACTION_FIRST = 0,
	SHOT_ACTION_LAST  = SHOT_ACTION_COUNT - 1
} type_SHOT_ACTION;

typedef enum {
	BUTTON_ACTION_NONE,
	BUTTON_ACTION_ISO,
	BUTTON_ACTION_SCRIPT,
	BUTTON_ACTION_HACK_MENU,
	BUTTON_ACTION_COUNT,
	BUTTON_ACTION_FIRST = 0,
	BUTTON_ACTION_LAST  = BUTTON_ACTION_COUNT - 1
} type_BUTTON_ACTION;

typedef enum {
	EAEB_DIRECTION_UP,
	EAEB_DIRECTION_DOWN,
	EAEB_DIRECTION_BOTH,
	EAEB_DIRECTION_COUNT,
	EAEB_DIRECTION_FIRST = 0,
	EAEB_DIRECTION_LAST  = EAEB_DIRECTION_COUNT - 1
} type_EAEB_DIRECTION;

typedef struct {
	int iso_in_viewfinder;
	int autoiso_enable;
	int autoiso_miniso;
	int autoiso_maxiso;
	int autoiso_mintv;
	int autoiso_maxav;
	int eaeb_frames;
	int eaeb_delay;
	int eaeb_ev;
	int eaeb_tv_min;
	int eaeb_tv_max;
	int eaeb_direction;
	int efl_aeb_frames;
	int efl_aeb_delay;
	int efl_aeb_ev;
	int efl_aeb_direction;
	int iso_aeb[5];
	int interval_delay;
	int interval_time;
	int interval_action;
	int interval_shots;
	int wave_delay;
	int wave_action;
	int wave_repeat;
	int wave_instant;
	int remote_delay;
	int timer_timeout;
	int timer_action;
	int main_order[10];
	int params_order[10];
	int shortcuts_order[10];
	int scripts_order[10];
	int info_order[10];
	int developer_order[10];
	int settings_order[10];
	int dim_lcd_down;
	int keep_power_on;
	int debug_on_poweron;
	int logfile_mode;
	int remote_enable;
	int developers_menu;
	int button_jump;
} type_SETTINGS;

extern type_SETTINGS settings;

extern int  settings_read();
extern void settings_write();
extern void settings_apply();

#endif /* SETTINGS_H_ */
