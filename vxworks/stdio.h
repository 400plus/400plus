#ifndef VXWORKS_STDIO_H_
#define VXWORKS_STDIO_H_

#include "vxworks.h"

extern int fdprintf  (int fd, const char *fmt, ...);
extern int printf    (const char *, ...);
extern int printErr  (const char *fmt, ...);
extern int sprintf   (char *, const char *, ...);
extern int sscanf    (const char *, const char *, ...);
extern int vfdprintf (int fd, const char *fmt, va_list ap);
extern int vfprintf  (FILE *, const char *, va_list);
extern int vprintf   (const char *, va_list);
extern int vsprintf  (char *, const char *, va_list);

#endif /* VXWORKS_STDIO_H_ */
