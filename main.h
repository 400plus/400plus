#ifndef MAIN_H_
#define MAIN_H_

#define NULL 0

#define TRUE  1
#define FALSE 0

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define INT_SWAP(x, y) do {int _SWAP_; _SWAP_=(x); (x)=(y); (y)=_SWAP_;} while(0)

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

// Events for SendToIntercom
typedef enum {
	IC_SET_AE                      = 0x01, //
	IC_SET_METERING                = 0x02, //
	IC_SET_EFCOMP                  = 0x03, //
	IC_SET_DRIVE                   = 0x04, //
	IC_SET_WB                      = 0x05, //
	IC_SET_AF                      = 0x06, //
	IC_SET_AF_POINT                = 0x07, //
	IC_SET_TV_VAL                  = 0x08, //
	IC_SET_AV_VAL                  = 0x09, //
	IC_SET_AV_COMP                 = 0x0A, //
	IC_SET_ISO                     = 0x0B, //
	IC_SET_RED_EYE                 = 0x0C, //
	IC_SET_AE_BKT                  = 0x0D, //
	IC_SET_WB_BKT                  = 0x0E, //
	IC_SET_BEEP                    = 0x0F, //
	IC_SET_COLOR_TEMP              = 0x10, //
	IC_SET_AUTO_POWER_OFF          = 0x12, //
	IC_SET_VIEW_TYPE               = 0x13, //
	IC_SET_REVIEW_TIME             = 0x14, //
	IC_SET_AUTO_ROTATE             = 0x15, //
	IC_SET_LCD_BRIGHTNESS          = 0x16, //
	IC_SET_DATE_TIME               = 0x17, //
	IC_SET_FILE_NUMBERING          = 0x18, //
	IC_SET_LANGUAGE                = 0x19, //
	IC_SET_VIDEO_SYSTEM            = 0x1A, //
	IC_SET_HISTOGRAM               = 0x1D, //
	IC_SET_COLOR_SPACE             = 0x21, //
	IC_SET_IMG_FORMAT              = 0x22, //
	IC_SET_IMG_SIZE                = 0x23, //
	IC_SET_IMG_QUALITY             = 0x24, //
	IC_SET_WBCOMP_GM               = 0x27, //
	IC_SET_WBCOMP_AB               = 0x28, //
	IC_SET_CF_SET_BUTTON_FUNC      = 0x2A, // C.Fn-01
	IC_SET_CF_NR_FOR_LONG_EXPOSURE = 0x2B, // C.Fn-02
	IC_SET_CF_EFAV_FIX_X           = 0x2C, // C.Fn-03
	IC_SET_CF_AFAEL_ACTIVE_BUTTON  = 0x2D, // C.Fn-04
	IC_SET_CF_EMIT_AUX             = 0x2E, // C.Fn-05
	IC_SET_CF_EXPLEVEL_INC_THIRD   = 0x2F, // C.Fn-06
	IC_SET_CF_EMIT_FLASH           = 0x30, //
	IC_SET_CF_EXTEND_ISO           = 0x31, //
	IC_SET_CF_AEB_SEQUENCE         = 0x32, //
	IC_SET_CF_SI_INDICATE          = 0x33, //
	IC_SET_CF_MENU_POS             = 0x34, //
	IC_SET_CF_MIRROR_UP_LOCK       = 0x35, // C.Fn-07
	IC_SET_CF_FPSEL_METHOD         = 0x36, //
	IC_SET_CF_FLASH_METERING       = 0x37, // C.Fn-08
	IC_SET_CF_FLASH_SYNC_REAR      = 0x38, // C.Fn-09
	IC_SET_CF_SAFETY_SHIFT         = 0x39, //
	IC_SET_CF_LENS_BUTTON          = 0x3A, //
	IC_SET_CF_ORIGINAL_EVAL        = 0x3D, //
	IC_SET_CF_QR_MAGNIFY           = 0x3C, // C.Fn-10
	IC_SET_CF_TFT_ON_POWER_ON      = 0x3B, // C.Fn-11
	IC_DIALOGON                    = 0x50, //
	IC_DIALOGOFF                   = 0x51, //
	IC_SHUTDOWN                    = 0x52, //
	IC_RELEASE                     = 0x53, //
	IC_ENTERFACTORYMODE            = 0x5D, //
	IC_EXITFACTORYMODE             = 0x5E, //
	IC_UILOCK                      = 0x5F, //
	IC_GUILOCK                     = 0x60, //
	IC_FIRMUP                      = 0x61, //
	IC_BAT_TYPE                    = 0x65, //
	IC_BC_LEVEL                    = 0x66, //
	IC_POWER_FLAG                  = 0x72, //
	IC_BUZZER                      = 0x73, //
	IC_TEMP                        = 0x74, //
	IC_TIMERCOUNTER                = 0x8C, //
	IC_MAIN_DIAL                   = 0x90, //
	IC_SETTINGS                    = 0x93, //
	IC_BUTTON_MENU                 = 0xA0, //
	IC_BUTTON_DISP                 = 0xA1, //
	IC_BUTTON_JUMP                 = 0xA2, //
	IC_BUTTON_PLAY                 = 0xA4, //
	IC_BUTTON_TRASH                = 0xA5, //
	IC_BUTTON_SET                  = 0xA6, //
	IC_AFPDLGOFF                   = 0xA7, //
	IC_BUTTON_DIAL                 = 0xA9, //
	IC_BUTTON_DIAL_LEFT            = ( 1 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	IC_BUTTON_DIAL_RIGHT           = ( 2 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	IC_BUTTON_UNK1                 = 0xAC, //
	IC_BUTTON_UP                   = 0xB1, //
	IC_BUTTON_DOWN                 = 0xB2, //
	IC_BUTTON_RIGHT                = 0xB3, //
	IC_BUTTON_LEFT                 = 0xB4, //
	IC_BUTTON_DP                   = 0xB8, //
	IC_AFPDLGON                    = 0xB9, //
	IC_BUTTON_DRIVE                = 0xBA, //
	IC_BUTTON_AV                   = 0xBB, //
	IC_MONOPEN                     = 0xC8, //
	IC_MONCLOSE                    = 0xC9, //
	IC_MONREAD                     = 0xCA, //
	IC_MONWRITE                    = 0xCB, //
	IC_MONCALL                     = 0xCC, //
	IC_SET_REALTIME_ISO_0          = 0xF0, //
	IC_SET_REALTIME_ISO_1          = 0xF1, //
	IC_EXIT_MCELL_TEST             = 0xF4  //
} intercom_event_t;

typedef enum {
	/*
	GUI_PRESS_DISP_BUTTON          = 0x10000000,
	GUI_START_MENU_MODE            = 0x10000007,
	GUI_START_INFO_MODE            = 0x10000008,
	GUI_START_PLAY_MODE            = 0x10000009,
	GUI_START_QR_MODE              = 0x1000000A,
	GUI_START_NOCFWARNING_MODE     = 0x1000000B,
	GUI_START_FULLNOWARNING_MODE   = 0x1000000C,
	GUI_START_FULLCF               = 0x1000000D,
	GUI_START_ERRCF_ERROR          = 0x1000000E,
	GUI_START_ERRCF_FULLNO         = 0x1000000F,
	GUI_START_ERRCF_PROTECT        = 0x10000010,
	GUI_START_ERRORCODE_MODE       = 0x10000011,
	GUI_START_INCOMPIMAGE_MODE     = 0x10000012,
	GUI_START_RTCSET_MODE          = 0x10000013,
	GUI_START_IDLE_MODE            = 0x10000014,
	GUI_POST_QR_IMAGE              = 0x10000015,
	GUI_DISP_RTCSET_MODE           = 0x10000018,
	GUI_DISP_NOCFWARNING_MODE      = 0x10000029,
	GUI_DISP_FULLNOWARNING_MODE    = 0x1000002A,
	GUI_DISP_FULLCF                = 0x1000002B,
	GUI_DISP_ERRCF_ERROR           = 0x1000002C,
	GUI_DISP_ERRCF_FULLNO          = 0x1000002D,
	GUI_DISP_ERRCF_PROTECT         = 0x1000002E,
	GUI_DISP_ERRORCODE_MODE        = 0x1000002F,
	GUI_DISP_INCOMPIMAGE_MODE      = 0x10000030,
	GUI_FINISH_QR_MODE             = 0x10000031,
	GUI_DISP_USBCONNECTTYPE_MODE   = 0x10000035,
	GUI_DISP_DIRECTTRANSFER_MODE   = 0x10000036,
	GUI_START_USBCONNECTTYPE_MODE  = 0x10000037,
	GUI_START_DIRECTTRANSFER_MODE  = 0x10000038,
	GUI_DISP_OLC_MODE              = 0x10000039,
	GUI_DISP_BULBCOUNT_MODE        = 0x1000003B,
	GUI_START_OLC_MODE             = 0x1000003C,
	GUI_START_BULBCOUNT_MODE       = 0x1000003D,
	GUI_DISP_ISO_MODE              = 0x10000043,
	GUI_DISP_AF_MODE               = 0x10000044,
	GUI_DISP_WB_MODE               = 0x10000045,
	GUI_DISP_MES_MODE              = 0x10000046,
	GUI_DISP_FP_SEL                = 0x10000048,
	GUI_DISP_QUAL_MODE             = 0x10000049,
	GUI_DISP_PICTURESTYLE_MODE     = 0x1000004A,
	GUI_DISP_FECOMP_MODE           = 0x1000004B,
	GUI_DISP_ACTIVESWEEP           = 0x1000004C,
	GUI_DISP_ACTIVESWEEP_OLC       = 0x1000004D,
	GUI_DISP_BATTEMPTY             = 0x1000004E,
	GUI_START_ISO_MODE             = 0x10000058,
	GUI_START_AF_MODE              = 0x10000059,
	GUI_START_WB_MODE              = 0x1000005A,
	GUI_START_MES_MODE             = 0x1000005B,
	GUI_START_DRIVE_MODE           = 0x1000005C,
	GUI_START_FP_SEL               = 0x1000005D,
	GUI_START_QUAL_MODE            = 0x1000005E,
	GUI_START_PICTURESTYLE_MODE    = 0x1000005F,
	GUI_START_FECOMP_MODE          = 0x10000060,
	GUI_START_ACTIVESWEEP          = 0x10000061,
	GUI_START_ACTIVESWEEP_OLC      = 0x10000062,
	GUI_START_BATTEMPTY            = 0x10000063,
	GUI_FINISH_ACTIVESWEEP         = 0x10000065,
	GUI_START_COLORBAR_DIALOG      = 0x1000006E,
	GUI_START_LCDADJUST_DIALOG     = 0x1000006F,
	GUI_DELETE_COLORBAR_DIALOG     = 0x10000070,
	GUI_DELETE_LCDADJUST_DIALOG    = 0x10000071,
	*/
	GUI_GOT_TOP_OF_CONTROL         = 0x800,
	// 801 ?
	GUI_INITIALIZE_CONTROLLER      = 0x802,
	//GUI_BUTTON_HALF_SHUTTER        = 0x804,
	GUI_BUTTON_RIGHT               = 0x807,
	GUI_BUTTON_LEFT                = 0x809,
	GUI_BUTTON_UP                  = 0x80B,
	GUI_BUTTON_DOWN                = 0x80D,
	GUI_BUTTON_MENU                = 0x80F,
	GUI_BUTTON_JUMP                = 0x810,
	GUI_BUTTON_SET                 = 0x812, //(code1 will be menu line number when set button was pressed)
	GUI_BUTTON_ZOOM_IN             = 0x819,
	GUI_BUTTON_ZOOM_IN_RELEASED    = 0x81A, // DISP_RELEASED
	GUI_BUTTON_ZOOM_OUT            = 0x81B,
	GUI_BUTTON_ZOOM_OUT_RELEASED   = 0x81C, // DISP_RELEASED
	// 820 ?
	GUI_BUTTON_DISP                = 0x829, // GUI_BUTTON_INFO
	GUI_BUTTON_DIAL_RIGHT          = 0x82B,
	GUI_BUTTON_DIAL_LEFT           = 0x82C,
	GUI_BUTTON_PLAY                = 0x10000000,
	GUI_BUTTON_TRASH               = 0x10000001,
	GUI_BUTTON_DP                  = 0x10000002,
	GUI_BUTTON_DRIVE               = 0x10000047,
	GUI_BLINK_RELATED              = 0x1000003E,
} gui_event_t;

typedef struct {                 // [*] Used and tested, others unknown
	int ae;                      // 0x0000 [*] [1]
	int metering;                // 0x0004 [*] [2]
	int efcomp;                  // 0x0008 [*]
	int drive;                   // 0x000c     [3]
	int wb;                      // 0x0010 [*] [4]
	int af;                      // 0x0014
	int af_point;                // 0x0018 [*] [5]
	int tv_val;                  // 0x001c [*] [F]
	int av_val;                  // 0x0020
	int av_comp;                 // 0x0024 [*]
	int iso;                     // 0x0028 [*]
	int red_eye;                 // 0x002c
	int ae_bkt;                  // 0x0030 [*]
	int wb_bkt;                  // 0x0034
	int beep;                    // 0x0038 [*]
	int color_temp;              // 0x003c [*]
	int auto_power_off;          // 0x0040     [6]
	int view_type;               // 0x0044
	int review_time;             // 0x0048     [7]
	int auto_rotate;             // 0x004c     [8]
	int lcd_brightness;          // 0x0050     [9]
	int date_time;               // 0x0054     [A]
	int file_numbering;          // 0x0058     [B]
	int language;                // 0x005c [*]
	int video_system;            // 0x0060     [C]
	int picture_style_mode;      // 0x0064
	int histogram;               // 0x0068     [D]
	int disp_afpoint;            // 0x006c
	int color_space;             // 0x0070     [E]
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

#define cameraMode (*(type_CAMERA_MODE*)&DPData)

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

// [6] Values for "auto_power_off"
//     Number of seconds to wait, 0x00 for OFF

// [7] Values for "review_time"
//     Number of seconds to wait, 0x00 for OFF, 0xFF for HOLD

// [8] Values for "auto_rotate"
#define AUTO_ROTATE_OFF         0x00
#define AUTO_ROTATE_COMP_CAMERA 0x01
#define AUTO_ROTATE_COMP        0x02

// [9] Values for "lcd_brightness"
//     Brightness in range 1 to 7

// [A] Values for "date_time"
#define DATE_TIME_YYMMDD 0x01
#define DATE_TIME_DDMMYY 0x02
#define DATE_TIME_MMDDYY 0x03

// [B] Values for "file_numbering"
#define FILE_NUMBERING_CONT 0x00
#define FILE_NUMBERING_AUTO 0x01

// [C] Values for "video_system"
#define VIDEO_SYSYEM_PAL  0x00
#define VIDEO_SYSTEM_NTSC 0x01

// [D] Values for "histogram"
#define HISTOGRAM_BRIGHTNESS 0x00
#define HISTOGRAM_RGB        0x01

// [E] Values for "color_space"
#define COLOR_SPACE_SRGB  0x00
#define COLOR_SPACE_ADOBE 0x01

// [F] Values for "tv_val"
//     0x10 => 30", 0x18 => 15", ..., 0x90 => 1/4000
#define TV_VAL_BULB 0x0C

// Used flags
#define FLAG_MAIN_GUI       (*(int*)(0x00001C88))
#define FLAG_CAMERA_BUSY    hRelSem
#define FLAG_METMOD_DIALOG  (*(int*)(0x000047EC)) // ?
#define FLAG_AFSLCT_DIALOG  (*(int*)(0x00004804))
#define FLAG_FACTORY_DIALOG hFaMain
#define FLAG_MENU_DIALOG    hMnBg
#define FLAG_FACE_SENSOR    FaceStatus
#define FLAG_RELEASE_COUNT  (*(int*)(0x0000EBFC))

// Documented flags
#define FLAG_DISPLAY_ON     (*(int*)(0x00006D58))

#define FLAG_GUI_MODE       GUIMode
typedef enum { // GUIModes
	GUIMODE_MAIN,            // 0x00 - main screen (white one)
	GUIMODE_REVIEW,          // 0x01 - review photos mode (activated with play btn)
	GUIMODE_MENU,            // 0x02 - main menu
	GUIMODE_RTCSET,          // 0x03 - Set internal clock from MENU
	GUIMODE_INFO,            // 0x04 - info screen (menu -> disp.)
	GUIMODE_NOCFWARNING,     // 0x05 - no CF card
	GUIMODE_QR,              // 0x06 - review image right after shot
	GUIMODE_FULLNOWARNING,   // 0x07 - ?
	GUIMODE_PICTURESTYLE,    // 0x08 - Picture Style
	GUIMODE_ISO,             // 0x09 - ISO
	GUIMODE_WB,              // 0x0A - WB
	GUIMODE_AFMODE,          // 0x0B - AF mode choosing screen
	GUIMODE_METER,           // 0x0C - Metering mode screen
	GUIMODE_QUAL,            // 0x0D - Quality screen selection from MENU
	GUIMODE_UNKNOWN_1,       // 0x0E - ?
	GUIMODE_DRIVE,           // 0x0F - Drive mode
	GUIMODE_AFPATTERN,       // 0x10 - AF zones select
	GUIMODE_OLC,             // 0x11 - Main screen (the white one)
	GUIMODE_BULBCOUNT,       // 0x12 - Bulb counter screen
	GUIMODE_CFFULL,          // 0x13 - CF is full
	GUIMODE_ERRCF_ERROR,     // 0x14 - CF Error ?
	GUIMODE_ERRCF_FULLNO,    // 0x15 - ?
	GUIMODE_ERRCF_PROTECT,   // 0x16 - ?
	GUIMODE_UNKNOWN_2,       // 0x17 - ?
	GUIMODE_ERRORCODE,       // 0x18 - error code screen
	GUIMODE_USBCONNECTTYPE,  // 0x19 - ?
	GUIMODE_DIRECTTRANSFER,  // 0x1A - ?
	GUIMODE_FLASHEV,         // 0x1B - Flash EV (SET from main dialog if configured at C.Fn-01)
	GUIMODE_INCOMPIMAGE,     // 0x1C - ?
	GUIMODE_BATTEMPTY,       // 0x1D - Battery empty
	GUIMODE_ACTIVESWEEP,     // 0x1E - Sweeping the sensor
	GUIMODE_ACTIVESWEEP_OLC, // 0x1F - Sweeping the sensor

// Fictitious modes
	GUIMODE_400PLUS,           // 0x20 - Our (400plus) menu mode
	GUIMODE_RENAME,            // 400Plus rename
	GUIMODE_400PLUS_OLD = 0x2D,// 400Plus old mode for the intercom
	GUIMODE_FACE        = 0x2F,// Face mode
} type_GUIMODE;


struct struct_DIALOG; // we do not know what is inside, it's just a type name
typedef struct struct_DIALOG type_DIALOG;
// this type should be used as a pointer always (e.g. type_DIALOG * dialog)
// reading from the memory where struct points, the first 4 bytes are pointing
// to 0xFF914960 ("aDIALOG" from funclist), so i guess the first element of
// the struct is "char *" with name of the dialog


// Handler for buttons in dialogs
typedef int(*type_BTN_HANDLER)(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

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
	int          type;      // GUIMode for intercom_proxy(), type_MENU_TYPE for menu_buttons_handler()
	type_ACTION *actions;
	int          _eol_;
} type_CHAIN;

// Global status
typedef struct {
	int       button_down;       // A button is down, and which one
	int       script_running;    // A script is running
	int       iso_in_viewfinder; // ISO is being displayed in the viewfinder
	int       afp_dialog;        // The last active dialog was the AF Point selection dialog
	int       main_dial_ae;      // AE mode selected in the main dial
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
extern void intercom_proxy(const int handler, char *message);

// Shared globals
extern type_STATUS status;

#endif /* MAIN_H_ */
