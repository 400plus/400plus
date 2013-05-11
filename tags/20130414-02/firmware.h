/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include "vxworks/vxworks.h"
#include <sys/types.h>

// Variables, Flags, Pointers, Handlers
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
	IC_SET_CF_TFT_ON_POWER_ON      = 0x3B, // C.Fn-11
	IC_SET_CF_QR_MAGNIFY           = 0x3C, // C.Fn-10
	IC_SET_CF_ORIGINAL_EVAL        = 0x3D, //
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
	IC_HELLO_WORD                  = 0x6E, // ? [First message received at intercom proxy; mostly empty]
	IC_INITIALIZATION              = 0x70, // ? [Second message at intercom; unknown contents]
	IC_POWER_FLAG                  = 0x72, //
	IC_BUZZER                      = 0x73, //
	IC_TEMP                        = 0x74, //
	IC_MEASURING                   = 0x80, //
	IC_MEASUREMENT                 = 0x81, //
	IC_SHOOT_START                 = 0x83, // ?
	IC_SHOOT_FINISH                = 0x85, // ? [MSG[2] contains focal length]
	IC_TIMERCOUNTER                = 0x8C, //
	IC_UNKNOWN_8D                  = 0x8D, // ? [Appears after initialization, but contains no info]
	IC_UNKNOWN_8E                  = 0x8E, // ? [Appears after initialization; unknown contents]
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
	IC_BUTTON_WHEEL                = 0xA9, //
	IC_BUTTON_WHEEL1               = 0xAA, // does the same as WHEEL
	IC_BUTTON_WHEEL_LEFT           = ( 1 << 8 ) | IC_BUTTON_WHEEL, // Fictitious btn
	IC_BUTTON_WHEEL_RIGHT          = ( 2 << 8 ) | IC_BUTTON_WHEEL, // Fictitious btn
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
} ic_event_t;

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
#define FLAG_METMOD_DIALOG  (*(int*)(0x000047EC))
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
	GUIMODE_400PLUS = 0x40,  // 400Plus mode
	GUIMODE_FACE    = 0x41,	 // Face mode
	GUIMODE_COUNT   = 0x4F   // Total number of active GUIMODEs (plus a safe margin)
} guimode_t;

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

// Some useful info
extern int  BodyID;
#define FLAG_BODY_ID     BodyID
#define FIRMWARE_VERSION ((char*)0x000053CC)
#define MODEL_NAME       ((char*)0x000053A8)
#define OWNER_NAME       ((char*)0x00005410)

extern int BurstCounter;  // remaining shots in burst mode (displayed in VF's bottom right corner)
extern dialog_t * hInfoCreative; // dialog handle for info screen
extern dialog_t * hMainDialog; // the main OLC dialog (white screen)
//#define hMainDialog (dialog_t*)(*(int*)(0x47F0))
extern int FaceStatus;    // 0 = no face, 1 = face (disp off)... see #32, this could give some solution
extern int GUIMode;       // Current GUI Mode
extern int hFaMain;       // Factory Dialog
extern int hMnBg;         // Menu Dialog
extern void *OlcInfoData; // OLC data

extern int logMsg(char *, ...);

// Memory management
extern void * AllocateMemory( unsigned int len );

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern int   Run_UnicodeString_Dataset_c(char *dest, const char *src, size_t size);

// Queue management

extern int *CreateMessageQueue(const char *nameMessageQueue, int param);
extern int  ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  PostMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  TryPostMessageQueue(void *hMessageQueue, void *pMessage, int forever);

// StdIO

extern int printErr(const char *, ...);             // printf to stderr
extern int printf_log(int, int, const char *, ...); // printf to the log system
extern int fdprintf(int fd, char *format, ...);     // printf to FD

// these are wrappers over stdio
extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);
extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);
extern void FIO_GetFileSize(char * file, int * size);
extern void FIO_SeekFile(int fd, long offset, int whence); // whence: SEEK_SET=0, SEEK_CUR=1, SEEK_END=2

// File IO

extern long fdConsole; // fd of stdout

// free space is reported in KB, drvltr is "A:"
extern int FP_GetDriveFreeSpace(char * drv_letter, int * result);

extern void *OpenLogFile(char *name);
extern void  CloseLogFile(void *logFile);

// Task management

extern void RiseEvent(char *name);

extern int* CreateTask(const char *name, int prio, int stack_size, void (*entry)(), long parm);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void SuspendTask(int *task);
extern void UnSuspendTask(int *task);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

// Task intercommunication

extern int IntercomHandler(const int handler, const char *message);
extern int SendToIntercom(int message, int length, int parm);
extern int IntercomHandlerButton(int button, int unknown);

// Semaphores

extern SEM_ID CreateBinarySemaphore(char * name, SEM_B_STATE state); // SEM_EMPTY (0), SEM_FULL (1)
extern int TakeSemaphore(SEM_ID sem, int time);
extern int GiveSemaphore(SEM_ID sem);
extern int DeleteSemaphore(int* sem);
extern SEM_ID hMainCtrlMonoSem;

// Event generation

extern int eventproc_PrintICUInfo();
extern int eventproc_RiseEvent(const char *event);
extern int eventproc_Release();

