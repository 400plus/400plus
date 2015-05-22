#ifndef VXWORKS_TIME_H_
#define VXWORKS_TIME_H_

#include "vxworks.h"

typedef int clockid_t;

#define CLOCK_REALTIME	0x00
#define TIMER_ABSTIME	0x01

typedef long int time_t;
typedef long int clock_t;

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct timespec {
	time_t tv_sec;
	long   tv_nsec;
};

struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};

extern char      *asctime     (const struct tm *timeptr);
extern int        asctime_r   (const struct tm *timeptr, char *asctimeBuf, size_t *buflen);
extern clock_t    clock       (void);
extern char      *ctime       (const time_t *timer);
extern char      *ctime_r     (const time_t *timer, char *asctimeBuf, size_t *buflen);
extern double     difftime    (time_t time1, time_t time0);
extern struct tm *gmtime      (const time_t *timer);
extern int        gmtime_r    (const time_t *timer, struct tm *timeBuffer);
extern struct tm *localtime   (const time_t *timer);
extern int        localtime_r (const time_t *timer, struct tm *timeBuffer);
extern time_t     mktime      (struct tm *timeptr);
extern size_t     strftime    (char *s, size_t n, const char *format, const struct tm *tptr);
extern time_t     time        (time_t *timer);

#endif /* VXWORKS_TIME_H_ */
