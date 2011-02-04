    .text
    .org 0


#define DEF(n,a) \
    .globl n; n = a

#define NSTUB(name, addr)\
    .globl name ;\
    .weak name ;\
    name: ;\
	ldr  pc, = addr

#define NHSTUB(name, addr)\
    .globl name ;\
    name: ;\
	ldr  pc, = addr

#define STUB(addr)\
    .globl sub_ ## addr ; sub_ ## addr = 0x ## addr

// vars

DEF(addr_0x1900,0x1900)
DEF(cache_0x1900,0xFFB602F0)
DEF(bss_begin,0x00DFB0)
DEF(bss_end,0x02A550)
DEF(sysStartType,0x028F60)
DEF(readyQHead        ,0x028DE0)
DEF(qPriBMapClassId   ,0x00D840)
DEF(readyQBMap        ,0x0298A0)
DEF(activeQHead       ,0x00D6E8)
DEF(qFifoClassId      ,0x00D880)
DEF(tickQHead         ,0x025A20)
DEF(qPriListClassId   ,0x00D7C4)
DEF(proc_sysMmuLibInit ,0x00DE5C)
DEF(MemDescArray       ,0x001918)
DEF(MemDescArrayCount  ,0x00197C)
DEF(fdConsole          ,0x00199C)
DEF(hResourceName,0x00CFD4)

DEF(OlcInfoData,0x0179E8)
DEF(OlcInfoChangedFlags,0x017AA8)
DEF(OlcInfoFlags,0x027E48)
DEF(hOlcInfoSem,0x017B0C)
DEF(hOlcInfoMessQueue,0x017B08)
DEF(OlcInfoEmptyStr,0xFF9408A8)
DEF(proc_OlcTftNotifyChange,0x005580)
DEF(OlcNotifyFreeze,0x005584)
DEF(OlcNotifyChangeInProgress,0x005594)
DEF(OlcCounterFlag1,0x005588)
DEF(OlcCounterFlag2,0x00558C)
DEF(OlcCounterFlag3,0x005590)

// 
STUB(FFB5F728)
STUB(FFB0FF74)
STUB(FFB2E108)
STUB(FFAFE5BC)
STUB(FFB07740)
STUB(FFB2BD6C)
STUB(FFA03B0C)
STUB(FFA05114)
STUB(FFA24838)
STUB(FFA35354)
STUB(FF926E40)
STUB(FFB29348)
STUB(FFA5D8A0)
STUB(FF95EC54)
STUB(FF9EB94C)
STUB(FF98CF4C)



// procs
#include  "funclist.txt"

.align 2
