#ifndef LANGUAGES_H_
#define LANGUAGES_H_

// we need MAX_WORD==32, but we use 64, because the UTF8 (cyrrilic langs) is 2 bytes per char
#define LP_MAX_WORD 64 // this is valid for the keys and section names too
#define LP_WORD(word) lang_pack_current[word]
#define MAX_LANGUAGES 30 // max languages we can choose from

#define LANGUAGES_FILENAME "LANGUAGES.INI"

// * P_ are page names.
// * I_ are menu items.
// * V_ are item values.
// * S_ are sub-menus.
#define LANGUAGE_PAIRS \
	LANG_PAIR( P_400PLUS,            "400plus"                   ) \
	LANG_PAIR( P_PARAMS,             "Parameters"                ) \
	LANG_PAIR( P_SETTINGS,           "Settings"                  ) \
	LANG_PAIR( P_SCRIPTS,            "Scripts"                   ) \
	LANG_PAIR( P_INFO,               "Info"                      ) \
	LANG_PAIR( P_RENAME,             "Rename"                    ) \
	LANG_PAIR( P_DEVELOPERS,         "Developers' Menu"          ) \
	LANG_PAIR( P_CMODES,             "Custom modes"              ) \
	LANG_PAIR( I_RELEASE_COUNT,      "Release count"             ) \
	LANG_PAIR( I_VERSION,            "Version"                   ) \
	LANG_PAIR( I_BODY_ID,            "Body ID"                   ) \
	LANG_PAIR( I_FIRMWARE,           "Firmware"                  ) \
	LANG_PAIR( I_OWNER,              "Owner"                     ) \
	LANG_PAIR( I_DUMP_MEMORY,        "Dump RAM after 5s"         ) \
	LANG_PAIR( I_MEMSPY_ENABLE,      "MemSpy Enable"             ) \
	LANG_PAIR( I_MEMSPY_DISABLE,     "MemSpy Disable"            ) \
	LANG_PAIR( I_DUMP_LOG_TO_FILE,   "Dump log to file"          ) \
	LANG_PAIR( I_PRINT_INFO,         "Print info to log"         ) \
	LANG_PAIR( I_ENTER_FACTORY_MODE, "Enter factory Mode"        ) \
	LANG_PAIR( I_EXIT_FACTORY_MODE,  "Exit  factory Mode"        ) \
	LANG_PAIR( I_TEST_DIALOGS,       "Test dialogs"              ) \
	LANG_PAIR( I_DEBUG_ON_POWERON,   "Debug on PowerOn"          ) \
	LANG_PAIR( I_LOGFILE_MODE,       "Log File Mode"             ) \
	LANG_PAIR( I_AF_FLASH,           "AF Flash"                  ) \
	LANG_PAIR( I_MIRROR_LOCKUP,      "Mirror Lockup"             ) \
	LANG_PAIR( I_FLASH_2ND_CURT,     "Flash 2nd curtain"         ) \
	LANG_PAIR( I_SAVE,               "Save"                      ) \
	LANG_PAIR( I_ASSIGN,             "Assign"                    ) \
	LANG_PAIR( I_UNASSIGN,           "Unassign"                  ) \
	LANG_PAIR( I_UPDATE,             "Update"                    ) \
	LANG_PAIR( I_RENAME,             "Rename"                    ) \
	LANG_PAIR( I_DELETE,             "Delete"                    ) \
	LANG_PAIR( S_AUTOISO,            "AutoISO"                   ) \
	LANG_PAIR( I_AUTOISO_ENABLE,     "Enable"                    ) \
	LANG_PAIR( I_AUTOISO_MINISO,     "Min ISO"                   ) \
	LANG_PAIR( I_AUTOISO_MAXISO,     "Max ISO"                   ) \
	LANG_PAIR( I_AUTOISO_MINTV,      "Min Tv"                    ) \
	LANG_PAIR( I_AUTOISO_MAXAV,      "Max Av"                    ) \
	LANG_PAIR( I_AUTOISO_RELAX,      "Relaxed"                   ) \
	LANG_PAIR( S_FLASH,              "Flash"                     ) \
	LANG_PAIR( S_IR,                 "Infrared Remote"           ) \
	LANG_PAIR( I_ISO,                "ISO"                       ) \
	LANG_PAIR( I_AV_COMP,            "AV comp."                  ) \
	LANG_PAIR( I_FLASH_COMP,         "Flash comp."               ) \
	LANG_PAIR( I_USE_FLASH,          "Disable flash"             ) \
	LANG_PAIR( I_AEB,                "AEB"                       ) \
	LANG_PAIR( I_COLOR_TEMP_K,       "Color temp. (K)"           ) \
	LANG_PAIR( I_DELAY,              "2s Delay"                  ) \
	LANG_PAIR( I_TIME,               "Time (s)"                  ) \
	LANG_PAIR( I_ACTION,             "Action"                    ) \
	LANG_PAIR( I_REPEAT,             "Repeat"                    ) \
	LANG_PAIR( I_INSTANT,            "Instant"                   ) \
	LANG_PAIR( I_FRAMES,             "Frames"                    ) \
	LANG_PAIR( I_STEP_EV,            "Step (EV)"                 ) \
	LANG_PAIR( I_MANUAL_L,           "Bulb min"                  ) \
	LANG_PAIR( I_MANUAL_R,           "Bulb max"                  ) \
	LANG_PAIR( I_INTERVAL,           "Interval"                  ) \
	LANG_PAIR( I_EXPOSURE,           "Exposure"                  ) \
	LANG_PAIR( I_RAMP_T,             "Ramp size (time)"          ) \
	LANG_PAIR( I_RAMP_S,             "Ramp size (shots)"         ) \
	LANG_PAIR( I_RAMPING_EXP,        "Ramping (exposure)"        ) \
	LANG_PAIR( I_RAMPING_TIME,       "Ramping (interval)"        ) \
	LANG_PAIR( I_EAEB,               "EAEB"                      ) \
	LANG_PAIR( I_SHOTS,              "Shots"                     ) \
	LANG_PAIR( I_VFORMAT,            "Video format (fps)"        ) \
	LANG_PAIR( I_RECTIME,            "Recording time"            ) \
	LANG_PAIR( I_PLAYTIME,           "Playback time"             ) \
	LANG_PAIR( I_DIRECTION,          "Direction"                 ) \
	LANG_PAIR( S_EXT_AEB,            "Extended AEB"              ) \
	LANG_PAIR( S_EFL_AEB,            "Flash AEB"                 ) \
	LANG_PAIR( S_APT_AEB,            "Aperture AEB"              ) \
	LANG_PAIR( S_ISO_AEB,            "ISO AEB"                   ) \
	LANG_PAIR( S_INTERVAL,           "Intervalometer"            ) \
	LANG_PAIR( S_BRAMP,              "Bulb ramping"              ) \
	LANG_PAIR( S_HANDWAVE,           "Handwaving"                ) \
	LANG_PAIR( S_TIMER,              "Self-Timer"                ) \
	LANG_PAIR( S_LEXP,               "Long exposures"            ) \
	LANG_PAIR( S_CALCULATOR,         "Calculator"                ) \
	LANG_PAIR( S_DOF_CALC,           "DOF Calculator"            ) \
	LANG_PAIR( I_KEEP_POWER_ON,      "Disable power-off"         ) \
	LANG_PAIR( I_REVIEW_OFF,         "Disable review"            ) \
	LANG_PAIR( I_INDICATOR,          "Indicator"                 ) \
	LANG_PAIR( I_LCD_SCRIPT,         "LCD display"               ) \
	LANG_PAIR( I_BTN_JUMP,           "Jump"                      ) \
	LANG_PAIR( I_BTN_TRASH,          "Trash"                     ) \
	LANG_PAIR( I_CMODES_CAMERA,      "Camera"                    ) \
	LANG_PAIR( I_CMODES_400PLUS,     "400plus"                   ) \
	LANG_PAIR( I_CMODES_ORDERING,    "Menu order"                ) \
	LANG_PAIR( I_CMODES_SETTINGS,    "Settings"                  ) \
	LANG_PAIR( I_CMODES_IMAGE,       "Image"                     ) \
	LANG_PAIR( I_CMODES_CFN,         "Custom Fn"                 ) \
	LANG_PAIR( I_IR_REMOTE_ENABLE,   "IR remote enable"          ) \
	LANG_PAIR( I_IR_REMOTE_DELAY,    "IR remote delay"           ) \
	LANG_PAIR( I_USE_DPAD,           "Use D-Pad"                 ) \
	LANG_PAIR( I_BUTTON_DISP,        "Better DISP button"        ) \
	LANG_PAIR( I_DEVELOPERS_MENU,    "Developers' menu"          ) \
	LANG_PAIR( I_LANGUAGE,           "Language"                  ) \
	LANG_PAIR( I_DIG_ISO_STEP,       "Digital ISO step"          ) \
	LANG_PAIR( I_PERSIST_AEB,        "Persist AEB"               ) \
	LANG_PAIR( I_INVERT_OLC,         "Change OLC Colors"         ) \
	LANG_PAIR( I_SAFETY_SHIFT,       "Safety Shift"              ) \
	LANG_PAIR( I_TV_VAL,             "Tv"                        ) \
	LANG_PAIR( I_AV_VAL,             "Av"                        ) \
	LANG_PAIR( I_EV_VAL,             "Ev"                        ) \
	LANG_PAIR( I_APPLY,              "Apply"                     ) \
	LANG_PAIR( I_FLENGTH,            "Focal length (mm)"         ) \
	LANG_PAIR( I_FDIST,              "Focus distance (m)"        ) \
	LANG_PAIR( I_DOFMIN,             "Min. DOF (m)"              ) \
	LANG_PAIR( I_DOFMAX,             "Max. DOF (m)"              ) \
	LANG_PAIR( S_SCRIPTS,            "Config. Scripts"           ) \
	LANG_PAIR( S_BUTTONS,            "Config. Buttons"           ) \
	LANG_PAIR( S_CMODES,             "Config. Custom modes"      ) \
	LANG_PAIR( S_PAGES,              "Config. Pages"             ) \
	LANG_PAIR( S_MENUS,              "Config. Menus"             ) \
	LANG_PAIR( S_QEXP,               "Config. Quick exposure"    ) \
	LANG_PAIR( V_OFF,                "Off"                       ) \
	LANG_PAIR( V_NO_LIMIT,           "No Limit"                  ) \
	LANG_PAIR( V_YES,                "Yes"                       ) \
	LANG_PAIR( V_NO,                 "No"                        ) \
	LANG_PAIR( V_ENABLED,            "Enabled"                   ) \
	LANG_PAIR( V_DISABLED,           "Disabled"                  ) \
	LANG_PAIR( V_EXT_ONLY,           "Ext Only"                  ) \
	LANG_PAIR( V_ONE_SHOT,           "One Shot"                  ) \
	LANG_PAIR( V_EXT_AEB,            "Ext. AEB"                  ) \
	LANG_PAIR( V_EFL_AEB,            "Flash AEB"                 ) \
	LANG_PAIR( V_APT_AEB,            "Apt. AEB"                  ) \
	LANG_PAIR( V_ISO_AEB,            "ISO AEB"                   ) \
	LANG_PAIR( V_LEXP,               "Long exp."                 ) \
	LANG_PAIR( V_NEW,                "New"                       ) \
	LANG_PAIR( V_OVERWRITE,          "Overwrite"                 ) \
	LANG_PAIR( V_APPEND,             "Append"                    ) \
	LANG_PAIR( V_NONE,               "None"                      ) \
	LANG_PAIR( V_SLOW,               "Slow"                      ) \
	LANG_PAIR( V_MEDIUM,             "Medium"                    ) \
	LANG_PAIR( V_FAST,               "Fast"                      ) \
	LANG_PAIR( V_KEEP,               "Keep"                      ) \
	LANG_PAIR( V_DIM,                "Dim down"                  ) \
	LANG_PAIR( V_INTISO,             "Intermediate ISO"          ) \
	LANG_PAIR( V_REPEAT,             "Repeat last script"        ) \
	LANG_PAIR( V_HACK_MENU,          "400plus Main Menu"         ) \
	LANG_PAIR( V_TOGGLE_FLASH,       "Flash on/off"              ) \
	LANG_PAIR( S_CMODE_NAME ,        "Custom mode"               ) \
	LANG_PAIR( S_INFINITE,           "INF!"                      ) \
	LANG_PAIR( V_CAMERA,             "Camera"                    ) \
	LANG_PAIR( I_WRAP_MENUS,         "Menus wrap"                ) \
	LANG_PAIR( I_NAVIGATE_MAIN,      "Navigate to main"          ) \
	LANG_PAIR( I_ENTER_MAIN,         "Enter to main"             ) \
	LANG_PAIR( I_AUTOSAVE,           "Autosave"                  ) \
	LANG_PAIR( I_RESTORE,            "Restore config."           ) \
	LANG_PAIR( I_RESTORE_SETTINGS,   "Restore settings"          ) \
	LANG_PAIR( I_RESTORE_CMODES,     "Restore custom modes"      ) \
	LANG_PAIR( I_DELETE_CMODES,      "Delete custom modes"       ) \
	LANG_PAIR( I_QEXP_MINTV,         "Min Tv"                    ) \
	LANG_PAIR( I_QEXP_WEIGTH,        "Weight"                    ) \
	LANG_PAIR( V_BOTH,               "Both"                      ) \
	LANG_PAIR( V_AV,                 "Av"                        ) \
	LANG_PAIR( V_TV,                 "Tv"                        ) \
	LANG_PAIR( S_NAMED_TEMPS,        "Named color temps."        ) \
	LANG_PAIR( V_NAMED_TEMP_0,       "Match flame"               ) \
	LANG_PAIR( V_NAMED_TEMP_1,       "Candle flame"              ) \
	LANG_PAIR( V_NAMED_TEMP_2,       "Tungsten light"            ) \
	LANG_PAIR( V_NAMED_TEMP_3,       "Fl. Warm White"            ) \
	LANG_PAIR( V_NAMED_TEMP_4,       "Fl. White"                 ) \
	LANG_PAIR( V_NAMED_TEMP_5,       "Fl. Cool White"            ) \
	LANG_PAIR( V_NAMED_TEMP_6,       "Fl. Daylight"              ) \
	LANG_PAIR( V_NAMED_TEMP_7,       "Daylight"                  ) \
	LANG_PAIR( V_NAMED_TEMP_8,       "Sunny"                     ) \
	LANG_PAIR( V_NAMED_TEMP_9,       "Flash"                     ) \
	LANG_PAIR( V_NAMED_TEMP_A,       "Cloudy"                    ) \
	LANG_PAIR( V_NAMED_TEMP_B,       "Shade"                     ) \
	LANG_PAIR( V_NAMED_TEMP_C,       "D50"                       ) \
	LANG_PAIR( V_NAMED_TEMP_D,       "D55"                       ) \
	LANG_PAIR( V_NAMED_TEMP_E,       "D65"                       ) \
	LANG_PAIR( V_NAMED_TEMP_F,       "D75"                       ) \
	LANG_PAIR( A_MIRROR_LOCKUP,      "Mirror Lockup"             ) \
	LANG_PAIR( A_FLASH,              "Flash"                     ) \
	LANG_PAIR( A_YES,                "Yes"                       ) \
	LANG_PAIR( A_NO,                 "No"                        ) \
	LANG_PAIR( A_WARNING,            "WARNING: Not intended for general usage!")

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
	L_LAST = L_COUNT - 1
};

extern const char *lang_pack_keys[L_COUNT];
extern char lang_pack_current[L_COUNT][LP_MAX_WORD];

extern void lang_pack_init(void);
extern void lang_pack_config(void);

#endif // LANGUAGES_H_
