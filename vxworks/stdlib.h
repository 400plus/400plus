#ifndef VXWORKS_STDLIB_H_
#define VXWORKS_STDLIB_H_

#include "vxworks.h"

void     abort    (void);
int      abs      (int i);
int      atexit   (void (*__func)(void));
double   atof     (const char *s);
int      atoi     (const char *s);
long     atol     (const register char *s);
void    *bsearch  (const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
div_t    div      (int numer, int denom);
void     div_r    (int numer, int denom, div_t *divStructPtr);
long     labs     (long i);
ldiv_t   ldiv     (long numer, long denom);
void     ldiv_r   (long numer, long denom, ldiv_t *divStructPtr);
int      mblen    (const char *s, size_t n);
int      mbtowc   (wchar_t *pwc, const char *s, size_t n);
int      wctomb   (char *s, wchar_t wchar);
size_t   mbstowcs (wchar_t *pwcs, const char *s, size_t n);
size_t   wcstombs (char *s, const wchar_t *pwcs, size_t n);
void     qsort    (void *bot, size_t nmemb, size_t size,int (*compar)(const void *, const void *));
int      rand     (void);
void    *srand    (uint_t seed);
double   strtod   (const char *s, char **endptr);
long     strtol   (const char *nptr, char **endptr, int base);
ulong_t  strtoul  (const char *nptr, char **endptr, int base);
int      system   (const char *string);

#endif /* VXWORKS_STDLIB_H_ */
