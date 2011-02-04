#include "headers.h"


extern void* cache_0xFFB602F0;

extern void* addr_0x1900;

void COPY()

{

  int i;

  long* from=(long*)0x800000;

  long* to  =(long*)0x7F0000;


  for (i=0; i<0x4000; i++)
  {

    to[i]=from[i];

  }

}



void my_romStart(int startType)

{

  unknown_cache(&cache_0xFFB602F0, &addr_0x1900, 0xC6B0>>2);

  my_usrInit(startType);

}



extern long bss_begin;

extern long bss_end;

extern long sysStartType;
extern void* readyQHead;

extern void* qPriBMapClassId;

extern void* readyQBMap;

extern void* activeQHead;

extern void* qFifoClassId;

extern void* tickQHead;

extern void* qPriListClassId;

extern my_usrRoot();



int my_usrInit(int startType)

{

  sysHwInit0();

  bzero(&bss_begin,(&bss_begin-&bss_end));

  sysStartType=startType;

  intVecBaseSet(0);

  cacheLibInit(1,2);

  excVecInit();

  sysHwInit();

  cacheEnable(0);

  cacheEnable(1);

  classLibInit();

  taskLibInit();

  qInit(&readyQHead,  qPriBMapClassId, &readyQBMap, 0x100);

  qInit(&activeQHead, qFifoClassId);
  qInit(&tickQHead,  qPriListClassId);

  workQInit();

  kernelInit(my_usrRoot, 0x4000, &bss_end, sysMemTop(), 0xC00, 0);

}



extern long* proc_sysMmuLibInit;

extern void* MemDescArray;

extern long MemDescArrayCount;

extern long fdConsole;

extern void usrClock();

extern void my_taskcreate_Startup();



int my_usrRoot(char* pMemPoolStart, unsigned int memPoolSize)

{

  eventLibInit();

  semBLibInit();

  semMLibInit();

  semCLibInit();

  semQLibInit();

  wdLibInit();

  taskHookInit();

  memInit(pMemPoolStart, memPoolSize);

  memPartLibInit(pMemPoolStart, memPoolSize);


  if (proc_sysMmuLibInit==0) goto usrRoot_failed;

  int (*_sysMmuLibInit)()=(void*)proc_sysMmuLibInit;

  if (_sysMmuLibInit(0x1000)!=0) goto usrRoot_failed;
  if (vmMpuLibInit(0x1000)!=0) goto usrRoot_failed;

  if (vmBaseGlobalMapInit(&MemDescArray,MemDescArrayCount,1)!=0) goto usrRoot_ok;


usrRoot_failed:

  
  printExc("usrRoot: MMU configuration failed, errno = %#x",*(long*)(GetErrorNumAddr()),0,0,0,0);

  reboot(1);


usrRoot_ok:


  sysClockConnect(usrClock,0);

  sysClockRateSet(60);
  sysClockEnable();

  selectInit(50);

  usrBootLineParse(0x1000);

  iosInit(20,50,"/null");

  ttyDrv();

  usrSerialInit();

  hashLibInit();

  envLibInit(1);

  sigInit();

  excInit();

  logInit(fdConsole,50);

  stdioInit();

  fioLibInit();

  selTaskDeleteHookAdd();

  sub_FFB5F728();

  my_taskcreate_Startup();

  return;

}




extern void my_task_Startup();

extern void task_Startup();



void my_taskcreate_Startup()

{

  CreateMainHeap(0x200000,0x800000-0x10000); // in end of MainHeap - own code - 64 Kb
 
  sub_FFB0FF74();

  sub_FFB2E108(0x386D4380);

  EnableDispatch();

  CreateTask("Startup", 0x19, 0x2000, my_task_Startup, 0);

}



extern void* hResourceName;

extern void AssertPrepare();

extern void my_OlcInfoInit();



void my_task_Startup()

{

  DebugManager(1,0x1F,0x180000,0x40000,0x1C0000);

  dmstart();
  dmProcInit();

  
  CreateMyTask(); // MyTask


  sub_FFAFE5BC();

  SetAssert();

  EventProcedureServiceInit();

  ShutDownProcInit();

  Install3VMemory(0xF8000000);

  RomManagerInit();

  CreateParamPubInstance();

  PropertyServiceInit();

  ErrorNumberListInit();

  FatalErrorsProcInit();

  RegisterISRs_OCH();

  BlockUntilAfterTimeoutProcInit(50);

  sub_FFB07740(0x10,8,0x1BBC);
  ResourceNameServiceInit();

  MemorySuite(0);

  sysClockRateSet_100(3);

  sub_FFB2BD6C();

  InitializeSerialIO();

  RtcInit(0x386D4380);

  AdjDefectsInit();

  CameraAdjsInit();

  SetAssertProc(AssertPrepare,0);


  my_InitializeIntercom();
 //  InitializeIntercom();


  AfeGainCmosParamInit();

  EngineInit();

  EDmacPriorityManager();

  EngineResourceInit();

  PowerMgrInit(0);

  ClockInit(1);

  RegisterISR_CAPREADY();

  FaceSensorInit();

  RemDrvInit();
  ActSweepInit();

  LcdInit();

  DisplayInit1();

  DisplayInit2();

  PowerSaveProcInit();

  sub_FFA03B0C();

  sub_FFA05114();

  InitializeImagePlayDriver();

  LensNameTblInit();

  LensPOTblInit();

  FlyingInit();

  CaptureInit();

  BathtubSaturateInit();

  Module_CaptureImagePass();

  ClearSomeCapMem();

  ColorAdjustmentsInit();

  Module_PreDarkPassInit();

  LoadSystemInfo();

  SharedBufferInit(0x10800000,0x18000000,0xEE0000,0xEE0000);

  FileCacheInit();
  PackMemInit();

  ImagePropInit();
  DigPropInit();

  ShootMainInit();
  //my_OlcInfoInit();
  OlcInfoInit();

  RegisterISR_EMERGENCY_CARDDOOR();

  MainCtrlInit();

  CaptureSemaphoreInit();

  VShadingInit();

  Module_CaptureDarkPassInit();

  Module_DarkSubtractionPassInit();
  BathtubInit();

  Module_BathtubCorrectPassInit();

  Module_VObIntegPassInit();

  SetProjectionInit();
  Module_DefectsDetectPassInit();

  DefsInit();
  WbDetectionInit();
  ObInit();

  Module_WbDetectionPassInit();
  DefsProcInit();

  Module_ObAreaCopyPassInit();
  Module_AdditionVTwoLinePassInit();

  VShadingProcInit();
  Module_VShadingCorrectPassInit();

  sub_FFA24838();
  HuffmanInit();

  RawToJpegPass_L_Init();
  RawToJpegPass_M2_Init();

  RawToJpegPass_S_Init();
  YcToJpegLargeFastInit();

  YcToJpegM2FastInit();
  YcToJpegSFastInit();

  RawToLosslessInit();
  Module_YcToTwainInit();

  RawToYcPass_S_Init();
  RawToYPackPass_S_Init();

  DvlpInit();
  DecodeJpegPassInit();
  HistPassInit();
  RectangleColorPassInit();
  RectangleCopyPassInit();

  ResizeYuvPassInit();
  sub_FFA35354();
  LpfPassInit();

  EncodeJpegPassInit();
  AdjRgbGainInit();
  LuckyInit();

/*  DebugManager(1,0x1F,0x180000,0x40000,0x1C0000);

  dmstart();

  dmProcInit();
*/
 // moved to begin

  SysInfoProcInit();

  TablesInit();

  ColorInit();

  CtrlManRecursiveLock();

  CtrlSrvInit(0x19);

  LangConInit();
  sub_FF926E40();

  CreateDispSwControlPubInstance();

  CreateMemoryManagerPubInstance();

  //GUIInit();
  my_GUIInit();
  GUIApiCalls();

  InitializeImagePlayer();

  ColorBarProcsInit();
  LcdAdjustProcsInit();

  sub_FFB29348();
  CMOSParamInit();

  CameraSettingsInit();
  BootDiskProcsInit();

  DDDInit();
  TFTInit();

  RegisterResourceName(hResourceName, "USR ROOT DEVICE HANDLE", 0x7B);

  RegisterResource_env(0xC02200B8, "U2VBUS");
  RegisterResource_env(1, "USBC20 VBUS SUPPORT");

  RegisterResource_env(0x14, "DEVICESPEED");
  USBC20_Init();
  USBC20_USBIF_Init();

  USBC20_BUFCON_Init();
  USBC20_CLK_Init();
  USBC20_HDMAC_Init();

  DCPClassFunctionsInit();
  USBDriverInit();
  RapiSwitcherInit();

  DCPClassInit();
  RAPITransportUSBInit();
  PTPRespondInit();

  PTPFrameworkInit();
  StartupPtpResponder();

  RapiTransportManagerInit();
  DCPClassInit();

  EventProcServerInit();
  sub_FFA5D8A0();
  DCPInit();

  SesnMngrInit();
  MemMngrInit();
  InitializeRapiTransportManager();

  PrintInit();
  sub_FF95EC54();
  SomePrintInit();
  sub_FF9EB94C();

  InitializeUSBDriver();
  TransMemoryInit();
  InitializeComCtrl();

  FactoryModeInit();
  DP_Init(0,0x1B,0,0);
  return_0();

  sub_FF98CF4C();
  EdLedProcsInit();
  CallBacksInit();

  RegistNotifyConnectDT();
  DPOF_Initialize();

  MpuMonInit();

  StartConsole();

}




extern void my_IntercomHandler();



int my_InitializeIntercom()

{

  printf("InitializeIntercom\n");

  InitIntercomData(my_IntercomHandler);

  CreateIntercomSem();

  return 0;

}


extern void* hOlcInfoMessQueue;
/*

extern int OlcInfoData[0xC0/4];

extern int OlcInfoChangedFlags[24];

extern int OlcInfoFlags[24];

extern char OlcInfoEmptyStr;

extern void* hOlcInfoSem;

extern void* proc_OlcTftNotifyChange;

extern int OlcNotifyFreeze;

extern int OlcNotifyChangeInProgress;

extern int OlcCounterFlag1;

extern int OlcCounterFlag2;

extern int OlcCounterFlag3;


#define OLC_CHANGE_OLC_INFO 0

#define OLC_CHANGE_OLC_INFO_DPR 1

#define OLC_FREEZE_NOTIFY 2

#define OLC_UNFREEZE_NOTIFY 3

#define OLC_SET_PROC_TFT_NOTIFY_CHANGE 4

#define OLC_MESSAGE_5 5

#define OLC_MESSAGE_6 6
#define OLC_DISP_WARNING_DLG 7



void my_task_OlcInfo()

{

  int* pMessage;

  int OlcInfoDataCopy[0xC0/4];

  int OlcNotifyUpdate;

  int flag;


  hOlcInfoSem=(void*)CreateBinarySemaphore2("OlcInfo",1);


  OlcInfoSpreadDataInit();

  memset(OlcInfoData,0,sizeof(OlcInfoData));

  memset(OlcInfoChangedFlags,0,sizeof(OlcInfoChangedFlags));

  OlcInfoData[1]=OlcInfoEmptyStr; // field_4

  OlcInfoData[4]=OlcInfoEmptyStr; // Exposure

  OlcInfoData[6]=OlcInfoEmptyStr; // Apperture

  OlcInfoData[8]=OlcInfoEmptyStr; // ISO


  while (1)
 {

    ReceiveMessageQueue(hOlcInfoMessQueue,&pMessage,0);

    OlcNotifyUpdate=0;
    TakeSemaphore(hOlcInfoSem,0);

    memcpy(OlcInfoDataCopy,OlcInfoData,sizeof(OlcInfoData));

    if (pMessage==0) break;


    switch (pMessage[0])
    {


      case OLC_CHANGE_OLC_INFO:

        ChangeOlcInfoData(OlcInfoDataCopy,OlcInfoFlags);

        if (IsOlcDataChanged(OlcInfoDataCopy)!=0) OlcNotifyUpdate=1;

        break;


      case OLC_CHANGE_OLC_INFO_DPR:

        ChangeOlcInfoDataDpr(OlcInfoDataCopy,pMessage[1]);

        ChangeOlcInfoData(OlcInfoDataCopy,OlcInfoFlags);

        if (IsOlcDataChanged(OlcInfoDataCopy)!=0) OlcNotifyUpdate=1;

        if (pMessage[1]!=0) MainHeapFree(pMessage[1]);

        break;


      case OLC_SET_PROC_TFT_NOTIFY_CHANGE:
        proc_OlcTftNotifyChange=(void*)pMessage[1];

        OlcNotifyUpdate=1;

        break;


      case OLC_FREEZE_NOTIFY:

        OlcNotifyFreeze=1;

        break;


      case OLC_UNFREEZE_NOTIFY:

        OlcNotifyFreeze=0;

        OlcNotifyUpdate=1;

        break;

*/
/*  wrong

      case OLC_MESSAGE_5:

        flag=pMessage[1];


        OlcCounterFlag2=1;

        OlcInfoDataCopy[42]=flag;


        if (OlcCounterFlag1==0)
	{

          flag=flag<<17;

          flag=flag>>17;

          if (flag>9999) flag=9999;

          OlcInfoDataCopy[39]=( pMessage[1]&8000 ? 1 : 2 );

          sprintf((char*)&OlcInfoDataCopy[40],"%d",flag);


          OlcInfoDataCopy[42]=flag;

          if (IsOlcDataChanged(OlcInfoDataCopy)!=0) OlcNotifyUpdate=1;

        }

        
OlcCounterFlag3=OlcInfoDataCopy[42];

        break;


      case OLC_MESSAGE_6:

        flag=pMessage[1];


        if (flag&0x8000)
	{


          if (OlcCounterFlag1!=0)
	  {

            if (OlcCounterFlag2!=0)
	    {

              SendOLC(OLC_MESSAGE_5,OlcCounterFlag3);

            }

            OlcCounterFlag1=flag;

            OlcInfoDataCopy[39]=flag&0x8000;

          }


        }
	else
	{


          flag=flag<<17;

          flag=flag>>17;

          if (flag>9999) flag=9999;

          OlcCounterFlag1=1;

          OlcInfoDataCopy[39]=1;

          sprintf((char*)&OlcInfoDataCopy[40],"%d",flag);

          OlcInfoDataCopy[43]=flag;

          OlcInfoDataCopy[42]=flag;


        }


        if (IsOlcDataChanged(OlcInfoDataCopy)!=0) OlcNotifyUpdate=1;

        break;

*/

/*
      case OLC_DISP_WARNING_DLG:

        flag=pMessage[1];

        ChangeOlcInfoDataDlg(OlcInfoDataCopy,flag>>31,(flag&(~0xC0000000)),flag>>30);

        if (IsOlcDataChanged(OlcInfoDataCopy)!=0) OlcNotifyUpdate=1;

        break;


    } //end switch



    if (OlcNotifyUpdate)

     if (!OlcNotifyFreeze)

      if (!OlcNotifyChangeInProgress)

      {

        OlcNotifyChangeInProgress=1;

        GiveSemaphore(hOlcInfoSem);


        if (proc_OlcTftNotifyChange!=0)
	{

          int (*_proc_OlcTftNotifyChange)()=(void*)proc_OlcTftNotifyChange;

          _proc_OlcTftNotifyChange();

        }


        OlcNotifyChange();

        continue;

      }


    GiveSemaphore(hOlcInfoSem);


  }
 

  ExitTask();

}

*/

//extern void task_OlcInfo();


/*
void my_OlcInfoInit()

{

  hOlcInfoMessQueue=(void*)CreateMessageQueue("OlcInfoMessQueue",0x40);

  CreateTask("OlcInfo", 0x17, 0, task_OlcInfo, 0);

} */
