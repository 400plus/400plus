#ifndef MESSAGE_H_
#define MESSAGE_H_

extern int ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int FOREVER);
extern int PostMessageQueue(void *hMessageQueue, void *pMessage, int FOREVER);

#endif /* MESSAGE_H_ */
