MC_T_Button:                            @ CODE XREF: MC_T_1_5+40p

var_C           = -0xC

                STMFD   SP!, {R4,LR}    @ Store Block to Memory
                MOV     R4, R0          @ &event_struct
                SUB     SP, SP, #4      @ Rd = Op1 - Op2
                LDMIB   R4, {R3,R12}    @ r3=sw_0 r4=a3_0
                                        @ r5=t_1 r6=sw_1 r7=a3_1
                                        @ r8=t_2 r9=sw_2 r10=a3_2
                                        @ r11=t_3 r12=sw_3
                MOV     R0, #1          @ int
                MOV     R1, #6          @ param_R2
                LDR     R2, =asw04d04d  @ "\t sw:%04d(%04d)"
                STR     R12, [SP]       @ lvar=sw_3
                BL      printf_log      @ Branch with Link
                LDR     R3, [R4,#4]     @ r3 = sw_0
                SUB     R3, R3, #162    @ Rd = Op1 - Op2
                CMP     R3, #26         @ switch 27 cases
                LDRLS   PC, [PC,R3,LSL#2] @ switch jump; if (r3 < 26) goto current_position + r2*4 (ints)
                B       loc_FF82695C    @ default
                                        @ jumptable FF8267E0 cases 1,2,4-8,11,14-19,22-25
@ ---------------------------------------------------------------------------
                .long _SetPowerFlag.1   @ jump table for switch statement
                .long loc_FF82695C
                .long loc_FF82695C
                .long _SetPowerFlag.1
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF826870
                .long _SetPowerFlag.1
                .long loc_FF82695C
                .long loc_FF826894
                .long loc_FF826854
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF826914
                .long loc_FF826924
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82695C
                .long loc_FF82693C
@ ---------------------------------------------------------------------------

loc_FF826854:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                LDR     R3, [R4,#8]     @ jumptable FF8267E0 case 13
                CMP     R3, #0          @ Set cond. codes on Op1 - Op2
                BNE     loc_FF826964    @ Branch
                LDR     R2, =err_MC_T   @ Load from Memory
                LDR     R3, [R2]        @ Load from Memory
                ORR     R3, R3, #2      @ Rd = Op1 | Op2
                B       loc_FF826888    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826870:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                LDR     R3, [R4,#8]     @ jumptable FF8267E0 case 9
                CMP     R3, #0          @ Set cond. codes on Op1 - Op2
                BNE     loc_FF826964    @ Branch
                LDR     R2, =err_MC_T   @ Load from Memory
                LDR     R3, [R2]        @ Load from Memory
                ORR     R3, R3, #1      @ Rd = Op1 | Op2

loc_FF826888:                           @ CODE XREF: MC_T_Button+BCj
                STR     R3, [R2]        @ Store to Memory
                BL      sub_FF821428    @ Branch with Link
                B       loc_FF826964    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826894:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
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

loc_FF8268C4:                           @ CODE XREF: MC_T_Button+10Cj
                LDR     R3, =unk_258A0  @ Load from Memory
                LDR     R2, [R3]        @ Load from Memory
                CMP     R2, #0          @ Set cond. codes on Op1 - Op2
                BEQ     loc_FF8268E0    @ Branch
                BL      sub_FFA22D6C    @ Branch with Link
                MOV     R0, R4          @ Rd = Op2
                BL      sub_FF825E28    @ Branch with Link

loc_FF8268E0:                           @ CODE XREF: MC_T_Button+120j
                BL      sub_FF811814    @ Branch with Link
                BL      change_playback_file_id2 @ Branch with Link
                LDR     R3, =MC_State   @ Load from Memory
                LDR     R2, [R3]        @ Load from Memory
                TST     R2, #0x800      @ Set cond. codes on Op1 & Op2
                BEQ     loc_FF826964    @ Branch
                BL      SetTurnDisplayEvent_2_after_1 @ Branch with Link
                B       loc_FF826964    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826900:                           @ CODE XREF: MC_T_Button+ECj
                LDR     R2, =err_MC_T   @ Load from Memory
                LDR     R3, [R2]        @ Load from Memory
                BIC     R3, R3, #4      @ Rd = Op1 & ~Op2
                STR     R3, [R2]        @ Store to Memory
                B       loc_FF826964    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826914:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                MOV     R1, #0          @ jumptable FF8267E0 case 20
                MOV     R2, R1          @ Rd = Op2
                MOV     R0, #IC_B6      @ Rd = Op2
                B       loc_FF826930    @ Branch
@ ---------------------------------------------------------------------------

loc_FF826924:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                MOV     R1, #0          @ jumptable FF8267E0 case 21
                MOV     R2, R1          @ Rd = Op2
                MOV     R0, #IC_B7      @ Rd = Op2

loc_FF826930:                           @ CODE XREF: MC_T_Button+170j
                BL      SendToIntercom  @ (int code, int flag1, int flag2);
                BL      eventproc_RemOn @ Branch with Link
                B       loc_FF826964    @ Branch
@ ---------------------------------------------------------------------------

loc_FF82693C:                           @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                BL      eventproc_TFTOff @ jumptable FF8267E0 case 26
                B       loc_FF826964    @ Branch
@ ---------------------------------------------------------------------------

_SetPowerFlag.1:                        @ CODE XREF: MC_T_Button+30j
                                        @ DATA XREF: MC_T_Button+38o
                LDR     R3, =PowerFlag  @ jumptable FF8267E0 cases 0,3,10
                LDR     R2, [R3]        @ Load from Memory
                MOV     R0, #IC_POWER_FLAG @ Rd = Op2
                ORR     R2, R2, #1      @ Rd = Op1 | Op2
                MOV     R1, #1          @ Rd = Op2
                BL      SendToIntercom  @ (int code, int flag1, int flag2);

loc_FF82695C:                           @ CODE XREF: MC_T_Button+30j
                                        @ MC_T_Button+34j
                                        @ DATA XREF: ...
                LDMIB   R4, {R0,R1}     @ default
                                        @ jumptable FF8267E0 cases 1,2,4-8,11,14-19,22-25
                BL      ManySendToGUI_and_other @ Branch with Link

loc_FF826964:                           @ CODE XREF: MC_T_Button+ACj
                                        @ MC_T_Button+C8j ...
                ADD     SP, SP, #4      @ Rd = Op1 + Op2
                LDMFD   SP!, {R4,PC}    @ Load Block from Memory
@ End of function MC_T_Button


