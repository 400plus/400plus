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
typedef enum {
        IC_AE_MODE                     = 0x01, // EVENT_SET_AE
        IC_AF_MES_MODE                 = 0x02, // EVENT_SET_METERING
        IC_SET_EFCOMP                  = 0x03, // EVENT_SET_EFCOMP
        IC_DRIVE_MODE                  = 0x04, // EVENT_SET_DRIVE
        IC_WBMODE                      = 0x05, // EVENT_SET_WB
        IC_SET_AF                      = 0x06, // EVENT_SET_AF
        IC_SET_AF_POINT                = 0x07, // EVENT_SET_AF_POINT
        IC_TV_VALUE                    = 0x08, // EVENT_SET_TV_VAL
        IC_AV_VALUE                    = 0x09, // EVENT_SET_AV_VAL
        IC_COMP_VALUE                  = 0x0A, // EVENT_SET_AV_COMP
        IC_ISO_VALUE                   = 0x0B, // EVENT_SET_ISO
        IC_SET_RED_EYE                 = 0x0C, // EVENT_SET_RED_EYE
        IC_SET_AE_BKT                  = 0x0D, // EVENT_SET_AE_BKT
        IC_SET_WB_BKT                  = 0x0E, // EVENT_SET_WB_BKT
        IC_SET_BEEP                    = 0x0F, // EVENT_SET_BEEP
        IC_SET_COLOR_TEMP              = 0x10, // EVENT_SET_COLOR_TEMP
        IC_COLOR_SPACE                 = 0x21, // EVENT_SET_COLOR_TEMP
        IC_QUALITY_1                   = 0x22, // EVENT_SET_IMG_FORMAT
        IC_QUALITY_2                   = 0x23, // EVENT_SET_IMG_SIZE
        IC_QUALITY_3                   = 0x24, // EVENT_SET_IMG_QUALITY
        IC_CF_SET_BUTTON_FUNC          = 0x2A, // EVENT_SET_CF_SET_BUTTON_FUNC // C.Fn-01
        IC_CF_NR_FOR_LONG_EXPOSURE     = 0x2B, // EVENT_SET_CF_NR_FOR_LONG_EXPOSURE // C.Fn-02
        IC_CF_EFAV_FIX_X               = 0x2C, // EVENT_SET_CF_EFAV_FIX_X // C.Fn-03
        IC_CF_AFAEL_ACTIVE_BUTTON      = 0x2D, // EVENT_SET_CF_AFAEL_ACTIVE_BUTTON // C.Fn-04
        IC_SET_CF_EMIT_AUX             = 0x2E, // EVENT_SET_CF_EMIT_AUX // C.Fn-05
        IC_SET_CF_EXPLEVEL_INC_THIRD   = 0x2F, // EVENT_SET_CF_EXPLEVEL_INC_THIRD   // C.Fn-06
        IC_SET_CF_EMIT_FLASH           = 0x30, // EVENT_SET_CF_EMIT_FLASH           
        IC_SET_CF_EXTEND_ISO           = 0x31, // EVENT_SET_CF_EXTEND_ISO           
        IC_SET_CF_AEB_SEQUENCE         = 0x32, // EVENT_SET_CF_AEB_SEQUENCE         
        IC_SET_CF_SI_INDICATE          = 0x33, // EVENT_SET_CF_SI_INDICATE          
        IC_SET_CF_MENU_POS             = 0x34, // EVENT_SET_CF_MENU_POS             
        IC_SET_CF_MIRROR_UP_LOCK       = 0x35, // C.Fn-07, //EVENT_SET_CF_MIRROR_UP_LOCK       
        IC_SET_CF_FPSEL_METHOD         = 0x36, // EVENT_SET_CF_FPSEL_METHOD         
        IC_SET_CF_FLASH_METERING       = 0x37, // C.Fn-08, //EVENT_SET_CF_FLASH_METERING       
        IC_SET_CF_FLASH_SYNC_REAR      = 0x38, // C.Fn-09, //EVENT_SET_CF_FLASH_SYNC_REAR      
        IC_SET_CF_SAFETY_SHIFT         = 0x39, // EVENT_SET_CF_SAFETY_SHIFT         
        IC_SET_CF_LENS_BUTTON          = 0x3A, // EVENT_SET_CF_LENS_BUTTON          
        IC_SET_CF_ORIGINAL_EVAL        = 0x3D, // EVENT_SET_CF_ORIGINAL_EVAL        
        IC_SET_CF_QR_MAGNIFY           = 0x3C, // C.Fn-10, //EVENT_SET_CF_QR_MAGNIFY           
        IC_SET_CF_TFT_ON_POWER_ON      = 0x3B, // C.Fn-11, //EVENT_SET_CF_TFT_ON_POWER_ON      
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
        IC_MONOPEN                     = 0xC8, // 
        IC_MONCLOSE                    = 0xC9, // 
        IC_MONREAD                     = 0xCA, // 
        IC_MONWRITE                    = 0xCB, // 
        IC_MONCALL                     = 0xCC, // 
        IC_SET_REALTIME_ISO_0          = 0xF0, // EVENT_SET_REALTIME_ISO_0    
        IC_SET_REALTIME_ISO_1          = 0xF1, // EVENT_SET_REALTIME_ISO_1    
        IC_EXIT_MCELL_TEST             = 0xF4  // 
} intercom_event_t;




#define EVENT_DIALOGON  0x50
#define EVENT_DIALOGOFF 0x51

#define EVENT_MAIN_DIAL 0x90
#define EVENT_SETTINGS  0x93

#define	EVENT_AFPDLGON  0xB9
#define	EVENT_AFPDLGOFF 0xA7

