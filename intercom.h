#ifndef INTERCOM_H_
#define INTERCOM_H_

#define INTERCOM_WAIT 1

extern void intercom_proxy   (const int handler, char *message);
extern int  send_to_intercom (int message, int parm);

#endif /* INTERCOM_H_ */
