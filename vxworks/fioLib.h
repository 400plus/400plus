#ifndef VXWORKS_FIOLIB_H_
#define VXWORKS_FIOLIB_H_

#include "vxworks.h"

extern void fioLibInit    (void);
extern int  fioFormatV    (const char *fmt, va_list vaList, FUNCPTR outRoutine, int outarg);
extern int  fioRead       (int fd, char *buffer, int maxbytes);
extern int  fioRdString   (int fd, char string[], int maxbytes);

#endif /* VXWORKS_FIOLIB_H_ */