typedef enum {	// code2 on button press:
	GUI_BUTTON_RIGHT		= 0x807,
	GUI_BUTTON_LEFT			= 0x809,
	GUI_BUTTON_UP			= 0x80B,
	GUI_BUTTON_DOWN			= 0x80D, //0x10000045,// 0x80D,
	GUI_BUTTON_MENU			= 0x80F,
	GUI_BUTTON_JUMP			= 0x810,
	GUI_BUTTON_SET			= 0x812, //(code1 will be menu line number when set button was pressed)
	GUI_BUTTON_ZOOM_IN		= 0x819,
	GUI_BUTTON_ZOOM_IN_RELEASED	= 0x81A,
	GUI_BUTTON_ZOOM_OUT		= 0x81B,
	GUI_BUTTON_ZOOM_OUT_RELEASED	= 0x81C,
	GUI_BUTTON_DISP			= 0x829,
	GUI_BUTTON_DIAL_RIGHT		= 0x82B,
	GUI_BUTTON_DIAL_LEFT		= 0x82C,
	GUI_BUTTON_PLAY			= 0x10000000,
	GUI_BUTTON_TRASH		= 0x10000001,
	GUI_BUTTON_DP			= 0x10000002,
	GUI_BUTTON_FACE			= 0x10000014,
	GUI_BUTTON_DRIVE		= 0x10000047,
	//GUI_BUTTON_AV			= 0x1000003E, // this is generated by other events too
} gui_event_t;

//#define	SOME_ACTION_AFTER_BTNS  0x8D // 10001101 - 141
//#define	SOME_OTHER_ACTION       0x74 // 01110100 - 116
//#define	BUTTON_STAR   0xA8 // 10101000 - 168 - ZOOM OUT - other things generates this

#define	BUTTON_MENU   0xA0 // 10100000 - 160
#define	BUTTON_DISP   0xA1 // 10100001 - 161
#define BUTTON_PLAY   0xA4 // 10100100 - 164
#define	BUTTON_SET    0xA6 // 10100110 - 166
//#define BUTTON_ZI     0xA7 // zoom in - should be tested
//#define BUTTON_ZO     0xA8 // zoom in - should be tested
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
	GUI_MODE_MAIN,		// 0x00 - main screen (white one)
	GUI_MODE_REVIEW,	// 0x01 - review photos mode (activated with play btn)
	GUI_MODE_MENU,		// 0x02 - main menu
	GUI_MODE_RTCSET,	// 0x03 - ?
	GUI_MODE_INFO,		// 0x04 - info screen (menu -> disp.)
	GUI_MODE_NOCFWARNING,	// 0x05 - no CF card
	GUI_MODE_QR,		// 0x06 - review image right after shot
	GUI_MODE_FULLNOWARNING,	// 0x07 - ?
	GUI_MODE_PICTURESTYLE,	// 0x08 - Picture Style
	GUI_MODE_ISO,		// 0x09 - Iso
	GUI_MODE_WB,		// 0x0A - WB
	GUI_MODE_AFMODE,	// 0x0B - AF mode choosing screen
	GUI_MODE_METER,		// 0x0C - Mettering screen ? (Sergei's name: MES_MODE)
	GUI_MODE_QUAL,		// 0x0D - Quality screen ?
	GUI_MODE_UNKNOWN_1,	// 0x0E - ?
	GUI_MODE_DRIVE,		// 0x0F - Drive ?
	GUI_MODE_AFPATTERN,	// 0x10 - AF zones select
	GUI_MODE_OLC,		// 0x11 - ?
	GUI_MODE_BULBCOUNT,	// 0x12 - Bulb counder screen
	GUI_MODE_CFFULL,	// 0x13 - CF is full
	GUI_MODE_ERRCF_ERROR,	// 0x14 - CF Error ?
	GUI_MODE_ERRCF_FULLNO,	// 0x15 - ?
	GUI_MODE_ERRCF_PROTECT,	// 0x16 - ?
	GUI_MODE_UNKNOWN_2,	// 0x17 - ?
	GUI_MODE_ERRORCODE,	// 0x18 - error code screen
	GUI_MODE_USBCONNECTTYPE,// 0x19 - ?
	GUI_MODE_DIRECTTRANSFER,// 0x1A - ?
	GUI_MODE_FLASHEV,	// 0x1B - Flash EV ?
	GUI_MODE_INCOMPIMAGE,	// 0x1C - ?
	GUI_MODE_BATTEMPTY,	// 0x1D - Battery empty
	GUI_MODE_ACTIVESWEEP,	// 0x1E - Sweeping the mirror ?
	GUI_MODE_ACTIVESWEEP_OLC,// 0x1F - Sweeping the mirror ?

// Fictitious modes
	GUI_MODE_400PLUS = 0x2D,// 400Plus mode
	GUI_MODE_RENAME  = 0x2E,// 400Plus rename
	GUI_MODE_FACE    = 0x2F	// Face mode
	GUI_MODE_400PLUS_NEW = 0x30,// 400Plus mode new
} type_GUI_MODE;


struct struct_DIALOG; // we do not know what is inside, it's just a type name
typedef struct struct_DIALOG type_DIALOG;
// this type should be used as a pointer always (e.g. type_DIALOG * dialog)
// reading from the memory where struct points, the first 4 bytes are pointing
// to 0xFF914960 ("aDIALOG" from funclist), so i guess the first element of
// the struct is "char *" with name of the dialog


// Handler for buttons in dialogs
typedef int(*type_BTN_HANDLER)(type_DIALOG * dialog, int r1, int code1, int r3, int r4, int r5, int r6, int code2);

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
extern void message_proxy(const int handler, char *message);

extern type_ACTION actions_400plus[];

void change_lang_pack();

// Shared globals
extern type_STATUS status;

#endif /* MAIN_H_ */
