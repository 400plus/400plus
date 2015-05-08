#ifndef VXWORKS_CACHELIB_H_
#define VXWORKS_CACHELIB_H_

#include "vxworks.h"

/* Cache types */

typedef enum {
	INSTRUCTION_CACHE = 0,
    DATA_CACHE        = 1,
    BRANCH_CACHE      = 2
} CACHE_TYPE;

/* Cache modes */

#define	CACHE_DISABLED         0x00
#define	CACHE_WRITETHROUGH     0x01
#define	CACHE_COPYBACK         0x02
#define	CACHE_WRITEALLOCATE    0x04
#define	CACHE_NO_WRITEALLOCATE 0x08
#define	CACHE_SNOOP_ENABLE     0x10
#define	CACHE_SNOOP_DISABLE    0x20
#define	CACHE_BURST_ENABLE     0x40
#define	CACHE_BURST_DISABLE    0x80

typedef	UINT CACHE_MODE;

/* Cache functions */

typedef	struct {
	FUNCPTR	enableRtn;
	FUNCPTR	disableRtn;
	FUNCPTR	lockRtn;
	FUNCPTR	unlockRtn;
	FUNCPTR	flushRtn;
	FUNCPTR	invalidateRtn;
	FUNCPTR	clearRtn;
	FUNCPTR	textUpdateRtn;
	FUNCPTR	pipeFlushRtn;
	FUNCPTR	dmaMallocRtn;
	FUNCPTR	dmaFreeRtn;
	FUNCPTR	dmaVirtToPhysRtn;
	FUNCPTR	dmaPhysToVirtRtn;
} CACHE_LIB;

typedef	struct {
	FUNCPTR	flushRtn;
	FUNCPTR	invalidateRtn;
	FUNCPTR	virtToPhysRtn;
	FUNCPTR	physToVirtRtn;
} CACHE_FUNCS;


STATUS  cacheLibInit       (CACHE_MODE instMode, CACHE_MODE dataMode);
STATUS  cacheEnable        (CACHE_TYPE cache);
STATUS  cacheDisable       (CACHE_TYPE cache);
STATUS  cacheLock          (CACHE_TYPE cache, void *address, size_t bytes);
STATUS  cacheUnlock        (CACHE_TYPE cache, void *address, size_t bytes);
STATUS  cacheFlush         (CACHE_TYPE cache, void *address, size_t bytes);
STATUS  cacheInvalidate    (CACHE_TYPE cache, void *address, size_t bytes);
STATUS  cacheClear         (CACHE_TYPE cache, void *address, size_t bytes);
STATUS  cacheTextUpdate    (void *address, size_t bytes);
void   *cacheDmaMalloc     (size_t bytes);
STATUS  cacheDmaFree       (void *pBuf);
STATUS  cacheDrvFlush      (CACHE_FUNCS *pFuncs, void *address, size_t bytes);
STATUS  cacheDrvInvalidate (CACHE_FUNCS *pFuncs, void *address, size_t bytes);
void   *cacheDrvVirtToPhys (CACHE_FUNCS *pFuncs, void *address);
void   *cacheDrvPhysToVirt (CACHE_FUNCS *pFuncs, void *address);

#endif /* VXWORKS_CACHELIB_H_ */
