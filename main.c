#include <vxworks.h>
#include <dirent.h>

#include "firmware.h"
#include "firmware/fio.h"
#include "firmware/eventproc.h"

#include "macros.h"

#include "cache_hacks.h"
#include "button.h"
#include "display.h"
#include "intercom.h"
#include "settings.h"
#include "persist.h"
#include "cmodes.h"
#include "debug.h"

#include "main.h"

// Main message queue
int *action_queue;

// Global status
status_t status = {
	button_down       : BUTTON_NONE,
	script_running    : FALSE,
	script_stopping   : FALSE,
	menu_running      : FALSE,
	shortcut_running  : SHORTCUT_NONE,
	afp_dialog        : FALSE,
	measuring         : FALSE,
	msm_count         : 0,
	msm_tv            : EV_ZERO,
	msm_av            : EV_ZERO,
	ignore_msg        : FALSE,
	vf_status         : VF_STATUS_NONE,
	lock_redraw       : FALSE,
};

void hack_relocate   (void);
void cache_hacks     (void);

void disable_cache_clearing (void);

void hack_dmProcInit                (void);
int  hack_register_gui_idle_handler (void *org_proc, int zero);
int  hack_init_intercom_data        (void *old_proc);
void hack_StartConsole              (void);

void hack_pre_init_hook  (void);
void hack_post_init_hook (void);

void hack_jump_trash_events (int r0, int r1, int button);

void action_dispatcher(void);

int check_create_folder(void);

// 400plus entry point
int main(void) {
	// If TRASH button is pressed, do not initialize 400plus at all
	if (BTN_TRASH != BTN_PRESSED) {
		// Switch blue LED on, it will be switched back off after initialization
		LEDBLUE = LEDON;

		// COPY the hack to our memory
		hack_relocate();

		// hack the caches
		cache_hacks();
	}

	// Jump to Original FirmWare's entry point
	ofw_entry_point();

	// We never reach this line
	return 0;
}

// 0xAF: check the devinfo for more details on why this routine is needed
void hack_relocate(void) {
	int i;

	long *from = (long*) 0x800000;
	long *to   = (long*) 0x7E0000;

	for (i = 0; i < 0x8000; i++) {
		to[i] = from[i];
	}
}

void cache_hacks(void) {
	flush_caches();

	// lock the caches so nobody replaces our hacks
	cache_lock();

	// prevent the OFW from clearing the caches
	disable_cache_clearing();

	// OFW allocates main heap from addr:0x200000 to addr:0x800000
	// we place our hack at the last 128kb (0x20000) of this space, at addr: 0x7E0000 (see hack_relocate())
	// the original instruction was: MOV R1, #0x800000
	// we change it to: MOV R1, #0x7E0000 (in binary the instruction looks like: 0xE3A0187E)
	cache_fake(0xFF811318, 0xE3A0187E, TYPE_ICACHE);

	// hookup to dmProcInit(), so we can enable massive debug and run our hack_pre_init_hook
	cache_fake(0xFF8111AC, ASM_BL(0xFF8111AC, &hack_dmProcInit), TYPE_ICACHE);

	// hookup our MainCtrlInit
	//cache_fake(0xFF8110E4, ASM_BL(0xFF8110E4, &hack_MainCtrlInit), TYPE_ICACHE);

#ifdef ENABLE_DEBUG
	// hookup our GUI_IdleHandler
	cache_fake(0xFF82A4F0, ASM_BL(0xFF82A4F0, &hack_register_gui_idle_handler), TYPE_ICACHE);
#endif

	// hookup our Intercom
	cache_fake(0xFFA5D590, ASM_BL(0xFFA5D590, &hack_init_intercom_data), TYPE_ICACHE);

	// hookup StartConsole, so we can run our hack_post_init_hook
	cache_fake(0xFF8112E8, ASM_BL(0xFF8112E8, &hack_StartConsole), TYPE_ICACHE);
}

void disable_cache_clearing(void) {
	cache_fake(0xFF8101A0, ASM_NOP, TYPE_ICACHE);
	cache_fake(0xFFB3736C, ASM_NOP, TYPE_ICACHE);
	cache_fake(0xFFB37378, ASM_NOP, TYPE_ICACHE);
	cache_fake(0xFFB373EC, ASM_NOP, TYPE_ICACHE);
}

void hack_dmProcInit(void) {
	dmProcInit();

#ifdef ENABLE_MASSIVE_DEBUG
	// the 2nd level is 32 flags for debug classes
	// the 3rd arg is log level, 0 == full debug, >0 == less debug
	dmSetStoreLevel(hDbgMgr, 0xFF, 0);
	dmSetPrintLevel(hDbgMgr, 0xFF, 0);
#endif

	hack_pre_init_hook();
}

int hack_register_gui_idle_handler(void * org_proc, int zero) {
	return CreateCtrlMain(&hack_GUI_IDLEHandler, zero);
}

int hack_init_intercom_data(void *old_proc) {
	return InitIntercomData(intercom_proxy);
}

void hack_StartConsole(void) {
	hack_post_init_hook();

	// StartConsole does not return
	StartConsole();
}

