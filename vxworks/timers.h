#ifndef VXWORKS_TIMERS_H_
#define VXWORKS_TIMERS_H_

#include "vxworks.h"

struct timespec {
	time_t tv_sec;
	long   tv_nsec;
};

extern int clock_getres  (clockid_t clock_id, struct timespec *res);
extern int clock_setres  (clockid_t clock_id, struct timespec *res);
extern int clock_gettime (clockid_t clock_id, struct timespec *tp);
extern int clock_settime (clockid_t clock_id, const struct timespec *tp);

#endif /* VXWORKS_TIMERS_H_ */
