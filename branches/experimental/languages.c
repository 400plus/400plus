#include "debug.h"

#include "languages.h"

char * LangPlus_lang_pack_set_word(int langid, int wordid, char* word);

char * LangPlus_lang_packs[16][L_EOL];
char LangPlus_current[L_EOL][MAX_LANG_WORD];
int LangPlus_last_langid = -1;

enum LanguageID {
	LANG_ENGLISH,
	LANG_GERMAN,
	LANG_FRENCH,
	LANG_DUTCH,
	LANG_DANISH,
	LANG_FINNISH,
	LANG_ITALIAN,
	LANG_NORWEGIAN,
	LANG_SWEDISH,
	LANG_SPANISH,
	LANG_RUSSIAN,
	LANG_SIMPLIFIED_CHINESE,
	LANG_TRADITIONAL_CHANISE,
	LANG_KOREAN,
	LANG_JAPANESE,
	LANG_POLISH
};

void LangPlus_lang_packs_init() {
	// set English first, it will set the defaults for every language
	// English Translations {{{
	debug_log("LangPack init(English) and all defaults");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_FREE_SPACE,		"Free Space");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_RELEASE_COUNT,	"ReleaseCount");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_OFF,		"Off");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_YES,		"Yes");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_NO,			"No");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_2S,			"2s");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ENABLED,		"Enabled");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_DISABLED,		"Disabled");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_EXT_ONLY,		"Ext Only");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_EXT_AEB,		"Ext. AEB");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ONE_SHOT,		"One Shot");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_INTERVAL,		"Interval");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_NO_LIMIT,		"No Limit");

	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESETS,	"Load presets");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESET_1,	"Load preset 1");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESET_2,	"Load preset 2");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESET_3,	"Load preset 3");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESET_4,	"Load preset 4");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_LOAD_PRESET_5,	"Load preset 5");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESETS,	"Save presets");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESET_1,	"Save preset 1");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESET_2,	"Save preset 2");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESET_3,	"Save preset 3");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESET_4,	"Save preset 4");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAVE_PRESET_5,	"Save preset 5");

	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_DEVELOPER,		"Developer");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ENTER_FACTORY_MODE,	"Enter factory Mode");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_EXIT_FACTORY_MODE,	"Exit  factory Mode");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_START_DEBUG_MODE,	"Start debug   Mode");

	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SETTINGS,		"Settings");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_DELAY,		"Delay");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ACTION,		"Action");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_REPEAT,		"Repeat");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_INSTANT,		"Instant");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_FRAMES,		"Frames");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_STEP_EV,		"Step (EV)");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_MANUAL_L,		"Manual [");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_MANUAL_R,		"Manual ]");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_TIME_S,		"Time (s)");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_EAEB,		"EAEB");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SHOTS,		"Shots");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_AV_COMP,		"AV comp");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_FLASH_COMP,		"Flash comp");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_AEB,		"AEB");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ISO_IN_VF,		"ISO in viewfinder");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SHORTCUTS_MENU,	"Shortcuts menu");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SAFETY_SHIFT,	"Safety Shift");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_COLOR_TEMP_K,	"Color Temp. (K)");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_USE_FLASH,		"Use flash");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_HANDWAVE,		"Handwave");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_TIMER_SPACES,	"Timer   ");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_IR_REMOTE_DELAY,	"IR remote delay");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_DEVELOPERS_MENU,	"Developers Menu");

	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SHORTCUTS,		"Shortcuts");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_ISO,		"ISO");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_EXTENDED_AEB,	"Extended AEB");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_INTERVALOMETER,	"Intervalometer");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_HAND_WAVING,	"Hand Waving");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_SELF_TIMER,		"Self Timer");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_AF_FLASH,		"AF Flash");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_MIRROR_LOCKUP,	"Mirror Lockup");
	LangPlus_lang_pack_set_word(LANG_ENGLISH, L_FLASH_2ND_CURT,	"Flash 2curt");
	// }}}

	// German Translations {{{
	//Semanticly correct, will tune it a little bit soon. <- M.Perenz
	debug_log("LangPlus init(German)");

	LangPlus_lang_pack_set_word(LANG_GERMAN, L_FREE_SPACE,		"CF-Card frei");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_RELEASE_COUNT,	"Anz. d. Aufn.");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_OFF,			"Aus");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_YES,			"Ja");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_NO,			"Nein");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_2S,			"2s");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ENABLED,		"Aktiviert");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_DISABLED,		"Deaktiviert");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_EXT_ONLY,		"Nur Ext.");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_EXT_AEB,		"Ext. AEB");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ONE_SHOT,		"Einzelaufnahme");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_INTERVAL,		"Intervall");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_NO_LIMIT,		"Unbegrenzt");

	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESETS,	"Presets laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESET_1,	"Preset 1 laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESET_2,	"Preset 2 laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESET_3,	"Preset 3 laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESET_4,	"Preset 4 laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_LOAD_PRESET_5,	"Preset 5 laden");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESETS,	"Presets speichern");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESET_1,	"Preset 1 speichern");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESET_2,	"Preset 2 speichern");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESET_3,	"Preset 3 speichern");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESET_4,	"Preset 4 speichern");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAVE_PRESET_5,	"Preset 5 speichern");

	LangPlus_lang_pack_set_word(LANG_GERMAN, L_DEVELOPER,		"Entwickler");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ENTER_FACTORY_MODE,	"Betrete Werksmenü");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_EXIT_FACTORY_MODE,	"Verlasse Werksmenü");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_START_DEBUG_MODE,	"Debugmodus starten");

	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SETTINGS,		"Einstellungen");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_DELAY,		"Verzögerung");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ACTION,		"Aktion");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_REPEAT,		"Wiederholen");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_INSTANT,		"Dauerhaft");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_FRAMES,		"Bilder");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_STEP_EV,		"Schritt (EV)");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_MANUAL_L,		"Manuell [");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_MANUAL_R,		"Manuell ]");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_TIME_S,		"Zeit (s)");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_EAEB,		"EAEB");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SHOTS,		"Aufnahmen");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_AV_COMP,		"AV Komp.");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_FLASH_COMP,		"Blitz Komp.");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_AEB,			"AEB");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ISO_IN_VF,		"ISO in Sucher");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SHORTCUTS_MENU,	"Shortcutsmenü");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SAFETY_SHIFT,	"Safety Shift");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_COLOR_TEMP_K,	"Farbtemp. (K)");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_USE_FLASH,		"Blitz benutzen");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_HANDWAVE,		"Handwave");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_TIMER_SPACES,	"Timer   ");
	//Maybe to long?
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_IR_REMOTE_DELAY,	"IR Fernausl. Verzögerung");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_DEVELOPERS_MENU,	"Entwicklermenü");

	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SHORTCUTS,		"Shortcuts");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_ISO,			"ISO");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_EXTENDED_AEB,	"Erweitertes AEB");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_INTERVALOMETER,	"Intervalometer");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_HAND_WAVING,		"Hand Waving");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_SELF_TIMER,		"Self Timer");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_AF_FLASH,		"AF Blitz");
	//Maybe to long)
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_MIRROR_LOCKUP,	"Spiegelverriegelung");
	LangPlus_lang_pack_set_word(LANG_GERMAN, L_FLASH_2ND_CURT,	"Blitz 2. Vorhang");
	// }}}

}

char * LangPlus_lang_pack_set_word(int langid, int wordid, char* word) {
	int i;

	if (langid == 0) {
		for (i=0; i<16; i++) {
			LangPlus_lang_packs[i][wordid] = word;
		}
	} else {
		LangPlus_lang_packs[langid][wordid] = word;
	}
}

void LangPlus_set_lang(int lang) {
	int word;
	char l[32];

	if (LangPlus_last_langid == lang)
		return;

	LangPlus_last_langid = lang;

	GetLanguageStr(lang, l);
	debug_log("LangPlus set lang to %s [%d]", l, lang);

	for (word=0; word<L_EOL; word++) {
		int ch = 0;
		// snprintf
		while (ch<MAX_LANG_WORD-1 && LangPlus_lang_packs[lang][word][ch] != 0) {
			// copy char by char
			LangPlus_current[word][ch] = LangPlus_lang_packs[lang][word][ch];
			ch++;
		}
		// Terminate string
		LangPlus_current[word][ch] = 0;
	}
}



// vim: foldenable foldmethod=marker

