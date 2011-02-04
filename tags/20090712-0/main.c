#include "headers.h"



int setMyPrintLevel()

{ int i;

   char* pt;

   pt = (char*) *(int*)0xD0A8;

   if (pt == 0) { return 0;}

   
for(i=0; i<=31; i++)
   {*(pt + 0x1C + (i<<1)) = 7;
   *(pt + 0x1D + (i<<1)) = 7; }
}

void* hMyTaskMessQue;


#define MY_MESS1 0x01


#define MY_MESS2 0x02


#define MY_MESS3 0x03
#define MY_MESS4 0x04






void MyGlobalStdSet ()

{
 int f1 = -1;

  while (f1==-1)
  { f1=FIO_CreateFile("A:/STDOUT.TXT");
 
    if (f1==-1) SleepTask(100);

  } ioGlobalStdSet(1,f1);    ioGlobalStdSet(2,f1);

}



extern void* hOlcInfoMessQueue;   

extern void SetDispIso();
extern void SetDispIso1();
extern void SetDispIso2();
int wait=0, test, modedial, sec1=0, sec2=0;

void MyTask ()

{
  //MyGlobalStdSet(); //Thai Remarked
 int* pMessage ;   int mesmode=3, receivemess ;

 while (1)
 { 
    ReceiveMessageQueue(hMyTaskMessQue,&pMessage,0); 
    TryReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
    TryReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
    //sec2=eventproc_GetSecond();
    //if (sec1==sec2) {continue;}
    //sec1=sec2;
    sec1++;
    wait=1;
    SleepTask(100);
    switch (pMessage[0])
    {

     case MY_MESS4:   //Test Mode Dial 
	modedial++;
	SetDispIso1();
    	//eventproc_RiseEvent("RequestBuzzer");
     	break;
/*
     case MY_MESS2:    

    	//SleepTask(200);
	test=*(int*)(0x47E8); //OlIso Dialog opened
	if (test!=0)
	{ SetDispIso2();
	   test1=0;  
	   eventproc_RiseEvent("RequestBuzzer");
	}
     	break;
*/

     case MY_MESS1:

	//eventproc_UILock();
         //Spot metering mode
	test=*(int*)(0x47EC) ; //OlMeterMode Dialog opened
	if (test!=0)
	{ pressButton_(166);   //Set button
                     eventproc_SetMesMode(&mesmode);  //Spot metering mode
	   eventproc_RiseEvent("RequestBuzzer");
	   eventproc_PrintICUInfo();
	   break;
	}
         //Debugmode enable--------- Need placed before FactoryMenu check 
	test=*(int*)(0x49F4) ; //Factory main Dialog opened	
	if (test!=0)
	{ MyGlobalStdSet(); 
	   eventproc_RiseEvent("RequestBuzzer");
	   break;
	}
         //Factory menu enable
	test=*(int*)(0x4A2C) ; //Main menu Dialog opened	
	if (test!=0)
	{ EnterFactoryMode();
	   SleepTask(20);
	   ExitFactoryMode();
	   break;
	}
          //extend_iso
	//eventproc_RiseEvent("RequestBuzzer");
//Test like canon did in firmware. not ok, still hang if press DP too fast 
//SomeStateLock();
//sub_FF936734();
//sub_FF82B518(0x9);
	SetDispIso();
//SomeStateUnLock();
//sub_FF936770();
//guiGraphics_clearImage();
//sub_FF84ED98 ();
//sub_FF82B518(0x0); //Blink Scr
SleepTask(600);
//	ChangeDprData(41,1);
	//break;
     }
   
  //MainHeapFree(pMessage);  
  //SleepTask(200); //wait for Camera refresh
  wait=0;
  //eventproc_UILock(1);
  }
 
}

char i80[5]="80  ", i100[5]="100 ", i125[5]="125 ", i160[5]="160 ", i200[5]="200 ",i250[5]="250 ";
char i320[5]="320 ", i400[5]="400 ", i500[5]="500 " , i640[5]="640 ", i800[5]="800 ", i1000[5]="1000";
char i1250[5]="1250", i1600[5]="1600", i2000[5]="2000", i2200[5]="2200", i3200[5]="3200";
int* isolab1=(int*)0x5798, *isolab2=(int*)0x579C, *isolab4=(int*)0x57A0,*isolab8=(int*)0x57A4, *isolab16=(int*)0x57A8;
char* iso1,*iso2,*iso4,*iso8,*iso16;
int wait0=0;  int wait1;

void SetDispIso ( )
{
    int flag, flag1;
    if (wait0==1 || wait1==1) goto END;
        wait0=1;
                  flag=*(int*)(0x16B60+0x28);
                    //ISO 1600->3200
	if (flag==0x6F) {flag1=0x68;  iso16=i1600; } //3200->1600	 
	if (flag==0x6E) {flag1=0x6F; iso16=i3200; } //2200->3200	 
	if (flag==0x6C) {flag1=0x6E; iso16=i2200; } //2000->2200	 
	if (flag==0x68) {flag1=0x6C; iso16=i2000; } //1600->2000
	if (flag<0x68) { iso16=i1600; }	 
                     //ISO 800->1250
  	if (flag==0x66) {flag1=0x60; iso8=i800; }// 1250 -> 800
 	if (flag==0x64) {flag1=0x66; iso8=i1250; } // 1000 -> 1250




                  if (flag==0x60) {flag1=0x64; iso8=i1000; } // 800 -> 1000


	if (flag<0x60 || flag>0x66) {iso8=i800;}
                     //ISO 400->640
	if (flag==0x5D) {flag1=0x58; iso4=i400; }// 640 -> 400 


 	if (flag==0x5C) {flag1=0x5D; iso4=i640; }// 500 -> 640


	if (flag==0x58) {flag1=0x5C; iso4=i500; }// 400 -> 500


	if (flag<0x58 || flag>0x5D) { iso4=i400;}
                     //ISO 200->320
 	if (flag==0x56) {flag1=0x50; iso2=i200;}// 320 -> 200


	if (flag==0x53) {flag1=0x56; iso2=i320; }// 250 -> 320


	if (flag==0x50) {flag1=0x53; iso2=i250;}// 200 -> 250


	if (flag<0x50 || flag>0x56) {iso2=i200;}  
                  //ISO 32-160
 	if (flag==0x4E)  {flag1=0x46; iso1=i80; }// 160 -> 16


	if (flag==0x4C)  {flag1=0x4E; iso1=i160;}//125 -> 160


	if (flag==0x48)  {flag1=0x4C; iso1=i125;}// 100 -> 125


	if (flag==0x46)  {flag1=0x48; iso1=i100; }// 80 -> 100


	//if (flag==0x3F)  {flag1=0x46;  }// 50 -> 80


	//if (flag==0x3D)  {flag1=0x3F; }// 40 -> 50


	//if (flag==0x3C)  {flag1=0x3D; }// 32 -> 40


	//if (flag==0x32)  {flag1=0x3C;  }// 16 -> 32


	if (flag>0x4E || flag<0x46)  {iso1=i100;}
                  *isolab1=(int)iso1;  *isolab2=(int)iso2; *isolab4=(int)iso4; *isolab8=(int)iso8; *isolab16=(int)iso16; 
	eventproc_SetIsoValue(&flag1); 
          wait0=0;  
     END:
          return;
} 


int wait2;
void SetDispIso2 ( )
{ int flag;
   if (wait2!=1)
   {   wait2=1;
	iso16=i1600; iso8=i800;  iso4=i400;  iso2=i200;  iso1=i100;
                  *isolab1=(int)iso1;  *isolab2=(int)iso2; *isolab4=(int)iso4; *isolab8=(int)iso8; *isolab16=(int)iso16; 
/*
	if (flag>0x4E || flag<0x46)  *isolab1=(int)iso1; 
	if (flag<0x50 || flag>0x56) *isolab2=(int)iso2; 
	if (flag<0x58 || flag>0x5D) *isolab4=(int)iso4; 
	if (flag<0x60 || flag>0x66) *isolab8=(int)iso8;
	if (flag<=0x68) *isolab16=(int)iso16; 
*/
        wait2=0;
   }
} 

void SetDispIso1 ( )
{
   int fla;
   if (wait1==1 || wait0==1) goto END1;
       wait1=1;
                  fla=*(int*)(0x16B60+0x28);
	if (fla==0x6F) {iso16=i3200; } //3200	 
	if (fla==0x6E) {iso16=i2200; } //2200	 
	if (fla==0x6C) {iso16=i2000; } //2000	 
	if (fla==0x68) {iso16=i1600; } //1600	 
	if (fla<0x68) { iso16=i1600; }	 
  	if (fla==0x66) {iso8=i1250; }// 1250
 	if (fla==0x64) {iso8=i1000; } // 1000


                  if (fla==0x60) {iso8=i800; } // 800
	if (fla<0x60 || fla>0x66) {iso8=i800;}
	if (fla==0x5D) { iso4=i640; }// 640 


 	if (fla==0x5C) { iso4=i500; }// 500 




                  if (fla==0x58) { iso4=i400; }// 400 
	if (fla<0x58 || fla>0x5D) { iso4=i400;}
	if (fla==0x56) {iso2=i320;}// 320 


 	if (fla==0x53) {iso2=i250; }// 250




                  if (fla==0x50) {iso2=i200;}// 200


	if (fla<0x50 || fla>0x56) {iso2=i200;}  
 	if (fla==0x4E)  { iso1=i160; }// 160
	if (fla==0x4C)  { iso1=i125;}//125


	if (fla==0x48)  { iso1=i100;}// 100


	if (fla==0x46)  { iso1=i80; }// 80 


	if (fla>0x4E || fla<0x46)  {iso1=i100;}
                 *isolab1=(int)iso1;  *isolab2=(int)iso2; *isolab4=(int)iso4; *isolab8=(int)iso8;  *isolab16=(int)iso16;
                  eventproc_SetIsoValue(&fla);
	//eventproc_RiseEvent("RequestBuzzer");
           wait1=0;
           END1:
    return;
} 

void CreateMyTask()

{


  hMyTaskMessQue=(void*)CreateMessageQueue("MyTaskMessQue",0x40);

  CreateTask("MyTask", 0x19, 0, MyTask,0);

}


void SendMyMessage(int param0, int param1)

{

  int* pMessage=(int*)MainHeapAlloc(8);
  pMessage[0]=param0;
  pMessage[1]=param1;

  PostMessageQueue(hMyTaskMessQue,pMessage,0);

}


int test1, test2;
void my_IntercomHandler (int r0, char* ptr)

{   
/*
     char s[255]; int i;

     s[0]=0;

     for (i=0;  i<ptr[0];  i++)   {sprintf(s+i*2,"%02X",ptr[i]);
  }

     printf_log(8,8,"[!] sz: %02X, code: %2X, hex: %s",ptr[0],ptr[1],s);

*/
  
     if(ptr[1]>=0x90 && ptr[1]<=0x93 &&modedial<3) {SendMyMessage(MY_MESS4,0);}  //Iso at switch on

     if(ptr[1]>=0x90 && ptr[1]<=0x93 &&modedial>2) {SetDispIso1();}  //Iso when roll mode dial
     if(ptr[1]== 0xB8 && sec1+2>sec2) {sec2++; SendMyMessage(MY_MESS1,0);}  // Press Dp to set Iso
   //if(ptr[1]>=0xB1 && ptr[1]<=0xB4) {SendMyMessage(MY_MESS2,0);}

   //Change ISO value when use default camera feature.  
     test2=*(int*)(0x47E8);  //OlIso Dialog opened
     if (test2==0 && test1!=0) {test1=0;ChangeDprData(41,1);}  //SendMyMessage(MY_MESS2,0);
   //if (test2==0 && test1==0) // do nothing
   //if (test2!=0 && test1!=0)  //do nothing
     if (test2!=0 && test1==0) {test1=1; SetDispIso2();}
  
     IntercomHandler(r0, ptr);

}

//--------------------------------
//Button Value
//160 Menu
//0xA5, A1: Trash, Jump  // not work
//164 (A4) Play
//166 Set butt
//B9: Disp.
//BA: Drive Mode
//0xBB AV +- button
//0xB3->B4:   L, R;   //0xB1=UP  0xB2=Dn  
//0x90->0x93 Mode Dial Tv Av M aDep

//------------------------------------
//SetAeValue address 0x16B60
//0: P
//1:Tv
//2:Av
//3:M
//4:unknow1
//5:ADEP

//-----------------------
//SendToIntercom(0x3C,1,0);(0x3C,1,1); Cho Cfn10 
//SendToIntercom(0x3B,1,1); //(0x3B,1,0); Cho Cfn11 
//SendToIntercom(0x39,1,1); //(0x39,1,0); Cho Cfn9 


//-------------------------Unknown_1CF0
//1CF0:  AeMode
//1CF2: MesMode
//1CF6: DriveMode
//1CFA: AfMode
//1CFE: TvValue
//1D00: AvValue
//1D02: CompValue
//1D04: IsoValue
