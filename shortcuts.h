#ifndef SHORTCUTS_H_
#define SHORTCUTS_H_

#define ACTION_MSG_TIMEOUT 2000
#define ACTION_AEB_TIMEOUT 1500

extern void shortcut_jump  (void);
extern void shortcut_trash (void);

extern void shortcut_event_end   (void);
extern void shortcut_event_set   (void);
extern void shortcut_event_up    (void);
extern void shortcut_event_down  (void);
extern void shortcut_event_right (void);
extern void shortcut_event_left  (void);

#endif
