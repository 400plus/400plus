#ifndef VXWORKS_STDLIB_H_
#define VXWORKS_STDLIB_H_

#include "vxworks.h"

typedef struct {
	int quot;
	int rem;
} div_t;

typedef struct {
	long int quot;
	long int rem;
} ldiv_t;

extern void     abort    (void);
extern int      abs      (int i);
extern int      atexit   (void (*__func)(void));
extern double   atof     (const char *s);
extern int      atoi     (const char *s);
extern long     atol     (const register char *s);
extern void    *bsearch  (const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
extern div_t    div      (int numer, int denom);
extern void     div_r    (int numer, int denom, div_t *divStructPtr);
extern long     labs     (long i);
extern ldiv_t   ldiv     (long numer, long denom);
extern void     ldiv_r   (long numer, long denom, ldiv_t *divStructPtr);
extern int      mblen    (const char *s, size_t n);
extern int      mbtowc   (wchar_t *pwc, const char *s, size_t n);
extern int      wctomb   (char *s, wchar_t wchar);
extern size_t   mbstowcs (wchar_t *pwcs, const char *s, size_t n);
extern size_t   wcstombs (char *s, const wchar_t *pwcs, size_t n);
extern void     qsort    (void *bot, size_t nmemb, size_t size,int (*compar)(const void *, const void *));
extern int      rand     (void);
extern void    *srand    (uint_t seed);
extern double   strtod   (const char *s, char **endptr);
extern long     strtol   (const char *nptr, char **endptr, int base);
extern ulong_t  strtoul  (const char *nptr, char **endptr, int base);
extern int      system   (const char *string);

#endif /* VXWORKS_STDLIB_H_ */
