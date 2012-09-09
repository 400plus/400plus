/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef STDLIB_H_
#define STDLIB_H_

#include <types.h>

typedef struct {
	int quot; /* quotient */
	int rem;  /* remainder */
} div_t ;

typedef struct {
	long quot; /* quotient */
	long rem;  /* remainder */
} ldiv_t ;

extern void    abort (void);
extern int     abs(int i);
extern int     atexit(void (*__func)(void));
extern double  atof(const char *s);
extern int     atoi(const char *s);
extern long    atol(const register char *s);
extern void   *bsearch(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar) (const void *, const void *));
extern div_t   div(int numer, int denom);
extern long    labs(long i);
extern ldiv_t  ldiv(long numer, long denom);
extern void    qsort(void *bot, size_t nmemb, size_t size, int (*compar) (const void *, const void *));
extern int     rand (void);
extern void   *srand(uint_t seed);
extern double  strtod (const char *s, char **endptr);
extern long    strtol(const char *nptr, char **endptr, int base);
extern ulong_t strtoul(const char *nptr,char **endptr, int base);
extern int     system(const char *string) ;

#endif
