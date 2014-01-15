/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MENU_INFO_H_
#define MENU_INFO_H_

#ifndef VERSION
#define VERSION "UNDEFINED"
#endif

#include "menupage.h"

enum {
	MENUPAGE_INFO_VERSION,
	MENUPAGE_INFO_RELEASE,
	MENUPAGE_INFO_BODYID,
	MENUPAGE_INFO_FIRMWARE,
	MENUPAGE_INFO_OWNER,
	MENUPAGE_INFO_COUNT,
	MENUPAGE_INFO_FIRST = 0,
	MENUPAGE_INFO_LAST  = MENUPAGE_INFO_COUNT - 1
};

extern menupage_t menupage_info;

#endif /* MENU_INFO_H_ */
