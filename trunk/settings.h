#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  7

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
	int color_temp;
	int av_comp;
	int flash_comp;
	int aeb_ev;
} type_SETTINGS;

extern type_SETTINGS settings;

extern void settings_read();
extern void settings_write();

#endif /* SETTINGS_H_ */
