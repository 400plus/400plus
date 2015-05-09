#ifndef VXWORKS_EXCLIB_H_
#define VXWORKS_EXCLIB_H_

#include "vxworks.h"

extern STATUS excVecInit       (void);
extern STATUS excConnect       (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
extern STATUS excIntConnect    (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
extern STATUS excCrtConnect    (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
extern STATUS excIntCrtConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
extern void   excVecSet        (FUNCPTR * vector, FUNCPTR function);
extern FUNCPTR excVecGet       (FUNCPTR * vector);

#endif /* VXWORKS_EXCLIB_H_ */
