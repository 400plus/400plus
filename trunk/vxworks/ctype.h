/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef CTYPE_H_
#define CTYPE_H_

extern int   isalnum(int);
extern int   isalpha(int);

extern int   isascii(int);

extern int   isblank(int);
extern int   iscntrl(int);
extern int   isdigit(int);
extern int   isgraph(int);
extern int   islower(int);
extern int   isprint(int);
extern int   ispunct(int);
extern int   isspace(int);
extern int   isupper(int);
extern int   isxdigit(int);

extern int   toascii(int);

extern int   tolower(int);
extern int   toupper(int);

#endif
