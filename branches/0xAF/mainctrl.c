#include "main.h"
#include "firmware.h"
#include "debug.h"

int * mainctrl;

extern void my_task_MainCtrl(int * msg);

typedef struct MC_Table_entry_struct {
	unsigned int t;
	unsigned int sw;
	unsigned int arg3;
} MC_Table_entry;

void my_task_MainCtrl(int * msg) {
	MC_Table_entry * event = (MC_Table_entry *)&MC_T_Table[*msg*3];

	printf_log(6, 6, aMcT04dS04xD, event->t, MC_State, *msg); // "[MC] T:%04d, S:%04X, %d"

	if (0) {
	} else if (event->t < 6) {
		MC_T_1_5(event);
	} else if (event->t < 8) {
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

	//org_task_MainCtrl(msg);
}


void __my_task_MainCtrl() {
	(*((int*)0xC0220000)) = 0x46; // turn on the blue led
	int msg;

	while (1) {
		MC_Table_entry * event;

		ReceiveMessageQueue(hMainMessQueue, &msg, 0);
		event = (MC_Table_entry *)&MC_T_Table[msg*3];

		printf("\n\nMC: Message Number: %02d, MC_State: 0x%04X, MC_T_Table: [t=%04d,act/sw=%08X,2=%08X]\n",
				msg, MC_State, event->t, event->sw, event->arg3  );

		my_task_MainCtrl(&msg);
	}

}


void my_MainCtrlInit() {
	hMainCtrlMonoSem = CreateBinarySemaphore("MonoSem", 0);

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
	hMainMessQueue = CreateMessageQueue(aMainMessQueue, 0x64);
	hMainDataQueue = CreateMessageQueue(aMainDataQueue, 0xC8);
	//mainctrl = CreateTask("MainCtrl", 0x15, 0x4000, my_task_MainCtrl, 0);
	CreateTask("MainCtr1", 0x15, 0x4000, __my_task_MainCtrl, 0);
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
