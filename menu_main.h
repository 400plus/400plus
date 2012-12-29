/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MENU_MAIN_H_
#define MENU_MAIN_H_

extern void menu_main_start();
extern void menu_main_save ();

typedef enum {
	MENUPAGE_PARAMS,
	MENUPAGE_SCRIPTS,
	MENUPAGE_INFO,
	MENUPAGE_SETTINGS,
	MENUPAGE_CMODES,
} MENUPAGE;

#endif /* MENU_MAIN_H_ */
