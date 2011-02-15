#ifndef MAIN_H_
#define MAIN_H_

#define TRUE  1
#define FALSE 0

#define	BUTTON_MENU   0xA0
#define	BUTTON_INFO   0xA1
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
#define	BUTTON_DISP   0xB9
#define	BUTTON_DRIVE  0xBA
#define	BUTTON_AV     0xBB

#define DP_PRESSED         0x01
#define MODE_DIAL          0x04
#define REQUEST_BUZZER     0x05
#define FACE_SENSOR_ISO    0x06
#define INFO_SCREEN        0x07
#define SAVE_SETTINGS      0x08
#define E_AEB              0x0A
#define INTERVAL           0x0B
#define FACE_SENSOR_NOISO  0x0C
#define SET_EVALUATIVE     0x0D
#define SWITCH_RAW_JPEG    0x0E
#define RESTORE_ISO        0x0F
#define RESTORE_WB         0x10

typedef struct {             // [*] Used and tested, others unknown
	int AEMode;              // 0x0000 [*] [1]
	int MeteringMode;        // 0x0004 [*] [2]
	int FlashExComp;         // 0x0008 [*]
	int DriveMode;           // 0x000c     [3]
	int WB;                  // 0x0010 [*]
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

#define cameraMode (*(type_CAMERA_MODE*)0x00016B60)

extern void my_IntercomHandler();

#endif /* MAIN_H_ */
