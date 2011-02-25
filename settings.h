#ifndef SETTINGS_H_
#define SETTINGS_H_

#define SETTINGS_FILE     "A:/SETTINGS"
#define SETTINGS_VERSION  0x09

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
	int white_balance;
	int color_temp;
	int av_comp;
	int flash_comp;
	int aeb_ev;
	int safety_shift;
	int not_emit_flash;
	int not_af_flash;
	int remote_delay;
} type_SETTINGS;

extern type_SETTINGS settings;

extern void settings_read();
extern void settings_write();
extern void settings_apply();

#endif /* SETTINGS_H_ */
