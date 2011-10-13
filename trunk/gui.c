#include "firmware.h"
#include "gui.h"
#include "main.h"

#ifdef ENABLE_DEBUG
const char * get_gui_name(int event);
#endif

int my_GUI_IDLEHandler(int unk0, int event, int param, int unk1) {

#ifdef ENABLE_DEBUG
	printf_log(8, 8, "[IDLE] 0x%08X, %s, 0x%08X, 0x%08X", unk0, get_gui_name(event), param, unk1);
#endif

	if (event == GUI_START_OLC_MODE)
		initialize_display();

	return GUI_IDLEHandler(unk0, event, param, unk1);
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
	int res1=sub_FF918C58(3);
	sub_FF92AD74(res1);
	sub_FF934DE8();

	off_1EE0=CreateFontManagerInstance(FontInit(1, 20), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);
	CreateFontManagerInstance(FontInit(1, 30), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);
	off_1EE0=CreateFontManagerInstance(FontInit(1, 36), &sub_FF92ADD8, &sub_FF92AF8C, &sub_FF92AFD8, &sub_FF92AF58, 1);

	int var1=0;
	int var2=0;
	sub_FF92D8EC(get_0x5178_aVramInstance(), &var1, &var2);

	hGUIWindowInstance = CreateWindowInstance(0, 0, var1, var2, GUIWindowInstanceProc, GetBrushFromSystemColor(3));

	some_do_with_window_instance(hGUIWindowInstance);
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








#ifdef ENABLE_DEBUG
const char * get_gui_name(int event) {
	static char name[20];

	switch (event) {
	case GUI_GOT_TOP_OF_CONTROL: return "GUI_GOT_TOP_OF_CONTROL";
	case GUI_LOST_TOP_OF_CONTROL: return "GUI_LOST_TOP_OF_CONTROL";
	case GUI_INITIALIZE_CONTROLLER: return "GUI_INITIALIZE_CONTROLLER";
	case GUI_TERMINATE_WINSYS: return "GUI_TERMINATE_WINSYS";
	case GUI_DELETE_DIALOG_REQUEST: return "GUI_DELETE_DIALOG_REQUEST";
	case GUI_BUTTON_RIGHT: return "GUI_BUTTON_RIGHT";
	case GUI_BUTTON_LEFT: return "GUI_BUTTON_LEFT";
	case GUI_BUTTON_UP: return "GUI_BUTTON_UP";
	case GUI_BUTTON_DOWN: return "GUI_BUTTON_DOWN";
	case GUI_BUTTON_MENU: return "GUI_BUTTON_MENU";
	case GUI_BUTTON_JUMP: return "GUI_BUTTON_JUMP";
	case GUI_BUTTON_SET: return "GUI_BUTTON_SET";
	case GUI_BUTTON_ZOOM_IN_PRESS: return "GUI_BUTTON_ZOOM_IN_PRESS";
	case GUI_BUTTON_ZOOM_IN_RELEASE: return "GUI_BUTTON_ZOOM_IN_RELEASE";
	case GUI_BUTTON_ZOOM_OUT_PRESS: return "GUI_BUTTON_ZOOM_OUT_PRESS";
	case GUI_BUTTON_ZOOM_OUT_RELEASE: return "GUI_BUTTON_ZOOM_OUT_RELEASE";
	case GUI_BUTTON_DISP: return "GUI_BUTTON_DISP";
	case GUI_BUTTON_DIAL_RIGHT: return "GUI_BUTTON_DIAL_RIGHT";
	case GUI_BUTTON_DIAL_LEFT: return "GUI_BUTTON_DIAL_LEFT";
	case GUI_BUTTON_PLAY: return "GUI_BUTTON_PLAY";
	case GUI_BUTTON_TRASH: return "GUI_BUTTON_TRASH";
	case GUI_BUTTON_DP: return "GUI_BUTTON_DP";
	case GUI_BUTTON_CF_CARD: return "GUI_BUTTON_CF_CARD";
	case GUI_START_MENU_MODE: return "GUI_START_MENU_MODE";
	case GUI_START_INFO_MODE: return "GUI_START_INFO_MODE";
	case GUI_START_PLAY_MODE: return "GUI_START_PLAY_MODE";
	case GUI_START_QR_MODE: return "GUI_START_QR_MODE";
	case GUI_START_NOCFWARNING_MODE: return "GUI_START_NOCFWARNING_MODE";
	case GUI_START_FULLNOWARNING_MODE: return "GUI_START_FULLNOWARNING_MODE";
	case GUI_START_FULLCF: return "GUI_START_FULLCF";
	case GUI_START_ERRCF_ERROR: return "GUI_START_ERRCF_ERROR";
	case GUI_START_ERRCF_FULLNO: return "GUI_START_ERRCF_FULLNO";
	case GUI_START_ERRCF_PROTECT: return "GUI_START_ERRCF_PROTECT";
	case GUI_START_ERRORCODE_MODE: return "GUI_START_ERRORCODE_MODE";
	case GUI_START_INCOMPIMAGE_MODE: return "GUI_START_INCOMPIMAGE_MODE";
	case GUI_START_RTCSET_MODE: return "GUI_START_RTCSET_MODE";
	case GUI_START_IDLE_MODE: return "GUI_START_IDLE_MODE";
	case GUI_POST_QR_IMAGE: return "GUI_POST_QR_IMAGE";
	case GUI_DISP_RTCSET_MODE: return "GUI_DISP_RTCSET_MODE";
	case GUI_DISP_NOCFWARNING_MODE: return "GUI_DISP_NOCFWARNING_MODE";
	case GUI_DISP_FULLNOWARNING_MODE: return "GUI_DISP_FULLNOWARNING_MODE";
	case GUI_DISP_FULLCF: return "GUI_DISP_FULLCF";
	case GUI_DISP_ERRCF_ERROR: return "GUI_DISP_ERRCF_ERROR";
	case GUI_DISP_ERRCF_FULLNO: return "GUI_DISP_ERRCF_FULLNO";
	case GUI_DISP_ERRCF_PROTECT: return "GUI_DISP_ERRCF_PROTECT";
	case GUI_DISP_ERRORCODE_MODE: return "GUI_DISP_ERRORCODE_MODE";
	case GUI_DISP_INCOMPIMAGE_MODE: return "GUI_DISP_INCOMPIMAGE_MODE";
	case GUI_FINISH_QR_MODE: return "GUI_FINISH_QR_MODE";
	case GUI_DISP_USBCONNECTTYPE_MODE: return "GUI_DISP_USBCONNECTTYPE_MODE";
	case GUI_DISP_DIRECTTRANSFER_MODE: return "GUI_DISP_DIRECTTRANSFER_MODE";
	case GUI_START_USBCONNECTTYPE_MODE: return "GUI_START_USBCONNECTTYPE_MODE";
	case GUI_START_DIRECTTRANSFER_MODE: return "GUI_START_DIRECTTRANSFER_MODE";
	case GUI_DISP_OLC_MODE: return "GUI_DISP_OLC_MODE";
	case GUI_DISP_BULBCOUNT_MODE: return "GUI_DISP_BULBCOUNT_MODE";
	case GUI_START_OLC_MODE: return "GUI_START_OLC_MODE";
	case GUI_START_BULBCOUNT_MODE: return "GUI_START_BULBCOUNT_MODE";
	case GUI_DISP_ISO_MODE: return "GUI_DISP_ISO_MODE";
	case GUI_DISP_AF_MODE: return "GUI_DISP_AF_MODE";
	case GUI_DISP_WB_MODE: return "GUI_DISP_WB_MODE";
	case GUI_DISP_MES_MODE: return "GUI_DISP_MES_MODE";
	case GUI_BUTTON_DRIVE: return "GUI_BUTTON_DRIVE";
	case GUI_DISP_FP_SEL: return "GUI_DISP_FP_SEL";
	case GUI_DISP_QUAL_MODE: return "GUI_DISP_QUAL_MODE";
	case GUI_DISP_PICTURESTYLE_MODE: return "GUI_DISP_PICTURESTYLE_MODE";
	case GUI_DISP_FECOMP_MODE: return "GUI_DISP_FECOMP_MODE";
	case GUI_DISP_ACTIVESWEEP: return "GUI_DISP_ACTIVESWEEP";
	case GUI_DISP_ACTIVESWEEP_OLC: return "GUI_DISP_ACTIVESWEEP_OLC";
	case GUI_DISP_BATTEMPTY: return "GUI_DISP_BATTEMPTY";
	case GUI_START_ISO_MODE: return "GUI_START_ISO_MODE";
	case GUI_START_AF_MODE: return "GUI_START_AF_MODE";
	case GUI_START_WB_MODE: return "GUI_START_WB_MODE";
	case GUI_START_MES_MODE: return "GUI_START_MES_MODE";
	case GUI_START_DRIVE_MODE: return "GUI_START_DRIVE_MODE";
	case GUI_START_FP_SEL: return "GUI_START_FP_SEL";
	case GUI_START_QUAL_MODE: return "GUI_START_QUAL_MODE";
	case GUI_START_PICTURESTYLE_MODE: return "GUI_START_PICTURESTYLE_MODE";
	case GUI_START_FECOMP_MODE: return "GUI_START_FECOMP_MODE";
	case GUI_START_ACTIVESWEEP: return "GUI_START_ACTIVESWEEP";
	case GUI_START_ACTIVESWEEP_OLC: return "GUI_START_ACTIVESWEEP_OLC";
	case GUI_START_BATTEMPTY: return "GUI_START_BATTEMPTY";
	case GUI_FINISH_ACTIVESWEEP: return "GUI_FINISH_ACTIVESWEEP";
	case GUI_START_COLORBAR_DIALOG: return "GUI_START_COLORBAR_DIALOG";
	case GUI_START_LCDADJUST_DIALOG: return "GUI_START_LCDADJUST_DIALOG";
	case GUI_DELETE_COLORBAR_DIALOG: return "GUI_DELETE_COLORBAR_DIALOG";
	case GUI_DELETE_LCDADJUST_DIALOG: return "GUI_DELETE_LCDADJUST_DIALOG";
	case GUI_UNKNOWN1: return "GUI_UNKNOWN1";
	case GUI_UNKNOWN2: return "GUI_UNKNOWN2";

	default:
		sprintf(name, "0x%08X", event);
		return name;
	}
}
#endif


