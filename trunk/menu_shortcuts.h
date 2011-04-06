#ifndef MENU_SHORTCUTS_H_
#define MENU_SHORTCUTS_H_

#define MENUITEM_YESNO(_NAME_, _VALUE_) MENUITEM_ENUM(_NAME_, _VALUE_, FALSE, yesno_strings)

extern void menu_shortcuts_start();
extern void menu_shortcuts_save();

#endif /* MENU_SHORTCUTS_H_ */
