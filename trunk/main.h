/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "scripts.h"

#define NULL 0

#define TRUE  1
#define FALSE 0

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define INT_SWAP(x, y) do {int _SWAP_; _SWAP_=(x); (x)=(y); (y)=_SWAP_;} while(0)

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

#define BTN_PRESSED     0x20
#define BTN_NOT_PRESSED 0x21
// button addresses
#define BTN_ADDR_TRASH  0xC0220130
#define BTN_ADDR_JUMP   0xC0220134

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
	// 0x1C == picture style ?
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
	IC_RELEASE_INHIBIT             = 0x55, // forbid the shooting, if we call these, we will have to update "is_release_permitted" flag too
	IC_RELEASE_PERMIT              = 0x57, // permit the shooting
	IC_RESET_SETTINGS              = 0x59, // it is called in reset settings, then 0x5A is called. so they both should be related
	IC_ENTERFACTORYMODE            = 0x5D, //
	IC_EXITFACTORYMODE             = 0x5E, //
	IC_UILOCK                      = 0x5F, //
	IC_GUILOCK                     = 0x60, //
	IC_FIRMUP                      = 0x61, //
	// 0x64 ?
	IC_BAT_TYPE                    = 0x65, //
	IC_BC_LEVEL                    = 0x66, //
	// 0x67 ?
	IC_CARD_FULL_MSG_IN_VF         = 0x6B, //
	IC_CHANGE_BAT_AND_OTHER_DIALOGS= 0x6C, //
	IC_SET_BURST_COUNTER           = 0x6D, //
	IC_POWER_FLAG                  = 0x72, //
	IC_BUZZER                      = 0x73, //
	IC_TEMP                        = 0x74, //
	IC_MEASURING                   = 0x80, //
	IC_MEASUREMENT                 = 0x81, //
	IC_SHOOTING                    = 0x83, // ?
	IC_TIMERCOUNTER                = 0x8C, //
	IC_SETTINGS_0                  = 0x90, //
	IC_SETTINGS_1                  = 0x91, //
	IC_SETTINGS_2                  = 0x92, //
	IC_SETTINGS_3                  = 0x93, //
	IC_BUTTON_MENU                 = 0xA0, //
	IC_BUTTON_DISP                 = 0xA1, //
	IC_BUTTON_JUMP                 = 0xA2, //
	IC_BUTTON_PLAY                 = 0xA4, //
	IC_BUTTON_TRASH                = 0xA5, //
	IC_BUTTON_SET                  = 0xA6, //
	IC_AFPDLGOFF                   = 0xA7, // hmm it seems like dialog destroy after all
	// and 0xA8 is perhaps dialog create.
	IC_BUTTON_DIAL                 = 0xA9, //
	IC_BUTTON_DIAL1                = 0xAA, // does the same as DIAL
	IC_BUTTON_DIAL_LEFT            = ( 1 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	IC_BUTTON_DIAL_RIGHT           = ( 2 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	IC_BUTTON_CARD_DOOR            = 0xAB, //
	IC_BUTTON_UNK1                 = 0xAC, //
	IC_BUTTON_POWER                = 0xAE, // change_menupos ?
	IC_BUTTON_BATTERY_DOOR         = 0xAF, //
	IC_BUTTON_UP                   = 0xB1, //
	IC_BUTTON_DOWN                 = 0xB2, //
	IC_BUTTON_RIGHT                = 0xB3, //
	IC_BUTTON_LEFT                 = 0xB4, //
	IC_BUTTON_HALF_SHUTTER         = 0xB6, //
	IC_BUTTON_FULL_SHUTTER         = 0xB7, //
	IC_BUTTON_DP                   = 0xB8, //
	IC_AFPDLGON                    = 0xB9, //
	IC_BUTTON_DRIVE                = 0xBA, //
	IC_BUTTON_AV                   = 0xBB, //
	IC_BUTTON_UNK2                 = 0xBC, // calls TFT OFF, i cannot find which button is this
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
	//GUI_PRESS_DISP_BUTTON          = 0x10000000,

	//GUI_IDC_DBN_OK                 = 0x6, // ?
	//GUI_IDC_DBN_CANCEL             = 0x7, // ?
	GUI_UNKNOWN_0x01               = 0x01, // Call DeleteDialogBox and return 0
	GUI_UNKNOWN_0x02               = 0x02, // Call [GUI_]Lock(),PaletteInit(),DisplayMode(),delete_child_dialog,DeleteDialogBox(),Unlock(),PaletteUnInit() and return 0; (probably deletes the dialog and it's childs)
	GUI_GOT_TOP_OF_CONTROL         = 0x800,
	GUI_LOST_TOP_OF_CONTROL        = 0x801,
	GUI_INITIALIZE_CONTROLLER      = 0x802,
	GUI_PUBLISHER_INSTANCE         = 0x803, // probably not visible by our handlers
	GUI_TERMINATE_WINSYS           = 0x804,
	GUI_DELETE_DIALOG_REQUEST      = 0x805,
	GUI_BUTTON_RIGHT               = 0x807,
	GUI_BUTTON_LEFT                = 0x809,
	GUI_BUTTON_UP                  = 0x80B,
	GUI_BUTTON_DOWN                = 0x80D,
	GUI_BUTTON_MENU                = 0x80F,
	GUI_BUTTON_JUMP                = 0x810,
	GUI_BUTTON_SET                 = 0x812, //(code1 will be menu line number when set button was pressed)
	GUI_BUTTON_ZOOM_IN_PRESS       = 0x819,
	GUI_BUTTON_ZOOM_IN_RELEASE     = 0x81A, // DISP_RELEASED // idle handler shows them w/o a reason, could be disp_release
	GUI_BUTTON_ZOOM_OUT_PRESS      = 0x81B,
	GUI_BUTTON_ZOOM_OUT_RELEASE    = 0x81C, // DISP_RELEASED // idle handler shows them w/o a reason, could be disp_release
	// 820 ? // SUB_DIAL (spin left) ? http://chdk.wikia.com/wiki/DryOS_structures
	// 823 ? // PRESS_MLT_CENTER_BUTTON ? http://chdk.wikia.com/wiki/DryOS_structures
	GUI_BUTTON_DISP                = 0x829, // GUI_BUTTON_INFO
	GUI_BUTTON_DIAL_RIGHT          = 0x82B, // on DIAL_[LEFT|RIGHT] the r4 and r5 in btn_handler
	GUI_BUTTON_DIAL_LEFT           = 0x82C, // are incremental counter for both of them, every dial increments them both
	// AFAIK (from the asm) DIAL_LEFT is the last with a small number
	GUI_BUTTON_PLAY                = 0x10000000,
	GUI_BUTTON_TRASH               = 0x10000001,
	GUI_BUTTON_DP                  = 0x10000002,
	// 0x10000019 ?
	// 0x10000021 ?

	// these names below could be incorrect
	GUI_BUTTON_CF_CARD             = 0x10000006, // could be
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
	GUI_BUTTON_DRIVE               = 0x10000047,
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

	GUI_UNKNOWN1                   = 0x1000003A, // related to mettering may be ?
	GUI_UNKNOWN2                   = 0x1000003E, // related to btns that repeats (AV, 1/2-SHUT) may be ?
} gui_event_t;


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
	GUIMODE_OFF,             // 0x00 - main screen off
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
	GUIMODE_OLC,             // 0x11 - Main screen (white one)
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
	GUIMODE_400PLUS = 0xFF,  // 400Plus mode
	GUIMODE_FACE    = 0xFE	 // Face mode
} type_GUIMODE;


