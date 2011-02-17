#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  6

typedef struct {
	int iso_in_viewfinder;
	int dp_opt;
	int eaeb_frames;
	int eaeb_delay;
	int eaeb_ev;
	int eaeb_m_min;
	int eaeb_m_max;
	int interval_time;
	int ir_inst;
} type_SETTINGS;

extern type_SETTINGS settings;

extern void settings_read();
extern void settings_write();

#endif /* SETTINGS_H_ */
