#ifndef VXWORKS_INTLIB_H_
#define VXWORKS_INTLIB_H_

#include "vxworks.h"

/* status */


/* intLib.S */
extern BOOL intContext (void);
extern int  intCount   (void);


/* intArchLib.S */
extern int      intLevelSet             (int level);
extern int      intLock                 (void);
extern void     intUnlock               (int lockKey);
extern int      intEnable               (int level);
extern int      intDisable              (int level);
extern STATUS   intConnect              (VOIDFUNCPTR *vector, VOIDFUNCPTR routine, int parameter);
extern void     intLockLevelSet         (int newLevel);
extern int      intLockLevelGet         (void);
extern void     intVecBaseSet           (FUNCPTR *baseAddr);
extern FUNCPTR *intVecBaseGet           (void);
extern STATUS   intVecTableWriteProtect (void);
extern void     intUninitVecSet         (VOIDFUNCPTR routine);

#endif /* VXWORKS_INTLIB_H_ */
