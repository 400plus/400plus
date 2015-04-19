#include <stdint.h>

#include "firmware.h"
#include "main.h"

#include "display.h"
#include "debug.h"

#include "gui.h"

// GUI_Command(4) for MENU BTN

int hack_GUI_IDLEHandler(int unk0, int event, int unused, int unk1) {

#ifdef ENABLE_DEBUG
	printf_log(8, 8, "[400Plus-IDLE] 0x%08X, %s, 0x%08X, 0x%08X", unk0, debug_gui_name(event), unused, unk1);
#endif

	return GUI_IDLEHandler(unk0, event, unused, unk1);
}

#if 0

// WARNING !
// this is very bare translation of GuiMainTask.
// this code is broken and will not work, it wont compile either.
// it's for reference only ... until i translate it as it should be...

void hack_task_GuiMainTask() {

	int * pMessage;
	int * hGuiLocalQueue = CreateMessageQueue(aGuiLocalQueue, 0x100);


	ReceiveMessageQueue(hGuiMainQueue, * pMessage, 0);

	if (pMessage == 0) {
		DebugAssert(apMessageNULL /* pMessage != NULL */, a__GUIGUI_C /* ../GUI/GUI.c */, 0xAD);
	}

	// r4=localQ
	r5=0;
	r6=0;

loc_FF82835C:

	if (*pMessage != 1)
		goto loc_FF8283D0;

	unsigned pMessage_4 = *(pMessage+4); // R2
	if (pMessage_4 > 1)
		goto loc_FF82839C;

	r6++;
	if (r6>3)
		goto loc_FF8283E0;

	*dword_1EE8++;
	*(pMessage+8) = dword_1EE8;
	goto loc_FF8283D0;


loc_FF82839C:
	if (pMessage_4 - 0x31 <= 8) {
		if (pMessage_4 == 0x28 || pMessage_4 == 0x2E)
			goto loc_FF8283C4;

		if (pMessage_4 == 0x2A)
			goto loc_FF8283C4;

		if (pMessage_4 != 0x2C)
			goto loc_FF8283D0;


loc_FF8283C4:
		r5++;
		if (r5 > 3)
			goto loc_FF8283E0;

loc_FF8283D0:
		PostMessageQueue(hGuiLocalQueue, pMessage, 0);

loc_FF8283E0:
		// r3 = mainQ
		// r1 = pmessage
		// r0 = *mainQ
		if ( TryReceiveMessageQueue(hGuiMainQueue, pMessage, *hGuiMainQueue) == 0 )
			goto loc_FF82835C;

		r5 = localQ;

	while (1) {

		r12 = pMessage;
		r4 = localQ->00;
		r3 = *pMessage;
		lr = *(pMessage+4);
		r2 = pMessage;
		r3 = *pMessage;

		if ( TryReceiveMessageQueue(localQ, &msg) == 0 ) {
			//printf_log(0x18, 1, "[GUIM] e:%d(%d) m:%d", ???);
			continue; // ???
		} else {
			printf_log(0x18, 1, "[GUIM]\tm:%d", GUIMode);
			break;
		}

		switch (*pMessage){
		case 0:
			DigiPropInit((*pMessage)->04, (*pMessage)->08, (*pMessage)->0c);
			MainHeapFree((*pMessage)->08);
			MainHeapFree((*pMessage)->0c);
			break;
		case 1: // gui_command
			GUI_Command(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		case 2:
			changeMode(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		case 3:
			SetSendDisplayModeToMC(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		case 4:
			SetSendStartModeToMC(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		case 5:
			sub_FF82B6C4(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		case 6:
			gui_machinecell(*pMessage->04, *pMessage->08, *pMessage->0c);
			break;
		default:
			break;
		}
	}
}
#endif

void hack_taskcreate_GuiMainTask() {
	hGuiMainQueue = CreateMessageQueue(aGuiMainQueue, 0x100);
	CreateTask(aGuiMainTask, 0x18, 0x2000, task_GuiMainTask, 0);
	//taskcreate_TurnDisplayTask(); // start
	hTurnDisplayEventFlag = (int*)CreateEventFlag(aTurndisplayeve, 0x24);
	CreateTask(aTurndisplaytas /* TurnDisplayTask */, 0x18, 0, task_TurnDisplayTask, 0);
	// taskcreate_TurnDisplayTask(); // end
	SendOlcSetProcTftNotifyChange(OlcTftNotifyChange); // registers OlcTftNotifyChange() routine to receive notify changes events, it actually posts messages to hGuiMainQueue (takes no parameters)
}

void hack_GUIInit() {

	m_pSendDisplayModeToMC=0;
	GUIIdleFlag=0;
	GUIMode=0;
	m_pSendStartModeToMC=0;

	hGuiSwSem = CreateBinarySemaphore(aGuiSwSem /*"GuiSwSem"*/, 1);

	TablesInit();

	WidgetBinaryBitmapInit(placeListFromTab(WIDGET_BINARY_BITMAP));
	WidgetCounterInit(placeListFromTab(WIDGET_COUNTER));
	WidgetFocusMarkInit(placeListFromTab(WIDGET_FOCUS_MARK));
	WidgetHistogramInit(placeListFromTab(WIDGET_HISTOGRAM));
	WidgetListSelectInit(placeListFromTab(WIDGET_LIST_SELECT));
	WidgetNavigateIconInit(placeListFromTab(WIDGET_NAVIGATE_ICON));
	WidgetPopupAEBInit(placeListFromTab(WIDGET_POPUP_AEB));
	WidgetPopupMenuInit(placeListFromTab(WIDGET_POPUP_MENU));
	WidgetProgressBarInit(placeListFromTab(WIDGET_PROGRESS_BAR));
	WidgetButtonInit(placeListFromTab(WIDGET_BUTTON));
	WidgetRectangle(placeListFromTab(WIDGET_RECTANGLE));
	WidgetScrollBarInit(placeListFromTab(WIDGET_SCROLL_BAR));
	WidgetSliderInit(placeListFromTab(WIDGET_SLIDER));
	WidgetTextInit(placeListFromTab(WIDGET_TEXT));
	WidgetListViewInit(placeListFromTab(WIDGET_LIST_VIEW));
	WidgetPopupSliderInit(placeListFromTab(WIDGET_POPUP_SLIDER));
	WidgetMenuTabInit(placeListFromTab(WIDGET_MENU_TAB));
	WidgetPaletteBitmapInit(placeListFromTab(WIDGET_PALETTE_BITMAP));
	WidgetAnimationBmpInit(placeListFromTab(WIDGET_ANIMATION_BMP));
	WidgetArchRectInit(placeListFromTab(WIDGET_ARCH_RECT));

	str_0x5188(1);

	sub_FF918D24(0);
	sub_FF92AD74(sub_FF918C58(3));
	sub_FF934DE8();

	off_1EE0=CreateFontManagerInstance(FontInit(1, 20), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);
	CreateFontManagerInstance(FontInit(1, 30), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);
	off_1EE0=CreateFontManagerInstance(FontInit(1, 36), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);

	int var1=0;
	int var2=0;
	sub_FF92D8EC(get_0x5178_aVramInstance(), &var1, &var2);

	hGUIWindowInstance = CreateWindowInstance(0, 0, var1, var2, GUIWindowInstanceProc, GetBrushFromSystemColor(3));

	window_instance_redraw(hGUIWindowInstance);
	//taskcreate_GuiMainTask();
	hack_taskcreate_GuiMainTask();
	CreateGUIPubInstance();
	taskcreate_tGraphics();
	CreateQRevImgQueue();
	Some_DP_GUI();
	SetGUIFactoryMenuProcInit();
	GUIuramodeInit();
	CreateCtrlMain(&hack_GUI_IDLEHandler, 0);
	//CreateCtrlMain(&GUI_IDLEHandler, 0);
	sub_FF833D50();
	sub_FF82B5AC();

	// Overwrite UpdateGUI
	TransferScreen = hack_TransferScreen;
}