// Dialog Item struct
typedef struct {
	int pSignature; // 0x00 - "DIALOGITEM"
	int field_4;    // 0x04
	int field_8;    // 0x08
	int field_C;    // 0x0C
	int jump_table; // 0x10 - pointer to a jumptable
	int field_14;   // 0x14
	int the_case;   // 0x18 - element from the jumptable to switch on it (in dlgItem_sub_FF917D00)
	//              // something like: goto jump_table[the_case];
} dialog_item_t;


// DIALOG struct
typedef struct struct_type_DIALOG dialog_t; // forward declaration

// Handler for events/buttons in dialogs
// r3 seems to get 2 values in halfwords... still dont know what they do
typedef int(*event_handler_t)(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

struct struct_type_DIALOG {
	char * pSignature;   // 0x0000 - "DIALOG"
	int field_0x0004;    // 0x0004
	int window_struct;   // 0x0008 - window instance
	int palette_struct;  // 0x000C - palette class
	int close_dialog;    // 0x0010 - when set to 1, DeleteDialogBox is called
	int template_num;    // 0x0014 - the number of the dialog template
	int field_0x0018;    // 0x0018 - some resource for this dialog
	int field_0x001C;    // 0x001C - another resource for the dialog
	int field_0x0020;    // 0x0020
	int field_0x0024;    // 0x0024
	int field_0x0028;    // 0x0028
	int field_0x002C;    // 0x002C
	int field_0x0030;    // 0x0030
	int field_0x0034;    // 0x0034
	int field_0x0038;    // 0x0038
	int field_0x003C;    // 0x003C
	int field_0x0040;    // 0x0040
	int field_0x0044;    // 0x0044
	int field_0x0048;    // 0x0048
	int field_0x004C;    // 0x004C
	int field_0x0050;    // 0x0050
	int field_0x0054;    // 0x0054
	int central_handler; // 0x0058 - the central handler ( DIALOGHandler() )
	int field_0x005C;    // 0x005C
	int field_0x0060;    // 0x0060
	int field_0x0064;    // 0x0064
	int field_0x0068;    // 0x0068
	int field_0x006C;    // 0x006C
	int field_0x0070;    // 0x0070
	int field_0x0074;    // 0x0074
	int field_0x0078;    // 0x0078
	event_handler_t *event_handler; // 0x007C
	int arg2;            // 0x0080 - the second arg to the handler
	dialog_item_t * dlg_item; // 0x0084 - structure that holds some dialog_item stuff, probably the selected item
	int field_0x0088;    // 0x0088
	int field_0x008C;    // 0x008C
	int field_0x0090;    // 0x0090
	int field_0x0094;    // 0x0094
	int brush_struct;    // 0x0098 - brush class
	// there are more for sure (perhaps to 0x00B8)
};

// Action definitions
typedef void(*type_TASK)();

typedef struct {
	int       button;
	int       block;
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
	int         button_down;       // A button is down, and which one
	int         script_running;    // A script is running
	int         script_stopping;   // The currently running script mist stop
	int         menu_running;      // A menu is running
	int         iso_in_viewfinder; // ISO is being displayed in the viewfinder
	int         afp_dialog;        // The last active dialog was the AF Point selection dialog
	int         main_dial_ae;      // AE mode selected in the main dial
	type_TASK   button_up_task;    // Task that must be executed when the current button is released
	int         button_up_block;   // Response when the current button is released
	int         last_preset;       // Last preset used
	int         ignore_ae_change;  // Ignore next AE change
	int         booting;           // Camera is still booting up
	int         measuring;         // Camera is measuring the scene
	int         measured_tv;       // Shutter speed as proposed by the metering
	int         measured_av;       // Aperture as proposed by the metering
	int         measured_ev;       // Exposure deviation as measured by the camera
	int         last_shot_tv;      // Shutter speed of the last shot taken
	int         last_shot_av;      // Aperture of the last shot taken
	int         ev_comp;           // Exposure compensation for AutoISO + M
	type_SCRIPT last_script;       // Last executed script
} type_STATUS;

// Main message queue
extern int *task_queue;

// Inline code
#define ENQUEUE_TASK(task) TryPostMessageQueue(task_queue, (task), FALSE);

#define END_OF_LIST  {_eol_ : TRUE}
#define IS_EOL(item) (item->_eol_)

// Our own code
extern void initialize();
extern void initialize_display();
extern void intercom_proxy(const int handler, char *message);

// Shared globals
extern type_STATUS status;

#endif /* MAIN_H_ */



#if 0

ChangeDprData (int what, int value);

  2: red_eye
  3: beep
  4: auto_power_off
  5: view_type
  6: review_time
  7: auto_rotate
  8: lcd_brightness
  9: file_numbering
 10: language
 11: video_system
 12: ptp
 13: picture_style_mode
 14: histogram
 15: color_space
 16: forbid_rel
 17: iso
 18: metering
 19: selected_af_mode
 21: face_sensor_disable
 23: drive
 24: wb
 26: color_temp
 27: date_time
 28: cfmenupos
 29: cf_set_button_func
 30: cf_nr_for_long_exposure
 31: cf_efav_fix_x
 32: cf_afael_active_button
 33: cf_emit_aux
 34: cf_explevel_inc_third
 35: cf_mirror_up_lock
 36: cf_flash_metering
 37: cf_flash_sync_rear
 38: cf_qr_magnify
 39: field_188
 40: cf_emit_flash
 41: cf_extend_iso
 42: cf_aeb_sequence
 43: cf_si_indicate
 44: cf_menu_pos
 45: cf_fpsel_method
 46: cf_safety_shift
 47: cf_lens_button
 55: efcomp
 66: ae_bkt
 90: usb_connect_type
 91: menupos
113: play_jump_type
114: playback_file_id
115: playback_file_id_pos
138: field_18C
156: wb_bkt
157: wbcomp_gm
158: wbcomp_ab

#endif


