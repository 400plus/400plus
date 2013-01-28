#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"

#include "menu_info.h"

type_MENUITEM menupage_info_items[] = {
	MENUITEM_PARAM(LP_WORD(L_I_RELEASE_COUNT), &FLAG_RELEASE_COUNT),
	MENUITEM_PARAM(LP_WORD(L_I_BODY_ID),       &BodyID),
	MENUITEM_INFO (LP_WORD(L_I_VERSION),        VERSION),
};

type_MENUPAGE menupage_info = {
	name        : LP_WORD(L_P_INFO),
	sibilings   : TRUE,
	length      : LENGTH(menupage_info_items),
	items       : menupage_info_items,
	ordering    : settings.info_order,
};
