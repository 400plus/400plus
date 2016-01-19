#include "cache_hacks.h"

#include "main.h"
#include "firmware.h"

#include "display.h"
#include "button.h"

void hack_entry_point(void);

void hack_halt    (void);
void hack_relocate(void);

void cache_hacks(void);

void hack_StartConsole  (void);
void hack_pre_init_hook (void);
void hack_post_init_hook(void);

void hack_dmProcInit(void);

void disable_cache_clearing(void);

int  hack_init_intercom_data       (void * old_proc);
int  hack_register_gui_idle_handler(void * org_proc, int zero);

#define busy_wait() do { volatile uint32_t i; for (i = 0; i < 1000000; i++); } while (0)

// this is ran in the beginning of the OFW's task init process
void hack_pre_init_hook(void) {
	initialize();
}

// we can run extra code at the end of the OFW's task init
void hack_post_init_hook(void) {
	// Inject our hacked_TransferScreen
	//TransferScreen = hack_TransferScreen;

	//cache_fake(0xFF92DA50, BL_INSTR(0xFF92DA50, &hack_FF92E704), TYPE_ICACHE);
	//cache_fake(0xFF92DA88, BL_INSTR(0xFF92DA88, &hack_FF92E4C4), TYPE_ICACHE);

	// Inject hack_send_jump_and_trash_buttons
	SetSendButtonProc(&hack_send_jump_and_trash_buttons, 0);
/*
	// take over the vram copy locations, so we can invert the screen
	cache_fake(0xFF92C5D8, BL_INSTR(0xFF92C5D8, &hack_invert_olc_screen), TYPE_ICACHE);
	cache_fake(0xFF92C5FC, BL_INSTR(0xFF92C5FC, &hack_invert_olc_screen), TYPE_ICACHE);
*/
	// prevent screen turn off on ptp (to see the debug on lcd)
	cache_fake(0xFF9DE0DC, MOV_R0_0_INSTR, TYPE_ICACHE);

	// these freezes the usb communication
	//cache_fake(0xFF81B9D0, MOV_R0_0_INSTR, TYPE_ICACHE); // prevent ui lock
	//cache_fake(0xFF81B400, MOV_R0_0_INSTR, TYPE_ICACHE); // prevent ui lock
	//cache_fake(0xFF9DDB24, MOV_R0_0_INSTR, TYPE_ICACHE); // prevent ui lock
}


// 400Plus entry point
void hack_entry_point(void) {
	if (BTN_TRASH != BTN_PRESSED) {
		LEDBLUE = LEDON;
		hack_relocate(); // COPY the hack to our memory
		cache_hacks(); // hack the caches
	}

	ofw_entry_point(); // jump to Original FirmWare's entry point
}

void hack_relocate(void) {
	// 0xAF: check the devinfo for more details on why this routine is needed
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
	cache_fake(0xFF8111AC, BL_INSTR(0xFF8111AC, &hack_dmProcInit), TYPE_ICACHE);

	// hookup our MainCtrlInit
	//cache_fake(0xFF8110E4, BL_INSTR(0xFF8110E4, &hack_MainCtrlInit), TYPE_ICACHE);

#ifdef ENABLE_DEBUG
	// hookup our GUI_IdleHandler
	cache_fake(0xFF82A4F0, BL_INSTR(0xFF82A4F0, &hack_register_gui_idle_handler), TYPE_ICACHE);
#endif

	// hookup our Intercom
	cache_fake(0xFFA5D590, BL_INSTR(0xFFA5D590, &hack_init_intercom_data), TYPE_ICACHE);

	// hookup StartConsole, so we can run our hack_post_init_hook
	cache_fake(0xFF8112E8, BL_INSTR(0xFF8112E8, &hack_StartConsole), TYPE_ICACHE);

	// Hack items in dialogs
	cache_fake(0xFF838300, BL_INSTR(0xFF838300, &hack_item_set_label_int), TYPE_ICACHE);
	cache_fake(0xFF837FEC, BL_INSTR(0xFF837FEC, &hack_item_set_label_str), TYPE_ICACHE);
}

void disable_cache_clearing(void) {
	cache_fake(0xFF8101A0, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB3736C, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB37378, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB373EC, NOP_INSTR, TYPE_ICACHE); // i cache
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

int hack_init_intercom_data(void * old_proc) {
	return InitIntercomData(intercom_proxy);
}

void hack_StartConsole(void) {
	hack_post_init_hook();
	StartConsole(); // should be the last one
}

#ifdef ENABLE_DEBUG
int hack_register_gui_idle_handler(void * org_proc, int zero) {
	return CreateCtrlMain(&hack_GUI_IDLEHandler, zero);
}
#endif

void hack_halt(void) {
	while ( 1 ) {
		LEDBLUE = LEDON;
		LEDRED  = LEDOFF;
		busy_wait();

		LEDBLUE = LEDOFF;
		LEDRED  = LEDON;
		busy_wait();
	}
}


