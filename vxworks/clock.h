#ifndef CLOCK_H_
#define CLOCK_H_

#include "vxworks.h"
#include "time.h"

extern int clock_getres (clockid_t clk_id, struct timespec *res);
extern int clock_gettime(clockid_t clk_id, struct timespec *tp);
extern int clock_settime(clockid_t clk_id, const struct timespec *tp);

#endif /* CLOCK_H_ */
