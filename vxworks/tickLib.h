#ifndef VXWORKS_TICKLIB_H_
#define VXWORKS_TICKLIB_H_

#include "vxworks.h"

extern void  tickAnnounce (void);
extern void  tickSet      (ULONG ticks);
extern ULONG tickGet      (void);

#endif /* VXWORKS_TICKLIB_H_ */
