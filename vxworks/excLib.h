#ifndef VXWORKS_EXCLIB_H_
#define VXWORKS_EXCLIB_H_

#include "vxworks.h"

STATUS excVecInit       (void);
STATUS excConnect       (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
STATUS excIntConnect    (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
STATUS excCrtConnect    (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
STATUS excIntCrtConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
void   excVecSet        (FUNCPTR * vector, FUNCPTR function);
FUNCPTR excVecGet       (FUNCPTR * vector);

#endif /* VXWORKS_EXCLIB_H_ */
