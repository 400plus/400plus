#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include <vxworks.h>

// Variables, Flags, Pointers, Handlers
#define BTN_PRESSED     0x20
#define BTN_NOT_PRESSED 0x21
// button addresses
#define BTN_ADDR_TRASH  0xC0220130
#define BTN_TRASH (*(int*)BTN_ADDR_TRASH)
#define BTN_ADDR_JUMP   0xC0220134
#define BTN_JUMP (*(int*)BTN_ADDR_JUMP)

#define LEDRED (*((int*)0xC02200A0))
#define LEDBLUE (*((int*)0xC0220000))
#define LEDON   0x46
#define LEDOFF  0x44

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

// Used flags
#define FLAG_CAMERA_BUSY    hRelSem
#define FLAG_FACE_SENSOR    FaceStatus
#define FLAG_RELEASE_COUNT  (*(int*)(0x0000EBFC))

// Some useful info

extern int  BodyID;
#define FLAG_BODY_ID     BodyID
#define FIRMWARE_VERSION ((char*)0x000053CC)
#define MODEL_NAME       ((char*)0x000053A8)
#define OWNER_NAME       ((char*)0x00005410)

extern int BurstCounter;  // remaining shots in burst mode (displayed in VF's bottom right corner)
extern int FaceStatus;    // 0 = no face, 1 = face (disp off)... see #32, this could give some solution

// Main & initialization routines

extern int ofw_entry_point(void);
extern int dmProcInit(void);
extern int StartConsole(void);
extern int SetSendButtonProc(void (*proc)(int, int, int), int unknown);

// Memory management

extern void * AllocateMemory( unsigned int len );


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

// File IO

extern long fdConsole; // fd of stdout

// free space is reported in KB, drvltr is "A:"
extern int FP_GetDriveFreeSpace(char * drv_letter, int * result);

extern void *OpenLogFile(char *name);
extern void  CloseLogFile(void *logFile);

// Task management

extern void RiseEvent(char *name);

extern int* CreateTask(const char *name, int prio, int stack_size, void (*entry)(void), long parm);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void SuspendTask(int *task);
extern void UnSuspendTask(int *task);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

// Task intercommunication

extern int InitIntercomData(void (*proxy)(const int, char *));
extern int IntercomHandler(const int handler, const char *message);
extern int SendToIntercom(int message, int length, int parm);
extern int IntercomHandlerButton(int button, int unknown);

// Semaphores
/*
extern SEM_ID CreateBinarySemaphore(char * name, SEM_B_STATE state); // SEM_EMPTY (0), SEM_FULL (1)
extern int TakeSemaphore(SEM_ID sem, int time);
extern int GiveSemaphore(SEM_ID sem);
extern int DeleteSemaphore(int* sem);
extern SEM_ID hMainCtrlMonoSem;
*/
// Display

extern char *sub_FF83A640(void); // cf free space - reports wrong ?

// Factory mode and debugging

extern int EnterFactoryMode(void);
extern int ExitFactoryMode(void);
extern int hDbgMgr;
// info on dmSet[Print|Store]Level() routines:
// second arg is bits field, i guess the debug classes has their own bits
// the 3rd arg is the level - 0 == max, 0xff == min
extern int dmSetPrintLevel(int DbgMgr, int dwFlag, int dwLevel);
extern int dmSetStoreLevel(int DbgMgr, int dwFlag, int dwLevel);

extern int dumpf(void);
extern int logMsg(char *, ...);


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

// Language

extern void GetLanguageStr(int lang_id, char * lang_str);

// MainCtrl

extern int CreateCtrlMain(int (*handler)(int, int, int, int), int zero);
extern int MC_dword_2A520;
extern int MC_dword_259C0;
extern int MC_State;
extern int MC_dword_26940;
extern int MC_dword_27BE0;
extern int dword_1C78;
extern int SendToMC_T_28(void);
extern int proc_CardDoor_Emergency(void);
extern int ErrorDetectActSweep(void);
extern int * hMainMessQueue;
extern int * hMainDataQueue;
extern int GetMainPreserveData_field_1C(void);
extern void task_MainCtrl(void);

// task_MainCtrl

extern int err_MC_T;
extern void sub_FF825078(void);
extern int MC_T_Table[];
extern char aMcT04dS04xD[];
extern char aMainMessQueue[];
extern char aMainDataQueue[];
extern int  DriveNotifyCallBack(void);
extern int  ChangeNotifyCallback_MC(void);
extern char aMainCannotPowo[];
extern char aMainCtrl[];
extern char aMonoSem[];
extern void SendToMC(int display_mode, int menu_mode, int zero);

// mc_button

extern char asw04d04d[];
extern int PowerFlag;
extern int *some_important_structure;
extern int unk_258A0;
extern void DDD_Capture(int);
extern void set_2A0E0_to_1(void);

// PTP

extern void * PTP_Actions (void * arg0, void * arg1, void * arg2, void * arg3, void * arg4);

#endif /* FIRMWARE_H_ */
