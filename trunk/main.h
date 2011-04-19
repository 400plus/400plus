#ifndef MAIN_H_
#define MAIN_H_

#define NULL 0

#define TRUE  1
#define FALSE 0

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define INT_SWAP(x, y) {int _SWAP_; _SWAP_=(x); (x)=(y); (y)=_SWAP_;}

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

// Events for SendToIntercom
#define EVENT_SET_AE         0x01
#define EVENT_SET_METERING   0x02
#define EVENT_SET_EFCOMP     0x03
#define EVENT_SET_DRIVE      0x04
#define EVENT_SET_WB         0x05
#define EVENT_SET_AF         0x06
#define EVENT_SET_AF_POINT   0x07
#define EVENT_SET_TV_VAL     0x08
#define EVENT_SET_AV_VAL     0x09
#define EVENT_SET_AV_COMP    0x0A
#define EVENT_SET_ISO        0x0B
#define EVENT_SET_RED_EYE    0x0C
#define EVENT_SET_AE_BKT     0x0D
#define EVENT_SET_WB_BKT     0x0E
#define EVENT_SET_BEEP       0x0F
#define EVENT_SET_COLOR_TEMP 0x10

#define EVENT_SET_IMG_FORMAT  0x22
#define EVENT_SET_IMG_SIZE    0x23
#define EVENT_SET_IMG_QUALITY 0x24

#define EVENT_SET_CF_SET_BUTTON_FUNC      0x2A // C.Fn-01
#define EVENT_SET_CF_NR_FOR_LONG_EXPOSURE 0x2B // C.Fn-02
#define EVENT_SET_CF_EFAV_FIX_X           0x2C // C.Fn-03
#define EVENT_SET_CF_AFAEL_ACTIVE_BUTTON  0x2D // C.Fn-04
#define EVENT_SET_CF_EMIT_AUX             0x2E // C.Fn-05
#define EVENT_SET_CF_EXPLEVEL_INC_THIRD   0x2F // C.Fn-06
#define EVENT_SET_CF_EMIT_FLASH           0x30
#define EVENT_SET_CF_EXTEND_ISO           0x31
#define EVENT_SET_CF_AEB_SEQUENCE         0x32
#define EVENT_SET_CF_SI_INDICATE          0x33
#define EVENT_SET_CF_MENU_POS             0x34
#define EVENT_SET_CF_MIRROR_UP_LOCK       0x35 // C.Fn-07
#define EVENT_SET_CF_FPSEL_METHOD         0x36
#define EVENT_SET_CF_FLASH_METERING       0x37 // C.Fn-08
#define EVENT_SET_CF_FLASH_SYNC_REAR      0x38 // C.Fn-09
#define EVENT_SET_CF_SAFETY_SHIFT         0x39
#define EVENT_SET_CF_LENS_BUTTON          0x3A
#define EVENT_SET_CF_ORIGINAL_EVAL        0x3D
#define EVENT_SET_CF_QR_MAGNIFY           0x3C // C.Fn-10
#define EVENT_SET_CF_TFT_ON_POWER_ON      0x3B // C.Fn-11

#define EVENT_SET_REALTIME_ISO_0    0xF0
#define EVENT_SET_REALTIME_ISO_1    0xF1

#define EVENT_DIALOGON  0x50
#define EVENT_DIALOGOFF 0x51

#define EVENT_SETTINGS  0x93

#define	EVENT_AFPDLGON  0xB9
#define	EVENT_AFPDLGOFF 0xA7

//#define	SOME_ACTION_AFTER_BTNS  0x8D // 10001101 - 141
//#define	SOME_OTHER_ACTION       0x74 // 01110100 - 116
//#define	BUTTON_STAR   0xA8 // 10101000 - 168 - ZOOM OUT - other things generates this

#define	BUTTON_MENU   0xA0 // 10100000 - 160
#define	BUTTON_DISP   0xA1 // 10100001 - 161
#define BUTTON_PLAY   0xA4 // 10100100 - 164
#define	BUTTON_SET    0xA6 // 10100110 - 166
#define	BUTTON_DIAL   0xA9 // 10101001 - 169
#define BUTTON_DIAL_LEFT  ( 1 << 8 ) | BUTTON_DIAL
#define BUTTON_DIAL_RIGHT ( 2 << 8 ) | BUTTON_DIAL
#define	BUTTON_UP     0xB1 // 10110001 - 177
#define	BUTTON_DOWN   0xB2 // 10110010 - 178
#define	BUTTON_RIGHT  0xB3 // 10110011 - 179
#define	BUTTON_LEFT   0xB4 // 10110100 - 180
#define	BUTTON_DP     0xB8 // 10111000 - 184
#define	BUTTON_DRIVE  0xBA // 10111010 - 186
#define	BUTTON_AV     0xBB // 10111011 - 187

