#ifndef VXWORKS_ENVLIB_H_
#define VXWORKS_ENVLIB_H_

extern int   envLibInit        (BOOL installHooks);
extern int   envPrivateCreate  (int taskId, int envSource);
extern int   envPrivateDestroy (int taskId);
extern int   putenv            (char *pEnvString);
extern char *getenv            (const char *name);
extern void  envShow           (int taskId);

#endif /* VXWORKS_ENVLIB_H_ */
