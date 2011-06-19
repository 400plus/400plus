#include "main.h"
#include "firmware.h"

#include "debug.h"

#include "languages.h"

const char *lang_packs[LANG_COUNT][L_COUNT] = {
	[LANG_ENGLISH] = {
		[L_FREE_SPACE]    = "Free Space",
		[L_RELEASE_COUNT] = "ReleaseCount",
		[L_OFF]           = "Off",
		[L_YES]           = "Yes",
		[L_NO]            = "No",
		[L_2S]            = "2s",
		[L_ENABLED]       = "Enabled",
		[L_DISABLED]      = "Disabled",
		[L_EXT_ONLY]      = "Ext Only",
		[L_EXT_AEB]       = "Ext. AEB",
		[L_ONE_SHOT]      = "One Shot",
		[L_INTERVAL]      = "Interval",
		[L_NO_LIMIT]      = "No Limit",

		[L_RENAME]        = "Rename",

		[L_LOAD_PRESETS]  = "Load presets",
		[L_SAVE_PRESETS]  = "Save presets",

		[L_PRESET_NAME]   = "Preset",

		[L_DEVELOPER]          = "Developer",
		[L_ENTER_FACTORY_MODE] = "Enter factory Mode",
		[L_EXIT_FACTORY_MODE]  = "Exit  factory Mode",
		[L_START_DEBUG_MODE]   = "Start debug   Mode",

		[L_SETTINGS]        = "Settings",
		[L_DELAY]           = "Delay",
		[L_ACTION]          = "Action",
		[L_REPEAT]          = "Repeat",
		[L_INSTANT]         = "Instant",
		[L_FRAMES]          = "Frames",
		[L_STEP_EV]         = "Step (EV)",
		[L_MANUAL_L]        = "Bulb min",
		[L_MANUAL_R]        = "Bulb max",
		[L_TIME_S]          = "Time (s)",
		[L_EAEB]            = "EAEB",
		[L_SHOTS]           = "Shots",
		[L_AV_COMP]         = "AV comp",
		[L_FLASH_COMP]      = "Flash comp",
		[L_AEB]             = "AEB",
		[L_ISO_IN_VF]       = "ISO in viewfinder",
		[L_SHORTCUTS_MENU]  = "Shortcuts menu",
		[L_SAFETY_SHIFT]    = "Safety Shift",
		[L_COLOR_TEMP_K]    = "Color Temp. (K)",
		[L_USE_FLASH]       = "Disable flash",
		[L_HANDWAVE]        = "Handwave",
		[L_TIMER_SPACES]    = "Timer   ",
		[L_IR_REMOTE_DELAY] = "IR remote delay",
		[L_DEVELOPERS_MENU] = "Developers Menu",

		[L_SCRIPTS_SPACES]  = "Scripts ",
		[L_DIM_LCD_DOWN]    = "LCD dim",
		[L_KEEP_POWER_ON]   = "APO dsbl",

		[L_SHORTCUTS]      = "Shortcuts",
		[L_ISO]            = "ISO",
		[L_EXTENDED_AEB]   = "Extended AEB",
		[L_INTERVALOMETER] = "Intervalometer",
		[L_HAND_WAVING]    = "Hand Waving",
		[L_SELF_TIMER]     = "Self Timer",
		[L_AF_FLASH]       = "AF Flash",
		[L_MIRROR_LOCKUP]  = "Mirror Lockup",
		[L_FLASH_2ND_CURT] = "Flash 2curt",

		[L_PRESETS_SPACES]   = "Presets ",
		[L_PRESETS_ADEP]     = "Use A-DEP",
		[L_PRESETS_CAMERA]   = "Camera",
		[L_PRESETS_400PLUS]  = "400plus",
		[L_PRESETS_SETTINGS] = "Settings",
		[L_PRESETS_IMAGE]    = "Image",
		[L_PRESETS_CFN]      = "Custom Fn",
	},
	[LANG_GERMAN] = {
		[L_FREE_SPACE]    = "CF-Card frei",
		[L_RELEASE_COUNT] = "Anz. d. Aufn.",
		[L_OFF]           = "Aus",
		[L_YES]           = "Ja",
		[L_NO]            = "Nein",
		[L_2S]            = "2s",
		[L_ENABLED]       = "Aktivie.",
		[L_DISABLED]      = "Deaktiv.",
		[L_EXT_ONLY]      = "Nur Ext.",
		[L_EXT_AEB]       = "Ext. AEB",
		[L_ONE_SHOT]      = "Einzela.",
		[L_INTERVAL]      = "Interv. ",
		[L_NO_LIMIT]      = "Unbegre.",

		[L_LOAD_PRESETS]  = "Presets laden",
		[L_SAVE_PRESETS]  = "Presets speichern",

		[L_PRESET_NAME]   = "Preset",

		[L_DEVELOPER]          = "Entwickler",
		[L_ENTER_FACTORY_MODE] = "Betrete Werksmenü",
		[L_EXIT_FACTORY_MODE]  = "Verlasse Werksmenü",
		[L_START_DEBUG_MODE]   = "Debugmodus starten",

		[L_SETTINGS]        = "Einstellungen",
		[L_DELAY]           = "Verz.",
		[L_ACTION]          = "Aktion",
		[L_REPEAT]          = "Wiederh.",
		[L_INSTANT]         = "Dauerhaft",
		[L_FRAMES]          = "Bilder",
		[L_STEP_EV]         = "SchrittEV",
		[L_MANUAL_L]        = "Manuell [",
		[L_MANUAL_R]        = "Manuell ]",
		[L_TIME_S]          = "Zeit (s)",
		[L_EAEB]            = "EAEB",
		[L_SHOTS]           = "Aufnahmen",
		[L_AV_COMP]         = "AV Komp.",
		[L_FLASH_COMP]      = "Blitz Komp.",
		[L_AEB]             = "AEB",
		[L_ISO_IN_VF]       = "ISO in Sucher",
		[L_SHORTCUTS_MENU]  = "Shortcutsmenu",
		[L_SAFETY_SHIFT]    = "Safety Shift",
		[L_COLOR_TEMP_K]    = "Farbtemp. (K)",
//		[L_USE_FLASH]       = "Blitz benutzen",
		[L_HANDWAVE]        = "Handwave",
		[L_TIMER_SPACES]    = "Timer   ",
		[L_IR_REMOTE_DELAY] = "IR Fernausl. Verz.",
		[L_DEVELOPERS_MENU] = "Entwicklermenü",

		[L_SHORTCUTS]      = "Shortcuts",
		[L_ISO]            = "ISO",
		[L_EXTENDED_AEB]   = "Erweitertes AEB",
		[L_INTERVALOMETER] = "Intervalometer",
		[L_HAND_WAVING]    = "Hand Waving",
		[L_SELF_TIMER]     = "Self Timer",
		[L_AF_FLASH]       = "AF Blitz",
		[L_MIRROR_LOCKUP]  = "Spiegelverriegel.",
		[L_FLASH_2ND_CURT] = "Blitz 2. Vorhang",
	},
	[LANG_SPANISH] = {
		[L_FREE_SPACE]    = "Esp. libre",
		[L_RELEASE_COUNT] = "Disparos totales",
		[L_OFF]           = " Off",
		[L_YES]           = " Sí",
		[L_NO]            = " No",
		[L_2S]            = " 2s",
		[L_ENABLED]       = "activo",
		[L_DISABLED]      = "inactivo",
		[L_EXT_ONLY]      = "sólo ext.",
		[L_EXT_AEB]       = "AEB ext. ",
		[L_ONE_SHOT]      = "1 toma",
		[L_INTERVAL]      = "Interval.",
		[L_NO_LIMIT]      = "ilimit.",

		[L_RENAME]        = "Renombra",

		[L_LOAD_PRESETS]  = "carga PRESET",
		[L_SAVE_PRESETS]  = "guarda PRESET",

		[L_PRESET_NAME]   = "Preset",

		[L_DEVELOPER]          = "Desarrolladores",
		[L_ENTER_FACTORY_MODE] = "entrar modo fábrica",
		[L_EXIT_FACTORY_MODE]  = "salir modo fábrica",
		[L_START_DEBUG_MODE]   = "modo depuración",

		[L_SETTINGS]        = "ajustes",
		[L_DELAY]           = "demora",
		[L_ACTION]          = "acción",
		[L_REPEAT]          = "repetir",
		[L_INSTANT]         = "instant",
		[L_FRAMES]          = "marcos",
		[L_STEP_EV]         = "paso(EV)",
		[L_MANUAL_L]        = "Bulb min",
		[L_MANUAL_R]        = "Bulb max",
		[L_TIME_S]          = "Tiempo",
		[L_EAEB]            = "EAEB",
		[L_SHOTS]           = "tomas",
		[L_AV_COMP]         = "Comp. AV",
		[L_FLASH_COMP]      = "Comp. flash",
		[L_AEB]             = "AEB",
		[L_ISO_IN_VF]       = "ISO en visor",
		[L_SHORTCUTS_MENU]  = "Accesos Directos",
		[L_SAFETY_SHIFT]    = "Desplazam. seg.",
		[L_COLOR_TEMP_K]    = "Temp. color (K)",
		[L_USE_FLASH]       = "Bloquea flash",
		[L_HANDWAVE]        = "TomaVisor",
		[L_TIMER_SPACES]    = "Temporizador",
		[L_IR_REMOTE_DELAY] = "Retardo IR",
		[L_DEVELOPERS_MENU] = "Desarrolladores",

		[L_SCRIPTS_SPACES]  = "Guiones  ",
		[L_DIM_LCD_DOWN]    = "LCD bajo",
		[L_KEEP_POWER_ON]   = "APO dsbl",

		[L_SHORTCUTS]      = "AC. DIRECTOS",
		[L_ISO]            = "ISO",
		[L_EXTENDED_AEB]   = "AEB extendido",
		[L_INTERVALOMETER] = "Intervalómetro",
		[L_HAND_WAVING]    = "Toma X Visor",
		[L_SELF_TIMER]     = "Temporizador",
		[L_AF_FLASH]       = "Flash AF",
		[L_MIRROR_LOCKUP]  = "Bloqueo espejo",
		[L_FLASH_2ND_CURT] = "Flash 2cort.",

		[L_PRESETS_SPACES]   = "Presets",
		[L_PRESETS_ADEP]     = "usa A-DEP",
		[L_PRESETS_CAMERA]   = "cámara",
		[L_PRESETS_400PLUS]  = "400D+",
		[L_PRESETS_SETTINGS] = "ajustes",
		[L_PRESETS_IMAGE]    = "imagen",
		[L_PRESETS_CFN]      = "Fn pers.",
	},
};

char lang_pack_current[L_COUNT][LP_MAX_WORD];

void lang_pack_config() {
	int  i;
	char lang[32];

	GetLanguageStr(cameraMode->language, lang);
	debug_log("Setting language to [%d] - '%s'", cameraMode->language, lang);

	for (i = L_FIRST; i < L_COUNT; i++)
		if(lang_packs[cameraMode->language][i] != NULL)
			strncpy(lang_pack_current[i], lang_packs[cameraMode->language][i], LP_MAX_WORD);
		else if(lang_packs[LANG_FIRST][i] != NULL)
			strncpy(lang_pack_current[i], lang_packs[LANG_FIRST][i], LP_MAX_WORD);
		else
			strncpy(lang_pack_current[i], "NULL", LP_MAX_WORD);
}
