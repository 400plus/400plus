	.text
	.org 0
	.globl my_GUIInit

my_GUIInit:
		var_34  = -0x34
		var_30  = -0x30
		var_2C  = -0x2C
		var_28  = -0x28

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
		B   _default

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
		B   _default

my_START_OLC_MODE:
		BL initialize_display
		B  START_OLC_MODE

.align 2
fin:
