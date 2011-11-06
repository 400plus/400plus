#ifndef LANGUAGES_H_
#define LANGUAGES_H_

// we need MAX_WORD==32, but we use 64, because the UTF8 (cyrrilic langs) is 2 bytes per char
#define LP_MAX_WORD 64 // this is valid for the keys and section names too
#define LP_WORD(word) lang_pack_current[word]

#define LANGUAGE_PAIRS                                    \
	LANG_PAIR( P_400PLUS,            "400plus"            ) \
	LANG_PAIR( P_PARAMS,             "Parameters"         ) \
	LANG_PAIR( P_SHORTCUTS,          "Shortcuts"          ) \
	LANG_PAIR( P_SETTINGS,           "Settings"           ) \
	LANG_PAIR( P_SCRIPTS,            "Scripts"            ) \
	LANG_PAIR( P_INFO,               "Info"               ) \
	LANG_PAIR( P_RENAME,             "Rename"             ) \
	LANG_PAIR( P_DEVELOPERS,         "Developers' Menu"   ) \
	LANG_PAIR( P_PRESETS,            "Presets"            ) \
	LANG_PAIR( I_RELEASE_COUNT,      "Release count"      ) \
	LANG_PAIR( I_BODY_ID,            "Body ID"            ) \
	LANG_PAIR( I_VERSION,            "Version"            ) \
	LANG_PAIR( I_DUMP_LOG_TO_FILE,   "Dump log to file"   ) \
	LANG_PAIR( I_PRINT_INFO,         "Print info to log"  ) \
	LANG_PAIR( I_ENTER_FACTORY_MODE, "Enter factory Mode" ) \
	LANG_PAIR( I_EXIT_FACTORY_MODE,  "Exit  factory Mode" ) \
	LANG_PAIR( I_DEBUG_ON_POWERON,   "Debug on PowerOn"   ) \
	LANG_PAIR( I_LOGFILE_MODE,       "Log File Mode"      ) \
	LANG_PAIR( OFF,                "Off"                ) \
	LANG_PAIR( YES,                "Yes"                ) \
	LANG_PAIR( NO,                 "No"                 ) \
	LANG_PAIR( 2S,                 "2s"                 ) \
	LANG_PAIR( ENABLED,            "Enabled"            ) \
	LANG_PAIR( DISABLED,           "Disabled"           ) \
	LANG_PAIR( EXT_ONLY,           "Ext Only"           ) \
	LANG_PAIR( EXT_AEB,            "Ext. AEB"           ) \
	LANG_PAIR( ONE_SHOT,           "One Shot"           ) \
	LANG_PAIR( INTERVAL,           "Interval"           ) \
	LANG_PAIR( NO_LIMIT,           "No Limit"           ) \
	LANG_PAIR( RENAME,             "Rename"             ) \
	LANG_PAIR( LOAD_PRESETS,       "Load presets"       ) \
	LANG_PAIR( SAVE_PRESETS,       "Save presets"       ) \
	LANG_PAIR( PRESET_NAME,        "Preset"             ) \
	LANG_PAIR( DEVELOPER,          "Developer"          ) \
	LANG_PAIR( TEST_DIALOGS,       "Test the dialogs"   ) \
	LANG_PAIR( NEW,                "New"                ) \
	LANG_PAIR( OVERWRITE,          "Overwrite"          ) \
	LANG_PAIR( APPEND,             "Append"             ) \
	LANG_PAIR( DELAY,              "Delay"              ) \
	LANG_PAIR( ACTION,             "Action"             ) \
	LANG_PAIR( REPEAT,             "Repeat"             ) \
	LANG_PAIR( INSTANT,            "Instant"            ) \
	LANG_PAIR( FRAMES,             "Frames"             ) \
	LANG_PAIR( STEP_EV,            "Step (EV)"          ) \
	LANG_PAIR( MANUAL_L,           "Bulb min"           ) \
	LANG_PAIR( MANUAL_R,           "Bulb max"           ) \
	LANG_PAIR( TIME_S,             "Time (s)"           ) \
	LANG_PAIR( EAEB,               "EAEB"               ) \
	LANG_PAIR( SHOTS,              "Shots"              ) \
	LANG_PAIR( AV_COMP,            "AV comp"            ) \
	LANG_PAIR( FLASH_COMP,         "Flash comp"         ) \
	LANG_PAIR( AEB,                "AEB"                ) \
	LANG_PAIR( ISO_IN_VF,          "ISO in viewfinder"  ) \
	LANG_PAIR( SHORTCUTS_MENU,     "Shortcuts menu"     ) \
	LANG_PAIR( SAFETY_SHIFT,       "Safety Shift"       ) \
	LANG_PAIR( COLOR_TEMP_K,       "Color Temp. (K)"    ) \
	LANG_PAIR( USE_FLASH,          "Disable flash"      ) \
	LANG_PAIR( HANDWAVE,           "Handwave"           ) \
	LANG_PAIR( TIMER_SPACES,       "Timer   "           ) \
	LANG_PAIR( IR_REMOTE_ENABLE,   "IR remote enable"   ) \
	LANG_PAIR( IR_REMOTE_DELAY,    "IR remote delay"    ) \
	LANG_PAIR( SCRIPTS_SPACES,     "Scripts "           ) \
	LANG_PAIR( DIM_LCD_DOWN,       "LCD dim"            ) \
	LANG_PAIR( KEEP_POWER_ON,      "APO dsbl"           ) \
	LANG_PAIR( ISO,                "ISO"                ) \
	LANG_PAIR( EXTENDED_AEB,       "Extended AEB"       ) \
	LANG_PAIR( INTERVALOMETER,     "Intervalometer"     ) \
	LANG_PAIR( HAND_WAVING,        "Hand Waving"        ) \
	LANG_PAIR( SELF_TIMER,         "Self Timer"         ) \
	LANG_PAIR( AF_FLASH,           "AF Flash"           ) \
	LANG_PAIR( MIRROR_LOCKUP,      "Mirror Lockup"      ) \
	LANG_PAIR( FLASH_2ND_CURT,     "Flash 2curt"        ) \
	LANG_PAIR( PRESETS_ADEP,       "Use A-DEP"          ) \
	LANG_PAIR( PRESETS_CAMERA,     "Camera"             ) \
	LANG_PAIR( PRESETS_400PLUS,    "400plus"            ) \
	LANG_PAIR( PRESETS_SETTINGS,   "Settings"           ) \
	LANG_PAIR( PRESETS_IMAGE,      "Image"              ) \
	LANG_PAIR( PRESETS_CFN,        "Custom Fn"          ) \
	LANG_PAIR( AUTOISO,            "AutoISO "           ) \
	LANG_PAIR( AUTOISO_ENABLE,     "Enable"             ) \
	LANG_PAIR( AUTOISO_MINISO,     "Min ISO"            ) \
	LANG_PAIR( AUTOISO_MAXISO,     "Max ISO"            ) \
	LANG_PAIR( AUTOISO_MINTV,      "Min Tv"             ) \
	LANG_PAIR( AUTOISO_MAXAV,      "Max Av"             ) \

enum LANG_WORDS_ENUM {
	#define LANG_PAIR(key, val) L_##key,
	LANGUAGE_PAIRS
	#undef LANG_PAIR
	// this will define the keys enum, eg:
	// L_FREE_SPACE,
	// L_RELEASE_COUNT,
	// etc...

	L_COUNT,
	L_FIRST = 0,
	L_LAST  = L_COUNT - 1
};

extern const char *lang_pack_keys[L_COUNT];
extern       char  lang_pack_current[L_COUNT][LP_MAX_WORD];

extern void lang_pack_init();
extern void lang_pack_config();

#endif // LANGUAGES_H_
