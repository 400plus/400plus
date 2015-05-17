#ifndef VXWORKS_STRING_H_
#define VXWORKS_STRING_H_

#include "vxworks.h"

/* bLib.S */
extern int   bcmp       (char *buf1, char *buf2, int nbytes);
extern void  binvert    (char *buf, int nbytes);
extern void  bswap      (char *buf1, char *buf2, int nbytes);
extern void  swab       (char *source, char *destination, int nbytes);
extern void  uswab      (char *source, char *destination, int nbytes);
extern void  bzero      (char *buffer, int nbytes);
extern void  bcopy      (const char *source, char *destination, int nbytes);
extern void  bcopyBytes (char *source, char *destination, int nbytes);
extern void  bcopyWords (char *source, char *destination, int nwords);
extern void  bcopyLongs (char *source, char *destination, int nlongs);
extern void  bfill      (char *buf, int nbytes, int ch);
extern void  bfillBytes (char *buf, int nbytes, int ch);
extern char *index      (const char *s, int c);
extern char *rindex     (const char *s, int c);

/* ansiString.h */
extern void   *memchr     (const void *m, int c, size_t n);
extern int     memcmp     (const void *s1, const void *s2, size_t n);
extern void   *memcpy     (void *destination, const void *source, size_t size);
extern void   *memmove    (void *destination, const void *source, size_t size);
extern void   *memset     (void *m, int c, size_t size);
extern char   *strcat     (char *destination, const char *append);
extern char   *strchr     (const char *s, int c);
extern int    strcmp      (const char *s1, const char *s2);
extern int    strcoll     (const char *s1, const char *s2);
extern char   *strcpy     (char *s1, const char *s2);
extern size_t  strcspn    (const char *s1, const char *s2);
extern STATUS  strerror_r (int errcode, char *buffer);
extern char   *strerror   (int errcode);
extern size_t  strlen     (const char *s);
extern char   *strncat    (char *dst, const char *src, size_t n);
extern int     strncmp    (const char *s1, const char *s2, size_t n);
extern char   *strncpy    (char *s1, const char *s2, size_t n);
extern char   *strpbrk    (const char *s1, const char *s2);
extern char   *strrchr    (const char *s, int c);
extern size_t  strspn     (const char *s, const char *sep);
extern char   *strstr     (const char *s, const char *find);
extern char   *strtok     (char *string, const char *separator);
extern char   *strtok_r   (char *string, const char *separators, char **ppLast);
extern size_t  strxfrm    (char *s1, const char *s2, size_t n);

#endif /* VXWORKS_STRING_H_ */
