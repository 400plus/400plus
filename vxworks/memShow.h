#ifndef VXWORKS_MEMSHOW_H_
#define VXWORKS_MEMSHOW_H_

#include "memLib.h"
#include "vxworks.h"

void   memShowInit    (void);
void   memShow        (int type);
STATUS memPartShow    (PART_ID partId, int type);
STATUS memPartInfoGet (PART_ID partId, MEM_PART_STATS * ppartStats);

#endif /* VXWORKS_MEMSHOW_H_ */