typedef struct {                 // [*] Used and tested, others unknown
	int ae;                      // 0x0000 [*] [1]
	int metering;                // 0x0004 [*] [2]
	int efcomp;                  // 0x0008 [*]
	int drive;                   // 0x000c     [3]
	int wb;                      // 0x0010 [*] [4]
	int af;                      // 0x0014
	int af_point;                // 0x0018 [*] [5]
	int tv_val;                  // 0x001c [*]
	int av_val;                  // 0x0020
	int av_comp;                 // 0x0024 [*]
	int iso;                     // 0x0028 [*]
	int red_eye;                 // 0x002c
	int ae_bkt;                  // 0x0030 [*]
	int wb_bkt;                  // 0x0034
	int beep;                    // 0x0038 [*]
	int color_temp;              // 0x003c [*]
	int auto_power_off;          // 0x0040
	int view_type;               // 0x0044
	int review_time;             // 0x0048
	int auto_rotate;             // 0x004c
	int lcd_brightness;          // 0x0050
	int date_time;               // 0x0054
	int file_numbering;          // 0x0058
	int language;                // 0x005c
	int video_system;            // 0x0060
	int picture_style_mode;      // 0x0064
	int histogram;               // 0x0068
	int disp_afpoint;            // 0x006c
	int color_space;             // 0x0070
	int img_format;              // 0x0074 [*]
	int img_size;                // 0x0078
	int img_quality;             // 0x007c
	int cfmenupos;               // 0x0080
	int menupos;                 // 0x0084
	int wbcomp_gm;               // 0x0088
	int wbcomp_ab;               // 0x008c
	int forbid_rel;              // 0x0090
	int cf_set_button_func;      // 0x0094
	int cf_nr_for_long_exposure; // 0x0098
	int cf_efav_fix_x;           // 0x009c
	int cf_afael_active_button;  // 0x00a0
	int cf_emit_aux;             // 0x00a4 [*]
	int cf_explevel_inc_third;   // 0x00a8 [*]
	int cf_emit_flash;           // 0x00ac [*]
	int cf_extend_iso;           // 0x00b0 [*]
	int cf_aeb_sequence;         // 0x00b4
	int cf_si_indicate;          // 0x00b8
	int cf_menu_pos;             // 0x00bc
	int cf_mirror_up_lock;       // 0x00c0 [*]
	int cf_fpsel_method;         // 0x00c4
	int cf_flash_metering;       // 0x00c8
	int cf_flash_sync_rear;      // 0x00cc [*]
	int cf_safety_shift;         // 0x00d0 [*]
	int cf_lens_button;          // 0x00d4
	int cf_original_eval;        // 0x00d8
	int cf_qr_magnify;           // 0x00dc
	int batt_bclevel;            // 0x00e0
	int batt_type;               // 0x00e4
	int print_user_property;     // 0x00e8
	int printer_property;        // 0x00ec
	int cluster_size;            // 0x00f0
	int remain_cluster;          // 0x00f4
	int file_id;                 // 0x00f8
	int avo;                     // 0x00fc
	int avmax;                   // 0x0100
	int ef_lens_exist;           // 0x0104
	int avail_shot;              // 0x0108
	int qrev_imgprop;            // 0x010c
	int printer_connect_type;    // 0x0110
	int mwbdat_red;              // 0x0114
	int mwbdat_green1;           // 0x0118
	int mwbdat_green2;           // 0x011c
	int mwbdat_blue;             // 0x0120
	int videojack_connect;       // 0x0124
	int incomp_image;            // 0x0128
	int status_busy_flag;        // 0x012c [*]
	int special_bc_result;       // 0x0130
	int reset_offtimer;          // 0x0134
	int printer_device_property; // 0x0138
	int printer_job_property;    // 0x013c
	int dpof_setting;            // 0x0140
	int gui_mode;                // 0x0144
	int dp_request_return;       // 0x0148
	int commadp_chg_config;      // 0x014c
	int play_jump_type;          // 0x0150
	int capability_setting;      // 0x0154
	int selected_af_mode;        // 0x0158
	int disable_ui_lock;         // 0x015c
	int isd_style_flag;          // 0x0160
	int ptp;                     // 0x0164
	int playback_file_id;        // 0x0168
	int playback_file_id_pos;    // 0x016c
	int usb_connect_type;        // 0x0170
	int face_sensor_disable;     // 0x0174
	int field_178;               // 0x0178
	int field_17C;               // 0x017c
	int field_180;               // 0x0180
	int field_184;               // 0x0184
	int cf_tft_on_power_on;      // 0x0188
	int field_18C;               // 0x018c
	int field_190;               // 0x0190
} type_CAMERA_MODE;

