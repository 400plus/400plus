#include "main.h"

#define LEDRED (*((int*)0xC02200A0))
#define LEDBLUE (*((int*)0xC0220000))
#define LEDON   0x46
#define LEDOFF  0x44



void MyTask ()
{
int k;
  
  //Iso 100=70
  //Iso 125=75
  //Iso 160=77
  //Iso 200=80
  //Iso 320=85
  //Iso 400=90
  //Iso 800=100
  //Iso 1600=110

  while (1) {   
  		   k=70;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k); 
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF;
		   SleepTask(4000);

  		   k=75;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k); 
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF;
		   SleepTask(4000);

  		   k=77;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k);
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF; 
		   SleepTask(4000);

  		   k=80;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k);
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF; 
		   SleepTask(4000);

  		   k=85;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k); 
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF;
		   SleepTask(4000);

  		   k=90;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k);
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF; 
		   SleepTask(4000);

  		   k=100;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k); 
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF;
		   SleepTask(4000);

  		   k=110;
		   eventproc_SetIsoValue(&k);
		   eventproc_PrintDefIso(&k);
		   LEDBLUE=LEDON;
		   SleepTask(500);
		   LEDBLUE=LEDOFF; 
		   SleepTask(4000);
  }//While 1
}

void CreateMyTask()
{
  CreateTask("MyTask", 0x19, 0x2000, MyTask, 0);
}

