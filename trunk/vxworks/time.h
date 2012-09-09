/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef TIME_H_
#define TIME_H_

#include <types.h>

struct timespec {
	time_t tv_sec;   /* seconds */
	long   tv_nsec;  /* nanoseconds */
};

struct tm {
	int tm_sec;         /* seconds */
	int tm_min;         /* minutes */
	int tm_hour;        /* hours */
	int tm_mday;        /* day of the month */
	int tm_mon;         /* month */
	int tm_year;        /* year */
	int tm_wday;        /* day of the week */
	int tm_yday;        /* day in the year */
	int tm_isdst;       /* daylight saving time */
};

extern char      *asctime       (const struct tm *timeptr);
extern int        asctime_r     (const struct tm *timeptr, char *asctimeBuf, size_t *buflen);
extern int        clock_gettime (clockid_t clockid, struct timespec *timespec);
extern char      *ctime         (const time_t *timer);
extern char      *ctime_r       (const time_t *timer, char *asctimeBuf, size_t *buflen);
extern double     difftime      (time_t time1, time_t time0);
extern struct tm *gmtime        (const time_t *timer);
extern int        gmtime_r      (const time_t *timer, struct tm *timeBuffer);
extern struct tm *localtime     (const time_t *timer);
extern int        localtime_r   (const time_t *timer, struct tm *timeBuffer);
extern time_t     mktime        (struct tm *timeptr);
extern size_t     strftime      (char *s, size_t n, const char *format, const struct tm *tptr);
extern time_t     time          (time_t *timer);

#endif
