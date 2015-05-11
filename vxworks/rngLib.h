#ifndef VXWORKS_RNGLIB_H_
#define VXWORKS_RNGLIB_H_

#include "vxworks.h"

typedef struct {} RING;
typedef RING *RING_ID;

RING_ID rngCreate    (int nbytes);
void    rngDelete    (RING_ID ringId);
void    rngFlush     (RING_ID ringId);
int     rngBufGet    (RING_ID rngId, char buffer, int maxbytes);
int     rngBufPut    (RING_ID rngId, char buffer, int nbytes);
BOOL    rngIsEmpty   (RING_ID ringId);
BOOL    rngIsFull    (RING_ID ringId);
int     rngFreeBytes (RING_ID ringId);
int     rngNBytes    (RING_ID ringId);
void    rngPutAhead  (RING_ID ringId, char byte, int offset);
void    rngMoveAhead (RING_ID ringId, int n);

#endif /* VXWORKS_RNGLIB_H_ */
