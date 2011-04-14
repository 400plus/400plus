#ifndef CUSTOM_H_
#define CUSTOM_H_

#define CUSTOM_FILE     "A:/CUSTOM_%u"
#define CUSTOM_VERSION  0x01

extern void custom_read (int id);
extern void custom_write(int id);
extern void custom_apply();

#endif /* CUSTOM_H_ */
