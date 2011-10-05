	.text
	.org 0
	.globl my_GUIInit //, UpdateInfoScreen //, my_StartInfoCreativeApp

	my_GUIInit:
		var_34          = -0x34
		var_30          = -0x30
		var_2C          = -0x2C
		var_28          = -0x28

		STMFD   SP!, {R4-R11,LR}
		LDR     R12, =m_pSendDisplayModeToMC
		LDR     R2, =GUIIdleFlag
		LDR     R3, =GUIMode
		LDR     R4, =m_pSendStartModeToMC
		MOV     R9, #0
		SUB     SP, SP, #0x10
		MOV     R1, #1
		LDR     R0, =aGuiSwSem
		STR     R9, [R12]
		STR     R9, [R2]
		STR     R9, [R3]
		STR     R9, [R4]
		BL      CreateBinarySemaphore
		LDR     R3, =hGuiSwSem
		STR     R0, [R3]
		BL      TablesInit
		MOV     R0, #1
		BL      placeListFromTab
		BL      WidgetBinaryBitmapInit
		MOV     R0, #3
		BL      placeListFromTab
		BL      WidgetCounterInit
		MOV     R0, #4
		BL      placeListFromTab
		BL      WidgetFocusMarkInit
		MOV     R0, #5
		BL      placeListFromTab
		BL      WidgetHistogramInit
		MOV     R0, #8
		BL      placeListFromTab
		BL      WidgetListSelectInit
		MOV     R0, #0xA
		BL      placeListFromTab
		BL      WidgetNavigateIconInit
		MOV     R0, #0xB
		BL      placeListFromTab
		BL      WidgetPopupAEBInit
		MOV     R0, #0xD
		BL      placeListFromTab
		BL      WidgetPopupMenuInit
		MOV     R0, #0xE
		BL      placeListFromTab
		BL      WidgetProgressBarInit
		MOV     R0, #2
		BL      placeListFromTab
		BL      WidgetButtonInit
		MOV     R0, #0xF
		BL      placeListFromTab
		BL      WidgetRectangle
		MOV     R0, #0x10
		BL      placeListFromTab
		BL      WidgetScrollBarInit
		MOV     R0, #0x11
		BL      placeListFromTab
		BL      WidgetSliderInit
		MOV     R0, #0x13
		BL      placeListFromTab
		BL      WidgetTextInit
		MOV     R0, #0x14
		BL      placeListFromTab
		BL      WidgetListViewInit
		MOV     R0, #0x16
		BL      placeListFromTab
		BL      WidgetPopupSliderInit
		MOV     R0, #9
		BL      placeListFromTab
		BL      WidgetMenuTabInit
		MOV     R0, #0x1C
		BL      placeListFromTab
		BL      WidgetPaletteBitmapInit
		MOV     R0, #0x17
		BL      placeListFromTab
		BL      WidgetAnimationBmpInit
		MOV     R0, #0x1B
		BL      placeListFromTab
		BL      WidgetArchRectInit
		MOV     R0, #1
		BL      str_0x5188
		MOV     R0, R9
		BL      sub_FF918D24
		MOV     R0, #3
		BL      sub_FF918C58
		MOV     R4, R0
		MOV     R0, #3
		BL      GetBrushFromSystemColor
		MOV     R11, R0
		MOV     R0, R4
		BL      sub_FF92AD74
		BL      sub_FF934DE8
		MOV     R1, #0x14
		MOV     R0, #1
		BL      FontInit
		LDR     R8, =sub_FF92ADD8
		LDR     R10, =sub_FF92AF8C
		LDR     R6, =sub_FF92AFD8
		LDR     R7, =sub_FF92AF58
		MOV     R4, #1
		MOV     R2, R10
		MOV     R3, R6
		MOV     R1, R8
		STR     R7, [SP]
		STR     R4, [SP,#4]
		BL      CreateFontManagerInstance
		LDR     R5, =off_1EE0
		MOV     R1, #0x1E
		STR     R0, [R5]
		MOV     R0, R4
		BL      FontInit
		MOV     R2, R10
		MOV     R3, R6
		MOV     R1, R8
		STR     R7, [SP,#0x34+var_34]
		STR     R4, [SP,#0x34+var_30]
		BL      CreateFontManagerInstance
		MOV     R1, #0x24
		MOV     R0, R4
		BL      FontInit
		MOV     R3, R6
		MOV     R1, R8
		STR     R0, [R5]
		MOV     R2, R10
		STR     R7, [SP,#0x34+var_34]
		STR     R4, [SP,#0x34+var_30]
		BL      CreateFontManagerInstance
		STR     R0, [R5]
		BL      get_0x5178
		ADD     R1, SP,#0x34+var_28
		ADD     R2, SP,#0x34+var_2C
		BL      sub_FF92D8EC
		LDR     R12, =GUIWindowInstanceProc
		LDR     R3, [SP,#0x34+var_2C]
		LDR     R2, [SP,#0x34+var_28]
		MOV     R1, R9
		MOV     R0, R9
		STR     R12, [SP,#0x34+var_34]
		STR     R11, [SP,#0x34+var_30]
		BL      CreateWindowInstance
		LDR     R3, =hGUIWindowInstance
		STR     R0, [R3]
		BL      some_do_with_window_instance
		BL      taskcreate_GuiMainTask
		BL      CreateGUIPubInstance
		BL      taskcreate_tGraphics
		BL      CreateQRevImgQueue
		BL      Some_DP_GUI
		BL      SetGUIFactoryMenuProcInit
		BL      GUIuramodeInit
		MOV     R1, R9
		LDR     R0, =my_GUI_IDLEHandler
		BL      CreateCtrlMain
		BL      sub_FF833D50
		BL      sub_FF82B5AC
		ADD     SP, SP, #0x10
		LDMFD   SP!, {R4-R11,PC}


my_GUI_IDLEHandler:
var_324 	= -0x324
var_19C 	= -0x19C
var_190 	= -0x190

		STMFD SP!, {R4,LR}
		LDR R2, =0x10000038
		SUB SP, SP, #0x31C
		CMP R1, R2
		MOV R4, R3
		BEQ START_DIRECTTRANSFER_MODE
		BHI my_loc_FF8292AC
		LDR R3, =0x10000012
		CMP R1, R3
		BEQ START_INCOMPIMAGE_MODE
		BHI loc_FF8291BC
		CMP R1, #0x10000009
		BEQ START_PLAY_MODE
		BHI loc_FF829170
		LDR R3, =0x829
		CMP R1, R3
		BEQ PRESS_INFO_BUTTON
		BHI loc_FF829158
		LDR R3, =0x802
		CMP R1, R3
		BEQ INITIALIZE_CONTROLLER
		BHI loc_FF829144
		CMP R1, #0x800
		BEQ GOT_TOP_OF_CONTROL
		B _default

my_loc_FF8292AC:
		LDR R3, =0x10000058
		CMP R1, R3
		BEQ START_ISO_MODE
		BHI loc_FF8293BC
		LDR R3, =0x10000046
		CMP R1, R3
		BEQ DISP_MES_MODE
		BHI loc_FF82933C
		LDR R3, =0x1000003D
		CMP R1, R3
		BEQ START_BULBCOUNT_MODE
		BHI loc_FF829310
		LDR R3, =0x1000003B
		CMP R1, R3
		BEQ DISP_BULBCOUNT_MODE
		BHI my_START_OLC_MODE
		LDR R3, =0x10000039
		CMP R1, R3
		BEQ DISP_OLC_MODE
		B _default

my_START_OLC_MODE:
		BL initialize_display
		B START_OLC_MODE

loc_FF829158:
		CMP R1, #0x10000007
		BEQ START_MENU_MODE
		BHI START_INFO_MODE
		CMP R1, #0x10000000
		BEQ PRESS_DISP_BUTTON
		B _default

START_INFO_MODE:
		LDR R4, =GUIMode
		MOV R1, #5
		LDR R2, =aGUIGUI_IDLEHandlerSTART_INFO_MODEd
		LDR R3, [R4]
		MOV R0, #0x18
		BL printf_log
		BL GUI_Lock
		BL GUI_PalleteInit
		MOV R0, #4
		BL GUI_StartMode
		BL GUI_ClearImage
		LDR R0, [R4]
		BL StartInfoMode
		BL GUI_UnLock
		BL GUI_PalleteUnInit
		BL GUI_ClearImage
		B _SetTurnDisplayEvent_1_after_2

StartInfoMode:

var_19C 	= -0x19C
var_18C 	= -0x18C

		STMFD SP!, {R4,LR}
		SUB SP, SP, #0x318
		ADD R4, SP, #0x320+var_19C
		MOV R0, R4
		BL GetDigiPropData
		MOV R2, #0x184
		MOV R0, SP
		ADD R1, SP, #0x320+var_18C
		BL memcpy
		LDMIA R4, {R0-R3}
		BL GetAeMode
		LDR R2, =GUI_ae_info
		MOV R3, R0,LSL#16
		CMP R3, #0x10000
		STRH R0, [R2]
		BNE _not_creative
		BL my_StartInfoCreativeApp
		B _skip

my_StartInfoCreativeApp:

var_10 	= -0x10

		STMFD SP!, {R4,R5,LR}
		LDR R4, =hInfoCreative
		LDR R3, [R4]
		SUB SP, SP, #4
		CMP R3, #0
		BEQ _zero
		BL StopInfoCreativeApp

_zero:
		MOV R12, #0
		MOV R0, R12
		MOV R1, R0
		LDR R2, =InfoCreativeAppProc
		MOV R3, #0x20
		STR R12, [SP,#0x10+var_10]
		BL CreateDialogBox
		MOV R3, R0
		ANDS R5, R3, #1
		MOV R0, #9
		LDR R1, =a__GuiInfoappIn
		MOV R2, #0x48
		STR R3, [R4]
		BEQ _not_error
		LDR R0, =a0_40
		BL DebugAssert
		LDR R0, [R4]
		B return

_not_error:
		BL PaletteChange
		LDR R1, =sub_FF840834
		LDR R2, [R4]
		LDR R0, =sub_FF8406E4
		BL dig_prop_some
		LDR R0, [R4]
		BL do_some_with_dialog
		MOV R0, R5

return:
		ADD SP, SP, #4
		LDMFD SP!, {R4,R5,PC}

sub_FF8406E4:

var_10 	= -0x10
arg_188 	=  0x188
arg_194 	=  0x194
arg_198 	=  0x198

		SUB SP, SP, #0x10
		STMFD SP!, {R4-R7,LR}
		SUB SP, SP, #0x188
		ADD R12, SP, #0x1AC+var_10
		STMIA R12, {R0-R3}
		LDR R7, =0x2140
		B loc_FF840754

loc_FF840700:
		LDRH R3, [R7,#2]
		CMP R3, #0
		LDR R6, =hInfoCreative
		MOV R0, SP
		ADD R1, SP, #0x1AC+arg_194
		MOV R2, #0x188
		BEQ loc_FF840750
		MOV R4, R3
		LDR R6, [R6]
		LDRH R5, [R7]
		BL memcpy
		ADD R12, SP, #0x1AC+arg_188
		LDMIA R12, {R1-R3}
		MOV R0, R4
		BL sub_FF83A578
		MOV R2, R0,LSL#16
		MOV R1, R5
		MOV R0, R6
		MOV R2, R2,LSR#16
		BL sub_FF838174

loc_FF840750:
		ADD R7, R7, #4

loc_FF840754:
		LDRH R3, [R7]
		CMP R3, #0
		BNE loc_FF840700
		ADD R7, SP, #0x1AC+arg_198
		LDR R6, =hInfoCreative
		MOV R0, SP
		MOV R1, R7
		MOV R2, #0x184
		LDR R5, [R6]
		BL memcpy
		ADD R4, SP, #0x1AC+arg_188
		LDMIA R4, {R0-R3}
		BL sub_FF83A6F4 // wb
		MOV R1, #0x10
		MOV R2, R0
		MOV R0, R5
		BL sub_FF837FA8
		MOV R2, #0x188
		MOV R0, SP
		ADD R1, SP, #0x1AC+arg_194
		LDR R5, [R6]
		BL memcpy
		LDMIA R4, {R1-R3}
		MOV R0, #0x1B
		BL choseFromTable
		MOV R0, R0,LSL#16
		MOV R1, #0
		MOV R0, R0,LSR#16
		BL sub_FF83E4AC //date/time
		MOV R1, #0xF
		MOV R2, R0
		MOV R0, R5
		BL sub_FF837FA8
		MOV R1, R7
		MOV R0, SP
		MOV R2, #0x184
		LDR R5, [R6]
		BL memcpy
		LDMIA R4, {R0-R3}
		BL sub_FF83A640 // cf free size
		MOV R1, #0x11
		MOV R2, R0
		MOV R0, R5
		BL sub_FF837FA8
		MOV R1, R7
		MOV R0, SP
		MOV R2, #0x184
		BL memcpy
		LDMIA R4, {R0-R3}
		BL sub_FF84031C
		ADD SP, SP, #0x188
		LDMFD SP!, {R4-R7,LR}
		ADD SP, SP, #0x10
		MOV PC, LR

sub_FF84031C:

var_FC 	= -0xFC
var_74 	= -0x74
var_70 	= -0x70
var_68 	= -0x68
var_64 	= -0x64
var_60 	= -0x60
var_5C 	= -0x5C
var_58 	= -0x58
var_10 	= -0x10
var_4 	= -4

		SUB SP, SP, #0x10
		STMFD SP!, {R4-R10,LR}
		SUB SP, SP, #0x1CC
		ADD R4, SP, #0x1FC+var_10
		STMIA R4, {R0-R3}
		MOV R0, SP
		ADD R1, SP, #0x1FC+var_4
		MOV R2, #0x188
		BL memcpy
		LDMIA R4, {R1-R3}
		MOV R0, #0xD
		BL choseFromTable
		LDR R3, =hInfoCreative
		MOV R6, R0
		MOV R2, R6,LSL#16
		LDR R0, [R3]
		MOV R2, R2,LSR#16
		MOV R1, #0x14
		BL sub_FF838174
		MOV R0, R6
		ADD R1, SP, #0x1FC+var_70
		BL PS_GetPictureStyleParam
		ADD R0, SP, #0x1FC+var_FC
		LDRSB R3, [R0,#0x91] //sharpness
		LDRSB R2, [R0,#0x90] //CONTRAST
		CMP R6, #5
		STR R3, [SP,#0x1FC+var_68]
		STR R2, [SP,#0x1FC+var_64]
		MOV R1, #0
		BNE loc_FF8403A8
		LDRSB R3, [R0,#0x92]
		LDRSB R2, [R0,#0x93]
		STR R3, [SP,#0x1FC+var_60]
		STR R2, [SP,#0x1FC+var_5C]
		B loc_FF8403D0

loc_FF8403A8:
		ADD R2, SP, #0x1FC+var_FC
		LDRSB R3, [R2,#0x92]
		LDRSB R2, [R2,#0x93]
		CMP R6, #8
		STR R3, [SP,#0x1FC+var_60]
		STR R2, [SP,#0x1FC+var_5C]
		BHI loc_FF8403D0
		CMP R6, #6
		LDRCS R6, [SP,#0x1FC+var_70]
		MOVCS R1, #1

loc_FF8403D0:
		SUBS R4, R1, #0
		BNE loc_FF840438
		CMP R6, #5
		MOV R7, #0x16
		MOV R8, #0x19
		MOV R10, #0x1C
		MOV R9, #0x1F
		BNE loc_FF84040C
		LDR R4, =hInfoCreative
		MOV R1, #0x1B
		LDR R0, [R4]
		MOV R2, #0xAE
		BL sub_FF8382DC
		MOV R2, #0x188
		B loc_FF840424

loc_FF84040C:
		LDR R4, =hInfoCreative
		MOV R1, #0x1B
		LDR R0, [R4]
		MOV R2, #0x57
		BL sub_FF8382DC
		MOV R2, #0x1A8

loc_FF840424:
		LDR R0, [R4]
		MOV R1, #0x1E
		ADD R2, R2, #3
		BL sub_FF8382DC
		B loc_FF8405E4

loc_FF840438:  //used when user def. picture style selected
		LDR R5, =hInfoCreative
		MOV R1, #0x13
		LDR R0, [R5]
		MOV R2, #0
		BL sub_FF838538
		MOV R2, R4
		LDR R0, [R5]
		MOV R1, #0xA
		BL sub_FF838538
		SUB R3, R6, #6
		CMP R3, #2
		BHI loc_FF84049C
		MOV R0, R6
		ADD R1, SP, #0x1FC+var_74
		BL sub_FF940488
		CMP R0, #0
		BNE loc_FF84049C
		LDR R3, [SP,#0x1FC+var_74]
		STRB R0, [R3,#0xC]
		MOV R3, R6,LSL#16
		LDR R0, [R5]
		MOV R3, R3,LSR#16
		MOV R1, #0xA
		LDR R2, [SP,#0x1FC+var_74]
		BL sub_FF8381DC

loc_FF84049C:
		LDR R4, =hInfoCreative
		MOV R2, R6,LSL#16
		MOV R2, R2,LSR#16
		LDR R0, [R4]
		MOV R1, #0xA
		MOV R7, #0x23
		BL sub_FF838174
		MOV R8, #0x24
		LDR R0, [R4]
		MOV R1, R7
		MOV R2, #1
		BL sub_FF838538
		MOV R10, #0x25
		LDR R0, [R4]
		MOV R1, R8
		MOV R2, #1
		BL sub_FF838538
		MOV R9, #0x26
		LDR R0, [R4]
		MOV R1, R10
		MOV R2, #1
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, R9
		MOV R2, #1
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x20
		MOV R2, #1
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x23
		MOV R2, #1
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x22
		MOV R2, #1
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x15
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x16
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x18
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x19
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1C
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1F
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1B
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1E
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x17
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1A
		MOV R2, #0
		BL sub_FF838538
		LDR R0, [R4]
		MOV R1, #0x1D
		MOV R2, #0
		BL sub_FF838538

loc_FF8405E4:
		ADD R5, SP, #0x1FC+var_58
		LDR R4, =hInfoCreative
		LDR R2, [SP,#0x1FC+var_68]
		LDR R1, =a1d
		MOV R0, R5
		BL sprintf
		MOV R1, R7
		LDR R0, [R4]
		MOV R2, R5
		BL sub_FF837FA8 //sharpness
		LDR R7, =a2d_0
		LDR R2, [SP,#0x1FC+var_64]
		MOV R1, R7
		MOV R0, R5
		BL sprintf
		LDR R0, [R4]
		MOV R1, R8
		MOV R2, R5
		BL sub_FF837FA8 //CONTRAST
		CMP R6, #5
		BNE loc_FF840654
		LDR R1, [SP,#0x1FC+var_60]
		LDR R3, =0x2160
		ADD R1, R1, R1,LSL#1
		ADD R1, R1, R3
		MOV R0, R5
		BL strcpy
		B loc_FF840664

loc_FF840654:
		MOV R0, R5
		MOV R1, R7
		LDR R2, [SP,#0x1FC+var_60]
		BL sprintf

loc_FF840664:
		LDR R3, =hInfoCreative
		ADD R4, SP, #0x1FC+var_58
		LDR R0, [R3]
		MOV R1, R10
		MOV R2, R4
		BL sub_FF837FA8
		CMP R6, #5
		BNE loc_FF84069C
		LDR R3, [SP,#0x1FC+var_5C]
		LDR R1, =(0x216C+3)
		MOV R0, R4
		ADD R1, R1, R3,LSL#1
		BL strcpy
		B loc_FF8406AC

loc_FF84069C:
		MOV R0, R4
		LDR R1, =a2d_0
		LDR R2, [SP,#0x1FC+var_5C]
		BL sprintf

loc_FF8406AC:
		LDR R3, =hInfoCreative
		MOV R1, R9
		LDR R0, [R3]
		ADD R2, SP, #0x1FC+var_58
		BL sub_FF837FA8
		ADD SP, SP, #0x1CC
		LDMFD SP!, {R4-R10,LR}
		ADD SP, SP, #0x10
		MOV PC, LR

sub_FF840834:

var_10 	= -0x10
var_4 	= -4
arg_188 	=  0x188
arg_194 	=  0x194
arg_198 	=  0x198

		SUB SP, SP, #0x10
		STMFD SP!, {R4-R8,LR}
		SUB SP, SP, #0x18C
		ADD R12, SP, #0x1B4+var_10
		STMIA R12, {R0-R3}
		LDR R7, =0x2140
		LDRH R3, [R7]
		CMP R3, #0
		MOV R8, #0
		BEQ loc_FF8408EC

loc_FF84085C:
		LDRH R3, [R7,#2]
		CMP R3, #0
		MOV R0, SP
		ADD R1, SP, #0x1B4+var_4
		MOV R2, #0x18C
		BEQ loc_FF8408DC
		MOV R4, R3
		BL memcpy
		ADD R12, SP, #0x1B4+var_10
		LDMIA R12, {R1-R3}
		MOV R0, R4
		BL SysConfFmt_Update
		MOVS R0, R0,LSL#16
		LDR R6, =hInfoCreative
		ADD R1, SP, #0x1B4+arg_194
		MOV R2, #0x188
		MOV R0, SP
		BEQ loc_FF8408DC
		LDR R6, [R6]
		LDRH R5, [R7]
		LDRH R4, [R7,#2]
		BL memcpy
		ADD R12, SP, #0x1B4+arg_188
		LDMIA R12, {R1-R3}
		MOV R0, R4
		BL sub_FF83A578
		MOV R2, R0,LSL#16
		MOV R1, R5
		MOV R0, R6
		MOV R2, R2,LSR#16
		MOV R8, #1
		BL sub_FF838174

loc_FF8408DC:
		ADD R7, R7, #4
		LDRH R3, [R7]
		CMP R3, #0
		BNE loc_FF84085C

loc_FF8408EC:
		ADD R6, SP, #0x1B4+var_4
		MOV R0, SP
		MOV R1, R6
		MOV R2, #0x18C
		BL memcpy
		ADD R5, SP, #0x1B4+var_10
		MOV R0, #0x43
		LDMIA R5, {R1-R3}
		BL SysConfFmt_Update
		MOVS R0, R0,LSL#16
		BEQ loc_FF840950
		LDR R3, =hInfoCreative
		MOV R0, SP
		ADD R1, SP, #0x1B4+arg_198
		MOV R2, #0x184
		LDR R4, [R3]
		BL memcpy
		ADD R12, SP, #0x1B4+arg_188
		LDMIA R12, {R0-R3}
		BL sub_FF83A6F4  //wb
		MOV R1, #0x10
		MOV R2, R0
		MOV R0, R4
		BL sub_FF837FA8
		MOV R8, #1

loc_FF840950:
		MOV R0, SP
		MOV R1, R6
		MOV R2, #0x18C
		BL memcpy
		MOV R0, #0x51
		LDMIA R5, {R1-R3}
		BL SysConfFmt_Update
		MOVS R0, R0,LSL#16
		BEQ loc_FF8409AC
		LDR R3, =hInfoCreative
		MOV R0, SP
		ADD R1, SP, #0x1B4+arg_198
		MOV R2, #0x184
		LDR R4, [R3]
		BL memcpy
		ADD R12, SP, #0x1B4+arg_188
		LDMIA R12, {R0-R3}
		BL sub_FF83A640
		MOV R1, #0x11
		MOV R2, R0
		MOV R0, R4
		BL sub_FF837FA8
		MOV R8, #1

loc_FF8409AC:
		CMP R8, #0
		BEQ loc_FF8409D0
		LDR R4, =hInfoCreative
		LDR R0, [R4]
		BL sub_FF917134
		LDR R0, [R4]
		BL sub_FF916614
		LDR R0, [R4]
		BL sub_FF917198

loc_FF8409D0:
		ADD SP, SP, #0x18C
		LDMFD SP!, {R4-R8,LR}
		ADD SP, SP, #0x10
		MOV PC, LR

.align 2
fin:
