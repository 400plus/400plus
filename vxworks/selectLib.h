#ifndef VXWORKS_SELECTLIB_H_
#define VXWORKS_SELECTLIB_H_

#include "vxworks.h"

typedef enum {
    SELREAD,
    SELWRITE
} SELECT_TYPE;

typedef struct {} SEL_WAKEUP_NODE;
typedef struct {} SEL_WAKEUP_LIST;

extern void        selectInit        (int numFiles);
extern int         select            (int width, fd_set *pReadFds, fd_set *pWriteFds, fd_set *pExceptFds, struct timeval *pTimeOut);
extern void        selWakeup         (SEL_WAKEUP_NODE *pWakeupNode);
extern void        selWakeupAll      (SEL_WAKEUP_LIST *pWakeupList, SELECT_TYPE type);
extern STATUS      selNodeAdd        (SEL_WAKEUP_LIST *pWakeupList, SEL_WAKEUP_NODE *pWakeupNode);
extern STATUS      selNodeDelete     (SEL_WAKEUP_LIST *pWakeupList, SEL_WAKEUP_NODE *pWakeupNode);
extern void        selWakeupListInit (SEL_WAKEUP_LIST *pWakeupList);
extern void        selWakeupListTerm (SEL_WAKEUP_LIST *pWakeupList);
extern int         selWakeupListLen  (SEL_WAKEUP_LIST *pWakeupList);
extern SELECT_TYPE selWakeupType     (SEL_WAKEUP_NODE *pWakeupNode);

#endif /* VXWORKS_SELECTLIB_H_ */
