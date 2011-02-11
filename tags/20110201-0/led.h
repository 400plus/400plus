#ifndef LED_H_
#define LED_H_

#define LED_RED  (*((int*)0xC02200A0))
#define LED_BLUE (*((int*)0xC0220000))
#define LED_ON   0x46
#define LED_OFF  0x44

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

#endif /* LED_H_ */
