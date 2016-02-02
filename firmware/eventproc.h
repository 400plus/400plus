#ifndef EVENTPROC_H_
#define EVENTPROC_H_

// Event generation

extern int eventproc_RiseEvent(const char *event);

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// Main display

extern int eventproc_PrintICUInfo(void);

// Shutter release

extern int eventproc_Release(void);

// Remote

extern int eventproc_RemOn(void);
extern int eventproc_RemOff(void);

#endif
