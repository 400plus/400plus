/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MENU_MAIN_H_
#define MENU_MAIN_H_

extern void menu_main_start();
extern void menu_main_save ();

enum {
	MENUPAGE_PARAMS,
	MENUPAGE_SCRIPTS,
	MENUPAGE_INFO,
	MENUPAGE_SETTINGS,
	MENUPAGE_CMODES,
	MENUPAGE_COUNT,
	MENUPAGE_FIRST = 0,
	MENUPAGE_LAST  = MENUPAGE_COUNT - 1
};

#endif /* MENU_MAIN_H_ */
