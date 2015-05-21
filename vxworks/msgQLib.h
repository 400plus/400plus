#ifndef VXWORKS_MSGQLIB_H_
#define VXWORKS_MSGQLIB_H_

#include "vxworks.h"

/* priorities */
#define MSG_PRI_NORMAL  0
#define MSG_PRI_URGENT  1

/* options */
#define MSG_Q_TYPE_MASK  0x01
#define MSG_Q_FIFO       0x00
#define MSG_Q_PRIORITY   0x01

/* status */
#define M_msgQLib                                0x00410000
#define S_msgQLib_INVALID_MSG_LENGTH             (M_msgQLib | 1)
#define S_msgQLib_NON_ZERO_TIMEOUT_AT_INT_LEVEL  (M_msgQLib | 2)
#define S_msgQLib_INVALID_QUEUE_TYPE             (M_msgQLib | 3)

typedef struct {} *MSG_Q_ID;

extern MSG_Q_ID msgQCreate  (int maxMsgs, int maxMsgLength, int options);
extern STATUS   msgQDelete  (MSG_Q_ID msgQId);
extern STATUS   msgQSend    (MSG_Q_ID msgQId, char *buffer, UINT nBytes, int timeout, int priority);
extern int      msgQReceive (MSG_Q_ID msgQId, char *buffer, UINT maxNBytes, int timeout);
extern int      msgQNumMsgs (MSG_Q_ID msgQId);

#endif /* VXWORKS_MSGQLIB_H_ */
