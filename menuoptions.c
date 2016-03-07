#include <vxworks.h>

#include "languages.h"
#include "macros.h"
#include "settings.h"

#include "menuoptions.h"

char *menuoptions_bool_strings[] = {
	[FALSE] = LP_WORD(L_V_NO),
	[TRUE]  = LP_WORD(L_V_YES),
};

char *menuoptions_flash_strings[FLASH_MODE_COUNT] = {
	[FLASH_MODE_ENABLED]  = LP_WORD(L_V_ENABLED),
	[FLASH_MODE_DISABLED] = LP_WORD(L_V_DISABLED),
	[FLASH_MODE_EXTONLY]  = LP_WORD(L_V_EXT_ONLY),
};

char *menuoptions_action_strings[SHOT_ACTION_COUNT] = {
	[SHOT_ACTION_SHOT]     = LP_WORD(L_V_ONE_SHOT),
	[SHOT_ACTION_EXT_AEB]  = LP_WORD(L_V_EXT_AEB),
	[SHOT_ACTION_EFL_AEB]  = LP_WORD(L_V_EFL_AEB),
	[SHOT_ACTION_APT_AEB]  = LP_WORD(L_V_APT_AEB),
	[SHOT_ACTION_ISO_AEB]  = LP_WORD(L_V_ISO_AEB),
	[SHOT_ACTION_LONG_EXP] = LP_WORD(L_V_LEXP),
};

char *menuoptions_logfile_strings[LOGFILE_MODE_COUNT] = {
	[LOGFILE_MODE_OVERWRITE] = LP_WORD(L_V_OVERWRITE),
	[LOGFILE_MODE_NEW]       = LP_WORD(L_V_NEW),
	[LOGFILE_MODE_APPEND]    = LP_WORD(L_V_APPEND)
};

char *menuoptions_btnactn_strings[SHORTCUT_COUNT] = {
	[SHORTCUT_NONE]         = LP_WORD(L_V_NONE),
	[SHORTCUT_ISO]          = LP_WORD(L_V_INTISO),
	[SHORTCUT_SCRIPT]       = LP_WORD(L_V_REPEAT),
	[SHORTCUT_MLU]          = LP_WORD(L_I_MIRROR_LOCKUP),
	[SHORTCUT_AEB]          = LP_WORD(L_I_AEB),
	[SHORTCUT_HACK_MENU]    = LP_WORD(L_V_HACK_MENU),
	[SHORTCUT_FLASH]        = LP_WORD(L_V_TOGGLE_FLASH),
	[SHORTCUT_DISPLAY]      = LP_WORD(L_I_BUTTON_DISP),
#ifdef DEV_BTN_ACTION
	[SHORTCUT_DEV_BTN]      = "DevBtn (DO NOT USE)",
#endif
};

char *menuoptions_direction_strings[EAEB_DIRECTION_COUNT] = {
	[EAEB_DIRECTION_UP]   = "+",
	[EAEB_DIRECTION_DOWN] = "-",
	[EAEB_DIRECTION_BOTH] = "+/-",
};

char *menuoptions_languages_strings[] = { // Just some place-holders
	"00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29"
};

char *menuoptions_vformat_strings[] = {
	"25",
	"30",
	"50",
	"60"
};

char *menuoptions_scrind_strings[SCRIPT_INDICATOR_COUNT] = {
	[SCRIPT_INDICATOR_NONE]   = LP_WORD(L_V_NONE),
	[SCRIPT_INDICATOR_SLOW]   = LP_WORD(L_V_SLOW),
	[SCRIPT_INDICATOR_MEDIUM] = LP_WORD(L_V_MEDIUM),
	[SCRIPT_INDICATOR_FAST]   = LP_WORD(L_V_FAST),
};

char *menuoptions_scrlcd_strings[SCRIPT_LCD_COUNT] = {
	[SCRIPT_LCD_KEEP] = LP_WORD(L_V_KEEP),
	[SCRIPT_LCD_DIM]  = LP_WORD(L_V_DIM),
	[SCRIPT_LCD_OFF]  = LP_WORD(L_V_OFF),
};

char *menuoptions_qexp_weight_strings[QEXP_WEIGHT_COUNT] = {
	[QEXP_WEIGHT_NONE] = LP_WORD(L_V_NONE),
	[QEXP_WEIGHT_AV]   = LP_WORD(L_V_AV),
	[QEXP_WEIGHT_TV]   = LP_WORD(L_V_TV),
};

char *menuoptions_digiso_steps_strings[] = {
	[0] = "1/8 EV",
	[1] = "1/4 EV",
	[2] = "1/2 EV",
};

char *menuoptions_olcinv_steps_strings[] = {
	[0] = LP_WORD(L_V_OFF),
	[1] = "#1",
	[2] = "#2",
	[3] = "#3",
	[4] = "#4",
	[5] = "#5",
	[6] = "#6",
	[7] = "#7",
	[8] = "#8",
	[9] = "#9",
	[10] = "#10",
	[11] = "#11",
	[12] = "#12",
	[13] = "#13",
	[14] = "#14",
	[15] = "#15",
	[16] = "#16",
	[17] = "#17",
	[18] = "#18",
	[19] = "#19",
	[20] = "#20",
	[21] = "#21",
	[22] = "#22",
	[23] = "#23",
	[24] = "#24",
	[25] = "#25",
	[26] = "#26",
	[27] = "#27",
	[28] = "#28",
	[29] = "#29",
	[30] = "#30",
	[31] = "#31",
	[32] = "#32",
	[33] = "#33",
};

list_t menuoptions_bool         = LIST(menuoptions_bool_strings);
list_t menuoptions_flash        = LIST(menuoptions_flash_strings);
list_t menuoptions_action       = LIST(menuoptions_action_strings);
list_t menuoptions_logfile      = LIST(menuoptions_logfile_strings);
list_t menuoptions_btnactn      = LIST(menuoptions_btnactn_strings);
list_t menuoptions_direction    = LIST(menuoptions_direction_strings);
list_t menuoptions_languages    = LIST(menuoptions_languages_strings);
list_t menuoptions_vformat      = LIST(menuoptions_vformat_strings);
list_t menuoptions_scrind       = LIST(menuoptions_scrind_strings);
list_t menuoptions_scrlcd       = LIST(menuoptions_scrlcd_strings);
list_t menuoptions_qexp_weight  = LIST(menuoptions_qexp_weight_strings);
list_t menuoptions_digiso_steps = LIST(menuoptions_digiso_steps_strings);
list_t menuoptions_olcinv_steps = LIST(menuoptions_olcinv_steps_strings);

