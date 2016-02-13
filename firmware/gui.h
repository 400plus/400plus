#ifndef GUI_H_
#define GUI_H_

// Flags

#define FLAG_GUI_MODE       GUIMode
#define FLAG_DISPLAY_ON     DisplayOn

// GUIModes

typedef enum {
	GUIMODE_OFF,             // 0x00 - main screen off
	GUIMODE_REVIEW,          // 0x01 - review photos mode (activated with play btn)
	GUIMODE_MENU,            // 0x02 - main menu
	GUIMODE_RTCSET,          // 0x03 - Set internal clock from MENU
	GUIMODE_INFO,            // 0x04 - info screen (menu -> disp.)
	GUIMODE_NOCFWARNING,     // 0x05 - no CF card
	GUIMODE_QR,              // 0x06 - review image right after shot
	GUIMODE_FULLNOWARNING,   // 0x07 - ?
	GUIMODE_PICTURESTYLE,    // 0x08 - Picture Style
	GUIMODE_ISO,             // 0x09 - ISO
	GUIMODE_WB,              // 0x0A - WB
	GUIMODE_AFMODE,          // 0x0B - AF mode choosing screen
	GUIMODE_METER,           // 0x0C - Metering mode screen
	GUIMODE_QUAL,            // 0x0D - Quality screen selection from MENU
	GUIMODE_UNKNOWN_1,       // 0x0E - ?
	GUIMODE_DRIVE,           // 0x0F - Drive mode
	GUIMODE_AFPATTERN,       // 0x10 - AF zones select
	GUIMODE_OLC,             // 0x11 - Main screen (white one)
	GUIMODE_BULBCOUNT,       // 0x12 - Bulb counter screen
	GUIMODE_CFFULL,          // 0x13 - CF is full
	GUIMODE_ERRCF_ERROR,     // 0x14 - CF Error ?
	GUIMODE_ERRCF_FULLNO,    // 0x15 - ?
	GUIMODE_ERRCF_PROTECT,   // 0x16 - ?
	GUIMODE_UNKNOWN_2,       // 0x17 - ?
	GUIMODE_ERRORCODE,       // 0x18 - error code screen
	GUIMODE_USBCONNECTTYPE,  // 0x19 - ?
	GUIMODE_DIRECTTRANSFER,  // 0x1A - ?
	GUIMODE_FLASHEV,         // 0x1B - Flash EV (SET from main dialog if configured at C.Fn-01)
	GUIMODE_INCOMPIMAGE,     // 0x1C - ?
	GUIMODE_BATTEMPTY,       // 0x1D - Battery empty
	GUIMODE_ACTIVESWEEP,     // 0x1E - Sweeping the sensor
	GUIMODE_ACTIVESWEEP_OLC, // 0x1F - Sweeping the sensor
// Fictitious modes
	GUIMODE_400PLUS  = 0x40,  // 400plus mode
	GUIMODE_FACE     = 0x41,  // Face mode
	GUIMODE_SHORTCUT = 0x42,  // A shortcut button is down
	GUIMODE_COUNT    = 0x4F   // Total number of active GUIMODEs (plus a safe margin)
} guimode_t;

// GUI Events

