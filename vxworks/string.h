#ifndef VXWORKS_STRING_H_
#define VXWORKS_STRING_H_

#include "vxworks.h"

/* bLib.S */

int   bcmp       (char *buf1, char *buf2, int nbytes);
void  binvert    (char *buf, int nbytes);
void  bswap      (char *buf1, char *buf2, int nbytes);
void  swab       (char *source, char *destination, int nbytes);
void  uswab      (char *source, char *destination, int nbytes);
void  bzero      (char *buffer, int nbytes);
void  bcopy      (const char *source, char *destination, int nbytes);
void  bcopyBytes (char *source, char *destination, int nbytes);
void  bcopyWords (char *source, char *destination, int nwords);
void  bcopyLongs (char *source, char *destination, int nlongs);
void  bfill      (char *buf, int nbytes, int ch);
void  bfillBytes (char *buf, int nbytes, int ch);
char *index      (const char *s, int c);
char *rindex     (const char *s, int c);

/* ansiString.h */

void   *memchr     (const void *m, int c, size_t n);
int     memcmp     (const void *s1, const void *s2, size_t n);
void   *memcpy     (void *destination, const void *source, size_t size);
void   *memmove    (void *destination, const void *source, size_t size);
void   *memset     (void *m, int c, size_t size);
char   *strcat     (char *destination, const char *append);
char   *strchr     (const char *s, int c);
int    strcmp      (const char *s1, const char *s2);
int    strcoll     (const char *s1, const char *s2);
char   *strcpy     (char *s1, const char *s2);
size_t  strcspn    (const char *s1, const char *s2);
STATUS  strerror_r (int errcode, char *buffer);
char   *strerror   (int errcode);
size_t  strlen     (const char *s);
char   *strncat    (char *dst, const char *src, size_t n);
int     strncmp    (const char *s1, const char *s2, size_t n);
char   *strncpy    (char *s1, const char *s2, size_t n);
char   *strpbrk    (const char *s1, const char *s2);
char   *strrchr    (const char *s, int c);
size_t  strspn     (const char *s, const char *sep);
char   *strstr     (const char *s, const char *find);
char   *strtok     (char *string, const char *separator);
char   *strtok_r   (char *string, const char *separators, char **ppLast);
size_t  strxfrm    (char *s1, const char *s2, size_t n);

#endif /* VXWORKS_STRING_H_ */
