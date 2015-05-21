#ifndef VXWORKS_MEMLIB_H_
#define VXWORKS_MEMLIB_H_

#include "vxworks.h"

/* status */
#define M_memLib                       0x00110000
#define S_memLib_NOT_ENOUGH_MEMORY     (M_memLib | 1)
#define S_memLib_INVALID_NBYTES        (M_memLib | 2)
#define S_memLib_BLOCK_ERROR           (M_memLib | 3)
#define S_memLib_NO_PARTITION_DESTROY  (M_memLib | 4)
#define S_memLib_PAGE_SIZE_UNAVAILABLE (M_memLib | 5)

typedef struct {} *PART_ID;
typedef struct {}  MEM_PART_STATS;

extern STATUS  memPartOptionsSet (PART_ID partId, unsigned options);
extern void   *memalign          (unsigned alignment, unsigned size);
extern void   *valloc            (unsigned size);
extern void   *memPartRealloc    (PART_ID partId, char *pBlock, unsigned nBytes);
extern int     memPartFindMax    (PART_ID partId);
extern void    memOptionsSet     (unsigned options);
extern void   *calloc            (size_t elemNum, size_t elemSize);
extern void   *realloc           (void * pBlock, size_t newSize);
extern STATUS  cfree             (char * pBlock);
extern int     memFindMax        (void);

#endif /* VXWORKS_MEMLIB_H_ */
