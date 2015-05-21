#ifndef VXWORKS_REBOOTLIB_H_
#define VXWORKS_REBOOTLIB_H_

#include "vxworks.h"

extern void   reboot        (int startType);
extern STATUS rebootHookAdd (FUNCPTR rebootHook);

#endif /* VXWORKS_REBOOTLIB_H_ */
