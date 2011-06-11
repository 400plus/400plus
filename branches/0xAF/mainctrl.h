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

#endif // MAINCTRL_H_
