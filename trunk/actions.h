/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef ACTIONS_H_
#define ACTIONS_H_

#define ACTION_MSG_TIMEOUT 2000
#define ACTION_AEB_TIMEOUT 1500

extern void start_up(void);

extern void dp_action(void);

extern void toggle_img_format     (void);
extern void toggle_CfMLU          (void);
extern void toggle_CfEmitFlash    (void);
extern void toggle_CfFlashSyncRear(void);
extern void toggle_AEB            (void);

extern void restore_iso     (void);
extern void restore_wb      (void);
extern void restore_metering(void);

extern void set_intermediate_iso      (void);
extern void set_metering_spot         (void);
extern void set_whitebalance_colortemp(void);

extern void button_jump_action (void);
extern void button_trash_action(void);

void drivemode_set(void);

#endif
