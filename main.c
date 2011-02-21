#include "io.h"
#include "led.h"
#include "file.h"
#include "task.h"
#include "menu.h"
#include "display.h"
#include "message.h"
#include "settings.h"

#include "main.h"

int* hMyTaskMessQue, *hMyFsTask;

int flag1;
int update=1;

int interval_original_ae_mode=0;

char* s_eaeb[2]={"Frames", "EV"};
char* s_m_eaeb[18]={"30", "15", "8", "4", "2", "1", "0.5", "1/4","1/8","1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000","1/4000"} ;

char* dp_button_string[4]={"Disabled", "Change ISO", "Extended AEB","Interval"};

void  my_IntercomHandler(int r0, char* ptr);

void  MyTask();
void  MyFSTask();
void  SendMyMessage(int param0, int param1);

void  MyGlobalStdSet();

void  RemoteInstantRelease(int ir);
void  SetDispIso();
void  MainGUISt();
void  restore_iso();
void  restore_wb();

void CreateMyTask() {
	hMyTaskMessQue=(int*)CreateMessageQueue("MyTaskMessQue",0x40);
	CreateTask("MyTask", 0x19, 0x2000, MyTask,0);
	hMyFsTask=(int*)CreateTask("MyFSTask", 0x1A, 0x2000, MyFSTask,0);
}