// Display

extern dialog_t *CreateDialogBox(int parm1, int parm2, event_handler_t, int template, int is_busy_maybe);
extern int DeleteDialogBox(dialog_t *dialog);
extern int dialog_redraw(dialog_t *dialog);

extern int dialog_item_set_int(dialog_t *dialog, const int code, const int   data);
extern int dialog_item_set_str(dialog_t *dialog, const int code, const char *text);

#define dialog_create(template, handler) CreateDialogBox(0, 0, handler, template, 0)

#define dialog_set_property_int dialog_item_set_int
#define dialog_set_property_str dialog_item_set_str

extern int InfoCreativeAppProc(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);
extern int olc_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

extern char *sub_FF83A640(); // cf free space - reports wrong ?

extern int PaletteChange(int color);

extern void GUI_Select_Item  (void *menu_handle, int menu_item);
extern void GUI_Highlight_Sub(void *menu_handle, int menu_item, int enable);
extern void GUI_Disable_Item (void *menu_handle, int menu_item, int enable);

/*PaletteChange(1); //changes menu to blue
// 0 red
// 1 blue
// 2 yelolw
// 0x12 black and white
// other numbers possible
*/

// Factory mode and debugging

extern int EnterFactoryMode();
extern int ExitFactoryMode();
extern int hDbgMgr;
// info on dmSet[Print|Store]Level() routines:
// second arg is bits field, i guess the debug classes has their own bits
// the 3rd arg is the level - 0 == max, 0xff == min
extern int dmSetPrintLevel(int DbgMgr, int dwFlag, int dwLevel);
extern int dmSetStoreLevel(int DbgMgr, int dwFlag, int dwLevel);

extern int ioGlobalStdSet(int handle, int file);

// Shutter stuff

extern int *hRelSem;	// semaphore handle, used for Camera Busy Flag too
extern char aRelSem[];   // semaphore name

// Remote shutter stuff -- this variables can help us detect any remote (may be)

extern int RemPulseWidthMin;
extern int RemPulseWidthMax;
extern int RemPulseDiffMin;
extern int RemPulseDiffMax;
extern int RemReleaseInstMin;
extern int RemReleaseInstMax;
extern int RemReleaseSelfMin;
extern int RemReleaseSelfMax;

extern int eventproc_RemOn();
extern int eventproc_RemOff();

// Language

extern void GetLanguageStr(int lang_id, char * lang_str);

// MainCtrl
extern int MC_dword_2A520;
extern int MC_dword_259C0;
extern int MC_State;
extern int MC_dword_26940;
extern int MC_dword_27BE0;
extern int dword_1C78;
extern int SendToMC_T_28();
extern int proc_CardDoor_Emergency();
extern int ErrorDetectActSweep();
extern int * hMainMessQueue;
extern int * hMainDataQueue;
extern int GetMainPreserveData_field_1C();
extern void task_MainCtrl();

// task_MainCtrl
extern int err_MC_T;
extern void sub_FF825078();
extern int MC_T_Table[];
extern char aMcT04dS04xD[];
extern char aMainMessQueue[];
extern char aMainDataQueue[];
extern int  DriveNotifyCallBack();
extern int  ChangeNotifyCallback_MC();
extern char aMainCannotPowo[];
extern char aMainCtrl[];
extern char aMonoSem[];

// mc_button
extern char asw04d04d[];
extern int PowerFlag;
extern int *some_important_structure;
extern int unk_258A0;
extern void DDD_Capture(int);
extern void set_2A0E0_to_1();

// gui / idle handler
extern int m_pSendDisplayModeToMC;
extern int GUIIdleFlag;
extern int GUIMode;
extern int m_pSendStartModeToMC;
extern int hGuiSwSem;
extern char aGuiSwSem[];
extern int off_1EE0;
extern int hGUIWindowInstance;
extern int sub_FF92ADD8();
extern int sub_FF92AF8C();
extern int sub_FF92AFD8();
extern int sub_FF92AF58();
extern int GUIWindowInstanceProc();
extern int GUI_IDLEHandler();
extern int * hGuiMainQueue;
extern char aGuiMainQueue[];
extern char aGuiMainTask[];
extern void task_GuiMainTask();
extern void OlcTftNotifyChange();
extern int * hTurnDisplayEventFlag;
extern char aTurndisplayeve[];
extern char aTurndisplaytas[];
extern void task_TurnDisplayTask();

// VRAM Semaphore

int  TakeVRAMSemaphore(int *address);
void GiveVRAMSemaphore(int *address);

// VRAM Transfer Screen

extern int(*TransferScreen)         (int r0, int r1, int r2, int r3, int a, int b, int c, int d);

extern int TransferNormalScreen     (int r0, int r1, int r2, int r3, int a, int b, int c, int d);
extern int TransferUpsideDownScreen (int r0, int r1, int r2, int r3, int a, int b, int c, int d);
extern int TransferMirrorScreen     (int r0, int r1, int r2, int r3, int a, int b, int c, int d);
extern int TransferRotatedScreen    (int r0, int r1, int r2, int r3, int a, int b, int c, int d);

#endif /* FIRMWARE_H_ */
