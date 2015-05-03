#ifndef VXWORKS_REBOOTLIB_H_
#define VXWORKS_REBOOTLIB_H_

#include "vxworks.h"

void   reboot        (int startType);
STATUS rebootHookAdd (FUNCPTR rebootHook);

#endif /* VXWORKS_REBOOTLIB_H_ */
