#include <vxworks.h>

#include "macros.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"

#include "menu_info.h"

menuitem_t menupage_info_items[] = {
	MENUITEM_INFO (MENUPAGE_INFO_VERSION,  LP_WORD(L_I_VERSION),        VERSION),
	MENUITEM_PARAM(MENUPAGE_INFO_RELEASE,  LP_WORD(L_I_RELEASE_COUNT), &FLAG_RELEASE_COUNT),
	MENUITEM_PARAM(MENUPAGE_INFO_BODYID,   LP_WORD(L_I_BODY_ID),       &FLAG_BODY_ID),
	MENUITEM_INFO (MENUPAGE_INFO_FIRMWARE, LP_WORD(L_I_FIRMWARE),       FIRMWARE_VERSION),
	MENUITEM_INFO (MENUPAGE_INFO_OWNER,    LP_WORD(L_I_OWNER),          OWNER_NAME),
};

menupage_t menupage_info = {
	name        : LP_WORD(L_P_INFO),
	sibilings   : TRUE,
	items       : LIST(menupage_info_items),
	ordering    : menu_order.info,
};
