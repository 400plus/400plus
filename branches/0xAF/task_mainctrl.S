.text
.org 0
.globl my_task_MainCtrl

my_task_MainCtrl:

var_1C          = -0x1C
var_18          = -0x18
var_14          = -0x14

                STMFD   SP!, {R4-R6,LR} // save r4-r6 and return address
                LDR     R5, =MC_T_Table // r5 = MC_T_Table
                LDR     R6, =MC_State   // r6 = MC_State
                LDR     R12, [r0]       // r12 = *message_number: from 0 to 99, then starts again from 0
                SUB     SP, SP, #0xC    // get stack = 12

                ADD     R4, R12, R12,LSL#1 // r4 = (msgnum + (msgnum << 1)) means: (msgnum + msgnum * 2) means: (msgnum * 3)
                MOV     R4, R4,LSL#2    // r4 = r4 * 4 - make it integer
                LDR     LR, [R6]        // return address(used as temp) = MC_State
                LDR     R3, [R4,R5]     // r3 = r5[r4] == MC_T_Table[msgnum*3]
                MOV     R0, #1          // r0 = 1
                LDR     R2, =aMcT04dS04xD // r2 = aMcT04dS04xD // "[MC] T:%04d, S:%04X, %d"
                MOV     R1, #6          // r1 = 6
                STR     LR, [SP,#0]     // localvar1 = MC_State
                STR     R12, [SP,#0x04] // localvar2 = msgnum
                BL      printf_log      // printf_log(1, 6, "[MC] T:%04d, S:%04X, %d", ??, MC_State, msgnum); // it seems last 2 args are comming from the stack ...
                LDR     R2, [R4,R5]     // r2 = MC_T_Table[msgnum*3]
                SUB     R3, R2, #1      // r3 = MC_T_Table[msgnum*3]-1
                CMP     R3, #4          // ? r3 == 4
                ADD     R0, R4, R5      // r0 = &MC_T_Table[msgnum*3] // address
                BHI     loc_FF81BEC8    // if (r3 > 4) goto loc_FF81BEC8;
                BL      MC_T_1_5        // call MC_T_1_5(&MC_T_Table[msgnum*3])
                B       return          // goto return
// ---------------------------------------------------------------------------

loc_FF81BEC8:
                SUB     R3, R2, #6      // r3 = MC_T_Table[msgnum*3] - 6
                CMP     R3, #1          // ? r3 == 1
                BHI     loc_FF81BEDC    // if (r3 > 1) goto loc_FF81BEDC;
                BL      MC_T_6_7        // MC_T_6_7(MC_T_Table[msgnum*3]);
                B       return          // goto return;
// ---------------------------------------------------------------------------

loc_FF81BEDC:
                SUB     R3, R2, #8      //
                CMP     R3, #12         //
                BHI     loc_FF81BEF0    //
                BL      MC_T_8_20       //
                B       return          // goto return
// ---------------------------------------------------------------------------

loc_FF81BEF0:
                SUB     R3, R2, #21     //
                CMP     R3, #4          //
                BHI     loc_FF81BF04    //
                BL      MC_T_21_25      //
                B       return          // goto return;
// ---------------------------------------------------------------------------

loc_FF81BF04:
                CMP     R2, #26 // MC_26      // ? r2 == 26
                BNE     loc_FF81BF40    // if (r2 != 26) goto loc_FF81BF40;
                BL      InitializeDriveManager // InitializeDriveManager();
                BL      InitializeDcfManager // InitializeDcfManager();
                BL      RegisterChangeNotifyCallback_DCF // RegisterChangeNotifyCallback_DCF()
                MOV     R1, #0          // r1 = 0
                LDR     R0, =DriveNotifyCallBack // r0 = DriveNotifyCallBack
                BL      RegisterDriveNotifyCallBack // RegisterDriveNotifyCallBack(DriveNotifyCallBack, 0);
                LDR     R0, =ChangeNotifyCallback_MC // r0 = ChangeNotifyCallback_MC
                MOV     R1, #0          // r1 = 0;
                BL      RegisterChangeNotifyCallback // RegisterChangeNotifyCallback(ChangeNotifyCallback_MC, 0);
                LDR     R3, =hMainCtrlMonoSem // r3 = &hMainCtrlMonoSem
                LDR     R0, [R3]        // r0 = &hMainCtrlMonoSem
                BL      GiveSemaphore   // GiveSemaphore(hMainCtrlMonoSem);
                B       return            // goto return
// ---------------------------------------------------------------------------

loc_FF81BF40:                            // CODE XREF: task_MainCtrl+ACj
                CMP     R2, #27 // MC_27      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF68    // Branch
                LDR     R3, [R6]        // Load from Memory
                ANDS    R2, R3, #0xC0   // Rd = Op1 & Op2
                BNE     return            // Branch
                LDR     R3, =unk_26AC0  // Load from Memory
                LDR     R0, =aMainCannotPowo // Load from Memory
                STR     R2, [R3]        // Store to Memory
                BL      ErrorCollectInstance // (char* err);
                B       return            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF68:                            // CODE XREF: task_MainCtrl+E8j
                CMP     R2, #28 // MC_28      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF7C    // Branch
                LDR     R0, [R0,#4]     // Load from Memory
                BL      some_with_FixFacePos_0 // Branch with Link
                B       return            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF7C:                            // CODE XREF: task_MainCtrl+110j
                CMP     R2, #29 // MC_29      // Set cond. codes on Op1 - Op2
                BNE     loc_FF81BF90    // Branch
                LDR     R0, [R0,#4]     // Load from Memory
                BL      MC_T_29         // Branch with Link
                B       return            // Branch
// ---------------------------------------------------------------------------

loc_FF81BF90:                            // CODE XREF: task_MainCtrl+124j
                CMP     R2, #30 // MC_30      // Set cond. codes on Op1 - Op2
                BNE     return            // Branch
                LDR     R4, [R0,#4]     // Load from Memory
                CMP     R4, #0          // Set cond. codes on Op1 - Op2
                BEQ     loc_FF81BFBC    // Branch
                MOV     R0, #0          // Rd = Op2
                BL      some_with_FixFacePos // Branch with Link
                BL      FaceSensorOff   // Branch with Link
                BL      StartFaceSensor // Branch with Link
                BL      sub_FF825078    // Branch with Link
                B       return            // Branch
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
                B       return            // Branch
// End of function task_MainCtrl


return:                                       // CODE XREF: MainCtrlInit+130j
        ADD     SP, SP, #0xC                // release the stack
        LDMFD   SP!, {R4-R6,PC}               // Load Block from Memory



.align 2
fin:
