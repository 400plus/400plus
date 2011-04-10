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
#define EVENT_SET_METMODE   0x02
#define EVENT_SET_FLASHCOMP 0x03
#define EVENT_SET_WBMODE    0x05
#define EVENT_SET_AFPOINT   0x07
#define EVENT_SET_TV        0x08
#define EVENT_SET_AV        0x09
#define EVENT_SET_COLORTEMP 0x10
#define EVENT_SET_EVCOMP    0x0A
#define EVENT_SET_ISO       0x0B
#define EVENT_SET_AEB       0x0D

#define EVENT_SET_QUALITY         0x22
#define EVENT_SET_CFN_AFFLASH     0x2E
#define EVENT_SET_CFN_NOFLASH     0x30
#define EVENT_SET_CFN_EXTISO      0x31
#define EVENT_SET_CFN_MLU         0x35
#define EVENT_SET_CFN_FLASHSYNCR  0x38
#define EVENT_SET_CFN_SAFETYSHIFT 0x39
#define EVENT_SET_REALTIMEISO0    0xF0
#define EVENT_SET_REALTIMEISO1    0xF1

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

typedef struct {             // [*] Used and tested, others unknown
	int AEMode;              // 0x0000 [*] [1]
	int MeteringMode;        // 0x0004 [*] [2]
	int FlashExComp;         // 0x0008 [*]
	int DriveMode;           // 0x000c     [3]
	int WB;                  // 0x0010 [*] [4]
	int AF;                  // 0x0014
	int AfPoint;             // 0x0018 [*] [5]
	int TvVal;               // 0x001c [*]
	int AvVal;               // 0x0020
	int AvComp;              // 0x0024 [*]
	int ISO;                 // 0x0028 [*]
	int RedEyeRed;           // 0x002c
	int AEB;                 // 0x0030 [*]
	int WbBracketing;        // 0x0034
	int Beep;                // 0x0038 [*]
	int ColorTemp;           // 0x003c [*]
	int IsoExpand;           // 0x0040
	int AutoPowerOff;        // 0x0044
	int ViewType;            // 0x0048
	int ReviewTime;          // 0x004c
	int AutoRotate;          // 0x0050
	int LcdBrightness;       // 0x0054
	int DateTime;            // 0x0058
	int FileNumbering;       // 0x005c
	int Language;            // 0x0060
	int VideoSystem;         // 0x0064
	int Communication;       // 0x0068
	int Parameter;           // 0x006c
	int ColorSpace;          // 0x0070
	int QualityRaw;          // 0x0074 [*]
	int QualitySize;         // 0x0078
	int QualityFine;         // 0x007c
	int MenuPosCf;           // 0x0080
	int MenuPos;             // 0x0084
	int WBCompGM;            // 0x0088
	int WBCompAB;            // 0x008c
	int ShootWithoutCard;    // 0x0090
	int CfSetButton;         // 0x0094
	int CfNoiseReduction;    // 0x0098
	int CfFlashSyncTimeAv;   // 0x009c
	int CfShutterAeButton;   // 0x00a0
	int CfAfAssistBeam;      // 0x00a4 [*]
	int CfSettingSteps;      // 0x00a8 [*]
	int CfNotEmitFlash;      // 0x00ac [*]
	int CfExtendIso;         // 0x00b0 [*]
	int CfAebSeq;            // 0x00b4
	int CfSiIndicate;        // 0x00b8
	int CfMenuPos;           // 0x00bc
	int CfMLU;               // 0x00c0 [*]
	int CfAfpSelection;      // 0x00c4
	int CfFlashMetering;     // 0x00c8
	int CfFlashSyncRear;     // 0x00cc [*]
	int CfSafetyShift;       // 0x00d0 [*]
	int CfLensButton;        // 0x00d4
	int CfOriginalEval;      // 0x00d8
	int BatteryLevel;        // 0x00dc
	int BatteryType;         // 0x00e0
	int PrintUserProperty;   // 0x00e4
	int PrinterProperty;     // 0x00e8
	int ClusterSize;         // 0x00ec
	int RemainCluster;       // 0x00f0
	int FileID;              // 0x00f4
	int LensMinAv;           // 0x00f8
	int LensMaxAv;           // 0x00fc
	int EfLens;              // 0x0100
	int AvailShot;           // 0x0104
	int QrevImgProp;         // 0x0108
	int PrinterConnectType;  // 0x010c
	int MWDatRed;            // 0x0110
	int MWDatGreen1;         // 0x0114
	int MWDatGreen2;         // 0x0118
	int MWDatBlue;           // 0x011c
	int VideoJackConnect;    // 0x0120
	int IncompImg;           // 0x0124
	int BusyFlag;            // 0x0128
} type_CAMERA_MODE;

#define cameraMode (*(type_CAMERA_MODE*)0x00016B60)

// [1] Values for AEMode
#define AE_MODE_P    0
#define AE_MODE_TV   1
#define AE_MODE_AV   2
#define AE_MODE_M    3
#define AE_MODE_ADEP 5
#define AE_MODE_AUTO 8

// [2] Values for MeteringMode
#define METERING_MODE_EVAL 0
#define METERING_MODE_SPOT 3

// [3] Values for DriveMode
#define DRIVE_MODE_SINGLE 0
#define DRIVE_MODE_BURST  1

// [4] Values for WB
#define WB_MODE_AUTO        0x00
#define WB_MODE_DAYLIGHT    0x01
#define WB_MODE_COUDY       0x02
#define WB_MODE_TUNGSTEN    0x03
#define WB_MODE_FLUORESCENT 0x04
#define WB_MODE_FLASH       0x05
#define WB_MODE_CUSTOM      0x06
#define WB_MODE_SHADE       0x07
#define WB_MODE_COLORTEMP   0x08

// [5] Values for AfPoint (can be ORed together to form patterns)
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
