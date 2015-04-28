#ifndef VXWORKS_STAT_H_
#define VXWORKS_STAT_H_

int fstat   (int fd, struct stat *pStat);
int stat    (char *name, struct stat *pStat);
int fstatfs (int fd, struct statfs *pStat);
int statfs  (char *name, struct statfs *pStat);
int utime   (char *file, struct utimbuf *newTimes);

#endif /* VXWORKS_STAT_H_ */
