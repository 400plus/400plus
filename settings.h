/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x3C

typedef enum {
	SHOT_ACTION_SHOT,
	SHOT_ACTION_EXT_AEB,
	SHOT_ACTION_EFL_AEB,
	SHOT_ACTION_ISO_AEB,
	SHOT_ACTION_LONG_EXP,
	SHOT_ACTION_COUNT,
	SHOT_ACTION_FIRST = 0,
	SHOT_ACTION_LAST  = SHOT_ACTION_COUNT - 1
} type_SHOT_ACTION;

typedef enum {
	BUTTON_ACTION_NONE,
	BUTTON_ACTION_ISO,
	BUTTON_ACTION_SCRIPT,
	BUTTON_ACTION_MLU,
	BUTTON_ACTION_AEB,
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

typedef enum {
	SCRIPT_INDICATOR_NONE,
	SCRIPT_INDICATOR_SLOW,
	SCRIPT_INDICATOR_MEDIUM,
	SCRIPT_INDICATOR_FAST,
	SCRIPT_INDICATOR_COUNT,
	SCRIPT_INDICATOR_FIRST = 0,
	SCRIPT_INDICATOR_LAST  = SCRIPT_INDICATOR_COUNT - 1
} type_SCRIPT_INDICATOR;

typedef enum {
	SCRIPT_LCD_KEEP,
	SCRIPT_LCD_DIM,
	SCRIPT_LCD_OFF,
	SCRIPT_LCD_COUNT,
	SCRIPT_LCD_FIRST = 0,
	SCRIPT_LCD_LAST  = SCRIPT_LCD_COUNT - 1
} type_SCRIPT_LCD;

typedef enum {
	LOGFILE_MODE_OVERWRITE,
	LOGFILE_MODE_NEW,
	LOGFILE_MODE_APPEND,
	LOGFILE_MODE_COUNT,
	LOGFILE_MODE_FIRST = 0,
	LOGFILE_MODE_LAST  = LOGFILE_MODE_COUNT - 1
} type_LOGFILE_MODE;

typedef enum {
	FLASH_MODE_ENABLED,
	FLASH_MODE_DISABLED,
	FLASH_MODE_EXTONLY,
	FLASH_MODE_COUNT,
	FLASH_MODE_FIRST = 0,
	FLASH_MODE_LAST  = FLASH_MODE_COUNT - 1
} type_FLASH_MODE;

typedef struct {
	int iso_in_viewfinder;
	int autoiso_enable;
	int autoiso_miniso;
	int autoiso_maxiso;
	int autoiso_mintv;
	int autoiso_maxav;
	int eaeb_delay;
	int eaeb_frames;
	int eaeb_ev;
	int eaeb_tv_min;
	int eaeb_tv_max;
	int eaeb_direction;
	int efl_aeb_delay;
	int efl_aeb_frames;
	int efl_aeb_ev;
	int efl_aeb_direction;
	int iso_aeb_delay;
	int iso_aeb[5];
	int interval_delay;
	int interval_time;
	int interval_action;
	int interval_shots;
	int wave_delay;
	int wave_action;
	int wave_repeat;
	int wave_instant;
	int lexp_delay;
	int lexp_time;
	int remote_delay;
	int timer_timeout;
	int timer_action;
	int main_order[10];
	int params_order[10];
	int scripts_order[10];
	int info_order[10];
	int developer_order[10];
	int settings_order[10];
	int keep_power_on;
	int script_lcd;
	int script_indicator;
	int debug_on_poweron;
	int logfile_mode;
	int remote_enable;
	int developers_menu;
	int button_jump;
	int button_trash;
	int button_disp;
	int language;
	int menu_wrap;
	int menu_navmain;
	int menu_entermain;
} type_SETTINGS;

extern type_SETTINGS settings;

extern int  settings_read();
extern void settings_write();
extern void settings_apply();
extern void settings_restore();

#endif /* SETTINGS_H_ */
