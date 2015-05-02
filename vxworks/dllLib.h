#ifndef VXWORKS_DLLLIB_H_
#define VXWORKS_DLLLIB_H_

#include "vxworks.h"

typedef struct dlnode {
    struct dlnode *next;
    struct dlnode *previous;
} DL_NODE;

#endif /* VXWORKS_DLLLIB_H_ */
