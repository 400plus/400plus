#ifndef VXWORKS_BOOTLIB_H_
#define VXWORKS_BOOTLIB_H_

#include "vxworks.h"

typedef struct {
	char bootDev       [BOOT_DEV_LEN];
	char hostName      [BOOT_HOST_LEN];
	char targetName    [BOOT_HOST_LEN];
	char ead           [BOOT_ADDR_LEN];
	char bad           [BOOT_ADDR_LEN];
	char had           [BOOT_ADDR_LEN];
	char gad           [BOOT_ADDR_LEN];
	char bootFile      [BOOT_FILE_LEN];
	char startupScript [BOOT_FILE_LEN];
	char usr           [BOOT_USR_LEN];
	char passwd        [BOOT_PASSWORD_LEN];
	char other         [BOOT_OTHER_LEN];
	int  procNum;
	int  flags;
} BOOT_PARAMS;

extern STATUS  bootBpAnchorExtract  (char *string, char ** pAnchorAdrs);
extern STATUS  bootNetmaskExtract   (char *string, int *pNetmask);
extern STATUS  bootStructToString   (char *paramString, BOOT_PARAMS *pBootParams);
extern char   *bootStringToStruct   (char *bootString, BOOT_PARAMS *pBootParams);
extern void    bootParamsErrorPrint (char *bootString, char *pError);
extern void    bootParamsPrompt     (char *string);
extern void    bootParamsShow       (char *paramString);

#endif /* VXWORKS_BOOTLIB_H_ */

