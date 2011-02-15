#include "io.h"
#include "led.h"
#include "file.h"
#include "task.h"
#include "event.h"
#include "message.h"

#include "main.h"

void MyGlobalStdSet ()
{ int f1 = -1;
  while (f1==-1)  { f1=FIO_CreateFile("A:/STDOUT.TXT");  if (f1==-1) SleepTask(100); }
  ioGlobalStdSet(1,f1);    //ioGlobalStdSet(2,f1);
}

int* hMyTaskMessQue, *hMyFsTask;//, *OrgFsMesQueHnd, *hMyFaceSensorMessQue;

#define safety_shift			(*((int*)0x16C30))
#define AEB						(*((int*)0x16B90))
#define av_half_stop			(*((int*)(0x16B60+0xA8)))
#define FaceSensor 				(*(int*)(0xCD38))
#define menu_dialog				(*(int*)(0x4A2C)) //Main menu Dialog opened
#define MeteringMode			(*(int*)(0x16B60+0x4))
#define DriveMode				(*(int*)(0x16B60+0x0C))
#define CurIsoValue				(*(int*)(0x16B60+0x28))
#define CurFlashComp			(*(int*)(0x16B60+0x08))
#define WhiteBalance			(*(int*)(0x16B60+0x10))
#define TvVal					(*(int*)(0x16B60+0x1C))
#define CfNotEmitFlash			(*(int*)(0x16B60+0xAC))
#define CurAvComp				(*(int*)(0x16B60+0x24))
#define CurAvCompCh				(*(char*)(0x16B60+0x24))
#define ReviewTime				(*(int*)(0x16B60+0x4c))
#define GUIMode					(*(int*)(0x00001ECC))
#define hInfoCreative			(*(int*)(0x0000213C))
//#define ShootWithoutCard		(*(int*)(0x16B60+0x90))

#define AE_Mode					(*(int*)(0x16B60))
extern void SpotImage(); extern void AfPointExtend(int); extern void MainGUISt();
extern void SetDispIso(); char* my_GUIString();
void restore_iso();
void restore_wb();

char i100[5]="100 ", i125[5]="125 ", i160[5]="160 ";
char i200[5]="200", i250[5]="250 ", i320[5]="320 ", i400[5]="400 ", i500[5]="500 " , i640[5]="640 ", i800[5]="800 ";
char i1000[5]="1000", i1250[5]="1250", i1600[5]="1600", i2000[5]="2000", i2500[5]="2500",i3200[5]="3200";
char* iso;
int test, modedial;  int spotmode=3, evalue=0;
int flag, flag1, test_iso;  //  int ia=0;
int i=0, option_number = 1;
int last_option = 13, update=1;
int flash_exp_val, av_comp_val, aeb_val, color_temp, ir_inst;

int eaeb_sub_menu=0, st_1=0, st_2=0;
int eaeb_frames=3, eaeb_ev=0x08;

//for M mode
int eaeb_m_min=0x10;
int eaeb_m_max=0x98;

int interval_time=2;
int interval_original_ae_mode=0;

char* s_eaeb[2]={"Frames", "EV"};
char* s_m_eaeb[18]={"30", "15", "8", "4", "2", "1", "0.5", "1/4","1/8","1/15", "1/30", "1/60", "1/125", "1/250", "1/500", "1/1000", "1/2000","1/4000"} ;


char* dp_button_string[4]={"Disabled", "Change ISO", "Extended AEB","Interval"};
int iso_in_viewfinder, dp_opt=1, eaeb_delay;
int settingsbuff[30];
#define settings_def_version 5
void ReadSettings()
{	int file = FIO_OpenFile("A:/settings", O_RDONLY, 644);
	if(file!=-1)
	{	FIO_ReadFile(file, (int *)settingsbuff, sizeof(settingsbuff));
		if(settingsbuff[0]==settings_def_version)
		{	iso_in_viewfinder = settingsbuff[ 1];
			dp_opt            = settingsbuff[ 2];
			eaeb_frames       = settingsbuff[ 3];
			eaeb_ev           = settingsbuff[ 4];
			eaeb_delay        = settingsbuff[ 5];
			interval_time     = settingsbuff[ 6];
			eaeb_m_min        = settingsbuff[ 7];
			eaeb_m_max        = settingsbuff[ 8];
			ir_inst           = settingsbuff[ 9];
		}
		FIO_CloseFile(file);
	}
}

void WriteSettings()
{	int file = FIO_OpenFile("A:/settings", O_CREAT|O_WRONLY , 644);
	if(file!=-1) {
		settingsbuff[ 0] = settings_def_version;
		settingsbuff[ 1] = iso_in_viewfinder;
		settingsbuff[ 2] = dp_opt;
		settingsbuff[ 3] = eaeb_frames;
		settingsbuff[ 4] = eaeb_ev;
		settingsbuff[ 5] = eaeb_delay;
		settingsbuff[ 6] = interval_time;
		settingsbuff[ 7] = eaeb_m_min;
		settingsbuff[ 8] = eaeb_m_max;
		settingsbuff[ 9] = ir_inst;

		FIO_WriteFile(file, settingsbuff, sizeof(settingsbuff));
		FIO_CloseFile(file);
	}
}

void UpdateStVariables()
{	switch (st_1)
	{	case 0: st_2=eaeb_frames;	break;
		case 1:
			if(av_half_stop)eaeb_ev &= 0xFC;
			else { if((eaeb_ev&7)!=0 && (eaeb_ev&3)==0)eaeb_ev -= 1;}
			st_2=eaeb_ev; break;
		case 2: st_2=eaeb_delay; break;
		case 3: st_2=eaeb_m_min; break;
		case 4: st_2=eaeb_m_max; break;
	}
}

void RemoteInstantRelease(int ir)
{	if(ir==1){*(int*)0x229AC=4500;*(int*)0x229B0=5560;}
	else if(ir==2){*(int*)0x229AC=6160;*(int*)0x229B0=7410;}
}

void MyTask ()
{	//MyGlobalStdSet(); //Thai Remarked
	int* pMessage ;   int dem; int t;
//	ia=*(int*)0xC300;
	int flash_exp_val_temp, av_comp_val_temp;
	int m;
	char  av_enc, av_dec, OldAvComp;
	SleepTask(1000);
	ReadSettings();
	RemoteInstantRelease(ir_inst);
	if(!*(int*)(0x16B60+0xB0))SendToIntercom(0x31, 1, 1);		// enable CFn.8 for ISO H
	SendToIntercom(0xF0,0,0); SendToIntercom(0xF1,0,0);	//Enable realtime ISO change
	while (1)
	{	//ChangeDprData(41,1); //this proc enable iso 16-80, 2000-3200
		ReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
		t=0;
		switch (pMessage[0])
		{
		case RESTORE_ISO:
			restore_iso();
			break;

		case RESTORE_WB:
			restore_wb();
			break;

		case SET_EVALUATIVE:
		 	if ( MeteringMode==3 )  // Spot is actived
			{ 	eventproc_SetMesMode(&evalue); }
			break;
		case SWITCH_RAW_JPEG:
			SendToIntercom(0x22, 1, *(int*) (0x16B60 + 0x74) ^ 3);
			break;
		case MODE_DIAL:   //Test Mode Dial
			if (AE_Mode<6) //in creative zone
			{	MainGUISt();
			}
			break;
		case REQUEST_BUZZER:
			eventproc_RiseEvent("RequestBuzzer");
			break;
		case DP_PRESSED:
			//Spot metering mode
			test=*(int*)(0x47EC) ; //OlMeterMode Dialog opened
			if (test!=0)
			{
				pressButton_(166);   //"Set" button
				eventproc_SetMesMode(&spotmode);  //Spot metering mode
				if (*(int*)(0x16B60+0x38)==1) eventproc_RiseEvent("RequestBuzzer");  // if set Beep On
				eventproc_PrintICUInfo();
				SleepTask(30);
				break;
			}

			//Debugmode enable--------- Need placed before FactoryMenu mode check
			test=*(int*)(0x49F4) ; //Factory main Dialog opened
			if (test!=0)
			{ 	MyGlobalStdSet();   eventproc_RiseEvent("RequestBuzzer");
				break;
			}

			//Factory menu enable
			if (menu_dialog!=0)
			{	EnterFactoryMode();  SleepTask(20);  ExitFactoryMode();
				break;
			}

			//extend_iso_hack
			//sub_FF82B518(9); //ISO mode
			if (AE_Mode>=6) break;
			if (dp_opt==1)SetDispIso();
			break;
		case FACE_SENSOR_ISO:
			test_iso=CurIsoValue;
			if(pMessage[1])
			{	if (test_iso<0x48) flag1 = 0x48;
				else if (test_iso<0x50) flag1 = 0x50;
				else if (test_iso<0x58) flag1 = 0x58;
				else if (test_iso<0x60) flag1 = 0x60;
				else if (test_iso<0x68) flag1 = 0x68;
				else{ flag1 = 0x6F;}
			}
			else
			{	if (test_iso>0x68) flag1 = 0x68;
				else if (test_iso>0x60) flag1 = 0x60;
				else if (test_iso>0x58) flag1 = 0x58;
				else if (test_iso>0x50) flag1 = 0x50;
				else flag1 = 0x48;
			}
			if(iso_in_viewfinder)
			if (AE_Mode==1 || AE_Mode==3)
			{	if(!CfNotEmitFlash){SendToIntercom(0x30,1,1); iso_in_viewfinder=2;}
				test=*(char*)(0x27E48);
				SendToIntercom(0x8,1,flag1+0x25);
			}
			for (dem=1; dem<11; dem++)
			{	if (*(int*)(0x1C88)!=1) //MAIN Gui idle command
				{	eventproc_SetIsoValue(&flag1);dem=11;
					SleepTask(20);
				} else; {SleepTask(100);}
			}
			break;
		case FACE_SENSOR_NOISO:
			if (AE_Mode==1 || AE_Mode==3){
				if(iso_in_viewfinder)SendToIntercom(0x8,1,test);
				if(iso_in_viewfinder==2){SendToIntercom(0x30,1,0); iso_in_viewfinder=1;}
			}
			break;
		case INFO_SCREEN:
			switch (pMessage[1])
			{
				case BUTTON_AV:
					switch(option_number)
					{	case 1:
						case 2:
							i^=1;update=0;break;
						case 7:
							if(color_temp<2200)color_temp=2200;
							else if(color_temp<3200)color_temp=3200;
							else if(color_temp<4000)color_temp=4000;
							else if(color_temp<5200)color_temp=5200;
							else if(color_temp<6000)color_temp=6000;
							else if(color_temp<7000)color_temp=7000;
							else if(color_temp>=7000)color_temp=2200;
							update=0;
							break;
					}
					break;
				case BUTTON_UP:
					if(option_number==1){option_number=last_option;}
					else{option_number-=1;}
					update=1;
					break;
				case BUTTON_DOWN:
					if(option_number==last_option){option_number=1;}
					else{option_number+=1;}
					update=1;
					break;
				case BUTTON_RIGHT:
					switch(option_number)
					{	case 1:av_comp_val=GetValue(av_comp_val,1);break;
						case 2:flash_exp_val=GetValue(flash_exp_val,1);break;
						case 3:aeb_val=GetValue(aeb_val,1); break;
						case 4:if (safety_shift==0) SendToIntercom(0x39,1,1);break;
						case 6:iso_in_viewfinder=1;WriteSettings();break;
						case 7:color_temp+=100;if (color_temp>11000)color_temp=1800;break;
						case 8:SendToIntercom(0x30,1,0);break;
						case 9:SendToIntercom(0x2E,1,0);break;
						case 10:if(dp_opt<3){dp_opt++;WriteSettings();}break;
						case 11:
							if(eaeb_sub_menu==0)
							{	if(st_1<4)
								{	st_1++;
									UpdateStVariables();
								}
							}
							else
							{	switch (st_1)
								{	case 0:
										if(st_2<9)st_2+=2;
										break;
									case 1:
										if(st_2<0x18)st_2=GetValue(st_2,1);
										break;
									case 2:
										st_2=1;
										break;
									case 3:
									case 4:
										if(st_2<=0x90)st_2+=8;//98 is maximum
										break;



								}
							}
							break;
						case 12:interval_time=interval_time<101?interval_time+1:1; break;
						case 13:
							ir_inst=1; RemoteInstantRelease(1); WriteSettings();
							break;
					}
					update=0;
					break;
				case BUTTON_LEFT:
					switch(option_number)
					{	case 1:av_comp_val=GetValue(av_comp_val,0);break;
						case 2:flash_exp_val=GetValue(flash_exp_val,0);break;
						case 3:aeb_val=GetValue(aeb_val,0); break;
						case 4:if (safety_shift==1) SendToIntercom(0x39,1,0);break;
						case 6:iso_in_viewfinder=0;WriteSettings();break;
						case 7:color_temp-=100;if (color_temp<1800)color_temp=11000;break;
						case 8:SendToIntercom(0x30,1,1);break;
						case 9:SendToIntercom(0x2E,1,1);break;
						case 10:if(dp_opt>0){dp_opt--;WriteSettings();}break;
						case 11:
							if(eaeb_sub_menu==0)
							{	if(st_1>0)
								{	st_1--;
									UpdateStVariables();
								}
							}
							else
							{	switch (st_1)
								{	case 0:
										if(st_2>3)st_2-=2;
										break;
									case 1:
										if(st_2>0x04)st_2=GetValue(st_2,0);
										break;
									case 2:
										st_2=0;
										break;
									case 3:
									case 4:
										if(st_2>=0x18)st_2-=8;//10 is minimum
										break;


								}
							}
							break;
						case 12:interval_time=interval_time>1?interval_time-1:100; break;
						case 13:
							ir_inst=0; RemoteInstantRelease(2); WriteSettings();
							break;
					}
					update=0;
					break;
			}
			sub_FF837FA8(hInfoCreative,0x11,my_GUIString());
			do_some_with_dialog(hInfoCreative);
			break;
		case SAVE_SETTINGS:
			switch(option_number)
			{	case 1:
					if(i)av_comp_val_temp=0-av_comp_val;else av_comp_val_temp=av_comp_val;
					SendToIntercom(0xA,1,av_comp_val_temp);
					break;
				case 2:
					if(i)flash_exp_val_temp=0-flash_exp_val;else flash_exp_val_temp=flash_exp_val;
					SendToIntercom(0x03,1,flash_exp_val_temp);
					break;
				case 3:SendToIntercom(0xd,1,aeb_val); break;
				case 7:
					SendToIntercom(0x10,2,color_temp);
					if (WhiteBalance!=0x08){SendToIntercom(0x5,1,0x08);}
					break;
				case 11:
					if(eaeb_sub_menu)
					{	switch (st_1)
						{	case 0: eaeb_frames=st_2;	break;
							case 1: eaeb_ev=st_2; break;
							case 2: eaeb_delay=st_2; break;
							case 3: eaeb_m_min=st_2; break;
							case 4: eaeb_m_max=st_2; break;
						}
						WriteSettings();
					}
					eaeb_sub_menu^=1;
					break;
				case 12:
				    WriteSettings();
				    break;
			}
			break;
		case E_AEB:
			if(st_2)
			{	eventproc_RiseEvent("RequestBuzzer");
				SleepTask(2000);
			}

			if(AE_Mode==3){
				int m_end;
				m=eaeb_m_min;
				do{
				  SendToIntercom(0x8,1,m);
				  SleepTask(5);
				  eventproc_Release();
				  SleepTask(5);
				  while(*(int*)(0x1CA8)){SleepTask(5);}
				  //SleepTask(850);


				if(eaeb_m_min==eaeb_m_max){
				  m_end=m;
				}else
				if(eaeb_m_min<eaeb_m_max){
				  m+=8;
				  m_end=eaeb_m_max+8;
				}else{
				  m-=8;
				  m_end=eaeb_m_max-8;
				}


				}while(	m!=m_end);



			}else{
			  if(av_half_stop)eaeb_ev &= 0xFC;
			  else { if((eaeb_ev&7)!=0 && (eaeb_ev&3)==0)eaeb_ev -= 1;}
			  OldAvComp=CurAvCompCh;
			  av_enc=CurAvCompCh;
			  av_dec=CurAvCompCh;
			  eventproc_Release();
			  m=0;
			  while(m<(eaeb_frames-1)/2)
			  {	av_dec -= eaeb_ev;
				  av_enc += eaeb_ev;
				  if(av_half_stop==0)
				  {	if((av_dec&0x06)==0x06)av_dec-=1;
					  else if((av_dec&0x07)==0x02)av_dec+=1;
					  if((av_enc&0x06)==0x06)av_enc-=1;
					  else if((av_enc&0x07)==0x02)av_enc+=1;
				  }
				  if(av_dec<0xCB)av_dec=0xCB;
				  if(av_enc>0x30)av_dec=0x30;
				  m++;
				  while(*(int*)(0x1CA8)){SleepTask(5);}
				  SendToIntercom(0xA,1,av_dec);
				  eventproc_Release();
				  while(*(int*)(0x1CA8)){SleepTask(5);}
				  SendToIntercom(0xA,1,av_enc);
				  eventproc_Release();
			  }
			  SleepTask(500);
			  SendToIntercom(0xA,1,OldAvComp);
			}

			eventproc_RiseEvent("RequestBuzzer");
			SleepTask(500);

			break;
		case INTERVAL:
		    interval_original_ae_mode= AE_Mode;
		    int i=0;
		    while(interval_original_ae_mode== AE_Mode){
		      while(*(int*)(0x1CA8)){SleepTask(5);}
		      eventproc_Release();
		      for(i=0;i<interval_time;i++){
			if(interval_original_ae_mode== AE_Mode) SleepTask(1000);
		      }

		    }
		    eventproc_RiseEvent("RequestBuzzer");

		    break;
		}
	}
}

void DispIso( )
{//	if (CurIsoValue!=0x48 && CurIsoValue!=0x50 && CurIsoValue!=0x58 && CurIsoValue!=0x60 && CurIsoValue!=0x68){
	switch(CurIsoValue) // Set ISO String
	{
		case 0x6F: iso=i3200;break; //3200
		case 0x6D: iso=i2500;break; //2500
		case 0x6C: iso=i2000;break; //2000
		case 0x68: iso=i1600;break; //1600
		case 0x66: iso=i1250;break; //1250
		case 0x64: iso=i1000;break; //1000
		case 0x60: iso=i800;break;  //800
		case 0x5D: iso=i640;break;  //640
		case 0x5C: iso=i500;break;  //500
		case 0x58: iso=i400;break;  //400
		case 0x56: iso=i320;break;  //320
		case 0x53: iso=i250;break;  //250
		case 0x50: iso=i200;break;  //200
		case 0x4E: iso=i160;break;  //160
		case 0x4C: iso=i125;break;  //125
		case 0x48: iso=i100;break;  //100
	}
	sub_FF837FA8(*(int*)(0x47F0),0x04,iso );
	do_some_with_dialog(*(int*)(0x47F0));
}

void SpotImage( )
{	sub_FF8382DC(*(int*)(0x47F0),0xD,246);
}

void KImage( )
{	sub_FF8382DC(*(int*)(0x47F0),0xC,207);
}

void FlashCompIm()
{	int flash_exp_val=CurFlashComp;
	int i=0, s;
	if (flash_exp_val>0x30)
	{	flash_exp_val=0x100-flash_exp_val;
		i=1;
	}
	switch (flash_exp_val)
	{	case 0x13:s=1;break;
		case 0x14:s=0;break;
		case 0x15:s=2;break;
		case 0x18:s=3;break;
		case 0x1B:s=5;break;
		case 0x1C:s=4;break;
		case 0x1D:s=6;break;
		case 0x20:s=7;break;
		case 0x23:s=9;break;
		case 0x24:s=8;break;
		case 0x25:s=10;break;
		case 0x28:s=11;break;
		case 0x2B:s=13;break;
		case 0x2C:s=12;break;
		case 0x2D:s=14;break;
		case 0x30:s=15;break;
	}
	if (i)s+=130;
	else s+=154;
	sub_FF8382DC(*(int*)(0x47F0),0xB,s);
}

void SetDispIso( )
{	switch(CurIsoValue)
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
	DispIso();
}

extern void MainGUISt()
{	if (AE_Mode<6)if (hMyFsTask!=0) UnSuspendTask(hMyFsTask);
}

void MyFSTask()
{	while (1)
	{	if (MeteringMode==3)SpotImage();
		if (WhiteBalance==8)KImage();
		if (CurFlashComp>0x10 && CurFlashComp<0xF0)FlashCompIm();
		DispIso();
		do_some_with_dialog(*(int*)(0x47F0));
		update=1;
		SuspendTask(hMyFsTask);
	}
}

void CreateMyTask()
{
	hMyTaskMessQue=(int*)CreateMessageQueue("MyTaskMessQue",0x40);
	CreateTask("MyTask", 0x19, 0x2000, MyTask,0);
	hMyFsTask=(int*)CreateTask("MyFSTask", 0x1A, 0x2000, MyFSTask,0);
}

void SendMyMessage(int param0, int param1)
{	int* pMessage=(int*)MainHeapAlloc(8);
	pMessage[0]=param0;  pMessage[1]=param1;
	TryPostMessageQueue(hMyTaskMessQue,pMessage,0);
}

int GetValue(int temp, int button)
{	if (temp==0 && button==0 && option_number!=3 && option_number!=11)i=1;
	if(i)button^=1;
	switch (button)
	{	case 0:
			if(av_half_stop==1)
			{	if((temp&3)!=0){temp &= 0xFC; break;}
				temp -= 4; break;
			}
			else
			{	if((temp&7)!=0 && (temp&3)==0){temp -= 1; break;}
				if((temp&5)==5)temp -= 2;
				else temp -= 3;
			}
			if(temp<0) temp=0;
			break;
		case 1:
			if(av_half_stop==1){temp = (temp & 0xFC) + 4; break;}
			else
			{	if((temp&7)!=0 && (temp&3)==0){temp += 1; break;}
				if((temp&3)==3)temp += 2;
				else temp += 3;
			}
			if(temp>0x30) temp=0x30;
			break;
	}
	if(temp==0 && i==1)i=0;
	return temp;
}

int one = 0, two = 0;
void HexToStr(int hex)
{			one = 0; two = 0;
			switch(hex&0xf0){
				case 0x10:
					one=2;
					break;
				case 0x20:
					one=4;
					break;
				case 0x30:
					one=6;
			}
			if((hex&0x08)==8)
				one++;
			switch(hex&0x07){
				case 3:
					two=3;
					break;
				case 4:
					two=5;
					break;
				case 5:
					two=7;
			}
}

char buff[17];
char* my_GUIString()
{	SleepTask(40);
	char sign[2] = {'+', '-'};
	switch(option_number)
	{	case 1:
			if (update)
			{	av_comp_val=CurAvComp;
				if (av_comp_val>0x30)
				{	av_comp_val=0x100-av_comp_val;
					i=1;
				}else i=0;
			}
			HexToStr(av_comp_val);
			sprintf(buff,"Av comp:         %c %u.%u",sign[i],one,two);
			return buff;
		case 2:
			if (update)
			{	flash_exp_val=CurFlashComp;
				if (flash_exp_val>0x30)
				{	flash_exp_val=0x100-flash_exp_val;
					i=1;
				}else i=0;
			}
			HexToStr(flash_exp_val);
			sprintf(buff,"Flash exp comp:  %c %u.%u",sign[i],one,two);
			return buff;
		case 3:
			if (update)aeb_val=AEB;i=0;
			HexToStr(aeb_val);
			sprintf(buff,"AEB:        +-%u.%u",one,two); return buff; break;
		case 4:
			if (safety_shift==0) return "Safety Shift:   Off";
			else return "Safety Shift:   On"; break;
		case 5:
			sprintf(buff,"Release Count: %u",*(int*)(0xEBFC));
			return buff;
		case 6:
			if (iso_in_viewfinder)return "Show ISO in Viewfinder: On";
			return "Show ISO in Viewfinder: Off";
		case 7:
			if (update)color_temp=*(int*)(0x16B9C);
			sprintf(buff,"Color Temperature: %uK",color_temp);
			return buff;
		case 8:
			if (CfNotEmitFlash)return "Flash:            Off";
			else return "Flash:            On";
		case 9:
			if (*(int*)(0x16C04))return "AF Assist Beam:       Off";
			else return "AF Assist Beam:       On";
		case 10:
			sprintf(buff,"DP Button:    %s",dp_button_string[dp_opt]);
			return buff;
		case 11:
			if (update)UpdateStVariables();
			if(st_1==1){HexToStr(st_2); sprintf(buff,"Extended AEB: %u.%u %s", one, two, s_eaeb[st_1]);return buff;}
			if(st_1==2)
			{	if(st_2)return "Extended AEB: 2sec. Delay";
				return "Extended AEB: No Delay";
			}
			if(st_1==3)
			{
			  sprintf(buff,"Extended AEB: M1 %s",  s_m_eaeb[(st_2-(0x10))>>3 ]);
			  return buff;
			}

			if(st_1==4)
			{
			  sprintf(buff,"Extended AEB: M2 %s",  s_m_eaeb[(st_2-(0x10))>>3 ]);
			  return buff;
			}


			sprintf(buff,"Extended AEB: %u %s", st_2, s_eaeb[st_1]);
			return buff;
		case 12:
			sprintf(buff,"Interval time: %u",interval_time);
			return buff;
		case 13:
			sprintf(buff,"IR Remote Release: %s",ir_inst==1?"Instant":"2sec.");
			return buff;
	}
}

void restore_iso() {
	test_iso = CurIsoValue;

	if (CurIsoValue > 0x68) {
		flag1 = 0x68;
	} else if (CurIsoValue > 0x60) {
		flag1 = 0x60;
	} else if (CurIsoValue > 0x58) {
		flag1 = 0x58;
	} else if (CurIsoValue > 0x50) {
		flag1 = 0x50;
	} else {
		flag1 = 0x48;
	}

	eventproc_SetIsoValue(&flag1);
}

void restore_wb() {
	if (WhiteBalance == 0x08) {
		SendToIntercom(0x5, 1, 0x00);
	}
}

void my_IntercomHandler(int r0, char* ptr) {
	if (FaceSensor) { // User has camera "on the face", display is blank
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
						// Start ISO display on viewfinder and increase ISO
						SendMyMessage(FACE_SENSOR_ISO, 1);
						return;
					} else {     // Button up
						// End ISO display on viewfinder
						SendMyMessage(FACE_SENSOR_NOISO, 0);
						return;
					}
				break;

			case BUTTON_LEFT:
					if(ptr[2]) { // Button down
						// Start ISO display on viewfinder and decrease ISO
						SendMyMessage(FACE_SENSOR_ISO, 0);
						return;
					} else {     // Button up
						// End ISO display on viewfinder
						SendMyMessage(FACE_SENSOR_NOISO, 0);
						return;
					}
				break;
		}
	} else {
	switch (ptr[1]) {
	case BUTTON_DP:
		if (AE_Mode > 5) {  //Switch to RAW or JPG in auto mode
			SendMyMessage(SWITCH_RAW_JPEG, 0);
			break;
		}
		if (GUIMode == 4) {
			SendMyMessage(SAVE_SETTINGS, 0);
			return;
		}
		if (GUIMode == 0xF || dp_opt == 2) {
			SendMyMessage(E_AEB, 0);
			return;
		}
		if (dp_opt == 3) {
			SendMyMessage(INTERVAL, 0);
			return;
		}
		if (GUIMode != 6) // Press Dp to set Iso
			SendMyMessage(DP_PRESSED, 0);
		break;
	case 0x93:
		SendMyMessage(MODE_DIAL, 0);//Iso at switch on & roll dial
		break;
	case BUTTON_AV:
		if (ptr[2]) {
			if (GUIMode == 4) {
				SendMyMessage(INFO_SCREEN, ptr[1]);
				return;
			}
		}
		break;
	case BUTTON_SET:
		if (GUIMode == 4) {
			SendMyMessage(SAVE_SETTINGS, 0);
			return;
		}
		break;
	case BUTTON_UP:
		if (ptr[2]) {
			if (GUIMode == 4) {
				SendMyMessage(INFO_SCREEN, ptr[1]);
				return;
			}
			if (GUIMode == 0x11 || GUIMode == 0) {  //Change ISO value when use default camera feature.
				SendMyMessage(RESTORE_ISO, 0);
				break;
			}
		}
		break;
	case BUTTON_DOWN:
		if (ptr[2]) {
			if (GUIMode == 4) {
				SendMyMessage(INFO_SCREEN, ptr[1]);
				return;
			}
			if (GUIMode == 0x11 || GUIMode == 0) {
				SendMyMessage(RESTORE_WB, 0);
				break;
			}
		}
		break;
	case BUTTON_RIGHT:
		if (ptr[2]) {
			if (GUIMode == 4) {
				SendMyMessage(INFO_SCREEN, ptr[1]);
				return;
			}
		}
		break;
	case BUTTON_LEFT:
		if (ptr[2]) {
			if (GUIMode == 0x11 || GUIMode == 0) { //Set Evaluative when "Active Meter Mode is Spot"
				SendMyMessage(SET_EVALUATIVE, 0);
				break;
			}
			if (GUIMode == 4) {
				SendMyMessage(INFO_SCREEN, ptr[1]);
				return;
			}
		}
		break;
	}
	}

	IntercomHandler(r0, ptr);
}

//0x90->0x93 Mode Dial Tv Av M aDep

//---------------0x16B60 store value same as 0x25E20---------------------
//AeValue address 0x16B60
	//0: P
	//1:Tv
	//2:Av
	//3:M
	//4:unknow1
	//5:A-DEP
	//8:Full Auto (Green rectangular)
//MesureValue address 0x16B60+4
	//3 Spot
	//0 Evaluative
//Drive mode address 0x16B60+0xC
	//0 Single shooting
	//1 Continuous shooting
//AvComp Value address 0x16B60+0x24
//IsoValue address 0x16B60+0x28

//-----------------------==SetPropertie
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


//-------------------------Unknown_1CF0
//1CF0: AeMode
//1CF2: MesMode
//1CF6: DriveMode
//1CFA: AfMode
//1CFE: TvValue
//1D00: AvValue
//1D02: AvCompValue
//1D04: IsoValue


//--------------------------
//6D58:   =1 Display on, =0 disp off
