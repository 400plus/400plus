#include "headers.h"



extern void* cache_0xFFB602F0;

extern void* addr_0x1900;




void COPY()

{

  int i;

  long* from=(long*)0x800000;

  long* to  =(long*)0x7F0000;


  for (i=0; i<4000; i++)
  {

    to[i]=from[i];

  }

}






//extern void MyTaskR();
extern void my_IntercomHandler();


extern void* hOlcInfoMessQueue;



int my_InitializeIntercom()
{

  printf("InitializeIntercom\n");

  InitIntercomData(my_IntercomHandler);

  CreateIntercomSem();

  return 0;

}

