#ifndef VXWORKS_KERNELLIB_H_
#define VXWORKS_KERNELLIB_H_

#include "vxworks.h"

extern void    kernelInit      (FUNCPTR rootRtn, unsigned rootMemSize, char *pMemPoolStart, char *pMemPoolEnd, unsigned intStackSize, int lockOutLevel);
extern char   *kernelVersion   (void)
extern STATUS  kernelTimeSlice (int ticks);

#endif /* VXWORKS_KERNELLIB_H_ */
