#ifndef VXWORKS_MEMPARTLIB_H_
#define VXWORKS_MEMPARTLIB_H_

#include "memLib.h"
#include "vxworks.h"

extern PART_ID  memPartCreate       (char * pPool, unsigned poolSize);
extern STATUS   memPartAddToPool    (PART_ID partId, char * pPool, unsigned poolSize);
extern void    *memPartAlignedAlloc (PART_ID partId, unsigned nBytes, unsigned alignment);
extern void    *memPartAlloc        (PART_ID partId, unsigned nBytes);
extern STATUS   memPartFree         (PART_ID partId, char * pBlock);
extern void     memAddToPool        (char * pPool, unsigned poolSize);
extern void    *malloc              (size_t nBytes);
extern void     free                (void * ptr);

#endif /* VXWORKS_MEMPARTLIB_H_ */
