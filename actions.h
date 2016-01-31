#ifndef ACTIONS_H_
#define ACTIONS_H_

extern void dp_action(void);

extern void set_metering_spot          (void);
extern void set_whitebalance_colortemp (void);
extern void toggle_img_format          (void);

extern void restore_iso      (void);
extern void restore_wb       (void);
extern void restore_metering (void);

void drivemode_set(void);

#endif
