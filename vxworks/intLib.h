#ifndef VXWORKS_INTLIB_H_
#define VXWORKS_INTLIB_H_

#include "vxworks.h"

/* status */
#define M_intLib                            0x00430000
#define S_intLib_NOT_ISR_CALLABLE           (M_intLib | 1)
#define S_intLib_VEC_TABLE_WP_UNAVAILABLE   (M_intLib | 2)

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
