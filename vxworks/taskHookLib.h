#ifndef VXWORKS_TASKHOOKLIB_H_
#define VXWORKS_TASKHOOKLIB_H_

void   taskHookInit         (void);
STATUS taskCreateHookAdd    (FUNCPTR createHook);
STATUS taskCreateHookDelete (FUNCPTR createHook);
STATUS taskSwitchHookAdd    (FUNCPTR switchHook);
STATUS taskSwitchHookDelete (FUNCPTR switchHook);
STATUS taskDeleteHookAdd    (FUNCPTR deleteHook);
STATUS taskDeleteHookDelete (FUNCPTR deleteHook);

#endif /* VXWORKS_TASKHOOKLIB_H_ */
