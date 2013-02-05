/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "languages.h"
#include "macros.h"
#include "settings.h"

#include "menuoptions.h"

char *menuoptions_bool_strings[] = {
	[false] = LP_WORD(L_V_NO),
	[true]  = LP_WORD(L_V_YES),
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

char *menuoptions_btnactn_strings[BUTTON_ACTION_COUNT] = {
	[BUTTON_ACTION_NONE]         = LP_WORD(L_V_NONE),
	[BUTTON_ACTION_ISO]          = LP_WORD(L_V_INTISO),
	[BUTTON_ACTION_SCRIPT]       = LP_WORD(L_V_REPEAT),
	[BUTTON_ACTION_MLU]          = LP_WORD(L_I_MIRROR_LOCKUP),
	[BUTTON_ACTION_AEB]          = LP_WORD(L_I_AEB),
	[BUTTON_ACTION_HACK_MENU]    = LP_WORD(L_V_HACK_MENU),
	[BUTTON_ACTION_TOGGLE_FLASH] = LP_WORD(L_V_TOGGLE_FLASH),
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

type_LIST menuoptions_bool = {
	length : LENGTH(menuoptions_bool_strings),
	data   : menuoptions_bool_strings
};

type_LIST menuoptions_flash = {
	length : LENGTH(menuoptions_flash_strings),
	data   : menuoptions_flash_strings
};

type_LIST menuoptions_action = {
	length : LENGTH(menuoptions_action_strings),
	data   : menuoptions_action_strings
};

type_LIST menuoptions_logfile = {
	length : LENGTH(menuoptions_logfile_strings),
	data   : menuoptions_logfile_strings
};

type_LIST menuoptions_btnactn = {
	length : LENGTH(menuoptions_btnactn_strings),
	data   : menuoptions_btnactn_strings
};

type_LIST menuoptions_direction = {
	length : LENGTH(menuoptions_direction_strings),
	data   : menuoptions_direction_strings
};

type_LIST menuoptions_languages = {
	length : LENGTH(menuoptions_languages_strings),
	data   : menuoptions_languages_strings
};

type_LIST menuoptions_vformat = {
	length : LENGTH(menuoptions_vformat_strings),
	data   : menuoptions_vformat_strings
};

type_LIST menuoptions_scrind = {
	length : LENGTH(menuoptions_scrind_strings),
	data   : menuoptions_scrind_strings
};

type_LIST menuoptions_scrlcd = {
	length : LENGTH(menuoptions_scrlcd_strings),
	data   : menuoptions_scrlcd_strings
};

type_LIST menuoptions_qexp_weight = {
	length : LENGTH(menuoptions_qexp_weight_strings),
	data   : menuoptions_qexp_weight_strings
};

type_LIST menuoptions_digiso_steps = {
	length : LENGTH(menuoptions_digiso_steps_strings),
	data   : menuoptions_digiso_steps_strings
};
