#ifndef VXWORKS_MEMSHOW_H_
#define VXWORKS_MEMSHOW_H_

#include "memLib.h"
#include "vxworks.h"

extern void   memShowInit    (void);
extern void   memShow        (int type);
extern STATUS memPartShow    (PART_ID partId, int type);
extern STATUS memPartInfoGet (PART_ID partId, MEM_PART_STATS * ppartStats);

#endif /* VXWORKS_MEMSHOW_H_ */
