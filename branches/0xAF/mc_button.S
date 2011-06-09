
.text
.org 0
.globl my_MC_T_Button

my_MC_T_Button:

	STMFD   SP!, {R4,LR}    @ Store Block to Memory
	MOV     R4, R0          @ &event_struct
	SUB     SP, SP, #4      @ Rd = Op1 - Op2

	LDMIB   R4, {R3,R12}    @ r3=sw r12=a3
	LDR     R3, [R4,#4]     @ r3 = *sw
	SUB     R3, R3, #162    @ r3 -= 162
	CMP     R3, #26         @ switch 27 cases
	LDRLS   PC, [PC,R3,LSL#2] @ switch jump; if (r3 < 26) goto current_position + r2*4 (ints)
	B       default    @ default
				@ jumptable FF8267E0 cases 1,2,4-8,11,14-19,22-25
@ ---------------------------------------------------------------------------
	.long _SetPowerFlag	@ 0
	.long default		@ 1
	.long default		@ 2
	.long _SetPowerFlag	@ 3
	.long default		@ 4
	.long default		@ 5
	.long default		@ 6
	.long default		@ 7
	.long default		@ 8
	.long loc_FF826870	@ 9
	.long _SetPowerFlag	@ 10
	.long default		@ 11
	.long loc_FF826894	@ 12
	.long loc_FF826854	@ 13
	.long default		@ 14
	.long default		@ 15
	.long default		@ 16
	.long default		@ 17
	.long default		@ 18
	.long default		@ 19
	.long loc_FF826914	@ 20
	.long loc_FF826924	@ 21
	.long default		@ 22
	.long default		@ 23
	.long default		@ 24
	.long default		@ 25
	.long loc_FF82693C	@ 26
@ ---------------------------------------------------------------------------

loc_FF826854:
	LDR     R3, [R4,#8]     @ jumptable FF8267E0 case 13
	CMP     R3, #0          @ Set cond. codes on Op1 - Op2
	BNE     return    @ Branch
	LDR     R2, =err_MC_T   @ Load from Memory
	LDR     R3, [R2]        @ Load from Memory
	ORR     R3, R3, #2      @ Rd = Op1 | Op2
	B       loc_FF826888    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826870:
	LDR     R3, [R4,#8]     @ jumptable FF8267E0 case 9
	CMP     R3, #0          @ Set cond. codes on Op1 - Op2
	BNE     return    @ Branch
	LDR     R2, =err_MC_T   @ Load from Memory
	LDR     R3, [R2]        @ Load from Memory
	ORR     R3, R3, #1      @ Rd = Op1 | Op2

loc_FF826888:                           @ CODE XREF: MC_T_Button+BCj
	STR     R3, [R2]        @ Store to Memory
	BL      sub_FF821428    @ Branch with Link
	B       return    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826894:
	LDR     R4, [R4,#8]     @ jumptable FF8267E0 case 12
	CMP     R4, #0          @ Set cond. codes on Op1 - Op2
	BNE     loc_FF826900    @ Branch
	LDR     R0, =err_MC_T   @ Load from Memory
	LDR     R2, =off_24860  @ Load from Memory
	LDR     R3, [R0]        @ Load from Memory
	LDR     R1, [R2,#0xBC]  @ Load from Memory
	ORR     R3, R3, #4      @ Rd = Op1 | Op2
	CMP     R1, #1          @ Set cond. codes on Op1 - Op2
	STR     R3, [R0]        @ Store to Memory
	BEQ     loc_FF8268C4    @ Branch
	BL      change_menupos  @ Branch with Link

loc_FF8268C4:
	LDR     R3, =unk_258A0  @ Load from Memory
	LDR     R2, [R3]        @ Load from Memory
	CMP     R2, #0          @ Set cond. codes on Op1 - Op2
	BEQ     loc_FF8268E0    @ Branch
	BL      sub_FFA22D6C    @ Branch with Link
	MOV     R0, R4          @ Rd = Op2
	BL      sub_FF825E28    @ Branch with Link

loc_FF8268E0:
	BL      sub_FF811814    @ Branch with Link
	BL      change_playback_file_id2 @ Branch with Link
	LDR     R3, =MC_State   @ Load from Memory
	LDR     R2, [R3]        @ Load from Memory
	TST     R2, #0x800      @ Set cond. codes on Op1 & Op2
	BEQ     return    @ Branch
	BL      SetTurnDisplayEvent_2_after_1 @ Branch with Link
	B       return    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826900:
	LDR     R2, =err_MC_T   @ Load from Memory
	LDR     R3, [R2]        @ Load from Memory
	BIC     R3, R3, #4      @ Rd = Op1 & ~Op2
	STR     R3, [R2]        @ Store to Memory
	B       return    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826914:
	MOV     R1, #0          @ jumptable FF8267E0 case 20
	MOV     R2, R1          @ Rd = Op2
	MOV     R0, #0xB6	@ IC_BUTTON_B6      @ Rd = Op2
	B       loc_FF826930    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826924:
	MOV     R1, #0          @ jumptable FF8267E0 case 21
	MOV     R2, R1          @ Rd = Op2
	MOV     R0, #0xB7	@ IC_BUTTON_B7      @ Rd = Op2

loc_FF826930:                           @ CODE XREF: MC_T_Button+170j
	BL      SendToIntercom  @ (int code, int flag1, int flag2);
	BL      eventproc_RemOn @ Branch with Link
	B       return    @ Branch
@ ---------------------------------------------------------------------------

loc_FF82693C:
	BL      eventproc_TFTOff @ jumptable FF8267E0 case 26
	B       return    @ Branch
@ ---------------------------------------------------------------------------

_SetPowerFlag:
	LDR     R3, =PowerFlag  @ jumptable FF8267E0 cases 0,3,10
	LDR     R2, [R3]        @ Load from Memory
	MOV     R0, #0x72	@ IC_POWER_FLAG @ Rd = Op2
	ORR     R2, R2, #1      @ Rd = Op1 | Op2
	MOV     R1, #1          @ Rd = Op2
	BL      SendToIntercom  @ (int code, int flag1, int flag2);

default:
	LDMIB   R4, {R0,R1}     @ default
	BL      ManySendToGUI_and_other @ Branch with Link

return:
	ADD     SP, SP, #4      @ Rd = Op1 + Op2
	LDMFD   SP!, {R4,PC}    @ Load Block from Memory





.align 2
fin:

