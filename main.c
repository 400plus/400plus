#include "headers.h"

int setMyPrintLevel()
{  int i;  char* pt;
   pt = (char*) *(int*)0xD0A8;
   if (pt == 0) { return 0;}
   for(i=0; i<=31; i) 	{*(pt + 0x1C + (i<<1)) = 7; *(pt + 0x1D + (i<<1)) = 7; }
}

void MyGlobalStdSet ()
{ int f1 = -1;
  while (f1==-1)  { f1=FIO_CreateFile("A:/STDOUT.TXT");  if (f1==-1) SleepTask(100); }
  ioGlobalStdSet(1,f1);    //ioGlobalStdSet(2,f1);
}

int* hMyTaskMessQue, *hMyFaceSensorMessQue, *hMyFsTask, *OrgFsMesQueHnd, *hMyAutoISOTask;
#define MY_MESS1 0x01
#define MY_MESS2 0x02
#define MY_MESS3 0x03
#define MY_MESS4 0x04
#define MY_MESS5 0x05
#define AutoISO_switch		(*((char*)0x179B5))
extern void SpotImage();  extern void AutoAvComp(); extern void AfPointExtend();
extern void SetDispIso(); extern void SetDispIso1(); extern void SetDispIso2(); void SetDispIso3(); void MyAutoISOTask();
void SetAEB();
//AvComp: 0->0; 3->1/3; 5->2/3; 8->1; 11->1+1/3; 13->1+2/3; 16->2; 18->2+1/3; 20->2+2/3; 23->3; 26->3+1/3; 28->3+2/3; 31->4
int AvComp3[25]={-31&0xFF,-28&0xFF,-26&0xFF,-23&0xFF,-20&0xFF,-18&0xFF,-16&0xFF,-13&0xFF,-11&0xFF,-8&0xFF,-5&0xFF,-3&0xFF,
 				  0,3,5,8,11,13,16,18,20,23,26,28,31}; 
int AvComp2[17]={-31&0xFF,-27&0xFF,-23&0xFF,-19&0xFF,-16&0xFF,-12&0xFF,-8&0xFF,-4&0xFF, 0, 4, 8, 12, 16, 19, 23, 27, 31}; 
int* AvC, currAvC, AFP_Sel;  
int AFP[42]={391, 7, 49, 385, 73, 120, 121, 126, 127, 505, //Center
			 24, 25, 26, 27, 386, 387, 409, 410, 411,  // Top
			 96, 97, 100, 101, 388, 389, 481, 484, 485,  //Bottom
 			 40, 41, 47, 168, 169, 174, 175,   //Left
			 80, 81, 87, 336, 337, 342, 343} ;  //Right
int wait=0, test, modedial;  int spotmode=3, evalue=0;
int flag, flag1;    int ia=0, ib=0x70;
/*
unsigned char SpotItem[]= {
0x80,0x79,0x91,0xFF, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x0E,0x00,0x00,0x00,  
0xFC,0xFF,0x20,0x00, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x6C,0x00,0x00,0x00,
0x01,0x00,0x00,0x01, 0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00, 0xDC,0x01,0x00,0x00, 
0xD8,0x00,0x00,0x00, 0x4E,0x00,0x00,0x00, 0x40,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 
0x98,0xE0,0x91,0xFF, 0x01,0x00,0x00,0x00, 0x01,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 
0xF4,0x01,0x00,0x00, 0x6D,0x01,0x00,0x00, 0x00,0x00,0x00,0x00, 0x14,0x00,0x00,0x00, 
0x1A,0x00,0x00,0x00, 0x2D,0x01,0x00,0x00, 0x2B,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00, 
0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF, 0x2C,0x00,0x00,0x00, 0x0E,0x00,0x00,0x00, 
0xFF,0xFF,0xFF,0xFF, 0xDC,0x01,0x00,0x00, 0xD8,0x00,0x00,0x00, 0x4E,0x00,0x00,0x00, 
0x40,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0x00, 0xFF,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF};
#define SpotItem_SIZE sizeof(SpotItem) //sizeof(SpotItem[0]))
*/
/*	FF917980 004B25D0 004B1420 00000003	0020FFFC 004B25A4 004B2630 0000006C
	00000001 004B1420 00000000 000001DC 000000D8 0000004E 00000040 00000000
	FF91E098 00000001 00000001 00000000 000001F4 0000016D 00000000 00000014
	0000001A 00000122 0000002B 00000001 00000000 00000000 00000000 00000000
	004B25C4 004B265C 0000002C 00000003 004B25B0 000001DC 000000D8 0000004E
	00000040 004B147C 004B2584 004B2630 ///00200000 00000014 
*/
int flag3, sw, sw2;

void SetAEB()
{
	signed char m = *(signed char*)(0x179B7);
	int n;
	if (m==-4) n=0x13;
	else if (m==-3) n=0x15;
	else if (m==-2) n=0x18;
	else if (m==-1) n=0x1B;
	else if (m==0) n=0x1D;
	else if (m==1) n=0x20;
	else if (m==2) n=0x23;
	else if (m==3) n=0x25;
	else if (m==4) n=0x28;
	SendToIntercom(0xd,1,n);
}

void SingleBlue()
{
	eventproc_EdLedOn(); SleepTask(50); eventproc_EdLedOff();
}

void SingleRed()
{
	*(int*)0xC02200A0=0x46; SleepTask(50); *(int*)0xC02200A0=0x44;
}

void MyTask ()
{	//MyGlobalStdSet(); //Thai Remarked
	int* pMessage ;   int dem;
	ia=*(int*)0xC300;
	while (1)
	{	ChangeDprData(41,1); //this proc enable iso 16-80
		ReceiveMessageQueue(hMyTaskMessQue,&pMessage,0); 
		TryReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
		TryReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
		wait=1;  //SleepTask(100); 
		switch (pMessage[0])
		{
		case MY_MESS4:   //Test Mode Dial 
			//modedial++;
			if (*(int*)(0x16B60)<6) //in creative zone
			{	SetDispIso1();
				if (hMyFsTask!=0 && *(int*)(0x16B60+0x4)==3) UnSuspendTask(hMyFsTask);
			} 	//SpotImage(); 
			break;
		case MY_MESS5:   //
			eventproc_RiseEvent("RequestBuzzer");			
			break;
		case MY_MESS3: //Notify Custom Focus Point Setting enable 	
			if (*(int*)(0x16B60+0x38)==1) eventproc_RiseEvent("RequestBuzzer"); // if set Beep on
			eventproc_EdLedOn(); *(int*)0xC02200A0=0x46;SleepTask(50); eventproc_EdLedOff(); *(int*)0xC02200A0=0x44; 
			//Blueled on,Redled on, sleep, Blueled off,Redled off  
			break;
		case MY_MESS2: //Check double press AutoFocusPoint button   
			AFP_Sel=1;
			SleepTask(700);
			AFP_Sel=0;
			//eventproc_RiseEvent("RequestBuzzer");
			break;
		case MY_MESS1:
			//eventproc_UILock();

			// AfPoint extend choice
			test=*(int*)(0x4804) ; //OlAfpointSelection Dialog opened
			if (test!=0) 
			{	AfPointExtend();
				break; 
			}

			//Spot metering mode
			test=*(int*)(0x47EC) ; //OlMeterMode Dialog opened
			if (test!=0)
			{ 	
			// write log: 
			int a, i, j;
/*			char s[0x3000*2] ; 
			for (i=0;  i<=0x80;  i=i+4)  
			{
				a=*(int*)(0x47EC+i); //*(int*)(0x179E8+i); //olcinfo data
				sprintf(s+i*2,"%08X",a);
			}
			printf("[@@@@@@] hex: %s",s);

			// write log: 
			for (i=0;  i<=0x3000;  i=i+4)  
			{
				a=*(int*) ( *(int*)(0x47EC)+i); //*(int*)(0x179E8+i); //olcinfo data
				sprintf(s+i*2,"%08X",a);
			}
			printf("[@@@@@@] hex: %s",s);
*/			
				pressButton_(166);   //"Set" button
				eventproc_SetMesMode(&spotmode);  //Spot metering mode
				if (*(int*)(0x16B60+0x38)==1) eventproc_RiseEvent("RequestBuzzer");  // if set Beep On
				eventproc_PrintICUInfo();
				SleepTask(30);
				if (hMyFsTask!=0 && *(int*)(0x16B60+0x4)==3) UnSuspendTask(hMyFsTask);
				//ia=ia+5;
				//int prop; for (prop=0x10; prop<=0x3F; prop++) {SendToIntercom(prop,1,0);} //Reset all custom and camera settings
/*		
				int MeterDlg, UnkEnd,IstItem, CurrItem, CurrItemAddr, CurrItemAddr1, LastOrgItemAddr,OrgValue, aFrom, aTo; 
				MeterDlg=*(int*)0x47EC;  UnkEnd=MeterDlg+0x5C; 
				CurrItemAddr=*(int*)(MeterDlg+0x74); CurrItem=*(int*)CurrItemAddr; IstItem=CurrItem;
				int aa=1;
				while (aa<=12)
				{	CurrItemAddr1=*(int*)(CurrItemAddr+0x4);
					if ((*(int*)(CurrItemAddr1+0x1C)==0x50 || *(int*)(CurrItemAddr1+0x1C)==0x6C) && CurrItem!=IstItem)
					//(CurrItem<=0x3 || CurrItem==0xB || CurrItem==0xC || CurrItem==0xD)
					{	//OrgValue=*(int*)(CurrItemAddr+0x8); *(int*)(CurrItemAddr+0x8)=OrgValue-0x10;
						OrgValue=*(int*)(CurrItemAddr1+0x2C); *(int*)(CurrItemAddr1+0x2C)=OrgValue-0x20;
					}
					if (*(int*)(CurrItemAddr+0x18)==UnkEnd) break;					
					CurrItemAddr=*(int*)(CurrItemAddr+0x18); CurrItem=*(int*)CurrItemAddr;
					aa=aa++; 
				}
				LastOrgItemAddr=CurrItemAddr; 
				aFrom=CurrItemAddr+0x2C-0x8; aTo=aFrom+SpotItem_SIZE+0x8; memcpy(aTo, aFrom, 0x48+0x8); //Copy bottom of original last item  to new location
				aTo=aFrom+0x8; aFrom=(int)&SpotItem;  memcpy(aTo, aFrom, SpotItem_SIZE); //Copy new item
				CurrItemAddr=aTo+0x8C; CurrItemAddr1=aTo;
				*(int*)(LastOrgItemAddr+0x18)=CurrItemAddr; *(int*)(LastOrgItemAddr+0x24)=CurrItemAddr1+0x14; 
				*(int*)(LastOrgItemAddr+0x28)=0x20;

				*(int*)(CurrItemAddr1+0x4)=CurrItemAddr1+0x20; *(int*)(CurrItemAddr1+0x8)=MeterDlg;
				*(int*)(CurrItemAddr1+0x14)=CurrItemAddr1-0xC; *(int*)(CurrItemAddr1+0x18)=CurrItemAddr-0xC;
				*(int*)(CurrItemAddr1+0x24)=MeterDlg;
				*(int*)(CurrItemAddr-0xC)=CurrItemAddr1+0x14; *(int*)(CurrItemAddr-0x8)=CurrItemAddr+0x20; 
				*(int*)(CurrItemAddr+0x4)=CurrItemAddr1; *(int*)(CurrItemAddr+0x18)=UnkEnd;
				*(int*)(CurrItemAddr+0x1C)=LastOrgItemAddr; *(int*)(CurrItemAddr+0x20)=CurrItemAddr-0xC;
				eventproc_RiseEvent("RequestBuzzer");
*/
			//do_some_with_dialog(*(int*)(0x47EC));
				break;
			} 			
			
	
			//Debugmode enable--------- Need placed before FactoryMenu mode check 
			test=*(int*)(0x49F4) ; //Factory main Dialog opened	
			if (test!=0)
			{ 	MyGlobalStdSet();   eventproc_RiseEvent("RequestBuzzer"); 
				break; 
			}
	
			//Factory menu enable
			test=*(int*)(0x4A2C) ; //Main menu Dialog opened	
			if (test!=0)
			{	EnterFactoryMode();  SleepTask(20);  ExitFactoryMode();
				break;
			}

			//extend_iso_hack
			//sub_FF82B518(9); //ISO mode
			if (*(int*)(0x16B60)>=6) goto End;
			for (dem=1; dem<11; dem++)
			{	if (*(int*)(0x1C88)!=1) //MAIN Gui idle command
				{	SetDispIso();dem=11;
					SleepTask(20);  SetDispIso1(); 
				} else; {SleepTask(100);}
			}
			AutoAvComp(); //Auto  Av Compensation for ISO lower than 100  			
			SendToIntercom(0xF0,0,0); SendToIntercom(0xF1,0,0);	//Enable realtime ISO change

			//AutoISO enable
			test=*(int*)(0x47E8) ; //ISO menu Dialog opened	
			if (test!=0)
			{	if (!AutoISO_switch){
					UnSuspendTask(hMyAutoISOTask); AutoISO_switch=1;
					SingleBlue();
				}
				else { SuspendTask(hMyAutoISOTask); AutoISO_switch=0; SingleRed();}
				SleepTask(700);
				break;
			} 
			//AEB enable
			test=*(int*)(0x4820) ; //Drive mode menu Dialog opened	
			if (test!=0)
			{	if (!sw2){ SetAEB(); sw2=1; SingleBlue();}
				else { 	SendToIntercom(0xd,1,0x00); sw2=0; SingleRed();}
				SleepTask(700);
				break;
			} 				 	
//SendToIntercom(0x8,4,ia); //Tv value:
//eventproc_SetTvValue(&ia);
//eventproc_PrintTgTableData();
//ia++;
//*(int*)(0x210928)=0x13E;
/*
*(int*)(0x47EC)=CreateDialogBox(0,0,0xFF85E2E8,0x53);
//PalettePush();
sub_FF85E5E8(*(int*)(0x47EC));
do_some_with_dialog(*(int*)(0x47EC));
*/			End:
			break;
			//eventproc_EnableDigitalGain(); //eventproc_DisableDigitalGain();		
			}
		//MainHeapFree(pMessage);  
		wait=0;
		//eventproc_UILock(1);
	}
//	}
}

