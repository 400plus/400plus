#include <vxworks.h>
#include <string.h>

#include "firmware/camera.h"

#include "main.h"
#include "firmware.h"

#include "settings.h"
#include "utils.h"
#include "ini.h"
#include "debug.h"

#include "languages.h"

char languages_found[MAX_LANGUAGES][MAX_SECTION];
static unsigned int languages_found_last = 0;

int lang_pack_sections(void *user, int lineno, const char *section);
int lang_pack_loader  (void* user, int lineno, const char* section, const char* name, const char* value);

// put the language keys into the hack, we need them to match the keys in languages.ini file
const char *lang_pack_keys[L_COUNT] = {
	#define LANG_PAIR(key, val) [L_##key] = #key,
	LANGUAGE_PAIRS
	#undef LANG_PAIR
	// this will define the keys eg:
	// [L_FREE_SPACE] = "FREE_SPACE",
	// [L_RELEASE_COUNT] = "RELEASE_COUNT",
	// etc...
};

// store English language into the hack, so we have at least one language available.
static const char *lang_pack_english[L_COUNT] = {
	#define LANG_PAIR(key, val) [L_##key] = val,
	LANGUAGE_PAIRS
	#undef LANG_PAIR
	// this will define the English language, eg:
	// [L_FREE_SPACE] = "Free Space",
	// [L_RELEASE_COUNT] = "ReleaseCount",
};

char lang_pack_current[L_COUNT][LP_MAX_WORD];
int  lang_pack_keys_loaded;

int lang_pack_sections(void *user, int lineno, const char *section) {
	strncpy0(languages_found[languages_found_last++], section, LP_MAX_WORD-1);
	languages_found[languages_found_last][0] = '\0';
	return 1;
}


void lang_pack_init() {
	int res = 0;

	strncpy0(languages_found[languages_found_last++], "Camera",  LP_MAX_WORD-1);
	strncpy0(languages_found[languages_found_last++], "ENGLISH", LP_MAX_WORD-1);
	languages_found[languages_found_last][0] = '\0';

	if ((res = ini_parse(MKPATH_NEW(LANGUAGES_FILENAME), NULL, NULL, lang_pack_sections, NULL)) == -1)
		res = ini_parse(MKPATH_OLD(LANGUAGES_FILENAME), NULL, NULL, lang_pack_sections, NULL);

	if (res != 0) {
		debug_log("ERROR: cannot parse sections from language.ini");

		if (res > 0)
			debug_log("Problem on line [%d] in languages.ini ", res);
		else
			debug_log("languages.ini not found");
	}

	lang_pack_config();
}

int lang_pack_loader(void* user, int lineno, const char* section, const char* name, const char* value) {
	int i;

	// find the KEY id
	// @todo: think of a better way to find our id
	for (i = L_FIRST; i < L_COUNT; i++) {
		if (!strncmp(lang_pack_keys[i], name, LP_MAX_WORD-1)) {
			// this is our id
			strncpy(lang_pack_current[i], value, LP_MAX_WORD-1);
			//debug_log("LANG: setting key [%s]: [%s]", lang_pack_keys[i], lang_pack_current[i]);
			lang_pack_current[i][LP_MAX_WORD-1] = 0;
			lang_pack_keys_loaded++;
		}
	}

	return 1; // return non-zero == success
}

void lang_pack_config() {
	int  i;
	static char lang[LP_MAX_WORD];

	GetLanguageStr(DPData.language, lang);

	if (settings.language != 0) {
		debug_log("Discarding camera language: [%s]", lang);
		strncpy0(lang, languages_found[settings.language], LP_MAX_WORD);
	}

	debug_log("Setting language to: [%s] <%s>", lang, (settings.language ? "forced" : "camera"));

	// load English always, so we overwrite previous language if there is any
	for (i = L_FIRST; i < L_COUNT; i++) {
		if (lang_pack_english[i] != NULL) {
			strncpy(lang_pack_current[i], lang_pack_english[i], LP_MAX_WORD);
			//debug_log("LANG: setting ENG key [%d]: [%s]", i, lang_pack_current[i]);
		} else {
			debug_log("BUG: missing ENG key: [%s][%d]", lang_pack_keys[i], i);
			strncpy(lang_pack_current[i], "*NULL*", LP_MAX_WORD);
		}
	}

	// if we need non-english language, load it from languages.ini
	if (settings.language != 0 || DPData.language > 0 /* ENGLISH */) {
		int res;

		stoupper(lang); // convert to upper case
		lang_pack_keys_loaded=0;

		if ((res = ini_parse(MKPATH_NEW(LANGUAGES_FILENAME), lang, lang_pack_loader, NULL, (void*)lang)) == -1)
			res = ini_parse(MKPATH_OLD(LANGUAGES_FILENAME), lang, lang_pack_loader, NULL, (void*)lang);

		if (res == 0) {
			debug_log("[%d] keys loaded from languages.ini.", lang_pack_keys_loaded);
		} else {
			debug_log("ERROR: cannot load language from file.");
			if (res > 0) {
				debug_log("Problem on line [%d] in languages.ini ", res);
			} else {
				debug_log("languages.ini not found");
			}
		}
	}

	// Update "Camera" in language selection menu
	strncpy0(languages_found[0], LP_WORD(L_V_CAMERA), LP_MAX_WORD-1);
}

