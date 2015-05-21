#ifndef VXWORKS_MSGQEVLIB_H_
#define VXWORKS_MSGQEVLIB_H_

#include "vxworks.h"
#include "msgQLib.h"

extern STATUS msgQEvStart (MSG_Q_ID msgQId, UINT32 events, UINT8 options);
extern STATUS msgQEvStop  (MSG_Q_ID msgQId);

#endif /* VXWORKS_MSGQEVLIB_H_ */
