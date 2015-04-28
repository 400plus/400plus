#ifndef VXWORKS_STAT_H_
#define VXWORKS_STAT_H_

extern int fstat   (int fd, struct stat *pStat);
extern int stat    (char *name, struct stat *pStat);
extern int fstatfs (int fd, struct statfs *pStat);
extern int statfs  (char *name, struct statfs *pStat);
extern int utime   (char *file, struct utimbuf *newTimes);

#endif /* VXWORKS_STAT_H_ */
