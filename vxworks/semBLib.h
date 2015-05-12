/*
 * semBLib.h
 *
 *  Created on: May 14, 2015
 *      Author: eperez
 */

#ifndef VXWORKS_SEMBLIB_H_
#define VXWORKS_SEMBLIB_H_

#include "vxworks.h"

/* status */
#define M_semLib                        0x00160000
#define S_semLib_INVALID_STATE			(M_semLib | 101)
#define S_semLib_INVALID_OPTION			(M_semLib | 102)
#define S_semLib_INVALID_QUEUE_TYPE		(M_semLib | 103)
#define S_semLib_INVALID_OPERATION		(M_semLib | 104)

/* options */
#define SEM_Q_FIFO          0x00
#define SEM_Q_PRIORITY      0x01
#define SEM_Q_MASK          0x03
#define SEM_DELETE_SAFE     0x04
#define SEM_INVERSION_SAFE  0x08

typedef enum {
	SEM_EMPTY,
	SEM_FULL
} SEM_B_STATE;

typedef struct {} *SEM_ID;

SEM_ID semBCreate (int options, SEM_B_STATE initialState);

#endif /* VXWORKS_SEMBLIB_H_ */
