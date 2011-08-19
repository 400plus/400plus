#include "main.h"
#include "firmware.h"

#include "debug.h"

#include "languages.h"
#include "ini.h"

// put the language keys to the ROM, we need them to match the keys in languages.ini file
const char *lang_pack_keys[L_COUNT] = {
	#define LANG_PAIR(key, val) [L_##key] = #key,
	LANGUAGE_PAIRS
	#undef LANG_PAIR
	// this will define the keys eg:
	// [L_FREE_SPACE] = "FREE_SPACE",
	// [L_RELEASE_COUNT] = "RELEASE_COUNT",
	// etc...
};

// store English language in the ROM, so we have at least one language available.
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

// see comment below before uncommenting this routine
/*
int lang_pack_sections(void *user, int lineno, const char *section) {
	debug_log("section found: [%s]", section);
	return 1;
}
*/

void lang_pack_init() {
	// this code should be uncommented and used to make a new menu for choosing
	// language different from the camera's one, this way we can have additional languages.
	// menu should look like this:
	// Camera Language [default]
	// German
	// Italian
	// French
	// etc...
	/*
	int res = 0;

	res = ini_parse("A:/languages.ini", NULL, NULL, lang_pack_sections, NULL);

	if (res == 0) {
		debug_log("sections parsed");
	} else {
		debug_log("ERROR: cannot parse sections from language.ini");
		if (res > 0) {
			debug_log("Problem on line [%d] in languages.ini ", res);
		} else {
			debug_log("languages.ini not found");
		}
	}
	*/
	lang_pack_config();
}

int lang_pack_loader(void* user, int lineno, const char* section, const char* name, const char* value) {
	int i;

	// after the ini_parser improvement, we should get only our section parsed, so no need to check the section

	// find the KEY id
	// @todo: think of a better way to find our id
	for (i = L_FIRST; i < L_COUNT; i++) {
		if (!strncmp(lang_pack_keys[i], name, LP_MAX_WORD)) {
			// this is our id
			strncpy(lang_pack_current[i], value, LP_MAX_WORD);
			lang_pack_keys_loaded++;
		}
	}

	return 1; // return non-zero == success
}

void lang_pack_config() {
	int  i;
	static char lang[32];

	GetLanguageStr(cameraMode->language, lang);
	debug_log("Setting language to [%d] - '%s'", cameraMode->language, lang);

	// load English always, so we overwrite previous language if there is any
	for (i = L_FIRST; i < L_COUNT; i++) {
		if (lang_pack_english[i] != NULL) {
			strncpy(lang_pack_current[i], lang_pack_english[i], LP_MAX_WORD);
		} else {
			strncpy(lang_pack_current[i], "*NULL*", LP_MAX_WORD);
		}
	}

	// if we need non-english language, load it from languages.ini
	if (cameraMode->language > 0 /* ENGLISH */) {
		int res;
		stoupper(lang); // convert to upper case
		lang_pack_keys_loaded=0;
		res = ini_parse("A:/languages.ini", lang, lang_pack_loader, NULL, (void*)lang);
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
}

