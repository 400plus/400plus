#include "main.h"
#include "mainctrl.h"
#include "firmware.h"
#include "tasks.h"
#include "debug.h"

const char * get_mc_name(int event);
const char * get_btn_name(int btn);

typedef struct MC_Table_entry_struct {
	mc_event_t t;
	int sw;
	int arg;
} mc_table_t;

void my_MC_T_Button(mc_table_t * event) {

	// AF: important original btns handled at 0xFF81C9F0 in the OFW

#ifdef ENABLE_DEBUG
	printf_log(1, 6, "\t sw:%s (arg:%04d)", get_btn_name(event->sw), event->arg);
#else
	printf_log(1, 6, asw04d04d /*"\t sw:%04d(%04d)"*/, event->sw, event->arg);
#endif

	switch (event->sw) {

	case MC_BUTTON_BATTERY_DOOR_OPEN: // 162+13 = 175 // bat door
		if (event->arg == 0) {
			err_MC_T |= 2;
			CardDoorEmergency_Func();
		}
		break;

	case MC_BUTTON_CARD_DOOR_OPEN: // 162+9 = 171 // card door
		if (event->arg == 0) {
			err_MC_T |= 1;
			CardDoorEmergency_Func();
		}
		break;

	case MC_BUTTON_POWER: // 162+12 = 174 // shutdown
		if (event->arg !=0) {
			err_MC_T = err_MC_T & ~4;
			break;
		} else {
			err_MC_T |= 4;
			if (*(some_important_structure + 0xBC) != 1) { // off_24860.0xBC -> offset in some structure
				change_menupos();
			}

			if (unk_258A0 != 0) { // i think this flag indicates that we are taking photo ATM
				set_dword_7610_to_0();
				DDD_Capture(event->arg);// Dust Delete Data ?
				// when DDD_Capture(), is called with arg==0 (like in this call)
				// it will call internaly End_DDD_Capture.
				// so i guess this is called when we turn off the camera, while it's shooting
				// to finish the taking of the photo
			}

			set_2A0E0_to_1();
			change_playback_file_id2();

			if (!(MC_State & 0x800)) {
				SetTurnDisplayEvent_2_after_1(); // turn off display
			}
		}
		break;

	case MC_BUTTON_HALF_SHUTTER: // 162+20 = 182
		SendToIntercom(IC_BUTTON_HALF_SHUTTER, 0, 0);
		eventproc_RemOn();
		break;

	case MC_BUTTON_FULL_SHUTTER: // 162+21 = 183
		SendToIntercom(IC_BUTTON_FULL_SHUTTER, 0, 0);
		eventproc_RemOn();
		break;

	case MC_BUTTON_UNK2: // 162+26 = 188
		beep();SleepTask(500);beep(); // if you hear 2 beeps, please tell me which btn you've pressed.
		eventproc_TFTOff();
		break;

	case MC_BUTTON_JUMP: // 162+0 = 162 // btn JUMP
		switch (FLAG_GUI_MODE) {
			case GUIMODE_MAIN:
			case GUIMODE_OLC:
				ENQUEUE_TASK(set_intermediate_iso);
				break;
			default:
				MC_T_Button(event);
				break;
		}
		break;

	case MC_BUTTON_TRASH: // 162+3 = 165 // btn TRASH
	case MC_BUTTON_UNK1: // 162+10= 172 // btn UNK1
		//printf_log(1, 6, "AF: btn: %d, PF: %d,%d\n", event->sw, PowerFlag, (PowerFlag|1));
		//SendToIntercom(IC_POWER_FLAG, 1, (PowerFlag|1)); // im not sure why this isnt working ?
		MC_T_Button(event); // so we call the original btn handler to take care of it.
		break;

	default:
		ManySendToGUI_and_other(event->sw, event->arg); // perhaps it would be good to have this one
		// reversed too, but it would take much time, as it's a big one
		break;
	}
}

