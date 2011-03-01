#ifndef TASKS_H_
#define TASKS_H_

extern void start_up();

extern void viewfinder_iso_inc();
extern void viewfinder_iso_dec();
extern void viewfinder_iso_end();

extern void dp_action();

extern void restore_iso();
extern void restore_wb();
extern void restore_metering();

extern void set_metering_spot();
extern void show_factory_menu();

#endif /* TASKS_H_ */
