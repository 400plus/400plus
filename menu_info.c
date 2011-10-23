#include "main.h"
#include "firmware.h"

#include "menu.h"
#include "menuitem.h"
#include "settings.h"

#include "menu_info.h"

int version = VERSION;

type_MENUITEM menupage_info_items[] = {
	MENUITEM_INFO("Release count", &FLAG_RELEASE_COUNT),
	MENUITEM_INFO("Body  ID     ", &BodyID),
	MENUITEM_INFO("Version      ", &version),
};

type_MENUPAGE menupage_info = {
	name        : "Info",
	length      : LENGTH(menupage_info_items),
	items       : menupage_info_items,
	ordering    : settings.info_order,
};
