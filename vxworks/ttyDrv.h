#ifndef VXWORKS_TTYDRV_H_
#define VXWORKS_TTYDRV_H_

#include "sioLib.h"

STATUS ttyDrv       (void);
STATUS ttyDevCreate (char *name, SIO_CHAN *pSioChan, int rdBufSize, int wrtBufSize);

#endif /* VXWORKS_TTYDRV_H_ */
