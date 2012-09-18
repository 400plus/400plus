/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <strings.h>

#include "main.h"
#include "firmware.h"

#include "init.h"

void my_romStart(int startType);
int  my_usrInit(int startType);
int  my_usrRoot(char* pMemPoolStart, unsigned int memPoolSize);

void my_taskcreate_Startup();
void my_task_Startup();
int  my_InitializeIntercom();

void COPY() {
	// AF: check the devinfo for more details on why this routine is needed
	int i;

	long *from = (long*) 0x800000;
	long *to   = (long*) 0x7E0000;

	for (i = 0; i < 0x8000; i++) {
		to[i] = from[i];
	}
}

// entry routine, entry.S calls this, so we enter here after power up.
void my_romStart(int startType) {
	unknown_cache(&cache_0xFFB602F0, &addr_0x1900, 0xC6B0 >> 2);
	my_usrInit(startType);
}

int my_usrInit(int startType) {
	sysHwInit0();

	bzero(&bss_begin, (&bss_begin - &bss_end));

	sysStartType = startType;
	intVecBaseSet(0);
	cacheLibInit(1, 2);
	excVecInit();
	sysHwInit();
	cacheEnable(0);
	cacheEnable(1);
	classLibInit();
	taskLibInit();

	qInit(&readyQHead,  qPriBMapClassId, &readyQBMap, 0x100);
	qInit(&activeQHead, qFifoClassId);
	qInit(&tickQHead,   qPriListClassId);

	workQInit();

	/* sysMemTop() - returns the LogBuffer address, the buffer is 1.5mb */
	kernelInit(my_usrRoot, 0x4000, &bss_end, sysMemTop(), 0xC00, 0);

	return 0;
}

int my_usrRoot(char* pMemPoolStart, unsigned int memPoolSize) {
	eventLibInit();
	semBLibInit();
	semMLibInit();
	semCLibInit();
	semQLibInit();
	wdLibInit();
	taskHookInit();

	memInit(pMemPoolStart, memPoolSize);
	memPartLibInit(pMemPoolStart, memPoolSize);

	if (proc_sysMmuLibInit == 0)
		goto usrRoot_failed;

	int (*_sysMmuLibInit)() = (void*) proc_sysMmuLibInit;

	if (_sysMmuLibInit(0x1000) != 0)
		goto usrRoot_failed;

	if (vmMpuLibInit(0x1000) != 0)
		goto usrRoot_failed;

	if (vmBaseGlobalMapInit(&MemDescArray, MemDescArrayCount, 1) == 0)
		goto usrRoot_failed;

	sysClockConnect(usrClock, 0);

	sysClockRateSet(60);
	sysClockEnable();

	selectInit(50);

	usrBootLineParse(0x1000);

	iosInit(20, 50, "/null");

	ttyDrv();

	usrSerialInit();
	hashLibInit();
	envLibInit(1);
	sigInit();
	excInit();
	logInit(fdConsole, 50);
	stdioInit();
	fioLibInit();

	selTaskDeleteHookAdd();

	sub_FFB5F728();

	my_taskcreate_Startup();

	return 0;

usrRoot_failed:

	printExc("usrRoot: MMU configuration failed, errno = %#x", *(long*) (GetErrorNumAddr()), 0, 0, 0, 0);

	reboot(1);


	return 0;
}

void my_taskcreate_Startup() {
	CreateMainHeap(0x200000, 0x800000 - 0x20000); // in end of MainHeap - own code - 128 Kb

	sub_FFB0FF74();
	sub_FFB2E108(0x386D4380);

	EnableDispatch();
	CreateTask("Startup", 0x19, 0x2000, my_task_Startup, 0);
}

void my_task_Startup() {
	DebugManager(1, 0x1F, 0x180000, 0x40000, 0x1C0000);

	dmstart();
	dmProcInit();

#ifdef ENABLE_MASSIVE_DEBUG
	// the 2nd level is 32 flags for debug classes
	// the 3rd arg is log level, 0 == full debug, >0 == less debug
	dmSetStoreLevel(hDbgMgr, 0xFF, 0);
	dmSetPrintLevel(hDbgMgr, 0xFF, 0);
#endif

	int disable_hack = (*(int*)BTN_ADDR_TRASH == BTN_PRESSED);
	if (!disable_hack) initialize(); // task_dispatcher

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

	sub_FFB07740(0x10, 8, 0x1BBC);
	ResourceNameServiceInit();

	MemorySuite(0);

	sysClockRateSet_100(3);

	sub_FFB2BD6C();

	InitializeSerialIO();

	RtcInit(0x386D4380);

	AdjDefectsInit();

	CameraAdjsInit();

	SetAssertProc(AssertPrepare, 0);

	if (disable_hack) {
		InitializeIntercom();
	} else {
		my_InitializeIntercom(); // InitializeIntercom();
	}

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

	SharedBufferInit(0x10800000, 0x18000000, 0xEE0000, 0xEE0000);

	FileCacheInit();
	PackMemInit();

	ImagePropInit();
	DigPropInit();

	ShootMainInit();

	OlcInfoInit();

	RegisterISR_EMERGENCY_CARDDOOR();

	if (disable_hack) {
		MainCtrlInit();
	} else {
		my_MainCtrlInit();
	}

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

	SysInfoProcInit();

	TablesInit();

	ColorInit();

	CtrlManRecursiveLock();

	CtrlSrvInit(0x19);

	LangConInit();
	sub_FF926E40();

	CreateDispSwControlPubInstance();

	CreateMemoryManagerPubInstance();

	if (disable_hack) {
		GUIInit();
	} else {
		my_GUIInit(); //GUIInit();
	}
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
	DP_Init(0, 0x1B, 0, 0);
	return_0();

	sub_FF98CF4C();
	EdLedProcsInit();
	CallBacksInit();

	RegistNotifyConnectDT();
	DPOF_Initialize();

	MpuMonInit();

	StartConsole();
}

int my_InitializeIntercom() {
	//printf("InitializeIntercom\n");
	InitIntercomData(intercom_proxy);
	CreateIntercomSem();

	return 0;
}
