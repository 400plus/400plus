#ifndef VXWORKS_IOSLIB_H_
#define VXWORKS_IOSLIB_H_

#include "dllLib.h"
#include "vxworks.h"

typedef struct {
	DL_NODE	 node;
	short	 drvNum;
	char    *name;
} DEV_HDR;

extern STATUS   iosInit       (int max_drivers, int max_files, char * nullDevName);
extern int      iosDrvInstall (FUNCPTR pCreate, FUNCPTR pDelete, FUNCPTR pOpen, FUNCPTR pClose, FUNCPTR pRead, FUNCPTR pWrite, FUNCPTR pIoctl);
extern STATUS   iosDrvRemove  (int drvnum, BOOL forceClose);
extern STATUS   iosDevAdd     (DEV_HDR *pDevHdr, char *name, int drvnum);
extern void     iosDevDelete  (DEV_HDR *pDevHdr);
extern DEV_HDR *iosDevFind    (char *name, char **pNameTail);
extern int      iosFdValue    (int fd);

#endif /* VXWORKS_IOSLIB_H_ */
