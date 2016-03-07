#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_

#define SHORTCUT_LABEL_ISO     " ISO "
#define SHORTCUT_LABEL_MLU     " MLU "
#define SHORTCUT_LABEL_AEB     " AEB "
#define	SHORTCUT_LABEL_FLASH   "FLASH"
#define	SHORTCUT_LABEL_DISPLAY "DISPL"

extern void shortcut_jump  (void);
extern void shortcut_trash (void);
extern void shortcut_disp  (void);
extern void shortcut_stop  (void);

extern void shortcut_event_disp  (void);
extern void shortcut_event_end   (void);
extern void shortcut_event_av    (void);
extern void shortcut_event_set   (void);
extern void shortcut_event_up    (void);
extern void shortcut_event_down  (void);
extern void shortcut_event_right (void);
extern void shortcut_event_left  (void);

#endif
