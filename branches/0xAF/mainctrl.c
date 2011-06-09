#include "main.h"
#include "mainctrl.h"
#include "firmware.h"
#include "debug.h"

// eventproc_RemOn, RemOff - should enable/disable remote controll

typedef struct MC_Table_entry_struct {
	mc_event_t t;
	int sw;
	int arg3;
} mc_table_t;

void my_MC_T_Button(mc_table_t * event) {

	printf_log(1, 6, "MC_BUTTON:\n");
	printf_log(1, 6, asw04d04d /*"\t sw:%04d(%04d)"*/, event->sw, event->arg3);

	switch (event->sw) {
	case 162:
	case 165:
	case 172:
		printf_log(1, 6, "AF: sent to intercom -> powerflag\n");
		SendToIntercom(IC_POWER_FLAG, 1, (PowerFlag | 1)); // PowerFlag.1 ?
		break;

	case 171:
		printf_log(1, 6, "AF: 171\n");
		if (event->arg3 == 0) {
			printf_log(1, 6, "AF: err_MC_T |= 1, sub...\n");
			err_MC_T |= 1;
			sub_FF821428();
		}
		break;

	case 175:
		printf_log(1, 6, "AF: 175\n");
		if (event->arg3 == 0) {
			printf_log(1, 6, "AF: err_MC_T |= 2, sub...\n");
			err_MC_T |= 2;
			sub_FF821428();
		}
		break;

	case 174:
		printf_log(1, 6, "AF: 174\n");
		if (event->arg3 !=0) {
			printf_log(1, 6, "AF: a3 != 0, err_MC_T &~4, ret\n");
			err_MC_T = err_MC_T & ~4;
			break;
		} else {
			printf_log(1, 6, "AF: err_MC_T|=4\n");
			err_MC_T |= 4;
			if (*(int *)(&off_24860 + 0xBC) != 1) { // off_24860.0xBC -> offset in some structure
				printf_log(1, 6, "AF: call change_menupos()\n");
				change_menupos();
			}

			if (unk_258A0 != 0) {
				printf_log(1, 6, "AF: sub,sub\n");
				sub_FFA22D6C();
				sub_FF825E28(event->arg3);
			}

			printf_log(1, 6, "AF: sub, change_playback\n");
			sub_FF811814();
			change_playback_file_id2();

			if (!(MC_State & 0x800)) {
				printf_log(1, 6, "AF: turndisplay 2,1 off\n");
				SetTurnDisplayEvent_2_after_1();
			}
		}
		break;

	case 182:
		printf_log(1, 6, "AF: 182, senttoIC B6\n");
		SendToIntercom(IC_BUTTON_B6, 0, 0);
		eventproc_RemOn();
		break;

	case 183:
		printf_log(1, 6, "AF: 183, senttoIC B7\n");
		SendToIntercom(IC_BUTTON_B7, 0, 0);
		eventproc_RemOn();
		break;

	case 188:
		printf_log(1, 6, "AF: tft off\n");
		eventproc_TFTOff();
		break;

	default:
		ManySendToGUI_and_other(event->sw, event->arg3);
		break;
	}
}

void my_task_MainCtrl() {

	// using printf() in this function makes troubles with shooting...
	// took me the whole eternity to understand that ...
	// perhaps the direct writing to STDOUT.TXT conflicts with writing the photo to the CF...

	(*((int*)0xC0220000)) = 0x46; // turn on the blue led
	mc_table_t * event;

	while (1) {
		int msg;

		ReceiveMessageQueue(hMainMessQueue, &msg, 0);
		event = (mc_table_t *)(&MC_T_Table[msg*3]);

		printf_log(1, 6, aMcT04dS04xD, event->t, MC_State, msg); // "[MC] T:%04d, S:%04X, %d"

		if (0) {
		} else if (event->t < 6) {
			if (event->t == MC_BUTTON) {
				my_MC_T_Button(event);
			} else {
				MC_T_1_5(event);
			}
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
