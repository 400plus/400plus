#ifndef VXWORKS_TYLIB_H_
#define VXWORKS_TYLIB_H_

#include "vxworks.h"

typedef struct {} TY_DEV;
typedef TY_DEV *TY_DEV_ID;

extern STATUS tyDevInit        (TY_DEV_ID pTyDev, int rdBufSize, int wrtBufSize, FUNCPTR txStartup);
extern STATUS tyDevRemove      (TY_DEV_ID pTyDev);
extern STATUS tyIRd            (TY_DEV_ID pTyDev, char inchar);
extern STATUS tyITx            (TY_DEV_ID pTyDev, char *pChar);
extern STATUS tyIoctl          (TY_DEV_ID pTyDev, int request, int arg);
extern int    tyRead           (TY_DEV_ID pTyDev, char *buffer, int maxbytes);
extern int    tyWrite          (TY_DEV_ID pTyDev, char *buffer, int nbytes);
extern void   tyAbortFuncSet   (FUNCPTR func);
extern void   tyAbortSet       (char ch);
extern void   tyBackspaceSet   (char ch);
extern void   tyDeleteLineSet  (char ch);
extern void   tyEOFSet         (char ch);
extern void   tyMonitorTrapSet (char ch);

#endif /* VXWORKS_TYLIB_H_ */
