#ifndef VXWORKS_LOGLIB_H_
#define VXWORKS_LOGLIB_H_

#include "vxworks.h"

extern STATUS logInit     (int fd, int maxMsgs);
extern int    logMsg      (char * fmt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern void   logFdSet    (int fd);
extern STATUS logFdAdd    (int fd);
extern STATUS logFdDelete (int fd);
extern void   logTask     (void);

#endif /* VXWORKS_LOGLIB_H_ */
