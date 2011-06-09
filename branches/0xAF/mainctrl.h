#ifndef MAINCTRL_H_
#define MAINCTRL_H_

typedef enum {
	MC_INFOANDCTRL          = 1,
	MC_BUTTON               = 2,
	MC_ACTION               = 4,
	MC_DISPLAY_MODE         = 6,
	MC_START_MODE           = 7,
	MC_DriveNotifyCallBack  = 8,
	MC_ChangeAvailShot      = 11,
	MC_ChangeNotifyCallback = 15,
	MC_CardDoor_Emergency   = 19,
	MC_REQ_UI_LOCK          = 22,
	MC_REQ_UI_UNLOCK        = 23,
} mc_event_t;

#endif // MAINCTRL_H_
