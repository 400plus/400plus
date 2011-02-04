    .text
    .org 0
    .globl _start, start

start:
_start:
                
		BL      COPY
		LDR     R0, =0xC0220000
		LDR     R1, =0x46
                STR     R1, [R0]
                LDR     R0, =0xC0100000
                LDR     R1, =0x4D3
                STR     R1, [R0]
                LDR     R0, =0xC0400000
                LDR     R1, =0x410005
                STR     R1, [R0,#8]
                MOV     R0, #0xC0000000
                LDR     R1, =0xD9C50000
                STR     R1, [R0,#0x10]
                LDR     SP, =0x1900
                MOV     R11, #0
                LDR     PC, =my_romStart
                BL      my_LedBlueOn
                B       loc_FF810054 

// ==========================================


my_LedRedOn:
                LDR     R0, =0xC02200A0
                LDR     R1, =0x46
                STR     R1, [R0]
                MOV     PC, LR

my_LedRedOff:
                LDR     R0, =0xC02200A0
                LDR     R1, =0x44
                STR     R1, [R0]
                MOV     PC, LR

my_LedBlueOn:
                LDR     R0, =0xC0220000
                LDR     R1, =0x46
                STR     R1, [R0]
                MOV     PC, LR

my_LedBlueOff:
                LDR     R0, =0xC0220000
                LDR     R1, =0x44
                STR     R1, [R0]
                MOV     PC, LR

// ==========================================

loc_FF810054:
                LDR     R0, =0xC0100000
                LDR     R1, =0x4D3
                STR     R1, [R0]
                LDR     R0, =0xC0400000
                LDR     R1, =0x410005
                STR     R1, [R0,#8]
                MOV     R0, #0xC0000000
                LDR     R1, =0xD9C50000
                STR     R1, [R0,#0x10]
                LDR     SP, =0x1900
                MOV     R11, #0
                LDR     PC, =my_romStart

my_romStart:
                LDR     R2, =0xC6B0
                STMFD   SP!, {R4,LR}
                MOV     R2, R2,LSR#2
                MOV     R4, R0
                MOV     R1, #0x1900
                LDR     R0, =0xFFB602F0
                BL      unknown_cache_
                MOV     R0, R4
                LDMFD   SP!, {R4,LR}
                B       my_usrInit


my_usrInit:
                STMFD   SP!, {R4,R5,LR}
                MOV     R4, R0
                SUB     SP, SP, #8
                LDR     R5, =0x2A550
                BL      sysHwInit0
                LDR     R0, =0xDFB0
                RSB     R1, R0, R5
                BL      bzero
                LDR     R3, =0x28F60
                MOV     R0, #0
                STR     R4, [R3]
                BL      intVecBaseSet
                MOV     R1, #2
                MOV     R0, #1
                BL      cacheLibInit
                BL      excVecInit
                BL      sysHwInit
                MOV     R0, #0
                BL      cacheEnable_
                MOV     R0, #1
                BL      cacheEnable_
                BL      classLibInit
                BL      taskLibInit
                LDR     R3, =0xD840
                LDR     R2, =0x298A0
                LDR     R1, [R3]
                LDR     R0, =0x28DE0
                MOV     R3, #0x100
                BL      qInit
                LDR     R3, =0xD880
                LDR     R0, =0xD6E8
                LDR     R1, [R3]
                BL      qInit
                LDR     R3, =0xD7C4
                LDR     R0, =0x25A20
                LDR     R1, [R3]
                BL      qInit
                BL      workQInit
                BL      sysMemTop
                MOV     R4, #0
                MOV     R3, R0
                MOV     R12, #0xC00
                MOV     R2, R5
                LDR     R0, =my_usrRoot
                MOV     R1, #0x4000
                STR     R12, [SP,#0x14-0x14]
                STR     R4, [SP,#0x14-0x10]
                BL      kernelInit
                ADD     SP, SP, #8
                LDMFD   SP!, {R4,R5,PC}
                MOV     PC, LR

my_usrRoot:
                STMFD   SP!, {R4,R5,LR}
                MOV     R4, R1
                MOV     R5, R0
                SUB     SP, SP, #8
                BL      eventLibInit
                BL      semBLibInit
                BL      semMLibInit
                BL      semCLibInit
                BL      semQLibInit
                BL      wdLibInit
                BL      taskHookInit
                MOV     R1, R4
                MOV     R0, R5
                BL      memInit
                MOV     R1, R4
                MOV     R0, R5
                BL      memPartLibInit
                LDR     R3, =0xDE5C
                LDR     R3, [R3]
                CMP     R3, #0
                MOV     R0, #0x1000
                BEQ     loc_FF810AB4
                MOV     LR, PC
                MOV     PC, R3
                CMP     R0, #0
                MOV     R0, #0x1000
                BNE     loc_FF810AB4
                BL      vmMpuLibInit
                CMP     R0, #0
                MOV     R2, #1
                LDR     R0, =0x1918
                BNE     loc_FF810AB4
                LDR     R3, =0x197C
                LDR     R1, [R3]
                BL      sub_FFB45DF4
                CMP     R0, #0
                BNE     loc_FF810ADC
loc_FF810AB4:
                BL      getErrorNumber
                MOV     R2, #0
                LDR     R1, [R0]
                MOV     R3, R2
                LDR     R0, =0xFF81089C
                STR     R2, [SP,#0x14-0x14]
                STR     R2, [SP,#0x14-0x10]
                BL      printExc
                MOV     R0, #1
                BL      reboot
loc_FF810ADC:
                MOV     R1, #0
                LDR     R0, =usrClock
                BL      sysClockConnect
                MOV     R0, #0x3C
                BL      sysClockRateSet
                BL      sysClockEnable
                MOV     R0, #0x32
                BL      selectInit
                MOV     R0, #0x1000
                BL      usrBootLineParse
                LDR     R2, =0xFF810A18
                MOV     R1, #0x32
                MOV     R0, #0x14
                BL      iosInit
                BL      ttyDrv
                BL      usrSerialInit
                BL      hashLibInit
                MOV     R0, #1
                BL      envLibInit
                BL      sigInit
                BL      sub_FFB50C90
                LDR     R3, =0x199C
                MOV     R1, #0x32
                LDR     R0, [R3]
                BL      logInit
                BL      stdioInit
                BL      fioLibInit
                BL      selTaskDeleteHookAdd
                BL      sub_FFB5F728 // cplusCtorsLink     

                // Add Hooks Create&Delete tasks

                //BL      task_hooks

                BL      my_taskcreate_Startup

                ADD     SP, SP, #8
                LDMFD   SP!, {R4,R5,PC}
                MOV     PC, LR


my_taskcreate_Startup:

                STR     LR, [SP,#-0x4]!
                MOV     R1, #0x800000
                MOV     R0, #0x200000
                SUB     SP, SP, #4
                BL      uai_FFB11D7C
                BL      uai_FFB0FF74
//                MOV     R0, #0x38400000
//                ADD     R0, R0, #0x2D4000
MOV R0,#0x4000
                ADD     R0, R0, #0x380
                BL      uai_FFB2E108
                BL      EnableDispatch
                BL      CreateMyTask
                MOV     R12, #0
                MOV     R1, #0x19
                MOV     R2, #0x2000
                LDR     R3, =my_task_Startup
                LDR     R0, =aStartup
                STR     R12, [SP,#4-0x4]
                BL      CreateTask
                ADD     SP, SP, #4
                LDR     PC, [SP],#0x4
                MOV     PC, LR

my_task_Startup:
                //BL      CreateMyTask

                STR     LR, [SP,#-4]!
                SUB     SP, SP, #4
                BL      sub_FFAFE5BC
                BL      write_multitaskAssert
                BL      RegProc_ExportAsEvent
                BL      RegProc_Shutdown
                MOV     R0, #0xF8000000
                BL      install3VMemory
                BL      romMenagerInit
                BL      sub_FFB23DC8
                BL      RegProc_PropertyService
                BL      RegProc_ErrorList
                BL      RegProc_FatalErrors
                BL      sub_FFB09D5C
                MOV     R0, #0x32
                BL      RegProc_BlockUntilAfterTimeout
                LDR     R2, =0x1BBC
                MOV     R1, #8
                MOV     R0, #0x10
                BL      sub_FFB07740
                BL      RegName_ResourceName
                MOV     R0, #0
                BL      memorySuite
                MOV     R0, #3
                BL      sysClockRateSet_100
                BL      sub_FFB2BD6C
                BL      serialIO_sub_FFB2BB14
//                MOV     R0, #0x38400000
//                ADD     R0, R0, #0x2D4000
MOV R0,#0x4000
                ADD     R0, R0, #0x380
                BL      sub_FFAF84E4
                BL      AdjustDefect
                BL      CameraAdjustments
                MOV     R1, #0
                LDR     R0, =AssertPrepare
                BL      writeproc_to_D184_D188
                BL      my_InitializeIntercom
                //BL      InitializeIntercom
                BL      AfeGain_CmosParam
                BL      EngInit
                BL      EDmacPriorityManager
                BL      sub_FFA2EA1C
                MOV     R0, #0
                BL      PowerMgrInit
                MOV     R0, #1
                BL      ClockInit
                BL      RegisterCapISR
                BL      taskcreate_FaceSensor
                BL      REMInit
                BL      taskcreate_ActSweep
                BL      LCDInit
                BL      sub_FFAFD2DC
                BL      DisplayInit
                BL      InitPowerSaveFunc
                BL      sub_FFA03B0C
                BL      sub_FFA05114
                BL      PlayInit
                BL      LensTableInit
                BL      LensPoTableInit
                BL      FlyingInit
                BL      CaptureInit_
                BL      RegProc_Bathtub_Saturate
                BL      sub_FFA40390
                BL      memset_193C8
                BL      ColorAdjustments
                BL      sub_FFA44A28
                BL      LoadSystemInfo
                MOV     R2, #0xEE0000
                MOV     R3, R2
                MOV     R1, #0x18000000
                MOV     R0, #0x10800000
                BL      SharedBufferInit
                BL      FileCacheInit
                BL      PackMemInit
                BL      ImagePropInit
                BL      taskcreate_DigProp
                BL      taskcreate_ShootMain
                BL      taskcreate_OlcInfo
                BL      SomeISRprocs

                BL      taskcreate_MainCtrl

                //BL      hook_pressbutton

                BL      sub_FFA024AC
                BL      VShadingInit
                BL      DarkPassInit
                BL      sub_FFA43068
                BL      BathTubInit
                BL      PREPRO_sub_FFA38AA8
                BL      sub_FFA453D8
                BL      SetProjectionInit
                BL      PREPRO_sub_FFA39480
                BL      DefsInit
                BL      WBDetectionInit
                BL      ObInit
                BL      PREPRO_sub_FFA44254
                BL      DefsEvents
                BL      PREPRO_sub_FFA4597C
                BL      PREPRO_sub_FFA45EDC
                BL      VShadingEvent
                BL      PREPRO_sub_FFA466D4
                BL      sub_FFA24838
                BL      HuffmanInit
                BL      PREPRO_sub_FFA3BD60
                BL      PREPRO_sub_FFA3D6D8
                BL      PREPRO_sub_FFA3EEA8
                BL      RESAMPLE_sub_FFA3C944
                BL      sub_FFA3E210
                BL      sub_FFA3F9DC
                BL      sub_FFA3A7D0
                BL      sub_FFA3B19C
                BL      sub_FFA37E3C
                BL      sub_FFA39F7C
                BL      sub_FFA3847C
                BL      sub_FFA2F1FC
                BL      sub_FFA30FD8
                BL      sub_FFA32268
                BL      sub_FFA32954
                BL      sub_FFA331BC
                BL      sub_FFA35354
                BL      sub_FFA31A24
                BL      sub_FFA369EC
                BL      RGBInit
                BL      LuckyInit
                MOV     R12, #0x1C0000
                MOV     R3, #0x40000
                MOV     R1, #0x1F
                MOV     R2, #0x180000
                MOV     R0, #1
                STR     R12, [SP,#4-4]
                BL      DebugMenager
                BL      DbgMgr_sub_FFB1EB28
                BL      RegProc_DbgMgr
                BL      IInit
                BL      LangInit_
                BL      LangInit
                BL      ctrlMan_sub_FF9136D4
                MOV     R0, #0x19
                BL      ctrlSrv_sub_FF914388
                BL      sub_FF9182CC
                BL      sub_FF926E40
                BL      sub_FF917824
                BL      sub_FF91772C
                BL      GUIInit
                BL      GUIApiCalls
                BL      PlayInit2
                BL      ColorBarInit
                BL      LCDAdjustInit
                BL      sub_FFB29348
                BL      CMOSParamInit
                BL      CameraSettingsInit
                BL      RegProc_BootDisk
                BL      DDDInit
                BL      TFTInit
                LDR     R3, =0xCFD4
                MOV     R2, #0x7B
                LDR     R0, [R3]
                LDR     R1, =aUSBROOTDEVICEHANDLE
                BL      registerResource
               MOV     R0, #0xB8
//                ADD     R0, R0, #0xC0000000
                LDR     R1, =aU2VBUS
                ADD     R0, R0, #0x220000
                BL      registerResource_env
                LDR     R1, =aUsbc20VbusSupp
                MOV     R0, #1
                BL      registerResource_env
                LDR     R1, =aDEVICESPEED
                MOV     R0, #0x14
                BL      registerResource_env
                BL      USB1
                BL      USB2
                BL      sub_FFA7BE14
                BL      sub_FFA7D778
                BL      sub_FFA8590C
                BL      sub_FFA5E0F4
                BL      sub_FFA76A30
                BL      sub_FFA6642C
                BL      DCPClassInit
                BL      RAPITransportUSBInit
                BL      PTPRespondInit
                BL      PTPFrameworkInit
                BL      sub_FF9DE698
                BL      sub_FFA70DE8
                BL      DCPClassInit
                BL      EventProcServerInit
                BL      sub_FFA5D8A0
                BL      DCPInit
                BL      sub_FF9D74F8
                BL      sub_FF9D9AD0
                BL      RAPIInit
                BL      PrintInit
                BL      sub_FF95EC54
                BL      sub_FF978AD0
                BL      sub_FF9EB94C
                BL      USB3
                BL      TransMemoryInit
                BL      InitializeComCtrl
                BL      FactoryModeRegisterPro
                MOV     R2, #0
                MOV     R1, #0x1B
                MOV     R3, R2
                MOV     R0, #1
                BL      DPInit
                BL      return_0
                BL      sub_FF98CF4C
                BL      EdLedRegisterProcedures
                BL      CallBacksInit
                BL      sub_FF82B2FC
                BL      DPOF_Initialize
                BL      MonInit
                BL      StartConsole
                ADD     SP, SP, #4
                LDR     PC, [SP],#4
                MOV     PC, LR
		


.align 2
fin:
