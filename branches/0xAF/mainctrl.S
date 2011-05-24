.text
.org 0
.globl my_MainCtrlInit

my_MainCtrlInit:

	STMFD   SP!, {R4-R8,LR}               // save r4-r8 and the return address
	MOV     R1, #0                        // r1 = 0
	LDR     R0, =aMonoSem_0               // r0 = "Mono Sem"
	SUB     SP, SP, #0x330                // get stack space
	BL      CreateBinarySemaphore         // call CreateBinarySemaphore("MonoSem", 0);
	LDR     R4, =MC_dword_27BE0           // r4 = MC_dword_27BE0
	LDR     R12, =MC_dword_2A520          // r12 = MC_dword_2A520
	LDR     R2, =MC_dword_259C0           // r2 = MC_dword_259C0
	LDR     R3, =MC_State                 // r3 = MC_State
	LDR     R1, =MC_dword_26940           // r1 = MC_dword_26940
	MOV     R6, #0                        // r6 = 0
	LDR     R5, =proc_CardDoor_Emergency  // r5 = proc_CardDoor_Emergency
	LDR     R8, =hMainCtrlMonoSem         // r8 = hMainCtrlMonoSem
	MOV     R7, #1                        // r7 = 1
	STR     R6, [R12]                     // MC_dword_2A520=0;
	STR     R6, [R2]                      // MC_dword_259C0=0;
	STR     R7, [R3]                      // MC_State=1;
	STR     R6, [R1]                      // MC_dword_26940=0;
	STR     R6, [R4]                      // MC_dword_27BE0=0;
	STR     R0, [R8]                      // hMainCtrlMonoSem=CreateBinarySemaphore("MonoSem",0);
	BL      PictureStyleInit              // call PictureStyleInit
	BL      sub_FF825AE4                  // call sub_FF825AE4
	MOV     R0, R5                        // r0 = proc_CardDoor_Emergency
	MOV     R1, R6                        // r1 = 0
	BL      SetEmergencyProc              // call SetEmergencyProc(proc_CardDoor_Emergency, 0);
	MOV     R0, R5                        // r0 = proc_CardDoor_Emergency
	MOV     R1, R6                        // r1 = 0
	BL      SetCardDoorProc               // call SetCardDoorProc(proc_CardDoor_Emergency, 0);
	MOV     R1, R6                        // r1 = 0
	LDR     R0, =SendToMC_T_28            // r0 = SendToMC_T_28
	BL      TryPostMessageQueueFds_7      // call TryPostMessageQueueFds_7(SendToMC_T_28, 0);
	LDR     R0, =ErrorDetectActSweep      // r0 = ErrorDetectActSweep
	BL      SetErrorDetectActSweepProc    // call SetErrorDetectActSweepProc(ErrorDetectActSweep);
	MOV     R1, #0x64                     // r1 = 0x64
	LDR     R0, =aMainMessQueue           // r0 = "MainMessQueue"
	BL      CreateMessageQueue            // call CreateMessageQueue("MainMessQueue", 0x64); store in hMainMessQueue
	LDR     R3, =hMainMessQueue           // r3 = hMainMessQueue
	MOV     R1, #0xC8                     // r1 = 0xC8
	STR     R0, [R3]                      // hMainMessQueue = CreateMessageQueue("MainMessQueue", 0x64); store in hMainDataQueue
	LDR     R0, =aMainDataQueue           // r0 = "MainDataQueue"
	BL      CreateMessageQueue            // call CreateMessageQueue("MainDataQueue", 0xC8);
	LDR     R3, =hMainDataQueue           // r3 = hMainDataQueue
	MOV     R1, #0x15                     // r1 = 0x15
	MOV     R2, #0x4000                   // r2 = 0x4000
	STR     R0, [R3]                      // hMainDataQueue = CreateMessageQueue("MainDataQueue", 0xC8);
	// AF: we need to change the task here
	LDR     R3, =my_task_MainCtrl         // r3 = task_MainCtrl
	LDR     R0, =aMainCtrl                // r0 = "MainCtrl"
	STR     R6, [SP,#0]                   // zero the stack[0] ?? zero_var
	BL      CreateTask                    // call CreateTask(/*name*/"MainCtrl", /*prio*/0x15, /*stack_size*/0x4000, /*routine*/task_MainCtrl)
	BL      DebugProcsInit                // call DebugProcsInit()
	BL      CreateInterComQueue           // call CreateInterComQueue()
	BL      MC_InitStart                  // call MC_InitStart()
	BL      IntercomHandlersInit          // call IntercomHandlersInit()
	BL      HandlersInit                  // call HandlersInit()
	BL      ShootMainHandlerInit          // call ShootMainHandlerInit()
	BL      sub_FF822DC0                  // call sub_FF822DC0()
	BL      sub_FF82296C                  // call sub_FF82296C()
	BL      SetDprPrinterProperty         // call SetDprPrinterProperty()
	BL      MC_RegisterEventProcedures    // call MC_RegisterEventProcedures()
	BL      GetMainPreserveData.field_1C_LSR30 // (unsigned)r0 = GetMainPreserveData.field_1C() div 0x20000000
	CMP     R0, R6                        // ? (r0 == 0) ... 
	MOV     R0, R6                        // r0 = 0
	BEQ     loc_FF81BD8C                  // ... if (r0 == 0) goto loc_FF81BD8C;
	BL      some_with_FixFacePos_0        // call some_with_FixFacePos_0
	MOV     R2, #0x198                    // r2 = 0x198
	ADD     R4, SP, R2                    // r4 = localvar[0x198]
	MOV     R1, R6                        // r1 = 0
	MOV     R0, R4                        // r0 = localvar
	BL      memset                        // memset (localvar, 0, 0x198);
	MOV     R0, R4                        // r0 = localvar[0x198]
	ADD     R1, SP, #4                    // r1 = localvar2[0x194]
	STR     R7, [SP,#0x30C]               // localvar.0x174 = 1 ???
	STR     R7, [SP,#0x178]               // localvar2.0x174 = 1 ???
	BL      SendMessageDprRequestChangeData // call SendMessageDprRequestChangeData(localvar, localvar2);
	
	// stack size 0x330
	//
	//    4      0x194             0x198
	// SP|-|---------------|-------------------|
	// 0=^ ^  [localvar2]  ^     [localvar]
	//     |               |
	//     |               |
	//     +- localvar2    +- localvar

loc_FF81BD8C:                                 // CODE XREF: MainCtrlInit+F8j
	BL      sub_FF823F34                  // r0 = sub_FF823F34()
	CMP     R0, #0                        // ? (r0 == 0) ...
	BNE     return                        // ... if (r0 != 0) goto return
	MOV     R1, R0                        // r1 = 0
	LDR     R0, [R8]                      // r0 = hMainCtrlMonoSem
	BL      TakeSemaphore                 // call TakeSemaphore(hMainCtrlMonoSem, 0);
	LDR     R3, =dword_1C78               // r3 = dword_1C78
	STR     R7, [R3]                      // *dword_1C78 = 1
	BL      get_0x1CCC                    // r0 = get_0x1CCC()
	CMP     R0, #0                        // ? (r0 == 0)
	BEQ     givesem                       // if (r0 == 0) goto givesem
	BL      AbortDcfOperation             // call AbortDcfOperation()
	MOV     R0, R7                        // r0 = 1
	MOV     R1, R0                        // r1 = 1
	BL      change_playback_file_id       // call change_playback_file_id(1, 1)
	BL      sub_FF823A44                  // call sub_FF823A44()

givesem:                                      // CODE XREF: MainCtrlInit+150j
	LDR     R0, [R8]                      // r0 = hMainCtrlMonoSem
	BL      GiveSemaphore                 // call GiveSemaphore(hMainCtrlMonoSem);

return:                                       // CODE XREF: MainCtrlInit+130j
	ADD     SP, SP, #0x330                // release the stack
	LDMFD   SP!, {R4-R8,PC}               // Load Block from Memory

.align 2
fin:
