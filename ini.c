/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:

http://code.google.com/p/inih/
*/

#include <vxworks.h>
#include <string.h>
#include <ioLib.h>
#include <ctype.h>

#include "firmware/fio.h"

#include "ini.h"
#include "utils.h"
#include "debug.h"
#include "languages.h"

/* Strip whitespace chars off end of given string, in place. Return s. */
static char* rstrip(char* s) {
	char* p = s + strlen(s);
	while (p > s && isspace(*--p))
		*p = '\0';
	return s;
}

/* Return pointer to first non-whitespace char in given string. */
static char* lskip(const char* s) {
	while (*s && isspace(*s))
		s++;
	return (char*)s;
}

/* Return pointer to first char c or ';' comment in given string, or pointer to
   null at end of string if neither found. ';' must be prefixed by a whitespace
   character to register as a comment. */
static char* find_char_or_comment(const char* s, char c) {
	int was_whitespace = 0;
	while (*s && *s != c && !(was_whitespace && *s == ';')) {
		was_whitespace = isspace(*s);
		s++;
	}
	return (char*)s;
}

/* See documentation in header file. */
int ini_parse_file(int file, const char* wanted_section, ini_line_handler handler, ini_section_handler shandler, void* user) {
	/* Uses a fair bit of stack (use heap instead if you need to) */
	char line[MAX_LINE];
	char section[MAX_SECTION] = "";
	char prev_name[MAX_NAME] = "";

	char* start;
	char* end;
	char* name;
	char* value;
	int lineno = 0;
	int error = 0;
	int section_found = 0;

	if (!wanted_section)
		section_found = 1;

	hack_fgets_init();
	/* Scan through file line by line */
	while (hack_fgets(line, sizeof(line), file) != NULL) {
		if (error) // 0xAF
			return error;

		lineno++;
		start = lskip(rstrip(line));

#if INI_ALLOW_MULTILINE
		if (*prev_name && *start && start > line) {
			/* Non-black line with leading whitespace, treat as continuation
			   of previous name's value (as per Python ConfigParser). */
			if (section_found && handler && !handler(user, lineno, section, prev_name, start) && !error)
				error = lineno;
		} else
#endif
		if (*start == ';' || *start == '#') {
			/* Per Python ConfigParser, allow '#' comments at start of line */
		} else if (*start == '[') {
			/* A "[section]" line */
			end = find_char_or_comment(start + 1, ']');
			if (*end == ']') {
				*end = '\0';
				strncpy0(section, start + 1, sizeof(section));
				*prev_name = '\0';
				if (wanted_section) { // 0xAF
					if (!strncmp(section, wanted_section, MAX_SECTION))
						section_found = 1;
					else
						section_found = 0;
				}
				if (shandler && !shandler(user, lineno, section) && !error)
					error = lineno;
			} else if (!error) {
				/* No ']' found on section line */
				error = lineno;
			}
		} else if (*start && *start != ';') {
			/* Not a comment, must be a name[=:]value pair */
			end = find_char_or_comment(start, '=');
			if (*end != '=') {
				end = find_char_or_comment(start, ':');
			}
			if (*end == '=' || *end == ':') {
				*end = '\0';
				name = rstrip(start);
				value = lskip(end + 1);
				end = find_char_or_comment(value, '\0');
				if (*end == ';')
					*end = '\0';
				rstrip(value);

				/* Valid name[=:]value pair found, call handler */
				strncpy0(prev_name, name, sizeof(prev_name));
				if (section_found && handler && !handler(user, lineno, section, name, value) && !error)
					error = lineno;
			} else if (!error) {
				/* No '=' or ':' found on name[=:]value line */
				error = lineno;
			}
		}
	}

	return error;
}

/* See documentation in header file. */
int ini_parse(const char* filename, const char* wanted_section, ini_line_handler handler, ini_section_handler shandler, void* user) {
	int error;

	int file = -1;

	if ((file = FIO_OpenFile(filename, O_RDONLY)) == -1)
		return -1;

	error = ini_parse_file(file, wanted_section, handler, shandler, user);

	FIO_CloseFile(file);

	return error;
}
