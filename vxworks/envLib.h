#ifndef VXWORKS_ENVLIB_H_
#define VXWORKS_ENVLIB_H_

#include "vxworks.h"

extern STATUS envLibInit        (BOOL installHooks);
extern STATUS envPrivateCreate  (int taskId, int envSource);
extern STATUS envPrivateDestroy (int taskId);
extern STATUS putenv            (char *pEnvString);
extern char  *getenv            (const char *name);
extern void   envShow           (int taskId);

#endif /* VXWORKS_ENVLIB_H_ */
