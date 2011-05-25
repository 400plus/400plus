.text
.org 0
.globl my_task_MainCtrl

my_task_MainCtrl:

var_1C          = -0x1C
var_18          = -0x18
var_14          = -0x14

                STMFD   SP!, {R4-R6,LR} // Store Block to Memory
                LDR     R5, =MC_T_Table // Load from Memory
                LDR     R6, =MC_State   // Load from Memory
                SUB     SP, SP, #0xC    // Rd = Op1 - Op2

loop:                                    // CODE XREF: task_MainCtrl+68j
                                        // task_MainCtrl+7CMj ...
                LDR     R3, =hMainMessQueue // Load from Memory
                ADD     R1, SP, #0x1C+var_14 // Rd = Op1 + Op2
                LDR     R0, [R3]        // Load from Memory
                MOV     R2, #0          // Rd = Op2
                BL      ReceiveMessageQueue // (void* hMessageQueue, void* pMessage, int FOREVER);
                LDR     R12, [SP,#0x1C+var_14] // Load from Memory
                ADD     R4, R12, R12,LSL#1 // Rd = Op1 + Op2
                MOV     R4, R4,LSL#2    // Rd = Op2
                LDR     LR, [R6]        // Load from Memory
                LDR     R3, [R4,R5]     // Load from Memory
                MOV     R0, #1          // Rd = Op2
                LDR     R2, =aMcT04dS04xD // Load from Memory
                MOV     R1, #6          // Rd = Op2
                STR     LR, [SP,#0x1C+var_1C] // Store to Memory
                STR     R12, [SP,#0x1C+var_18] // Store to Memory
                BL      printf_log      // Branch with Link
                LDR     R2, [R4,R5]     // Load from Memory
                SUB     R3, R2, #1      // Rd = Op1 - Op2
                CMP     R3, #4          // Set cond. codes on Op1 - Op2
                ADD     R0, R4, R5      // Rd = Op1 + Op2
                BHI     loc_FF81BEC8    // Branch
                BL      MC_T_1_5        // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BEC8:                            // CODE XREF: task_MainCtrl+60j
                SUB     R3, R2, #6      // Rd = Op1 - Op2
                CMP     R3, #1          // Set cond. codes on Op1 - Op2
                BHI     loc_FF81BEDC    // Branch
                BL      MC_T_6_7        // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BEDC:                            // CODE XREF: task_MainCtrl+74j
                SUB     R3, R2, #8      // Rd = Op1 - Op2
                CMP     R3, #12         // Set cond. codes on Op1 - Op2
                BHI     loc_FF81BEF0    // Branch
                BL      MC_T_8_20       // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BEF0:                            // CODE XREF: task_MainCtrl+88j
                SUB     R3, R2, #21     // Rd = Op1 - Op2
                CMP     R3, #4          // Set cond. codes on Op1 - Op2
                BHI     loc_FF81BF04    // Branch
                BL      MC_T_21_25      // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF04:                            // CODE XREF: task_MainCtrl+9Cj
                CMP     R2, #26 // MC_26      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF40    // Branch
                BL      InitializeDriveManager // Branch with Link
                BL      InitializeDcfManager // Branch with Link
                BL      RegisterChangeNotifyCallback_DCF // Branch with Link
                MOV     R1, #0          // Rd = Op2
                LDR     R0, =DriveNotifyCallBack // Load from Memory
                BL      RegisterDriveNotifyCallBack // Branch with Link
                LDR     R0, =ChangeNotifyCallback_MC // Load from Memory
                MOV     R1, #0          // Rd = Op2
                BL      RegisterChangeNotifyCallback // Branch with Link
                LDR     R3, =hMainCtrlMonoSem // Load from Memory
                LDR     R0, [R3]        // Load from Memory
                BL      GiveSemaphore   // (hSem);
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF40:                            // CODE XREF: task_MainCtrl+ACj
                CMP     R2, #27 // MC_27      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF68    // Branch
                LDR     R3, [R6]        // Load from Memory
                ANDS    R2, R3, #0xC0   // Rd = Op1 & Op2
                BNE     loop            // Branch
                LDR     R3, =unk_26AC0  // Load from Memory
                LDR     R0, =aMainCannotPowo // Load from Memory
                STR     R2, [R3]        // Store to Memory
                BL      ErrorCollectInstance // (char* err);
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF68:                            // CODE XREF: task_MainCtrl+E8j
                CMP     R2, #28 // MC_28      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF7C    // Branch
                LDR     R0, [R0,#4]     // Load from Memory
                BL      some_with_FixFacePos_0 // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF7C:                            // CODE XREF: task_MainCtrl+110j
                CMP     R2, #29 // MC_29      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF90    // Branch
                LDR     R0, [R0,#4]     // Load from Memory
                BL      MC_T_29         // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF90:                            // CODE XREF: task_MainCtrl+124j
                CMP     R2, #30 // MC_30      // Set cond. codes on Op1 - Op2
                BNE     loop            // Branch
                LDR     R4, [R0,#4]     // Load from Memory
                CMP     R4, #0          // Set cond. codes on Op1 - Op2
                BEQ     loc_FF81BFBC    // Branch
                MOV     R0, #0          // Rd = Op2
                BL      some_with_FixFacePos // Branch with Link
                BL      FaceSensorOff   // Branch with Link
                BL      StartFaceSensor // Branch with Link
                BL      sub_FF825078    // Branch with Link
                B       loop            // Branch
// ---------------------------------------------------------------------------

loc_FF81BFBC:                            // CODE XREF: task_MainCtrl+144j
                MOV     R0, #1          // Rd = Op2
                BL      some_with_FixFacePos_0 // Branch with Link
                MOV     R0, #1          // Rd = Op2
                BL      some_with_FixFacePos // Branch with Link
                MOV     R1, R4          // Rd = Op2
                MOV     R0, #0x51 // IC_51  // IC_DIALOGOFF     // Rd = Op2
                MOV     R2, R1          // Rd = Op2
                BL      SendToIntercom  // (int code, int flag1, int flag2);
                B       loop            // Branch
// End of function task_MainCtrl





.align 2
fin:
