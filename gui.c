#include "firmware.h"
#include "gui.h"
#include "main.h"
#include "debug.h"


// GUI_Command(4) for MENU BTN

int my_GUI_IDLEHandler(int unk0, int event, int unused, int unk1) {

#ifdef ENABLE_DEBUG
	printf_log(8, 8, "[400Plus-IDLE] 0x%08X, %s, 0x%08X, 0x%08X", unk0, debug_gui_name(event), unused, unk1);
#endif

	if (event == GUI_START_OLC_MODE)
		initialize_display();

	return GUI_IDLEHandler(unk0, event, unused, unk1);
}


void my_GUIInit() {

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
	taskcreate_GuiMainTask();
	CreateGUIPubInstance();
	taskcreate_tGraphics();
	CreateQRevImgQueue();
	Some_DP_GUI();
	SetGUIFactoryMenuProcInit();
	GUIuramodeInit();
	CreateCtrlMain(&my_GUI_IDLEHandler, 0);
	//CreateCtrlMain(&GUI_IDLEHandler, 0);
	sub_FF833D50();
	sub_FF82B5AC();
}

