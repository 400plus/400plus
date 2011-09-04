#ifndef MAINCTRL_H_
#define MAINCTRL_H_

typedef enum {
	MC_INFOANDCTRL          = 0x01,
	MC_BUTTON               = 0x02,
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

typedef enum {
	MC_BUTTON_MENU                 = 0xA0, //
	MC_BUTTON_DISP                 = 0xA1, //
	MC_BUTTON_JUMP                 = 0xA2, //
	MC_BUTTON_PLAY                 = 0xA4, //
	MC_BUTTON_TRASH                = 0xA5, //
	MC_BUTTON_SET                  = 0xA6, //
	MC_DIALOG1                     = 0xA7, //
	MC_DIALOG2                     = 0xA8, //
	MC_BUTTON_DIAL                 = 0xA9, //
	MC_BUTTON_DIAL_LEFT            = ( 1 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	MC_BUTTON_DIAL_RIGHT           = ( 2 << 8 ) | IC_BUTTON_DIAL, // Fictitious btn
	MC_BUTTON_CARD_DOOR_OPEN       = 0xAB, //
	MC_BUTTON_UNK1                 = 0xAC, //
	MC_BUTTON_POWER                = 0xAE, //
	MC_BUTTON_BATTERY_DOOR_OPEN    = 0xAF, //
	MC_BUTTON_UP                   = 0xB1, //
	MC_BUTTON_DOWN                 = 0xB2, //
	MC_BUTTON_RIGHT                = 0xB3, //
	MC_BUTTON_LEFT                 = 0xB4, //
	MC_BUTTON_HALF_SHUTTER         = 0xB6, //
	MC_BUTTON_FULL_SHUTTER         = 0xB7, //
	MC_BUTTON_DP                   = 0xB8, //
	MC_AFPDLGON                    = 0xB9, //
	MC_BUTTON_DRIVE                = 0xBA, //
	MC_BUTTON_CARD_DOOR_CLOSE      = 0xBB, //
	MC_BUTTON_UNK2                 = 0xBC, // calls TFT OFF, i cannot find which button is this

} mc_button_t;

#endif // MAINCTRL_H_
