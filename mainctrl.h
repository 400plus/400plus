#ifndef MAINCTRL_H_
#define MAINCTRL_H_

#include "firmware.h"

typedef enum {
	MC_INFOANDCTRL          = 0x01,
	MC_BUTTON               = 0x02,
	MC_TestBasicChk_arg_F6  = 0x03,
	MC_ACTION               = 0x04,
	MC_DISPLAY_MODE         = 0x06,
	MC_START_MODE           = 0x07,
	MC_DriveNotifyCallBack  = 0x08,
	MC_ChangeAvailShot      = 0x0B,
	MC_ShutDown             = 0x0D,
	MC_ChangeNotifyCallback = 0x0F,
	MC_CardDoor_Emergency   = 0x13,
	MC_REQ_UI_LOCK          = 0x16,
	MC_REQ_UI_UNLOCK        = 0x17,
} mc_event_t;

// look at 0xFF81C9F0 in OFW for handler
typedef enum {
	MC_BUTTON_MENU                 = IC_BUTTON_MENU,
	MC_BUTTON_DISP                 = IC_BUTTON_DISP,
	MC_BUTTON_JUMP                 = IC_BUTTON_JUMP,
	// 0xA3 ?? does something in asm
	MC_BUTTON_PLAY                 = IC_BUTTON_PLAY,
	MC_BUTTON_TRASH                = IC_BUTTON_TRASH,
	MC_BUTTON_SET                  = IC_BUTTON_SET,
	MC_DIALOG1                     = IC_AFPDLGOFF, // seems like dialog destroy
	MC_DIALOG2                     = 0xA8, // could be dialog create
	MC_BUTTON_WHEEL                = IC_BUTTON_WHEEL,
	MC_BUTTON_WHEEL1               = IC_BUTTON_WHEEL1, // does the same as WHEEL
	MC_BUTTON_WHEEL_LEFT           = ( 1 << 8 ) | IC_BUTTON_WHEEL, // Fictitious btn
	MC_BUTTON_WHEEL_RIGHT          = ( 2 << 8 ) | IC_BUTTON_WHEEL, // Fictitious btn
	MC_BUTTON_CARD_DOOR_OPEN       = IC_BUTTON_CARD_DOOR,
	MC_BUTTON_UNK1                 = IC_BUTTON_UNK1,
	MC_BUTTON_POWER                = IC_BUTTON_POWER,
	MC_BUTTON_BATTERY_DOOR_OPEN    = IC_BUTTON_BATTERY_DOOR,
	// 0xB0 ?? does something in asm
	MC_BUTTON_UP                   = IC_BUTTON_UP,
	MC_BUTTON_DOWN                 = IC_BUTTON_DOWN,
	MC_BUTTON_RIGHT                = IC_BUTTON_RIGHT,
	MC_BUTTON_LEFT                 = IC_BUTTON_LEFT,
	// 0xB5 ?? does the same as B0
	MC_BUTTON_HALF_SHUTTER         = IC_BUTTON_HALF_SHUTTER,
	MC_BUTTON_FULL_SHUTTER         = IC_BUTTON_FULL_SHUTTER,
	MC_BUTTON_DP                   = IC_BUTTON_DP,
	MC_AFPDLGON                    = IC_AFPDLGON,
	MC_BUTTON_DRIVE                = IC_BUTTON_DRIVE,
	MC_BUTTON_CARD_DOOR_CLOSE      = IC_BUTTON_AV, // decide which one is the real one
	MC_BUTTON_AV                   = IC_BUTTON_AV, // probably AV
	MC_BUTTON_UNK2                 = IC_BUTTON_UNK2, // calls TFT OFF, i cannot find which button is this
} mc_button_t;

#endif // MAINCTRL_H_
