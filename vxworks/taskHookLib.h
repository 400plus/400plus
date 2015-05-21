#ifndef VXWORKS_TASKHOOKLIB_H_
#define VXWORKS_TASKHOOKLIB_H_

extern void   taskHookInit         (void);
extern STATUS taskCreateHookAdd    (FUNCPTR createHook);
extern STATUS taskCreateHookDelete (FUNCPTR createHook);
extern STATUS taskSwitchHookAdd    (FUNCPTR switchHook);
extern STATUS taskSwitchHookDelete (FUNCPTR switchHook);
extern STATUS taskDeleteHookAdd    (FUNCPTR deleteHook);
extern STATUS taskDeleteHookDelete (FUNCPTR deleteHook);

#endif /* VXWORKS_TASKHOOKLIB_H_ */
