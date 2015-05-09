#ifndef VXWORKS_ERRNOLIB_H_
#define VXWORKS_ERRNOLIB_H_

#include "vxworks.h"

extern int    errnoGet       (void);
extern int    errnoOfTaskGet (int taskId);
extern STATUS errnoSet       (int errorValue);
extern STATUS errnoOfTaskSet (int taskId, int errorValue);

#endif /* VXWORKS_ERRNOLIB_H_ */
