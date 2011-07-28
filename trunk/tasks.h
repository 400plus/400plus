#ifndef TASKS_H_
#define TASKS_H_

typedef enum {
	IMG_SETTING_RAW,
	IMG_SETTING_RAW_JPEG_L,
	IMG_SETTING_JPEG_L_HIGH,
	IMG_SETTING_JPEG_L_LOW,
	IMG_SETTING_JPEG_M_HIGH,
	IMG_SETTING_JPEG_M_LOW,
	IMG_SETTING_JPEG_S_HIGH,
	IMG_SETTING_JPEG_S_LOW
} type_IMG_SETTING;

extern void start_up();

extern void dp_action();
extern void toggle_img_setting();
extern void set_img_setting();
extern void toggle_CfMLU();
extern void toggle_CfFlashSyncRear();

extern void restore_iso();
extern void restore_wb();
extern void restore_metering();

extern void set_metering_spot();
extern void set_whitebalance_colortemp();
extern void set_iso_high();

#endif /* TASKS_H_ */
