#ifndef VXWORKS_SELECTLIB_H_
#define VXWORKS_SELECTLIB_H_

#include "vxworks.h"

typedef enum {
    SELREAD,
    SELWRITE
} SELECT_TYPE;

typedef struct {} SEL_WAKEUP_NODE;
typedef struct {} SEL_WAKEUP_LIST;

void        selectInit        (int numFiles);
int         select            (int width, fd_set *pReadFds, fd_set *pWriteFds, fd_set *pExceptFds, struct timeval *pTimeOut);
void        selWakeup         (SEL_WAKEUP_NODE *pWakeupNode);
void        selWakeupAll      (SEL_WAKEUP_LIST *pWakeupList, SELECT_TYPE type);
STATUS      selNodeAdd        (SEL_WAKEUP_LIST *pWakeupList, SEL_WAKEUP_NODE *pWakeupNode);
STATUS      selNodeDelete     (SEL_WAKEUP_LIST *pWakeupList, SEL_WAKEUP_NODE *pWakeupNode);
void        selWakeupListInit (SEL_WAKEUP_LIST *pWakeupList);
void        selWakeupListTerm (SEL_WAKEUP_LIST *pWakeupList);
int         selWakeupListLen  (SEL_WAKEUP_LIST *pWakeupList);
SELECT_TYPE selWakeupType     (SEL_WAKEUP_NODE *pWakeupNode);

#endif /* VXWORKS_SELECTLIB_H_ */
