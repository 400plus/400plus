#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILENAME "SETTINGS"
#define SETTINGS_VERSION  0x4A

#define CCT_COUNT 16

#include "languages.h"
#include "menu_main.h"
#include "menu_params.h"
#include "menu_scripts.h"
#include "menu_info.h"
#include "menu_developer.h"
#include "menu_settings.h"

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
	SHORTCUT_NONE,
	SHORTCUT_ISO,
	SHORTCUT_SCRIPT,
	SHORTCUT_MLU,
	SHORTCUT_AEB,
	SHORTCUT_HACK_MENU,
	SHORTCUT_FLASH,
	SHORTCUT_DISPLAY,
#ifdef DEV_BTN_ACTION
	SHORTCUT_DEV_BTN,
#endif
	SHORTCUT_COUNT,
	SHORTCUT_FIRST = 0,
	SHORTCUT_LAST  = SHORTCUT_COUNT - 1
} shortcut_t;

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
	int shortcut_jump;
	int shortcut_trash;
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
	int invert_olc;
} settings_t;

extern settings_t settings;

typedef struct {
	int main       [MENUPAGE_COUNT];
	int params     [MENUPAGE_PARAMS_COUNT];
	int scripts    [MENUPAGE_SCRIPTS_COUNT];
	int info       [MENUPAGE_INFO_COUNT];
	int developer  [MENUPAGE_DEVEL_COUNT];
	int settings   [MENUPAGE_SETTINGS_COUNT];
	int named_temps[CCT_COUNT];
} menu_order_t;

extern menu_order_t menu_order;

typedef struct {
	int  initd;
	int  temps[CCT_COUNT];
	char names[CCT_COUNT][LP_MAX_WORD];
} named_temps_t;

extern named_temps_t named_temps;

extern int  settings_read(void);
extern void settings_write(void);
extern void settings_apply(void);
extern void settings_restore(void);

extern void named_temps_init(menu_t *menu);

#endif /* SETTINGS_H_ */