#define cameraMode (*(type_CAMERA_MODE*)0x00016B60)

// [1] Values for "ae"
#define AE_MODE_P    0
#define AE_MODE_TV   1
#define AE_MODE_AV   2
#define AE_MODE_M    3
#define AE_MODE_ADEP 5
#define AE_MODE_AUTO 8

// [2] Values for "metering"
#define METERING_MODE_EVAL 0
#define METERING_MODE_SPOT 3

// [3] Values for "drive"
#define DRIVE_MODE_SINGLE 0
#define DRIVE_MODE_BURST  1

// [4] Values for "wb"
#define WB_MODE_AUTO        0x00
#define WB_MODE_DAYLIGHT    0x01
#define WB_MODE_COUDY       0x02
#define WB_MODE_TUNGSTEN    0x03
#define WB_MODE_FLUORESCENT 0x04
#define WB_MODE_FLASH       0x05
#define WB_MODE_CUSTOM      0x06
#define WB_MODE_SHADE       0x07
#define WB_MODE_COLORTEMP   0x08

// [5] Values for "af_point" (can be ORed together to form patterns)
#define AF_POINT_C  0x0001 // Center
#define AF_POINT_T  0x0002 // Top
#define AF_POINT_B  0x0004 // Bottom
#define AF_POINT_TL 0x0008 // Top-left
#define AF_POINT_TR 0x0010 // Top-right
#define AF_POINT_BL 0x0020 // Bottom-left
#define AF_POINT_BR 0x0040 // Bottom-right
#define AF_POINT_L  0x0080 // Left
#define AF_POINT_R  0x0100 // Right

// Used flags
#define FLAG_MAIN_GUI       (*(int*)(0x00001C88))
#define FLAG_CAMERA_BUSY    (*(int*)(0x00001CA8))
#define FLAG_GUI_MODE       (*(int*)(0x00001ECC))
#define FLAG_METMOD_DIALOG  (*(int*)(0x000047EC))
#define FLAG_AFSLCT_DIALOG  (*(int*)(0x00004804))
#define FLAG_FACTORY_DIALOG (*(int*)(0x000049F4))
#define FLAG_MENU_DIALOG    (*(int*)(0x00004A2C))
#define FLAG_FACE_SENSOR    (*(int*)(0x0000CD38))
#define FLAG_RELEASE_COUNT  (*(int*)(0x0000EBFC))

// Documented flags
#define FLAG_DISPLAY_ON     (*(int*)(0x00006D58))

// Values for FLAG_GUI_MODE
#define GUI_MODE_MAIN      0x00
#define GUI_MODE_REVIEW    0x01
#define GUI_MODE_MENU      0x02
#define GUI_MODE_INFO      0x04
#define GUI_MODE_ISO       0x09
#define GUI_MODE_WB        0x0A
#define GUI_MODE_AFMODE    0x0B
#define GUI_MODE_METER     0x0C
#define GUI_MODE_DRIVE     0x0F
#define GUI_MODE_AFPATTERN 0x10
#define GUI_MODE_OFF       0x11
#define GUI_MODE_FLASHEV   0x1B

// Fictitious modes
#define GUI_MODE_FACE      0xFF
#define GUI_MODE_FACTORY   0xFE
#define GUI_MODE_400PLUS   0xFD

// Action definitions
typedef void(*type_TASK)();

typedef enum {
	RESP_BLOCK,
	RESP_PASS,
	RESP_RELEASE
} type_RESP;

typedef struct {
	int       button;
	int       holds;
	type_RESP resp;
	type_TASK task[2];
	int       _eol_;
} type_ACTION;

typedef struct {
	int          gui_mode;
	type_ACTION *actions;
	int          _eol_;
} type_CHAIN;

// Global status
typedef struct {
	int       button_down;       // A button is down, and which one
	int       script_running;    // A script is running
	int       iso_in_viewfinder; // ISO is being displayed in the viewfinder
	int       afp_dialog;        // The last active dialog was the AF Point selection dialog
	type_TASK button_up_task;    // Task that must be executed when the current button is released
	type_RESP button_up_resp;    // Response when the current button is released
} type_STATUS;

// Main message queue
extern int *message_queue;

// Inline code
#define ENQUEUE_TASK(task) TryPostMessageQueue(message_queue, (task), FALSE);

#define END_OF_LIST  {_eol_ : TRUE}
#define IS_EOL(item) (item->_eol_)

// Our own code
extern void initialize();
extern void initialize_display();
extern void message_proxy(const int handler, char *message);

// Shared globals
extern type_STATUS status;

#endif /* MAIN_H_ */
