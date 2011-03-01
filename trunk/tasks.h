#ifndef TASKS_H_
#define TASKS_H_

extern void start_up();

void viewfinder_iso_inc();
void viewfinder_iso_dec();
void viewfinder_iso_end();

extern void set_intermediate_iso();
extern void set_metering_spot();
extern void switch_raw_jpeg();
extern void show_factory_menu();
extern void start_debug_mode();

extern void restore_iso();
extern void restore_wb();
extern void restore_metering();

#endif /* TASKS_H_ */
