#ifndef VXWORKS_RNGLIB_H_
#define VXWORKS_RNGLIB_H_

#include "vxworks.h"

typedef struct {} RING;
typedef RING *RING_ID;

extern RING_ID rngCreate    (int nbytes);
extern void    rngDelete    (RING_ID ringId);
extern void    rngFlush     (RING_ID ringId);
extern int     rngBufGet    (RING_ID rngId, char buffer, int maxbytes);
extern int     rngBufPut    (RING_ID rngId, char buffer, int nbytes);
extern BOOL    rngIsEmpty   (RING_ID ringId);
extern BOOL    rngIsFull    (RING_ID ringId);
extern int     rngFreeBytes (RING_ID ringId);
extern int     rngNBytes    (RING_ID ringId);
extern void    rngPutAhead  (RING_ID ringId, char byte, int offset);
extern void    rngMoveAhead (RING_ID ringId, int n);

#endif /* VXWORKS_RNGLIB_H_ */