// this is ran in the beginning of the OFW's task init process
void hack_pre_init_hook(void) {
	action_queue = (int*)CreateMessageQueue("action_queue", 0x40);
	CreateTask("Action Dispatcher", 25, 0x2000, action_dispatcher, 0);

	// Hack labels in some dialogs
	cache_fake(0xFF837FEC, ASM_BL(0xFF837FEC, &hack_item_set_label), TYPE_ICACHE);
	cache_fake(0xFF838300, ASM_BL(0xFF838300, &hack_item_set_label), TYPE_ICACHE);

	// Hack redraw on some dialogs, to prevent flickering when entering our menu
	cache_fake(0xFF916434, ASM_B(0xFF916434, &hack_dialog_redraw), TYPE_ICACHE);
}

// we can run extra code at the end of the OFW's task init
void hack_post_init_hook(void) {
	// Inject our hacked_TransferScreen
	//TransferScreen = hack_TransferScreen;

	//cache_fake(0xFF92DA50, ASM_BL(0xFF92DA50, &hack_FF92E704), TYPE_ICACHE);
	//cache_fake(0xFF92DA88, ASM_BL(0xFF92DA88, &hack_FF92E4C4), TYPE_ICACHE);

	// Intercept JUMP and TRASH buttons
	SetSendButtonProc(&hack_jump_trash_events, 0);

	// take over the vram copy locations, so we can invert the screen
	//cache_fake(0xFF92C5D8, ASM_BL(0xFF92C5D8, &hack_invert_olc_screen), TYPE_ICACHE);
	//cache_fake(0xFF92C5FC, ASM_BL(0xFF92C5FC, &hack_invert_olc_screen), TYPE_ICACHE);

	// prevent screen turn off on ptp (to see the debug on lcd)
	//cache_fake(0xFF9DE0DC, ASM_MOV_R0_INT(0), TYPE_ICACHE);

	// these freezes the usb communication
	//cache_fake(0xFF81B9D0, ASM_MOV_R0_INT(0), TYPE_ICACHE); // prevent ui lock
	//cache_fake(0xFF81B400, ASM_MOV_R0_INT(0), TYPE_ICACHE); // prevent ui lock
	//cache_fake(0xFF9DDB24, ASM_MOV_R0_INT(0), TYPE_ICACHE); // prevent ui lock
}

void hack_jump_trash_events(int r0, int r1, int button) {
	switch (button) {
	case 4: // JUMP_UP
		button_handler(BUTTON_RELEASE, TRUE);
		break;
	case 5: // JUMP_DOWN
		button_handler(BUTTON_JUMP, TRUE);
		break;
	case 8: // TRASH_UP
		button_handler(BUTTON_RELEASE, TRUE);
		break;
	case 9: // TRASH_DOWN
		button_handler(BUTTON_TRASH, TRUE);
		break;
	}
}

// Our own thread uses this dispatcher to execute tasks

void action_dispatcher(void) {
	action_t action;

	// Loop while receiving messages
	for (;;) {
		ReceiveMessageQueue(action_queue, &action, FALSE);
		action();
	}
}

void enqueue_action(action_t action) {
	TryPostMessageQueue(action_queue, (action), FALSE);
}

void start_up() {
	// Check and create our 400PLUS folder
	status.folder_exists = check_create_folder();

	// Recover persisting information
	persist_read();

	// Read settings from file
	settings_read();

	// If configured, start debug mode
	if (settings.debug_on_poweron)
		start_debug_mode();

	// If configured, restore AEB
	if (settings.persist_aeb)
		send_to_intercom(IC_SET_AE_BKT, persist.aeb);

	// Enable IR remote
	// i'm not sure where to call this? perhaps this isn't the right place.
	if (settings.remote_enable)
		remote_on();

	// Enable extended ISOs
	// Enable (hidden) CFn.8 for ISO H
	send_to_intercom(IC_SET_CF_EXTEND_ISO, 1);

	// Enable realtime ISO change
	send_to_intercom(IC_SET_REALTIME_ISO_0, 0);
	send_to_intercom(IC_SET_REALTIME_ISO_1, 0);

	// Set current language
	enqueue_action(lang_pack_init);

	// Read custom modes configuration from file
	enqueue_action(cmodes_read);

	// And optionally apply a custom mode
	enqueue_action(cmode_recall);

    // turn off the blue led after it was lighten by our hack_task_MainCtrl()
	eventproc_EdLedOff();

#ifdef MEMSPY
	debug_log("starting memspy task");
	CreateTask("memspy", 0x1e, 0x1000, memspy_task, 0);
#endif

#if 0
	debug_log("=== DUMPING DDD ===");
	printf_DDD_log( (void*)(int)(0x00007604+0x38) );

	debug_log("maindlg @ 0x%08X, handler @ 0x%08X", hMainDialog, hMainDialog->event_handler);

	debug_log("dumping");
	long *addr   = (long*) 0x7F0000;

	int file = FIO_OpenFile("A:/dump.bin", O_CREAT | O_WRONLY , 644);

	if (file != -1) {
		FIO_WriteFile(file, addr, 0xFFFF);
		FIO_CloseFile(file);
		beep();
	}
#endif
}

/*
 * Look for a "400PLUS" folder, and create it if it does not exist
 */

int check_create_folder(void)
{
    DIR *dirp;

	if ((dirp = opendir(FOLDER_PATH)) == NULL) {
		if(FIO_CreateDirectory(FOLDER_PATH)) {
			return FALSE;
		} else {
			return TRUE;
		}
    } else {
    	closedir(dirp);
    	return TRUE;
    }
}
