#include "headers.h"


int setMyPrintLevel()

{
  int i;

  char* pt;

  pt = (char*) *(int*)0xD0A8;

  if (pt == 0) { return 0;}



  for(i=0; i<=31; i++)

  {
 
   *(pt + 0x1C + (i<<1)) = 7;
   *(pt + 0x1D + (i<<1)) = 7;

  }

}





void* hMyTaskMessQue;


#define MY_MESS1 0x01


#define MY_MESS2 0x02


#define MY_MESS3 0x03



/*


void MyGlobalStdSet ()

{
 int f1 = -1;

  while (f1==-1)
  {

     f1=FIO_CreateFile("A:/STDOUT.TXT");
 
    if (f1==-1) SleepTask(100);

  }


  ioGlobalStdSet(1,f1);

  ioGlobalStdSet(2,f1);

}


*/

void MyTask ()

{

//  MyGlobalStdSet(); //Thai Remarked
  int* pMessage;
  int flag, flag1;
  int mesmode=3; int facto=0; 
  int AvComp=1; //must be 1 here 

 while (1)
 {
    ReceiveMessageQueue(hMyTaskMessQue,&pMessage,0);
    SleepTask(200); //wait a moment for previos instance to finish
    ChangeDprData(41,1);
    switch (pMessage[0])
    {


     case MY_MESS3:

	if (AvComp==1)
	{
          //EnterFactoryMode(); 	// same result
	  eventproc_EnterFactoryMode(); // same result
 	  SleepTask(300); //wait for Camera refresh
	}
        //ExitFactoryMode();
	eventproc_ExitFactoryMode();
	break;


     case MY_MESS2:

 	AvComp=(AvComp!=1);
	//eventproc_RequestBuzzer();
	SleepTask(200); 
	break;
     
     case MY_MESS1:

     //Set Spot metering
	if (AvComp==1)
	{
          eventproc_SetMesMode(&mesmode); //Spot metering mode
	  SleepTask(50);
	  RiseEvent("RequestBuzzer");
	  break;
  	}
	else;
	{ 
	   //cf_extend_iso

     	   
//  100  200   400   8000  1600
	   // 0x48, 0x50, 0x58, 0x60, 0x68

           flag=*(int*)(0x16B60+0x28);


        //ISO 1600->3200
		if (flag==0x6F) flag1=0x68; //3200->1600	 
		if (flag==0x6E) flag1=0x6F; //2200->3200	 
		if (flag==0x6C) flag1=0x6E; //2000->2200	 
		if (flag==0x68) flag1=0x6C; //1600->2000	 

          //ISO 800->1250
	  	if (flag==0x66) flag1=0x60; // 1250 -> 800
	 	if (flag==0x64) flag1=0x66; // 1000 -> 1250


	

        if (flag==0x60) flag1=0x64; // 800 -> 1000


	 
          //ISO 400->640
		if (flag==0x5D) flag1=0x58; // 640 -> 400 


	 	if (flag==0x5C) flag1=0x5D; // 500 -> 640


	

        if (flag==0x58) flag1=0x5C; // 400 -> 500



          //ISO 200->320
		if (flag==0x56) flag1=0x50; // 320 -> 160


	 	if (flag==0x53) flag1=0x56; // 250 -> 320


	

        if (flag==0x50) flag1=0x53; // 200 -> 250



          //ISO 32-160
 	 	if (flag==0x4E)  flag1=0x32; // 160 -> 16


		if (flag==0x4C)  flag1=0x4E; // 125 -> 160


		if (flag==0x48)  flag1=0x4C; // 100 -> 125


		if (flag==0x46)  flag1=0x48; // 80 -> 100


	 	if (flag==0x3F)  flag1=0x46; // 50 -> 80


	

        if (flag==0x3D)  flag1=0x3F; // 40 -> 50


	

        if (flag==0x3C)  flag1=0x3D; // 32 -> 40


	

        if (flag==0x32)  flag1=0x3C; // 16 -> 32



          eventproc_SetIsoValue(&flag1); 
	  SleepTask(50); // try a little delay
	  RiseEvent("RequestBuzzer");
	  break;
	}	
     }
   
  MainHeapFree(pMessage);  
  SleepTask(200); //wait for Camera refresh
 }

}


void CreateMyTask()

{


  hMyTaskMessQue=(void*)CreateMessageQueue("MyTaskMessQue",0x40);

  CreateTask("MyTask", 0x19, 0x2000, MyTask, 0);

}





void SendMyMessage(int param0, int param1)

{

  int* pMessage=(int*)MainHeapAlloc(8);

  pMessage[0]=param0;
  pMessage[1]=param1;

  PostMessageQueue(hMyTaskMessQue,pMessage,0);

}



// ================================================


void my_IntercomHandler (int r0, char* ptr)

{
/*
  char s[255];

  int i;

  s[0]=0;

  for (i=0;  i<ptr[0];  i++)
  {

    sprintf(s+i*2,"%02X",ptr[i]);

  }

  printf_log(8,8,"[!] sz: %02X, code: %2X, hex: %s",ptr[0],ptr[1],s);

*/

 if (ptr[1]==0xB8)  {  SendMyMessage(MY_MESS1,0);}

 if(ptr[1]==0xBB)  { SendMyMessage(MY_MESS2,0); }

 if(ptr[1]==0xBA)  { SendMyMessage(MY_MESS3,0); }


  IntercomHandler(r0, ptr); 

 
}


//--------------------------------
//Button Value
//0xA5, A1: Trash, Jump  // not work
//B9: Disp.
//BA: Drive Mode
//0xBB AV +- button
//0xB7 || ptr[1]==0xB6 || ptr[1]==0xB5 //One of these 3 must be the Left Arrow