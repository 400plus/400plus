
.text
.org 0
.globl org_task_MainCtrl

org_task_MainCtrl:

	STMFD   SP!, {R4-R6,LR}       @ save r4-r6 and return address
	LDR     R5, =MC_T_Table       @ r5 = MC_T_Table
	LDR     R6, =MC_State         @ r6 = MC_State
	LDR     R12, [r0]             @ r12 = *message_number: from 0 to 100 then starts again from 0
	SUB     SP, SP, #0xC          @ get stack = 12

	ADD     R4, R12, R12,LSL#1    @ r4 = (msgnum + (msgnum << 1)) means: (msgnum + msgnum * 2) means: (msgnum * 3)
	MOV     R4, R4,LSL#2          @ r4 = r4 * 4 - make it integer
	LDR     LR, [R6]              @ return address(used as temp) = *MC_State
	LDR     R3, [R4,R5]           @ r3 = r5[r4] == *MC_T_Table[msg*3]
	MOV     R0, #1                @ r0 = 1
	LDR     R2, =aMcT04dS04xD     @ r2 = aMcT04dS04xD // "[MC] T:%04d, S:%04X, %d"
	MOV     R1, #6                @ r1 = 6
	STR     LR, [SP,#0]           @ localvar1 = MC_State
	STR     R12, [SP,#0x04]       @ localvar2 = msgnum
	BL      printf_log            @ printf_log(1, 6, "[MC] T:%04d, S:%04X, %d", MC_T_Table[msg*3], MC_State, msgnum);
	@                               it seems last 2 args are comming from the stack ...
	LDR     R2, [R4,R5]           @ r2 = *MC_T_Table[msgnum*3] (T)
	SUB     R3, R2, #1            @ r3 = *MC_T_Table[msgnum*3]-1 (T-1)
	CMP     R3, #4                @ ? r3 == 4
	ADD     R0, R4, R5            @ r0 = &MC_T_Table[msgnum*3] // address
	BHI     MC_6_and_more          @ if (r3 > 4) goto MC_5_and_more;
	BL      MC_T_1_5              @ call MC_T_1_5(&MC_T_Table[msgnum*3])
	B       return                @ goto return
@ ---------------------------------------------------------------------------

MC_6_and_more:
	SUB     R3, R2, #6      @ r3 = *MC_T_Table[msgnum*3] - 1 - 6
	CMP     R3, #1          @ ? r3 == 1
	BHI     MC_8_and_more   @ if (r3 > 1) goto loc_FF81BEDC;
	BL      MC_T_6_7        @ MC_T_6_7(MC_T_Table[msgnum*3]);
	B       return          @ goto return;
@ ---------------------------------------------------------------------------

MC_8_and_more:
	SUB     R3, R2, #8      @
	CMP     R3, #12         @
	BHI     MC_21_and_more  @
	BL      MC_T_8_20       @ MC_T_8_20(MC_T_Table[msg*3]);
	B       return          @ goto return
@ ---------------------------------------------------------------------------

MC_21_and_more:
	SUB     R3, R2, #21     @
	CMP     R3, #4          @
	BHI     MC_26_and_more  @
	BL      MC_T_21_25      @ MC_T_8_20(MC_T_Table[msg*3]);
	B       return          @ goto return;
@ ---------------------------------------------------------------------------

MC_26_and_more:
	CMP     R2, #26         @ MC_26      // ? r2 == 26
	BNE     MC_27_and_more    @ if (r2 != 26) goto MC_27_and_more;
	@ only if 26
	BL      InitializeDriveManager @ InitializeDriveManager();
	BL      InitializeDcfManager @ InitializeDcfManager();
	BL      RegisterChangeNotifyCallback_DCF @ RegisterChangeNotifyCallback_DCF()
	MOV     R1, #0          @ r1 = 0
	LDR     R0, =DriveNotifyCallBack @ r0 = DriveNotifyCallBack
	BL      RegisterDriveNotifyCallBack @ RegisterDriveNotifyCallBack(DriveNotifyCallBack, 0);
	LDR     R0, =ChangeNotifyCallback_MC @ r0 = ChangeNotifyCallback_MC
	MOV     R1, #0          @ r1 = 0;
	BL      RegisterChangeNotifyCallback @ RegisterChangeNotifyCallback(ChangeNotifyCallback_MC, 0);
	LDR     R3, =hMainCtrlMonoSem @ r3 = hMainCtrlMonoSem
	LDR     R0, [R3]        @ r0 = hMainCtrlMonoSem
	BL      GiveSemaphore   @ GiveSemaphore(hMainCtrlMonoSem);
	B       return            @ goto return
@ ---------------------------------------------------------------------------

MC_27_and_more:
	CMP     R2, #27         @ MC_27
	BNE     MC_28_and_more  @ Branch
	@ only if 27
	LDR     R3, [R6]        @ r3 = MC_State
	ANDS    R2, R3, #0xC0   @ ? (r2 = MC_State & 0b11000000)
	BNE     return          @ if (MC_State & 0b11000000) return;
	LDR     R3, =err_MC_T   @ r3 = err_MC_T
	STR     R2, [R3]        @ err_MC_T = r2 (T)
	LDR     R0, =aMainCannotPowo @ r0 = "Main: Cannot PowOff at Emergency."
	BL      ErrorCollectInstance @ ErrorCollectInstance("Main: Cannot PowOff at Emergency");
	B       return          @ goto return
@ ---------------------------------------------------------------------------

MC_28_and_more:
	CMP     R2, #28         @ MC_28
	BNE     MC_29_and_more  @ Branch
	LDR     R0, [R0,#4]     @ &MC_T_Table[msg*3]+1 == SW/ACT
	BL      some_with_FixFacePos_0 @ some_with_FixFacePos_0(event->sw);
	B       return          @ Branch
@ ---------------------------------------------------------------------------

MC_29_and_more:
	CMP     R2, #29		@ MC_29
	BNE     MC_30           @ Branch
	LDR     R0, [R0,#4]     @ &MC_T_Table[msg*3]+1 == SW/ACT
	BL      MC_T_29         @ MC_T_29(event->sw);
	B       return		@ Branch
@ ---------------------------------------------------------------------------

MC_30:
	CMP     R2, #30         @ MC_30
	BNE     return          @ Branch
	LDR     R4, [R0,#4]     @ &MC_T_Table[msg*3]+1 == SW/ACT
	CMP     R4, #0          @ if (event->sw == 0)
	BEQ     MC_30_sw_0      @ if (event->sw == 0) goto MC_30_sw_0
	MOV     R0, #0          @ Rd = Op2
	BL      some_with_FixFacePos @ some_with_FixFacePos(0);
	BL      FaceSensorOff   @ FaceSensorOff()
	BL      StartFaceSensor @ StartFaceSensor()
	BL      sub_FF825078    @ sub_FF825078()
	B       return          @ Branch
@ ---------------------------------------------------------------------------

MC_30_sw_0:
	MOV     R0, #1          @ r0 = 1
	BL      some_with_FixFacePos_0 @ some_with_FixFacePos_0(1);
	MOV     R0, #1          @ r0 = 1
	BL      some_with_FixFacePos @ some_with_FixFacePos(1);
	MOV     R1, R4          @ r1 = event->sw == 0
	MOV     R0, #0x51       @ IC_51 == IC_DIALOGOFF
	MOV     R2, R1          @ r2 = event->sw == 0
	BL      SendToIntercom  @ SendToIntercom(IC_DIALOGOFF, 0, 0);
	B       return          @ Branch
@ End of function task_MainCtrl


return:
	ADD     SP, SP, #0xC                  @ release the stack
	LDMFD   SP!, {R4-R6,PC}               @ Load Block from Memory



.align 2
fin:
