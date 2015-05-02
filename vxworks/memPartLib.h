#ifndef VXWORKS_MEMPARTLIB_H_
#define VXWORKS_MEMPARTLIB_H_

#include "memLib.h"
#include "vxworks.h"

PART_ID  memPartCreate       (char * pPool, unsigned poolSize);
STATUS   memPartAddToPool    (PART_ID partId, char * pPool, unsigned poolSize);
void    *memPartAlignedAlloc (PART_ID partId, unsigned nBytes, unsigned alignment);
void    *memPartAlloc        (PART_ID partId, unsigned nBytes);
STATUS   memPartFree         (PART_ID partId, char * pBlock);
void     memAddToPool        (char * pPool, unsigned poolSize);
void    *malloc              (size_t nBytes);
void     free                (void * ptr);

#endif /* VXWORKS_MEMPARTLIB_H_ */