typedef enum {
	//GUI_PRESS_DISP_BUTTON          = 0x10000000,
	//GUI_IDC_DBN_OK                 = 0x6, // ?
	//GUI_IDC_DBN_CANCEL             = 0x7, // ?
	GUI_UNKNOWN_0x01               = 0x01, // Call DeleteDialogBox and return 0
	GUI_UNKNOWN_0x02               = 0x02, // Call [GUI_]Lock(),PaletteInit(),DisplayMode(),delete_child_dialog,DeleteDialogBox(),Unlock(),PaletteUnInit() and return 0; (probably deletes the dialog and it's childs)
	GUI_GOT_TOP_OF_CONTROL         = 0x800,
	GUI_LOST_TOP_OF_CONTROL        = 0x801,
	GUI_INITIALIZE_CONTROLLER      = 0x802,
	GUI_PUBLISHER_INSTANCE         = 0x803, // probably not visible by our handlers
	GUI_TERMINATE_WINSYS           = 0x804,
	GUI_DELETE_DIALOG_REQUEST      = 0x805,
	GUI_BUTTON_RIGHT               = 0x807,
	GUI_BUTTON_LEFT                = 0x809,
	GUI_BUTTON_UP                  = 0x80B,
	GUI_BUTTON_DOWN                = 0x80D,
	GUI_BUTTON_MENU                = 0x80F,
	GUI_BUTTON_JUMP                = 0x810,
	GUI_BUTTON_SET                 = 0x812, //(code1 will be menu line number when set button was pressed)
	GUI_BUTTON_ZOOM_IN_PRESS       = 0x819,
	GUI_BUTTON_ZOOM_IN_RELEASE     = 0x81A, // DISP_RELEASED // idle handler shows them w/o a reason, could be disp_release
	GUI_BUTTON_ZOOM_OUT_PRESS      = 0x81B,
	GUI_BUTTON_ZOOM_OUT_RELEASE    = 0x81C, // DISP_RELEASED // idle handler shows them w/o a reason, could be disp_release
	// 820 ? // SUB_DIAL (spin left) ? http://chdk.wikia.com/wiki/DryOS_structures
	// 823 ? // PRESS_MLT_CENTER_BUTTON ? http://chdk.wikia.com/wiki/DryOS_structures
	GUI_BUTTON_DISP                = 0x829, // GUI_BUTTON_INFO
	GUI_BUTTON_DIAL_RIGHT          = 0x82B, // on DIAL_[LEFT|RIGHT] the r4 and r5 in btn_handler
	GUI_BUTTON_DIAL_LEFT           = 0x82C, // are incremental counter for both of them, every dial increments them both
	// AFAIK (from the asm) DIAL_LEFT is the last with a small number
	GUI_BUTTON_PLAY                = 0x10000000,
	GUI_BUTTON_TRASH               = 0x10000001,
	GUI_BUTTON_DP                  = 0x10000002,
	// 0x10000019 ?
	// 0x10000021 ?
	// these names below could be incorrect
	GUI_BUTTON_CF_CARD             = 0x10000006, // could be
	GUI_START_MENU_MODE            = 0x10000007,
	GUI_START_INFO_MODE            = 0x10000008,
	GUI_START_PLAY_MODE            = 0x10000009,
	GUI_START_QR_MODE              = 0x1000000A,
	GUI_START_NOCFWARNING_MODE     = 0x1000000B,
	GUI_START_FULLNOWARNING_MODE   = 0x1000000C,
	GUI_START_FULLCF               = 0x1000000D,
	GUI_START_ERRCF_ERROR          = 0x1000000E,
	GUI_START_ERRCF_FULLNO         = 0x1000000F,
	GUI_START_ERRCF_PROTECT        = 0x10000010,
	GUI_START_ERRORCODE_MODE       = 0x10000011,
	GUI_START_INCOMPIMAGE_MODE     = 0x10000012,
	GUI_START_RTCSET_MODE          = 0x10000013,
	GUI_START_IDLE_MODE            = 0x10000014,
	GUI_POST_QR_IMAGE              = 0x10000015,
	GUI_DISP_RTCSET_MODE           = 0x10000018,
	GUI_DISP_NOCFWARNING_MODE      = 0x10000029,
	GUI_DISP_FULLNOWARNING_MODE    = 0x1000002A,
	GUI_DISP_FULLCF                = 0x1000002B,
	GUI_DISP_ERRCF_ERROR           = 0x1000002C,
	GUI_DISP_ERRCF_FULLNO          = 0x1000002D,
	GUI_DISP_ERRCF_PROTECT         = 0x1000002E,
	GUI_DISP_ERRORCODE_MODE        = 0x1000002F,
	GUI_DISP_INCOMPIMAGE_MODE      = 0x10000030,
	GUI_FINISH_QR_MODE             = 0x10000031,
	GUI_DISP_USBCONNECTTYPE_MODE   = 0x10000035,
	GUI_DISP_DIRECTTRANSFER_MODE   = 0x10000036,
	GUI_START_USBCONNECTTYPE_MODE  = 0x10000037,
	GUI_START_DIRECTTRANSFER_MODE  = 0x10000038,
	GUI_DISP_OLC_MODE              = 0x10000039,
	GUI_DISP_BULBCOUNT_MODE        = 0x1000003B,
	GUI_START_OLC_MODE             = 0x1000003C,
	GUI_START_BULBCOUNT_MODE       = 0x1000003D,
	GUI_DISP_ISO_MODE              = 0x10000043,
	GUI_DISP_AF_MODE               = 0x10000044,
	GUI_DISP_WB_MODE               = 0x10000045,
	GUI_DISP_MES_MODE              = 0x10000046,
	GUI_BUTTON_DRIVE               = 0x10000047,
	GUI_DISP_FP_SEL                = 0x10000048,
	GUI_DISP_QUAL_MODE             = 0x10000049,
	GUI_DISP_PICTURESTYLE_MODE     = 0x1000004A,
	GUI_DISP_FECOMP_MODE           = 0x1000004B,
	GUI_DISP_ACTIVESWEEP           = 0x1000004C,
	GUI_DISP_ACTIVESWEEP_OLC       = 0x1000004D,
	GUI_DISP_BATTEMPTY             = 0x1000004E,
	GUI_START_ISO_MODE             = 0x10000058,
	GUI_START_AF_MODE              = 0x10000059,
	GUI_START_WB_MODE              = 0x1000005A,
	GUI_START_MES_MODE             = 0x1000005B,
	GUI_START_DRIVE_MODE           = 0x1000005C,
	GUI_START_FP_SEL               = 0x1000005D,
	GUI_START_QUAL_MODE            = 0x1000005E,
	GUI_START_PICTURESTYLE_MODE    = 0x1000005F,
	GUI_START_FECOMP_MODE          = 0x10000060,
	GUI_START_ACTIVESWEEP          = 0x10000061,
	GUI_START_ACTIVESWEEP_OLC      = 0x10000062,
	GUI_START_BATTEMPTY            = 0x10000063,
	GUI_FINISH_ACTIVESWEEP         = 0x10000065,
	GUI_START_COLORBAR_DIALOG      = 0x1000006E,
	GUI_START_LCDADJUST_DIALOG     = 0x1000006F,
	GUI_DELETE_COLORBAR_DIALOG     = 0x10000070,
	GUI_DELETE_LCDADJUST_DIALOG    = 0x10000071,
	GUI_UNKNOWN1                   = 0x1000003A, // related to mettering may be ?
	GUI_UNKNOWN2                   = 0x1000003E, // related to btns that repeats (AV, 1/2-SHUT) may be ?
} gui_event_t;

// forward declaration

typedef struct _dialog_t dialog_t;

// Handler for events / buttons in dialogs

typedef int(*event_handler_t)(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

// Dialog Item struct

typedef struct {
	int pSignature; // 0x00 - "DIALOGITEM"
	int field_4;    // 0x04
	int field_8;    // 0x08
	int field_C;    // 0x0C
	int jump_table; // 0x10 - pointer to a jumptable
	int field_14;   // 0x14
	int the_case;   // 0x18 - element from the jumptable to switch on it (in dlgItem_sub_FF917D00)
	//              // something like: goto jump_table[the_case];
} dialog_item_t;

// Dialog struct

struct dialog_t {
	char * pSignature;   // 0x0000 - "DIALOG"
	int field_0x0004;    // 0x0004
	int window_struct;   // 0x0008 - window instance
	int palette_struct;  // 0x000C - palette class
	int close_dialog;    // 0x0010 - when set to 1, DeleteDialogBox is called
	int template_num;    // 0x0014 - the number of the dialog template
	int field_0x0018;    // 0x0018 - some resource for this dialog
	int field_0x001C;    // 0x001C - another resource for the dialog
	int field_0x0020;    // 0x0020
	int field_0x0024;    // 0x0024
	int field_0x0028;    // 0x0028
	int field_0x002C;    // 0x002C
	int field_0x0030;    // 0x0030
	int field_0x0034;    // 0x0034
	int field_0x0038;    // 0x0038
	int field_0x003C;    // 0x003C
	int field_0x0040;    // 0x0040
	int field_0x0044;    // 0x0044
	int field_0x0048;    // 0x0048
	int field_0x004C;    // 0x004C
	int field_0x0050;    // 0x0050
	int field_0x0054;    // 0x0054
	int central_handler; // 0x0058 - the central handler ( DIALOGHandler() )
	int field_0x005C;    // 0x005C
	int field_0x0060;    // 0x0060
	int field_0x0064;    // 0x0064
	int field_0x0068;    // 0x0068
	int field_0x006C;    // 0x006C
	int field_0x0070;    // 0x0070
	int field_0x0074;    // 0x0074
	int field_0x0078;    // 0x0078
	event_handler_t *event_handler; // 0x007C
	int arg2;            // 0x0080 - the second arg to the handler
	dialog_item_t *dlg_item; // 0x0084 - structure that holds some dialog_item stuff, probably the selected item
	int field_0x0088;    // 0x0088
	int field_0x008C;    // 0x008C
	int field_0x0090;    // 0x0090
	int field_0x0094;    // 0x0094
	int brush_struct;    // 0x0098 - brush class
	// there are more for sure (perhaps to 0x00B8)
};

// Undocumented

typedef struct _window_t window_t;

extern int GUIMode;       // Current GUI Mode
extern int DisplayOn;     // Is display on?

extern dialog_t *hInfoCreative; // dialog handle for info screen
extern dialog_t *hMainDialog;   // the main OLC dialog (white screen)

// Dialogs

#define dialog_create(template, handler) CreateDialogBox(0, 0, handler, template, 0)

#define dialog_set_property_int dialog_item_set_int
#define dialog_set_property_str dialog_item_set_str

extern dialog_t *CreateDialogBox(int parm1, int parm2, event_handler_t, int template, int is_busy_maybe);
extern int       DeleteDialogBox(dialog_t *dialog);

extern void dialog_redraw        (dialog_t *dialog);
extern void dialog_item_set_int  (dialog_t *dialog, const int item, const int   data);
extern void dialog_item_set_str  (dialog_t *dialog, const int item, const char *data);
extern void dialog_item_set_label(dialog_t *dialog, const int type, const void *data, const int length, const int item);

extern int dialog_event_handler (dialog_t *dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);
extern int olc_event_handler    (dialog_t *dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

extern void GUI_Select_Item  (void *menu_handle, int menu_item);
extern void GUI_Highlight_Sub(void *menu_handle, int menu_item, int enable);
extern void GUI_Disable_Item (void *menu_handle, int menu_item, int enable);

extern void window_instance_redraw(window_t *window);

// Switch display on / off

extern int SetTurnDisplayEvent_1_after_2(void);
extern int SetTurnDisplayEvent_2_after_1(void);

// Palette

extern void GUI_PaletteInit   (void);
extern void GUI_PaletteUnInit (void);
extern void GUI_PalettePush   (void);
extern void GUI_PalettePop    (void);
extern int  GUI_PaletteChange (int pallete);

// Other

extern void GUI_Lock         (void);
extern void GUI_UnLock       (void);
extern void GUI_ClearImage   (void);
extern void GUI_RefreshImage (void);
extern void GUI_StartMode    (guimode_t mode);

// Udocumented

extern int GUI_IDLEHandler(int unk0, int event, int unused, int unk1);

#endif
