#ifndef VXWORKS_STAT_H_
#define VXWORKS_STAT_H_

#include "vxworks.h"

extern STATUS fstat   (int fd, struct stat *pStat);
extern STATUS stat    (char *name, struct stat *pStat);
extern STATUS fstatfs (int fd, struct statfs *pStat);
extern STATUS statfs  (char *name, struct statfs *pStat);
extern int    utime   (char *file, struct utimbuf *newTimes);

#endif /* VXWORKS_STAT_H_ */