void my_task_MainCtrl() {

	// using printf() in this function makes troubles with shooting...
	// took me the whole eternity to understand that ...
	// we can use the canon's printf_log of course.
	// perhaps the direct writing to STDOUT.TXT conflicts with writing the photo to the CF...
	// after all we are redirecting the console to STDOUT.TXT, and the camera would not
	// expect that someone other than canon's routines will try to write to the CF.

	(*((int*)0xC0220000)) = 0x46; // turn on the blue led
	mc_table_t * event;

	while (1) {
		int msg;

		ReceiveMessageQueue(hMainMessQueue, &msg, 0);
		event = (mc_table_t *)(&MC_T_Table[msg*3]);


#ifdef ENABLE_DEBUG
		printf_log(1, 6, "[MC] T:%s, S:%04X, %d", get_mc_name(event->t), MC_State, msg);
#else
		printf_log(1, 6, aMcT04dS04xD, event->t, MC_State, msg); // "[MC] T:%04d, S:%04X, %d"
#endif

		if (0) {
		} else if (event->t < 6) {
			if (event->t == MC_BUTTON) {
				my_MC_T_Button(event); // we add our handler here
			} else {
				MC_T_1_5(event);
			}
		} else if (event->t < 8) {
			// AF: if (6): debug the display_mode params
			// when the MENU btn is pressed
			// SendToMC(MC_DISPLAY_MODE, MENU_MODE(2), 0); happens
			// or when leaving IDLE_MODE(0) is sent
			// also debug DPData before and after SendToMC(...)
			MC_T_6_7(event);
		} else if (event->t < 21) {
			MC_T_8_20(event);
		} else if (event->t < 26) {
			MC_T_21_25(event);
		} else if (event->t == 26) {
			InitializeDriveManager();
			InitializeDcfManager();
			RegisterChangeNotifyCallback_DCF();
			RegisterDriveNotifyCallBack(DriveNotifyCallBack, 0);
			RegisterChangeNotifyCallback(ChangeNotifyCallback_MC, 0);
			GiveSemaphore(hMainCtrlMonoSem);
		} else if (event->t == 27) {
			if (!(MC_State & 0b11000000)) {
				err_MC_T = event->t;
				ErrorCollectInstance(aMainCannotPowo); // "Main: Cannot PowOff at Emergency"
			}
		} else if (event->t == 28) {
			some_with_FixFacePos_0(event->sw);
		} else if (event->t == 29) {
			MC_T_29(event->sw);
		} else if (event->t == 30) {
			if (event->sw == 0) {
				some_with_FixFacePos_0(1);
				some_with_FixFacePos(1);
				SendToIntercom(IC_DIALOGOFF, 0, 0);
			} else {
				some_with_FixFacePos(0);
				FaceSensorOff();
				StartFaceSensor();
				sub_FF825078();
			}
		} else {
			printf("!!!!! should not be here, the OFW never checks this situation.\n");
		}

	} // while(1)
}


void my_MainCtrlInit() {
	hMainCtrlMonoSem = CreateBinarySemaphore(aMonoSem, 0);

	MC_dword_2A520 = 0;
	MC_dword_259C0 = 0;
	MC_State = 1;
	MC_dword_26940 = 0;
	MC_dword_27BE0 = 0;

	PictureStyleInit();
	sub_FF825AE4();
	SetEmergencyProc(proc_CardDoor_Emergency, 0);
	SetCardDoorProc(proc_CardDoor_Emergency, 0);
	TryPostMessageQueueFds_7(SendToMC_T_28, 0);
	SetErrorDetectActSweepProc(ErrorDetectActSweep);
	hMainMessQueue = (int*)CreateMessageQueue(aMainMessQueue, 0x64);
	hMainDataQueue = (int*)CreateMessageQueue(aMainDataQueue, 0xC8);
	CreateTask(aMainCtrl, 0x15, 0x4000, my_task_MainCtrl, 0);
	DebugProcsInit();
	CreateInterComQueue();
	MC_InitStart();
	IntercomHandlersInit();
	HandlersInit();
	ShootMainHandlerInit();
	sub_FF822DC0();
	sub_FF82296C();
	SetDprPrinterProperty();
	MC_RegisterEventProcedures();

	if (GetMainPreserveData_field_1C_LSR30()==0)
		goto loc_FF81BD8C;

	some_with_FixFacePos_0(0);

	unsigned char localvar1[0x198];
	unsigned char localvar2[0x194];

	memset(localvar1, 0, 0x198);
	localvar1[0x174] = 1;
	localvar2[0x174] = 1;

	SendMessageDprRequestChangeData(localvar1, localvar2);

loc_FF81BD8C:
	if (sub_FF823F34() != 0)
		goto out;

	TakeSemaphore(hMainCtrlMonoSem, 0);
	dword_1C78 = 1;

	if (get_0x1CCC() == 0)
		goto givesem;

	AbortDcfOperation();
	change_playback_file_id(1, 1);
	sub_FF823A44();

givesem:
	GiveSemaphore(hMainCtrlMonoSem);

out:
	return;
}


