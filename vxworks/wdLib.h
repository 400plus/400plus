#ifndef VXWORKS_WDLIB_H_
#define VXWORKS_WDLIB_H_

#include "vxworks.h"

typedef struct {} *WDOG_ID;

extern WDOG_ID wdCreate (void);
extern STATUS  wdDelete (WDOG_ID wdId);
extern STATUS  wdStart  (WDOG_ID wdId, int delay, FUNCPTR pRoutine, int parameter);
extern STATUS  wdCancel (WDOG_ID wdId);

#endif /* VXWORKS_WDLIB_H_ */
