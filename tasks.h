#ifndef TASKS_H_
#define TASKS_H_

extern void start_up();

extern void dp_action();
extern void switch_raw_jpeg();

extern void restore_iso();
extern void restore_wb();
extern void restore_metering();

extern void set_metering_spot();
extern void set_whitebalance_colortemp();
extern void set_iso_high();

extern void factory_or_debug();

#endif /* TASKS_H_ */
