/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:

http://code.google.com/p/inih/

@todo: 0xAF - make a routine to parse only specified section, we do not need to parse all sections

*/

//#include <stdio.h>
//#include <ctype.h> // 0xAF - linker cannot see __ctype_ptr__  and we have VxWorks isspace() already, so this is not needed
//#include <string.h>

#include "ini.h"
#include "utils.h"
#include "debug.h"

#define MAX_LINE 100
#define MAX_SECTION 32
#define MAX_NAME 32

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

/* Version of strncpy that ensures dest (size bytes) is null-terminated. */
static char* strncpy0(char* dest, const char* src, size_t size) {
	strncpy(dest, src, size);
	dest[size - 1] = '\0';
	return dest;
}

/* See documentation in header file. */
int ini_parse_file(int fd, int (*handler)(void*, int line, const char*, const char*, const char*), void* user) {
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

	my_fgets_init();
	/* Scan through file line by line */
	while (my_fgets(line, sizeof(line), fd) != NULL) {
		if (error) // 0xAF
			return error;

		lineno++;
		start = lskip(rstrip(line));

#if INI_ALLOW_MULTILINE
		if (*prev_name && *start && start > line) {
			/* Non-black line with leading whitespace, treat as continuation
			   of previous name's value (as per Python ConfigParser). */
			if (!handler(user, lineno, section, prev_name, start) && !error)
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
				if (!handler(user, lineno, section, name, value) && !error)
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
int ini_parse(const char* filename, int (*handler)(void*, int, const char*, const char*, const char*), void* user) {
	int fd;
	int error;

	if ( (fd = FIO_OpenFile(filename, O_RDONLY, 644)) < 0 )
		return -1;
	error = ini_parse_file(fd, handler, user);
	close(fd);
	return error;
}
