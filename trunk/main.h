#ifndef MAIN_H_
#define MAIN_H_

#define TRUE  1
#define FALSE 0

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

#define EVENT_SETTINGS 0x93
#define	EVENT_AFSELECT 0xB9

#define	BUTTON_MENU   0xA0
#define	BUTTON_DISP   0xA1
#define	BUTTON_PLAY   0xA4
#define	BUTTON_TRASH  0xA5
#define	BUTTON_SET    0xA6
#define	BUTTON_ZI     0xA7
#define	BUTTON_ZO     0xA8
#define	BUTTON_UP     0xB1
#define	BUTTON_DOWN   0xB2
#define	BUTTON_RIGHT  0xB3
#define	BUTTON_LEFT   0xB4
#define	BUTTON_DP     0xB8
#define	BUTTON_DRIVE  0xBA
#define	BUTTON_AV     0xBB

#define RESTORE_DISPLAY       0x04
#define INFO_SCREEN           0x07
#define SAVE_SETTINGS         0x08
#define E_AEB                 0x0A
#define INTERVAL              0x0B
#define FACE_SENSOR_NOISO     0x0C
#define RESTORE_METERING      0x0D
#define SWITCH_RAW_JPEG       0x0E
#define RESTORE_ISO           0x0F
#define RESTORE_WB            0x10
#define VIEWFINDER_ISO_INC    0x11
#define VIEWFINDER_ISO_DEC    0x12
#define VIEWFINDER_ISO_END    0x13
#define MENU_SET              0x21
#define	MENU_UP               0x22
#define	MENU_DOWN             0x23
#define	MENU_RIGHT            0x24
#define	MENU_LEFT             0x25
#define MENU_SWAP             0x26
#define MENU_ESC              0x27
#define MENU_INIT             0x28
#define SET_METERING_SPOT     0x29
#define SHOW_FACTORY_MENU     0x2A
#define START_DEBUG_MODE      0x2B
#define SET_INTERMEDIATE_ISO  0x2c

typedef struct {             // [*] Used and tested, others unknown
	int AEMode;              // 0x0000 [*] [1]
	int MeteringMode;        // 0x0004 [*] [2]
	int FlashExComp;         // 0x0008 [*]
	int DriveMode;           // 0x000c     [3]
	int WB;                  // 0x0010 [*] [4]
	int AF;                  // 0x0014
	int AfPoint;             // 0x0018
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
	int CfMLU;               // 0x00c0
	int CfAfpSelection;      // 0x00c4
	int CfFlashMetering;     // 0x00c8
	int CfFlashSyncRear;     // 0x00cc
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

#define cameraMode (*(type_CAMERA_MODE*)0x16B60)

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
#define GUI_OFF          0x00
#define GUI_MODE_REVIEW  0x01
#define GUI_MODE_MENU    0x02
#define GUI_MODE_INFO    0x04
#define GUI_MODE_ISO     0x09
#define GUI_MODE_WB      0x0A
#define GUI_MODE_AF      0x0B
#define GUI_MODE_DRIVE   0x0F
#define GUI_MODE_METER   0x0C
#define GUI_MODE_MAIN    0x11
#define GUI_MODE_FLASHEV 0x1B

extern void CreateMyTask();
extern void my_IntercomHandler();

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern void sprintf(char*, char*, ...);

// Queue management

extern int *CreateMessageQueue(const char *nameMessageQueue, int param);
extern int  ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  PostMessageQueue(void *hMessageQueue, void *pMessage, int forever);

// File management

#define O_RDONLY  0x0000
#define O_WRONLY  0x0001
#define O_RDWR    0x0002
#define O_CREAT   0x0200
#define O_TRUNC   0x0400

typedef long FILE;

extern int open(const char *name, int flags, int mode);
extern int read(int fd, void *buffer, long nbytes);
extern int write(int fd, void *buffer, long nbytes);
extern int close(int fd);

extern FILE* fopen(const char *file, const char *mode);
extern int   fread(void *buffer, long size, long count, FILE *fp);
extern int   fwrite(const void *buffer, long size, long count, FILE *fp);
extern int   fclose(FILE *fp);

extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);

extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);

extern void *OpenLogFile(char *name);
extern void  CloseLogFile(void *logFile);

// Task management

extern void RiseEvent(char *name);

extern int CreateTask(const char *name, int prio, int stack_size, void *entry, long parm);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void SuspendTask(int *task);
extern void UnSuspendTask(int *task);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

#endif /* MAIN_H_ */