void my_IntercomHandler(int r0, char* ptr) {
	do {
		// Status-independent events
		switch (ptr[1]) {
		case EVENT_SETTINGS: // Mode dial moved, settings changed
			// Re-apply changes
			SendMyMessage(MODE_DIAL, 0);
			continue;
		}

		if (FLAG_FACE_SENSOR) { // User has camera "on the face", display is blank
			switch(ptr[1]) {
			case BUTTON_UP:
				if(ptr[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_DOWN:
				if(ptr[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_RIGHT:
				if(ptr[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and increase ISO
						SendMyMessage(VIEWFINDER_ISO_INC, 0);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					SendMyMessage(VIEWFINDER_ISO_END, 0);
					return;
				}
				break;
			case BUTTON_LEFT:
				if(ptr[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and decrease ISO
						SendMyMessage(VIEWFINDER_ISO_DEC, 0);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					SendMyMessage(VIEWFINDER_ISO_END, 0);
					return;
				}
				break;
			}
		} else {
			switch (FLAG_GUI_MODE) {
			case GUI_OFF:
			case GUI_MODE_MAIN:
				switch (ptr[1]) {
				case BUTTON_UP:
					if (ptr[2]) { // Button down
						// Restore ISO to nearest standard value
						SendMyMessage(RESTORE_ISO, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (ptr[2]) { // Button down
						// Restore WB to AWB
						SendMyMessage(RESTORE_WB, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (ptr[2]) { // Button down
						 // Restore metering mode to EVALUATIVE
						SendMyMessage(SET_EVALUATIVE, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_DP:
					if (cameraMode.AEMode > 6) { // Non-creative modes
						SendMyMessage(SWITCH_RAW_JPEG, 0);
						return;
					} else {
						switch (settings.dp_opt) {
							case 1: // Set intermediate ISO
								SendMyMessage(DP_PRESSED, 0);
								return;
							case 2: // Start extended AEB script
								SendMyMessage(E_AEB, 0);
								return;
							case 3: // Start interval script
								SendMyMessage(INTERVAL, 0);
								return;
						}
					}
					break;
				}
				break;
			case GUI_MODE_INFO:
				switch (ptr[1]) {
				case BUTTON_DP:
				case BUTTON_SET:
					// Save menu settings
					SendMyMessage(MENU_SAVE, 0);
					return;
				case BUTTON_UP:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_UP, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_DOWN, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_RIGHT:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_RIGHT, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_LEFT, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_AV:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_SWAP, 0);
						return;
					} else {      // Button up
					}
					break;
				}
				break;
			case GUI_MODE_METER:
				switch (ptr[1]) {
				case BUTTON_DP:
					SendMyMessage(DP_PRESSED, 0);
					return;
				}
				break;
			}
		}
	} while(FALSE);

	IntercomHandler(r0, ptr);
}

void MyTask () {
	int *pMessage;
	int dem;

	int m;
	int av_enc, av_dec, OldAvComp;

	static int tv_value, no_emit_flash;
	int spotmode = 3, evalue = 0;

	SleepTask(1000);
	settings_read();
	RemoteInstantRelease(settings.ir_inst);

	// enable CFn.8 for ISO H
	if (!cameraMode.CfExtendIso)
		SendToIntercom(0x31, 1, 1);

	//Enable realtime ISO change
	SendToIntercom(0xF0, 0, 0);
	SendToIntercom(0xF1, 0, 0);

	while (TRUE) {
		ReceiveMessageQueue(hMyTaskMessQue, &pMessage, 0);

		switch (pMessage[0]) {
		case RESTORE_ISO:
			restore_iso();
			break;
		case RESTORE_WB:
			restore_wb();
			break;
		case SET_EVALUATIVE:
		 	if (cameraMode.MeteringMode == METERING_MODE_SPOT)  // Spot is actived
				eventproc_SetMesMode(&evalue);
			break;
		case SWITCH_RAW_JPEG:
			SendToIntercom(0x22, 1, cameraMode.QualityRaw ^ 3);
			break;
		case MODE_DIAL:
			if (cameraMode.AEMode < 6) //in creative zone
				MainGUISt();
			break;
		case REQUEST_BUZZER:
			eventproc_RiseEvent("RequestBuzzer");
			break;
		case DP_PRESSED:
			//Spot metering mode
			if (FLAG_METMOD_DIALOG) { //MeterMode Dialog opened
				pressButton_(BUTTON_SET);   //"Set" button
				eventproc_SetMesMode(&spotmode);  //Spot metering mode
				if (cameraMode.Beep) // if set Beep On
					eventproc_RiseEvent("RequestBuzzer");
				eventproc_PrintICUInfo();
				SleepTask(30);
				break;
			}

			if (FLAG_FACTORY_DIALOG != 0) {
				MyGlobalStdSet();
				eventproc_RiseEvent("RequestBuzzer");
				break;
			}

			//Factory menu enable
			if (FLAG_MENU_DIALOG) {
				EnterFactoryMode();
				SleepTask(20);
				ExitFactoryMode();
				break;
			}

			if (cameraMode.AEMode < 6 && settings.dp_opt == 1)
				SetDispIso();

			break;
		case VIEWFINDER_ISO_INC:
			if      (cameraMode.ISO < 0x48) flag1 = 0x48;
			else if (cameraMode.ISO < 0x50) flag1 = 0x50;
			else if (cameraMode.ISO < 0x58) flag1 = 0x58;
			else if (cameraMode.ISO < 0x60) flag1 = 0x60;
			else if (cameraMode.ISO < 0x68) flag1 = 0x68;
			else                            flag1 = 0x6F;

			if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
				no_emit_flash = cameraMode.CfNotEmitFlash;
				SendToIntercom(0x30, 1, 1);

				tv_value = cameraMode.TvVal;
				SendToIntercom(0x08, 1, flag1 + 0x25);

				eventproc_SetIsoValue(&flag1);
			}
			break;
		case VIEWFINDER_ISO_DEC:
			if      (cameraMode.ISO > 0x68) flag1 = 0x68;
			else if (cameraMode.ISO > 0x60) flag1 = 0x60;
			else if (cameraMode.ISO > 0x58) flag1 = 0x58;
			else if (cameraMode.ISO > 0x50) flag1 = 0x50;
			else                            flag1 = 0x48;

			if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
				no_emit_flash = cameraMode.CfNotEmitFlash;
				SendToIntercom(0x30, 1, 1);

				tv_value = cameraMode.TvVal;
				SendToIntercom(0x08, 1, flag1 + 0x25);

				eventproc_SetIsoValue(&flag1);
			}
			break;
		case VIEWFINDER_ISO_END:
			if (cameraMode.AEMode == AE_MODE_TV || cameraMode.AEMode == AE_MODE_M) {
				SendToIntercom(0x30, 1, no_emit_flash);
				SendToIntercom(0x08, 1, tv_value);
			}
			break;
		case MENU_SWAP:
			menu_swap();
			break;
		case MENU_UP:
			menu_up();
			break;
		case MENU_DOWN:
			menu_down();
			break;
		case MENU_RIGHT:
			menu_right();
			break;
		case MENU_LEFT:
			menu_left();
			break;
		case MENU_SAVE:
			menu_save();
			break;
		case E_AEB:
			if (settings.eaeb_delay) {
				eventproc_RiseEvent("RequestBuzzer");
				SleepTask(2000);
			}

			if (cameraMode.AEMode == AE_MODE_M) {
				int m_end;
				m = settings.eaeb_m_min;
				do {
					SendToIntercom(0x8, 1, m);
					SleepTask(5);
					eventproc_Release();
					SleepTask(5);
					while(FLAG_CAMERA_BUSY)
						SleepTask(5);

					if(settings.eaeb_m_min == settings.eaeb_m_max) {
						m_end=m;
					} else if(settings.eaeb_m_min < settings.eaeb_m_max) {
						m += 8;
						m_end = settings.eaeb_m_max + 8;
					} else {
						m -= 8;
						m_end = settings.eaeb_m_max - 8;
					}
				} while(m != m_end);
			} else {
			  if (cameraMode.CfSettingSteps)
					settings.eaeb_ev &= 0xFC;
			  else if((settings.eaeb_ev & 7) != 0 && (settings.eaeb_ev & 3) == 0)
					settings.eaeb_ev -= 1;

			  OldAvComp = cameraMode.AvComp;

			  av_enc = cameraMode.AvComp;
			  av_dec = cameraMode.AvComp;

			  eventproc_Release();

			  m = 0;
			  while (m < (settings.eaeb_frames - 1) / 2) {
				  av_dec -= settings.eaeb_ev;
				  av_enc += settings.eaeb_ev;

				  if (cameraMode.CfSettingSteps == 0) {
					  if ((av_dec & 0x06) == 0x06)
							av_dec -= 1;
					  else if((av_dec & 0x07) == 0x02)
							av_dec += 1;

					  if ((av_enc & 0x06) == 0x06)
							av_enc -= 1;
					  else if((av_enc & 0x07) == 0x02)
							av_enc += 1;
				  }

				  //if(av_dec<0xCB)av_dec=0xCB;
				  //if(av_enc>0x30)av_enc=0x30;

				  m++;

				  while (FLAG_CAMERA_BUSY)
						SleepTask(5);

				  SendToIntercom(0xA, 1, av_dec);
				  eventproc_Release();

				  while (FLAG_CAMERA_BUSY)
						SleepTask(5);

				  SendToIntercom(0xA, 1, av_enc);
				  eventproc_Release();
			  }

			  SleepTask(500);
			  SendToIntercom(0xA, 1, OldAvComp);
			}

			eventproc_RiseEvent("RequestBuzzer");
			SleepTask(500);
			break;
		case INTERVAL:
			interval_original_ae_mode = cameraMode.AEMode;
			int i = 0;
			while (interval_original_ae_mode == cameraMode.AEMode) {
				while(FLAG_CAMERA_BUSY)
					SleepTask(5);

				eventproc_Release();
				for(i = 0; i < settings.interval_time; i++) {
					if(interval_original_ae_mode == cameraMode.AEMode)
						SleepTask(1000);
				}
			}

			eventproc_RiseEvent("RequestBuzzer");

			break;
		}
	}
}

void MyFSTask()
{
	while (1)
	{
		SuspendTask(hMyFsTask);
		display_refresh();
		update = 1;
	}
}

void SendMyMessage(int param0, int param1)
{	int* pMessage=(int*)MainHeapAlloc(8);
	pMessage[0]=param0;  pMessage[1]=param1;
	TryPostMessageQueue(hMyTaskMessQue,pMessage,0);
}

void MyGlobalStdSet ()
{ int f1 = -1;
  while (f1==-1)  { f1=FIO_CreateFile("A:/STDOUT.TXT");  if (f1==-1) SleepTask(100); }
  ioGlobalStdSet(1,f1);    //ioGlobalStdSet(2,f1);
}

void RemoteInstantRelease(int ir)
{	if(ir==1){*(int*)0x229AC=4500;*(int*)0x229B0=5560;}
	else if(ir==2){*(int*)0x229AC=6160;*(int*)0x229B0=7410;}
}

void SetDispIso( )
{	switch(cameraMode.ISO)
	{	case 0x6F: flag1=0x68; break;// 3200-> 1600
		case 0x6D: flag1=0x6F; break;// 2500-> 3200
		case 0x6C: flag1=0x6D; break;// 2000-> 2500
		case 0x68: flag1=0x6C; break;// 1600-> 2000
		case 0x66: flag1=0x60; break;// 1250-> 800
		case 0x64: flag1=0x66; break;// 1000-> 1250
		case 0x60: flag1=0x64; break;// 800 -> 1000
		case 0x5D: flag1=0x58; break;// 640 -> 400
		case 0x5C: flag1=0x5D; break;// 500 -> 640
		case 0x58: flag1=0x5C; break;// 400 -> 500
		case 0x56: flag1=0x50; break;// 320 -> 200
		case 0x53: flag1=0x56; break;// 250 -> 320
		case 0x50: flag1=0x53; break;// 200 -> 250
		case 0x4E: flag1=0x48; break;// 160 -> 125
		case 0x4C: flag1=0x4E; break;// 125 -> 160
		case 0x48: flag1=0x4C; break;// 100 -> 125
	}

	eventproc_SetIsoValue(&flag1);
	SleepTask(10);

	display_refresh();
}

extern void MainGUISt() {
	if (cameraMode.AEMode<6)
		if (hMyFsTask!=0)
			UnSuspendTask(hMyFsTask);
}

void restore_iso() {
	if (cameraMode.ISO > 0x68) {
		flag1 = 0x68;
	} else if (cameraMode.ISO > 0x60) {
		flag1 = 0x60;
	} else if (cameraMode.ISO > 0x58) {
		flag1 = 0x58;
	} else if (cameraMode.ISO > 0x50) {
		flag1 = 0x50;
	} else {
		flag1 = 0x48;
	}

	eventproc_SetIsoValue(&flag1);
}

void restore_wb() {
	if (cameraMode.WB == 0x08) {
		SendToIntercom(0x5, 1, 0x00);
	}
}



//SendToIntercom(0x1,1,1); //(0x0,1,2);  Zonedial mode P TV AV....
//SendToIntercom(0x2,1,1); //(0x2,1,0);  Meter mode Eval, Center...
//SendToIntercom(0x3,1,1); //(0x3,1,0);  Flash ex comp
//SendToIntercom(0x4,1,1); //(0x4,1,0);  drive mode
//SendToIntercom(0x5,1,1); //(0x5,1,0);  WB chose
//SendToIntercom(0x6,1,1); //(0x6,1,0);  MF manual focus
//SendToIntercom(0x7,1,1); // AF point selecttion: can extend some special: 7, 27, 41,47, 49, 73, 81,87, 97, 101, 105,113, 120,121, 116, 127, 135,
//					139,165,168,169, 175, 185,
//SendToIntercom(0x8,2,1); //Tv value:
//SendToIntercom(0xA,1,1); //AV comp ex selecttion: can extend some special
//SendToIntercom(0xB,1,1); // ISO set
//SendToIntercom(0xC,1,1); // Red eye
//SendToIntercom(0xD,1,1); //AEB BRK
//SendToIntercom(0xE,1,1); //WB BRK
//SendToIntercom(0xF,1,1); // Beep
//SendToIntercom(22,1,1); // LCDBrightness
//SendToIntercom(34,1,1); // RAW only, L+RAW, L only
//SendToIntercom(35,1,1); // S,M,L. Combine no.34 to M+RAW OK, S+RAW not ok
//SendToIntercom(36,1,1); // JPG Fine or Medium quality.
//SendToIntercom(43,1,1); // wb+-
//SendToIntercom(44~~>49,1,1); // Cf1-->6
//SendToIntercom(54,1,1); // Cf7
//SendToIntercom(56,1,1); // Cf8
//SendToIntercom(0x3C,1,0); //(0x3C,1,1); Cfn10
//SendToIntercom(0x3B,1,1); //(0x3B,1,0); Cfn11
//SendToIntercom(0x39,1,1); //(0x39,1,0);  Cfn9
//SendToIntercom(0x59,1,1); // Clear camera seting
//SendToIntercom(0x61,1,1); // Start update firmware
//SendToIntercom(0x6B,1,1); // Full CF viewfinder message
//SendToIntercom(0x6C,1,1); // Change Battery dialog
//SendToIntercom(0x6D,1,1); // Burst counter set

