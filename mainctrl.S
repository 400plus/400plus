.text
.org 0
.globl my_MainCtrlInit

my_MainCtrlInit:

	var_348         = -0x348
	var_344         = -0x344
	var_1D0         = -0x1D0
	var_3C          = -0x3C

	STMFD   SP!, {R4-R8,LR} // Store Block to Memory
	MOV     R1, #0          // Rd = Op2
	LDR     R0, =aMonoSem_0 // Load from Memory
	SUB     SP, SP, #0x330  // Rd = Op1 - Op2
	BL      CreateBinarySemaphore // (char* name, int flag)
	LDR     R4, =MC_dword_27BE0 // Load from Memory
	LDR     R12, =MC_dword_2A520 // Load from Memory
	LDR     R2, =MC_dword_259C0 // Load from Memory
	LDR     R3, =MC_State   // Load from Memory
	LDR     R1, =MC_dword_26940 // Load from Memory
	MOV     R6, #0          // Rd = Op2
	LDR     R5, =proc_CardDoor_Emergency // Load from Memory
	LDR     R8, =hMainCtrlMonoSem // Load from Memory
	MOV     R7, #1          // Rd = Op2
	STR     R6, [R12]       // MC_dword_2A520=0;
	STR     R6, [R2]        // MC_dword_259C0=0;
	STR     R7, [R3]        // MC_S=1;
	STR     R6, [R1]        // MC_dword_26940=0;
	STR     R6, [R4]        // MC_dword_27BE0=0;
	STR     R0, [R8]        // hMainCtrlMonoSem=CreateBinarySemaphore("MonoSem",0);
	BL      PictureStyleInit // Branch with Link
	BL      sub_FF825AE4    // Branch with Link
	MOV     R0, R5          // Rd = Op2
	MOV     R1, R6          // Rd = Op2
	BL      SetEmergencyProc // (proc, arg);
	MOV     R0, R5          // Rd = Op2
	MOV     R1, R6          // Rd = Op2
	BL      SetCardDoorProc // (proc, arg);
	MOV     R1, R6          // Rd = Op2
	LDR     R0, =SendToMC_T_28 // Load from Memory
	BL      TryPostMessageQueueFds_7 // (proc, int)
	LDR     R0, =ErrorDetectActSweep // Load from Memory
	BL      SetErrorDetectActSweepProc // Branch with Link
	MOV     R1, #0x64 // 'd' ; Rd = Op2
	LDR     R0, =aMainMessQueue // Load from Memory
	BL      CreateMessageQueue // (char* name, int);
	LDR     R3, =hMainMessQueue // Load from Memory
	MOV     R1, #0xC8 // '+' ; Rd = Op2
	STR     R0, [R3]        // Store to Memory
	LDR     R0, =aMainDataQueue // Load from Memory
	BL      CreateMessageQueue // (char* name, int);
	LDR     R3, =hMainDataQueue // Load from Memory
	MOV     R1, #0x15       // Rd = Op2
	MOV     R2, #0x4000     // Rd = Op2
	STR     R0, [R3]        // Store to Memory
	// AF change task here
	LDR     R3, =my_task_MainCtrl // Load from Memory
	LDR     R0, =aMainCtrl  // Load from Memory
	STR     R6, [SP,#0x348+var_348] // Store to Memory
	BL      CreateTask      // (const char *name, int prio, int stack_size /*?*/, void *entry, long parm /*?*/);
	BL      DebugProcsInit  // Branch with Link
	BL      CreateInterComQueue // Branch with Link
	BL      MC_InitStart    // Branch with Link
	BL      IntercomHandlersInit // Branch with Link
	BL      HandlersInit    // Branch with Link
	BL      ShootMainHandlerInit // Branch with Link
	BL      sub_FF822DC0    // Branch with Link
	BL      sub_FF82296C    // Branch with Link
	BL      SetDprPrinterProperty // Branch with Link
	BL      MC_RegisterEventProcedures // Branch with Link
	BL      GetMainPreserveData.field_1C_LSR30 // Branch with Link
	CMP     R0, R6          // Set cond. codes on Op1 - Op2
	MOV     R0, R6          // Rd = Op2
	BEQ     loc_FF81BD8C    // Branch
	BL      some_with_FixFacePos_0 // Branch with Link
	MOV     R2, #0x198      // Rd = Op2
	ADD     R4, SP, R2      // Rd = Op1 + Op2
	MOV     R1, R6          // Rd = Op2
	MOV     R0, R4          // Rd = Op2
	BL      memset          // (char* addr, char ch, int size);
	MOV     R0, R4          // Rd = Op2
	ADD     R1, SP, #0x348+var_344 // Rd = Op1 + Op2
	STR     R7, [SP,#0x348+var_3C] // Store to Memory
	STR     R7, [SP,#0x348+var_1D0] // Store to Memory
	BL      SendMessageDprRequestChangeData // (data_0x198, data_0x194);

loc_FF81BD8C:                            // CODE XREF: MainCtrlInit+F8j
	BL      sub_FF823F34    // Branch with Link
	CMP     R0, #0          // Set cond. codes on Op1 - Op2
	BNE     loc_FF81BDD4    // Branch
	MOV     R1, R0          // Rd = Op2
	LDR     R0, [R8]        // Load from Memory
	BL      TakeSemaphore   // (hSem, flag);
	LDR     R3, =dword_1C78 // Load from Memory
	STR     R7, [R3]        // Store to Memory
	BL      get_0x1CCC      // Branch with Link
	CMP     R0, #0          // Set cond. codes on Op1 - Op2
	BEQ     loc_FF81BDCC    // Branch
	BL      AbortDcfOperation // Branch with Link
	MOV     R0, R7          // Rd = Op2
	MOV     R1, R0          // Rd = Op2
	BL      change_playback_file_id // Branch with Link
	BL      sub_FF823A44    // Branch with Link

loc_FF81BDCC:                            // CODE XREF: MainCtrlInit+150j
	LDR     R0, [R8]        // Load from Memory
	BL      GiveSemaphore   // (hSem);

loc_FF81BDD4:                            // CODE XREF: MainCtrlInit+130j
	ADD     SP, SP, #0x330  // Rd = Op1 + Op2
	LDMFD   SP!, {R4-R8,PC} // Load Block from Memory

.align 2
fin:
