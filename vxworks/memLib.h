#ifndef VXWORKS_MEMLIB_H_
#define VXWORKS_MEMLIB_H_

#include "vxworks.h"

typedef struct {} *PART_ID;
typedef struct {} MEM_PART_STATS;

STATUS  memPartOptionsSet (PART_ID partId, unsigned options);
void   *memalign          (unsigned alignment, unsigned size);
void   *valloc            (unsigned size);
void   *memPartRealloc    (PART_ID partId, char * pBlock, unsigned nBytes);
int     memPartFindMax    (PART_ID partId);
void    memOptionsSet     (unsigned options);
void   *calloc            (size_t elemNum, size_t elemSize);
void   *realloc           (void * pBlock, size_t newSize);
STATUS  cfree             (char * pBlock);
int     memFindMax        (void);

#endif /* VXWORKS_MEMLIB_H_ */
