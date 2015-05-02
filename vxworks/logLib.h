#ifndef VXWORKS_LOGLIB_H_
#define VXWORKS_LOGLIB_H_

#include "vxworks.h"

STATUS logInit     (int fd, int maxMsgs);
int    logMsg      (char * fmt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void   logFdSet    (int fd);
STATUS logFdAdd    (int fd);
STATUS logFdDelete (int fd);
void   logTask     (void);

#endif /* VXWORKS_LOGLIB_H_ */