void SpotImage( )
{	int dem;
	for (dem=1; dem<11; dem++)
	{	if(*(int*)(0x16B60+0x4)==3 ) 
		//if mesmode =3(spot) then display image
		{sub_FF8382DC(*(int*)(0x47F0),0xD,246); do_some_with_dialog(*(int*)(0x47F0));
		}
		else; { SleepTask(20);}
	}
}

void AfPointExtend()
{ 	int dem, currAFset;
	currAFset=*(int*)(0x16B60+0x18);
	for(dem=0;dem<41;dem++) { if(currAFset==AFP[dem])  break; }  
	if (dem>=41) {SendToIntercom(7,2,AFP[0]);}
	else {SendToIntercom(7,2,AFP[dem+1]);}
	//SendToIntercom(7,2,ia); ia++; //For test 512 pattern (2 bytes variable ia)
}


void AutoAvComp()
{	int dem;
	// Change AvComp when use Iso 16->80
	if (*(int*)(0x16B60+0x60)==1) 			// if set Video = NTSC
	{	currAvC=*(int*)(0x16B60+0x24);  	//get current Avcomp value
		if (*(int*)(0x16B60+0xA8)==0) 		// Av 1/3 stop
		{	AvC=AvComp3;
			for(dem=0;dem<=24;dem++) { if(currAvC==AvC[dem])  break; }  
			if (flag1>=0x32 && flag1<=0x3F) //ISO 16 to 50 
			{	if (flag1==0x32 && dem>=9) SendToIntercom(0xA,1,AvC[dem-9]);			
				if (flag1==0x32 && dem< 9) SendToIntercom(0xA,1,AvC[0]);			
				if (flag1==0x3C && dem==23) SendToIntercom(0xA,1,AvC[dem+1]);			
				if (flag1==0x3C && dem< 23) SendToIntercom(0xA,1,AvC[dem+2]);			
				if (flag1!=0x32 && flag1!=0x3C && dem<24) SendToIntercom(0xA,1,AvC[dem+1]);
			}
			if (flag1==0x46) //ISO 80
			{   if (flag>0x46 && dem> 1) SendToIntercom(0xA,1,AvC[dem-2]);  
				if (flag>0x46 && dem==1) SendToIntercom(0xA,1,AvC[dem-1]);  
				if (flag<0x46 && dem==23) SendToIntercom(0xA,1,AvC[dem+1]);  
				if (flag<0x46 && dem==22) SendToIntercom(0xA,1,AvC[dem+2]);  
				if (flag<0x46 && dem< 22) SendToIntercom(0xA,1,AvC[dem+3]);  
			}
			if (flag1==0x48 && dem<23) SendToIntercom(0xA,1,AvC[dem+2]); //Iso 100  
			if (flag1==0x48 && dem==23) SendToIntercom(0xA,1,AvC[0]); //Iso 100  
			}  
		else 									//Av 1/2 stop
		{	AvC=AvComp2;  						
			for(dem=0;dem<=17;dem++) { if(currAvC==AvC[dem])  break; }  
			if (flag1>=0x32 && flag1<=0x3F) 	//ISO 16 to 50 
			{	if (flag1==0x32 && dem>=6) SendToIntercom(0xA,1,AvC[dem-6]);			
				if (flag1==0x32 && dem< 6) SendToIntercom(0xA,1,AvC[0]);			
				if (flag1!=0x32 && dem<17) SendToIntercom(0xA,1,AvC[dem+1]);
			}
			if (flag1==0x46) 					//ISO 80
			{	if (flag>0x46 && dem> 0) SendToIntercom(0xA,1,AvC[dem-1]);  
				if (flag<0x46 && dem< 16) SendToIntercom(0xA,1,AvC[dem+2]);  
				if (flag<0x46 && dem==16) SendToIntercom(0xA,1,AvC[0]);  
				}
			if (flag1==0x48 && dem<17) SendToIntercom(0xA,1,AvC[dem+1]); //Iso 100  
		}
	}
	if (flag1>=0x32 && flag1<=0x3F) {
		/*GUIchangeMode();  int fla=*(int*)(0x179e8+0x28); eventproc_SetAeMode(&fla);*/ 
		sub_FF85EC8C(); do_some_with_dialog(*(int*)(0x47F0)); }
}

char i16[5]="16 ", i32[5]="32 ", i40[5]="40 ", i50[5]="50 ", i80[5]="80  ", i100[5]="100 ", i125[5]="125 ", i160[5]="160 ";
char i200[5]="200", i250[5]="250 ", i320[5]="320 ", i400[5]="400 ", i500[5]="500 " , i640[5]="640 ", i800[5]="800 ";
char i1000[5]="1000", i1250[5]="1250", i1600[5]="1600", i2000[5]="2000", i2500[5]="2500",i3200[5]="3200", isoblank[5]="    ";
int* isolab1=(int*)0x5798, *isolab2=(int*)0x579C, *isolab4=(int*)0x57A0,*isolab8=(int*)0x57A4, *isolab16=(int*)0x57A8;
int* isoolc=(int*)(0x179E8+0x20);
//int* isohack=(int*)(0x179e8+0x1c);
char* iso; //, iso1,*iso2,*iso4,*iso8,*iso16;
int wait0=0;  int wait1;

void SetDispIso ( )
{ 	if (wait0==1 || wait1==1) goto END;
    wait0=1;
	flag=*(int*)(0x16B60+0x28);
                     //ISO 1600->3200
	if (flag==0x6F) {flag1=0x68; iso=i1600;goto SET; } //3200->1600	 
	if (flag==0x6D) {flag1=0x6F; iso=i3200;goto SET; } //2500->3200	 
	if (flag==0x6C) {flag1=0x6D; iso=i2500;goto SET; } //2000->2500	 
	if (flag==0x68) {flag1=0x6C; iso=i2000;goto SET;} //1600->2000
	//if (flag<0x68) { iso16=i1600; }	 
                     //ISO 800->1250
  	if (flag==0x66) {flag1=0x60; iso=i800;goto SET; }// 1250 -> 800
 	if (flag==0x64) {flag1=0x66; iso=i1250;goto SET;} // 1000 -> 1250
    if (flag==0x60) {flag1=0x64; iso=i1000;goto SET;} // 800 -> 1000
	//if (flag<0x60 || flag>0x66) {iso8=i800;}
                     //ISO 400->640
	if (flag==0x5D) {flag1=0x58; iso=i400;goto SET; }// 640 -> 400 
 	if (flag==0x5C) {flag1=0x5D; iso=i640;goto SET; }// 500 -> 640
	if (flag==0x58) {flag1=0x5C; iso=i500;goto SET;}// 400 -> 500
	//if (flag<0x58 || flag>0x5D) { iso4=i400;}
                     //ISO 200->320
 	if (flag==0x56) {flag1=0x50; iso=i200;goto SET;}// 320 -> 200
	if (flag==0x53) {flag1=0x56; iso=i320;goto SET; }// 250 -> 320
	if (flag==0x50) {flag1=0x53; iso=i250;goto SET;}// 200 -> 250
	//if (flag<0x50 || flag>0x56) {iso2=i200;}  
                     //ISO 32-160
	if (flag==0x4E)  // 160 -> 16 or 80
	{	if ( *(int*)(0x16B60+0x90)==0 ) {flag1=0x32; iso=i16; } //ShootWithoutCard on 
		else{flag1=0x46; iso=i80;} 
		goto SET; 
	}
	if (flag==0x4C)  {flag1=0x4E; iso=i160;goto SET;}//125 -> 160
	if (flag==0x48)  {flag1=0x4C; iso=i125;goto SET;}// 100 -> 125
	if (flag==0x46)  {flag1=0x48; iso=i100;goto SET; }// 80 -> 100
	if ( *(int*)(0x16B60+0x90)==0 ) 
	{	if (flag==0x3F)  {flag1=0x46; iso=i80;goto SET; }// 50 -> 80
		if (flag==0x3D)  {flag1=0x3F; iso=i50;goto SET; }// 40 -> 50
		if (flag==0x3C)  {flag1=0x3D; iso=i40;goto SET; }// 32 -> 40
		if (flag==0x32)  {flag1=0x3C; iso=i32; goto SET; }// 16 -> 32
	} 
	else 
	{ if (flag>=0x32 && flag<=0x3F){flag1=0x46; iso=i80;} 
	}
	//if (flag>0x4E || flag<0x32)  {iso1=i100;}
	SET:
    //*isolab1=(int)iso1;  *isolab2=(int)iso2; *isolab4=(int)iso4; *isolab8=(int)iso8; *isolab16=(int)iso16; 
    if (flag1>0x3F) {*isolab1=(int)iso;  *isolab2=(int)iso; *isolab4=(int)iso; *isolab8=(int)iso; *isolab16=(int)iso;} 
	else {*isolab1=(int)isoblank;} 
	eventproc_SetIsoValue(&flag1);    
    wait0=0;  
	END:
    return_0();
} 

void SetDispIso3 ( )
{	
	if (flag3==0x6F) {iso=i3200; goto SET3;} //3200	 
	if (flag3==0x6D) {iso=i2500; goto SET3;} //2500	 
	if (flag3==0x6C) {iso=i2000; goto SET3;} //2000	 
	if (flag3==0x68) {iso=i1600; goto SET3;} //1600	 
  	if (flag3==0x66) {iso=i1250; goto SET3;}// 1250
 	if (flag3==0x64) {iso=i1000; goto SET3;} // 1000
	if (flag3==0x60) {iso=i800;goto SET3; } // 800
	if (flag3==0x5D) {iso=i640; goto SET3;}// 640 
 	if (flag3==0x5C) {iso=i500; goto SET3;}// 500 
	if (flag3==0x58) {iso=i400; goto SET3;}// 400 
	if (flag3==0x56) {iso=i320;goto SET3;}// 320 
	if (flag3==0x53) {iso=i250;goto SET3; }// 250
	if (flag3==0x50) {iso=i200;goto SET3;}// 200
 	if (flag3==0x4E) {iso=i160;goto SET3; }// 160
	if (flag3==0x4C) {iso=i125;goto SET3;}//125
	if (flag3==0x48) {iso=i100;goto SET3;}// 100
    SET3:
      if (flag3>=0x46) {*isolab1=(int)iso;  *isolab2=(int)iso; *isolab4=(int)iso; *isolab8=(int)iso; *isolab16=(int)iso;} 
	else {*isolab1=(int)isoblank;} 
	eventproc_SetIsoValue(&flag3);    
	SleepTask(20); 
 	*isoolc=(int)iso;
} 

int wait2;
void SetDispIso2 ( )
{ 	int flag2;
	if (wait2!=1)
	{   wait2=1;
		*isolab1=(int)i100;  *isolab2=(int)i200; *isolab4=(int)i400; *isolab8=(int)i800; *isolab16=(int)i1600; 
        flag2=0x48; eventproc_SetIsoValue(&flag2);
        wait2=0;
	}
} 

void SetDispIso1 ( )
{	int fla;
	if (wait1==1 || wait0==1) goto END1;
    wait1=1;
    fla=*(int*)(0x16B60+0x28);
	if (fla==0x6F) {iso=i3200; goto SET1;} //3200	 
	if (fla==0x6D) {iso=i2500; goto SET1;} //2500	 
	if (fla==0x6C) {iso=i2000; goto SET1;} //2000	 
	if (fla==0x68) {iso=i1600; goto SET1;} //1600	 
	//if (fla<0x68) { iso16=i1600; }	 
  	if (fla==0x66) {iso=i1250; goto SET1;}// 1250
 	if (fla==0x64) {iso=i1000; goto SET1;} // 1000
    if (fla==0x60) {iso=i800;goto SET1; } // 800
	//if (fla<0x60 || fla>0x66) {iso8=i800;}
	if (fla==0x5D) { iso=i640; goto SET1;}// 640 
 	if (fla==0x5C) { iso=i500; goto SET1;}// 500 
    if (fla==0x58) { iso=i400; goto SET1;}// 400 
	//if (fla<0x58 || fla>0x5D) { iso4=i400;}
	if (fla==0x56) {iso=i320;goto SET1;}// 320 
	if (fla==0x53) {iso=i250;goto SET1; }// 250
    if (fla==0x50) {iso=i200;goto SET1;}// 200
	//if (fla<0x50 || fla>0x56) {iso2=i200;}  
 	if (fla==0x4E)  { iso=i160;goto SET1; }// 160
	if (fla==0x4C)  { iso=i125;goto SET1;}//125
	if (fla==0x48)  { iso=i100;goto SET1;}// 100
	if (fla==0x46)  { iso=i80;goto SET1; }// 80 
	if (fla==0x3F)  {iso=i50; goto SET1; }// 50 
	if (fla==0x3D)  {iso=i40; goto SET1;}// 40 
	if (fla==0x3C)  {iso=i32; goto SET1;}// 32 
	if (fla==0x32)  {iso=i16; goto SET1; }// 16
	//if (fla>0x4E || fla<0x32)  {iso1=i100;}
	//  eventproc_SetIsoValue(&fla);
	//eventproc_RiseEvent("RequestBuzzer");
    SET1:
	*isoolc=(int)iso;
	//isohack=(int*)(0x179e8+0x44);
	//*isohack=1;
    wait1=0;
    END1:
    return;
} 

void MyFSTask()
{	int* pMessage;// =(int*)MainHeapAlloc(8);
	while (1)
	{	if (*(int*)(0x16B60)>=6 || *(int*)(0x16B60+0x4)!=3) SuspendTask(hMyFsTask);  //Preset Zone
		//OrgFsMesQueHnd=(int*)*(int*)0x22C34; //Save default FS handle
		//ReceiveMessageQueue(OrgFsMesQueHnd,&pMessage,0);
		//TryPostMessageQueue(OrgFsMesQueHnd,pMessage,0);

		//eventproc_RequestBuzzer();
		SpotImage();
		SleepTask(400);
		//MainHeapFree(pMessage);
	}
}

void MyAutoISOTask()
{	while (1)
	{
		if (*(int*)(0x16B60)==0 || *(int*)(0x16B60)==2) {
		int cur_speed;
		int low_sp;
		int iso_h;
		int high_sp;
		int highest_iso;
		int cur_iso,iso_shift,shift,i,ii,a,aa;
		char iso_t[]=          {0x48,0x4C,0x4E,0x50,0x53,0x56,0x58,0x5C,0x5D,0x60,
					0x64,0x66,0x68,0x6C,0x6D,0x6F};

		char speed[]=          {0x0C,0x10,0x13,0x15,0x18,0x1B,0x1D,0x20,0x24,0x25,
					0x28,0x2B,0x2D,0x30,0x33,0x35,0x38,0x3B,0x3d,0x40,
					0x43,0x45,0x48,0x4B,0x4D,0x50,0x54,0x55,0x58,0x5C,
					0x5D,0x60,0x63,0x65,0x68,0x6B,0x6D,0x70,0x73,0x75,
					0x78,0x7B,0x7D,0x80,0x83,0x85,0x88,0x8B,0x8D,0x90,
					0x93,0x95,0x98};

	if (!sw){
		SleepTask(400);
		char shutter_set_p=*(int*)(0x16b7c);
		for (i=0; i<53; i++){
			if (shutter_set_p<=speed[i]){
				low_sp=i;
				sw=1;
				break;
			}
		}
		char iso_full_st=(*(char*)(0x179B4));
		if (iso_full_st==0x04)iso_h=15;
		else if (iso_full_st==0x03)iso_h=12;
		else if (iso_full_st==0x02)iso_h=9;
		else if (iso_full_st==0x01)iso_h=6;
		else if (iso_full_st==0x00)iso_h=3;
		else if (iso_full_st>0x04)iso_h=0;
		char iso_st=(*(char*)(0x179B6));
		if (iso_st<=0x04)iso_h+=iso_st;
		if (iso_h>15) iso_h=15;
		highest_iso = iso_t[iso_h];
		//char high_shift=(*(char*)(0x179B5));
		//high_sp = low_sp+high_shift;
		high_sp = low_sp+1;
		if (!AutoISO_switch)SuspendTask(hMyAutoISOTask);
		flag3=highest_iso;
		*(int*)(0x16B60+0x28)=highest_iso;
		SetDispIso3();
		//SendToIntercom(0xF0,0,0); SendToIntercom(0xF1,0,0);
		//if (hMyFsTask!=0 && *(int*)(0x16B60+0x4)==3) UnSuspendTask(hMyFsTask);
		//eventproc_RiseEvent("RequestBuzzer");
	}
	cur_iso=*(int*)(0x16B60+0x28);
	cur_speed=*(char*)(0x27E48);

	if (cur_speed<=speed[low_sp-1]){
		ii=100;
		aa=100;
		if (cur_iso<highest_iso){
			for (i=0; i<53; i++){
				if (cur_speed<=speed[i]){
					ii=i;
					break;
				}
			}
			for (a=0; a<16; a++){
				if (cur_iso==iso_t[a]){
					aa=a;
					break;
				}
			}
			if (ii!=100 && aa!=100){
				shift=low_sp-ii;
				if (shift<0)shift=0;
				iso_shift = aa+shift;
				if (iso_shift>15) iso_shift=15;
				flag3=iso_t[iso_shift];
				if (flag3>highest_iso) flag3 = highest_iso;
/*				if (iso_shift>iso_h){
					if ((ii+(iso_h-aa))>26) iso_shift=iso_h;
					else iso_shift=aa+(26-ii);
				}
				if (iso_shift>15) iso_shift=15;
				flag3=iso_t[iso_shift]; */
				SetDispIso3();
	   		}
		}
	}

	if (cur_speed>=speed[high_sp+1]){
		ii=100;
		aa=100;
		if (cur_iso>0x48){
			for (i=53; i>0; i--){
				if (cur_speed>=speed[i]){
					ii=i;
					break;
				}
			}
			for (a=0; a<16; a++){
				if (cur_iso==iso_t[a]){
					aa=a;
					break;
				}
			}
			if (ii!=100 && aa!=100){
				shift=ii-high_sp;
				if (shift<0)shift=0;
				iso_shift = aa-shift;
				if (iso_shift<0) iso_shift=0;
				flag3=iso_t[iso_shift];
				SetDispIso3();
			}

		}
	}
	   SleepTask(400);
	}
	else {sw=0; SleepTask(400);}
	}
}


void SetEvaluativeDefault()
{ 	if ( *(int*)(0x16B60+0x4)==3 )  // Spot is actived 	
	{ 	eventproc_SetMesMode(&evalue); }
}

void CreateMyTask()
{
	hMyTaskMessQue=(int*)CreateMessageQueue("MyTaskMessQue",0x40);
	CreateTask("MyTask", 0x19, 0x2000, MyTask,0);
	// My FS messQue
	//hMyFaceSensorMessQue =(int*)CreateMessageQueue("hMyFaceSensorMessQue",0x40);
	hMyFsTask=(int*)CreateTask("MyFSTask", 0x1A, 0x2000, MyFSTask,0);
	hMyAutoISOTask=(int*)CreateTask("MyAutoISOTask", 0x1A, 0x2000, MyAutoISOTask, 0);
}

void SendMyMessage(int param0, int param1)
{	int* pMessage=(int*)MainHeapAlloc(8);
	pMessage[0]=param0;  pMessage[1]=param1;
	TryPostMessageQueue(hMyTaskMessQue,pMessage,0);
}

int test1, test2, test3, test4;
void my_IntercomHandler (int r0, char* ptr)
{   int thu;
    char s[255]; int i;
	// Write Log
/*	s[0]=0;
    for (i=0;  i<ptr[0];  i++)   {sprintf(s+i*2,"%02X",ptr[i]);}
    printf_log(8,8,"[!] sz: %02X, code: %2X, hex: %s",ptr[0],ptr[1],s);
*/  
    if(ptr[1]>=0x90 && ptr[1]<=0x93) {SendMyMessage(MY_MESS4,0);}  //Iso at switch on & roll dial
    if(ptr[1]== 0xB8) {SendMyMessage(MY_MESS1,0);}  // Press Dp to set Iso

	//Change ISO value when use default camera feature.  
    test2=*(int*)(0x47E8);  //OlIso Dialog opened
	if (test2==0 && test1!=0) {test1=0;} 
	//if (test2==0 && test1==0) // do nothing 
	//if (test2!=0 && test1!=0)  //do nothing
	if (test2!=0 && test1==0) {test1=1; SetDispIso2();}

	//Set Evaluative when "Active Meter Mode is Spot"   
	test4=*(int*)(0x47EC) ; //OlMeterMode Dialog opened
	if (test4==0 && test3!=0) {test3=0;} 
	//if (test2==0 && test1==0) // do nothing
	//if (test2!=0 && test1!=0)  //do nothing
	if (test4!=0 && test3==0) {test3=1; SetEvaluativeDefault();}

	// AFP pattern
	if(ptr[1]==0x50) 
	{	if(*(int*)(0x4804)!=0) {ptr[1]=0x51; IntercomHandler(r0, ptr); ptr[1]=0x50;}
	}
	if(ptr[1]==0xB9) {SendMyMessage(MY_MESS2,0);} //Auto focus point selection dialog on
	if(ptr[1]==0xA7)  //Auto focus point selection dialog off and custom on 
	{	if(AFP_Sel==1) {/*IntercomHandler(r0, ptr);*/ ptr[1]=0xB9; SendMyMessage(MY_MESS3,0);}
	}  	

	//if(ptr[1]>0x50 && ptr[1]<0x80) {SendMyMessage(MY_MESS5,0);}  // Test some key
	IntercomHandler(r0, ptr);
}



//--------------------------------
//Button Value
//160 (0xA0) Menu
//0xA5, A1: Trash, Jump  // not work
//164 (A4) Play
//166 (A6)Set butt
//B9: Disp. ? or Focus Frame
//BA: Drive Mode
//0xBB AV +- button
//0xB3->B4:   L, R;   //0xB1=UP  0xB2=Dn  
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
