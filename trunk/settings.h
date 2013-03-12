/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x49

#define CCT_COUNT 16

#include "languages.h"

typedef enum {
	SHOT_ACTION_SHOT,
	SHOT_ACTION_EXT_AEB,
	SHOT_ACTION_EFL_AEB,
	SHOT_ACTION_APT_AEB,
	SHOT_ACTION_ISO_AEB,
	SHOT_ACTION_LONG_EXP,
	SHOT_ACTION_COUNT,
	SHOT_ACTION_FIRST = 0,
	SHOT_ACTION_LAST  = SHOT_ACTION_COUNT - 1
} shot_action_t;

typedef enum {
	BUTTON_ACTION_NONE,
	BUTTON_ACTION_ISO,
	BUTTON_ACTION_SCRIPT,
	BUTTON_ACTION_MLU,
	BUTTON_ACTION_AEB,
	BUTTON_ACTION_HACK_MENU,
	BUTTON_ACTION_TOGGLE_FLASH,
	BUTTON_ACTION_COUNT,
	BUTTON_ACTION_FIRST = 0,
	BUTTON_ACTION_LAST  = BUTTON_ACTION_COUNT - 1
} button_action_t;

typedef enum {
	EAEB_DIRECTION_UP,
	EAEB_DIRECTION_DOWN,
	EAEB_DIRECTION_BOTH,
	EAEB_DIRECTION_COUNT,
	EAEB_DIRECTION_FIRST = 0,
	EAEB_DIRECTION_LAST  = EAEB_DIRECTION_COUNT - 1
} eaeb_direction_t;

typedef enum {
	SCRIPT_INDICATOR_NONE,
	SCRIPT_INDICATOR_SLOW,
	SCRIPT_INDICATOR_MEDIUM,
	SCRIPT_INDICATOR_FAST,
	SCRIPT_INDICATOR_COUNT,
	SCRIPT_INDICATOR_FIRST = 0,
	SCRIPT_INDICATOR_LAST  = SCRIPT_INDICATOR_COUNT - 1
} script_indicator_t;

typedef enum {
	SCRIPT_LCD_KEEP,
	SCRIPT_LCD_DIM,
	SCRIPT_LCD_OFF,
	SCRIPT_LCD_COUNT,
	SCRIPT_LCD_FIRST = 0,
	SCRIPT_LCD_LAST  = SCRIPT_LCD_COUNT - 1
} script_lcd_t;

typedef enum {
	LOGFILE_MODE_OVERWRITE,
	LOGFILE_MODE_NEW,
	LOGFILE_MODE_APPEND,
	LOGFILE_MODE_COUNT,
	LOGFILE_MODE_FIRST = 0,
	LOGFILE_MODE_LAST  = LOGFILE_MODE_COUNT - 1
} logfile_mode_t;

typedef enum {
	FLASH_MODE_ENABLED,
	FLASH_MODE_DISABLED,
	FLASH_MODE_EXTONLY,
	FLASH_MODE_COUNT,
	FLASH_MODE_FIRST = 0,
	FLASH_MODE_LAST  = FLASH_MODE_COUNT - 1
} flash_mode_t;

typedef enum {
	QEXP_WEIGHT_NONE,
	QEXP_WEIGHT_AV,
	QEXP_WEIGHT_TV,
	QEXP_WEIGHT_COUNT,
	QEXP_WEIGHT_FIRST = 0,
	QEXP_WEIGHT_LAST  = QEXP_WEIGHT_COUNT - 1
} qexp_weight_t;

typedef struct {
	int use_dpad;
	int autoiso_enable;
	int autoiso_miniso;
	int autoiso_maxiso;
	int autoiso_mintv;
	int autoiso_maxav;
	int autoiso_relaxed;
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
	int apt_aeb_delay;
	int apt_aeb_frames;
	int apt_aeb_ev;
	int apt_aeb_direction;
	int iso_aeb_delay;
	int iso_aeb[5];
	int interval_delay;
	int interval_time;
	int interval_action;
	int interval_shots;
	int bramp_delay;
	int bramp_time;
	int bramp_shots;
	int bramp_exp;
	int bramp_ramp_t;
	int bramp_ramp_s;
	int bramp_ramp_exp;
	int bramp_ramp_time;
	int wave_delay;
	int wave_action;
	int wave_repeat;
	int wave_instant;
	int lexp_delay;
	int lexp_time;
	int remote_delay;
	int timer_timeout;
	int timer_action;
	int keep_power_on;
	int review_off;
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
	int digital_iso_step;
	int menu_wrap;
	int menu_navmain;
	int menu_entermain;
	int menu_autosave;
	int qexp_mintv;
	int qexp_weight;
	int persist_aeb;
} settings_t;

extern settings_t settings;

typedef struct {
	int main       [10];
	int params     [10];
	int scripts    [10];
	int info       [10];
	int developer  [10];
	int settings   [10];
	int named_temps[CCT_COUNT];
} menu_order_t;

extern menu_order_t menu_order;

typedef struct {
	int  initd;
	int  temps[CCT_COUNT];
	char names[CCT_COUNT][LP_MAX_WORD];
} named_temps_t;

extern named_temps_t named_temps;

extern int  settings_read();
extern void settings_write();
extern void settings_apply();
extern void settings_restore();

extern void named_temps_init();

#endif /* SETTINGS_H_ */
