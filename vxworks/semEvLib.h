#ifndef VXWORKS_SEMEVLIB_H_
#define VXWORKS_SEMEVLIB_H_

#include "vxworks.h"
#include "semLib.h"

extern STATUS semEvStart (SEM_ID semId, UINT32 events, UINT8 options);
extern STATUS semEvStop  (SEM_ID semId);

#endif /* VXWORKS_SEMEVLIB_H_ */
