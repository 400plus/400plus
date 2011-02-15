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

extern void my_IntercomHandler();

#endif /* MAIN_H_ */