#ifdef ENABLE_DEBUG
const char * get_mc_name(int event) {
	static char name[20];

	switch (event) {
	case GUI_GOT_TOP_OF_CONTROL: return "GUI_GOT_TOP_OF_CONTROL";
	case MC_INFOANDCTRL: return "MC_INFOANDCTRL";
	case MC_BUTTON: return "MC_BUTTON";
	case MC_ACTION: return "MC_ACTION";
	case MC_DISPLAY_MODE: return "MC_DISPLAY_MODE";
	case MC_START_MODE: return "MC_START_MODE";
	case MC_DriveNotifyCallBack: return "MC_DriveNotifyCallBack";
	case MC_ChangeAvailShot: return "MC_ChangeAvailShot";
	case MC_ShutDown: return "MC_ShutDown";
	case MC_ChangeNotifyCallback: return "MC_ChangeNotifyCallback";
	case MC_CardDoor_Emergency: return "MC_CardDoor_Emergency";
	case MC_REQ_UI_LOCK: return "MC_REQ_UI_LOCK";
	case MC_REQ_UI_UNLOCK: return "MC_REQ_UI_UNLOCK";
	default:
		sprintf(name, "0x%08X", event);
		return name;
	}
}

const char * get_btn_name(int btn) {
	static char name[20];

	switch(btn) {
	case MC_BUTTON_MENU: return "MC_BUTTON_MENU";
	case MC_BUTTON_DISP: return "MC_BUTTON_DISP";
	case MC_BUTTON_JUMP: return "MC_BUTTON_JUMP";
	case MC_BUTTON_PLAY: return "MC_BUTTON_PLAY";
	case MC_BUTTON_TRASH: return "MC_BUTTON_TRASH";
	case MC_BUTTON_SET: return "MC_BUTTON_SET";
	case MC_DIALOG1: return "MC_DIALOG1";
	case MC_DIALOG2: return "MC_DIALOG2";
	case MC_BUTTON_DIAL: return "MC_BUTTON_DIAL";
	case MC_BUTTON_DIAL1: return "MC_BUTTON_DIAL1";
	case MC_BUTTON_DIAL_LEFT: return "MC_BUTTON_DIAL_LEFT";
	case MC_BUTTON_DIAL_RIGHT: return "MC_BUTTON_DIAL_RIGHT";
	case MC_BUTTON_CARD_DOOR_OPEN: return "MC_BUTTON_CARD_DOOR_OPEN";
	case MC_BUTTON_UNK1: return "MC_BUTTON_UNK1";
	case MC_BUTTON_POWER: return "MC_BUTTON_POWER";
	case MC_BUTTON_BATTERY_DOOR_OPEN: return "MC_BUTTON_BATTERY_DOOR_OPEN";
	case MC_BUTTON_UP: return "MC_BUTTON_UP";
	case MC_BUTTON_DOWN: return "MC_BUTTON_DOWN";
	case MC_BUTTON_RIGHT: return "MC_BUTTON_RIGHT";
	case MC_BUTTON_LEFT: return "MC_BUTTON_LEFT";
	case MC_BUTTON_HALF_SHUTTER: return "MC_BUTTON_HALF_SHUTTER";
	case MC_BUTTON_FULL_SHUTTER: return "MC_BUTTON_FULL_SHUTTER";
	case MC_BUTTON_DP: return "MC_BUTTON_DP";
	case MC_AFPDLGON: return "MC_AFPDLGON";
	case MC_BUTTON_DRIVE: return "MC_BUTTON_DRIVE";
	case MC_BUTTON_AV: return "MC_BUTTON_AV";
	case MC_BUTTON_UNK2: return "MC_BUTTON_UNK2";
	default:
		sprintf(name, "0x08X", btn);
		return name;
	}
}
#endif



