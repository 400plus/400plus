#ifndef LOWLEVEL_H_
#define LOWLEVEL_H_

extern void* cache_0xFFB602F0;
extern void* addr_0x1900;

extern long bss_begin;
extern long bss_end;

extern long sysStartType;

extern void* readyQHead;
extern void* readyQBMap;

extern void* qPriBMapClassId;
extern void* qFifoClassId;
extern void* qPriListClassId;

extern void* hResourceName;
extern void* hOlcInfoMessQueue;

extern void* activeQHead;
extern void* tickQHead;

extern long* proc_sysMmuLibInit;

extern void* MemDescArray;
extern long  MemDescArrayCount;

extern long fdConsole;

extern void usrClock();
extern void AssertPrepare();

#endif /* LOWLEVEL_H_ */
