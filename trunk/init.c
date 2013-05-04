/**
 * $Revision$
 * $Date$
 * $Author$
 */

// !!! IMPORTANT !!!
// Keep this code here in the beginning of the file, it is our entry point
asm(
	".text\n"
	".globl _start\n"
	"_start:\n"
	"B hack_entry_point\n"
);

#include <strings.h>
#include "cache_hacks.h"

#include "main.h"
#include "firmware.h"

#include "display.h"
#include "button.h"

void hack_halt();
void hack_relocate();
void cache_hacks();
void hack_StartConsole();
void hack_pre_init_hook();
void hack_post_init_hook();
void hack_dmProcInit();
void disable_cache_clearing();
void set_our_control_register();
int  hack_init_intercom_data(void * old_proc);
int  hack_register_gui_idle_handler(void * org_proc, int zero);


// this is ran in the beginning of the OFW's task init process
void hack_pre_init_hook() {
	initialize();
}

// we can run extra code at the end of the OFW's task init
void hack_post_init_hook() {
	TransferScreen = hack_TransferScreen;
	SetSendButtonProc(&hack_send_jump_and_trash_buttons, 0);

	// take over the vram copy locations, so we can invert the screen
	cache_fake(0xFF92C5D8, BL_INSTR(0xFF92C5D8, &hack_invert_olc_screen), TYPE_ICACHE);
	cache_fake(0xFF92C5FC, BL_INSTR(0xFF92C5FC, &hack_invert_olc_screen), TYPE_ICACHE);
}


// 400Plus entry point
void hack_entry_point() {
	if (BTN_TRASH != BTN_PRESSED) {
		LEDBLUE = LEDON;
		hack_relocate(); // COPY the hack to our memory
		cache_hacks(); // hack the caches
	}

	ofw_entry_point(); // jump to Original FirmWare's entry point
}

void hack_relocate() {
	// 0xAF: check the devinfo for more details on why this routine is needed
	int i;
	long *from = (long*) 0x800000;
	long *to   = (long*) 0x7E0000;

	for (i = 0; i < 0x8000; i++) {
		to[i] = from[i];
	}
}

void cache_hacks() {
	flush_caches();

	//cache_lock(); // lock the caches so nobody replaces our hacks
	icache_lock();

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

	// hookup our GUI_IdleHandler
	cache_fake(0xFF82A4F0, BL_INSTR(0xFF82A4F0, &hack_register_gui_idle_handler), TYPE_ICACHE);

	// hookup our Intercom
	cache_fake(0xFFA5D590, BL_INSTR(0xFFA5D590, &hack_init_intercom_data), TYPE_ICACHE);

	// hookup StartConsole, so we can run our hack_post_init_hook
	cache_fake(0xFF8112E8, BL_INSTR(0xFF8112E8, &hack_StartConsole), TYPE_ICACHE);
}

void disable_cache_clearing() {
	// the camera is reseting the control register
	// i dont know if this code is already ran, when we poison the caches
	// keep it here just in case (do some testing)
	//cache_fake(0xFF810194, BL_INSTR(0xFF810194, &set_our_control_register), TYPE_ICACHE);

	//cache_fake(0xFF810AA8, MOV_R0_1_INSTR, TYPE_ICACHE);
	// we do not remove the whole routine, remove only the call to sub_FFB5DC58:
	//cache_fake(0xFFB45E2C, NOP_INSTR, TYPE_ICACHE); // i cache
	// actually, we do not need to remove this call too, since the hacks below will take care of it
	// keep it here just in case (do some testing)

	cache_fake(0xFF8101A0, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB3736C, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB37378, NOP_INSTR, TYPE_ICACHE); // i cache
	cache_fake(0xFFB373EC, NOP_INSTR, TYPE_ICACHE); // i cache

	// D cache clearing addresses: FF8101A4, FFB30028, FFB372EC, FFB3731C, FFB37334, FFB37358, FFB37360, FFB373A4, FFB373C8
}

void hack_dmProcInit() {
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

void hack_StartConsole() {
	hack_post_init_hook();
	StartConsole(); // should be the last one
}

int hack_register_gui_idle_handler(void * org_proc, int zero) {
	return CreateCtrlMain(&hack_GUI_IDLEHandler, zero);
}

#define busy_wait() do { volatile uint32_t i; for (i = 0; i < 1000000; i++); } while (0)
void hack_halt() {
	while ( 1 ) {
		LEDBLUE = LEDON;
		LEDRED  = LEDOFF;
		busy_wait();

		LEDBLUE = LEDOFF;
		LEDRED  = LEDON;
		busy_wait();
	}
}

// 0xAF: keep this in case we need it.
// after some testing, if everything is ok, we can remove it
#if 0
void set_our_control_register() {
	asm volatile (
		//"MOV  R1, #0x78           \n" // OFW was setting bit 3:6 only (reserved)
		"MOV    R1, #0              \n" // we set few bits more
		//"MRC  p15, 0, R1,c1,c0, 0 \n"

		"ORR    R1, R1, #0x01       \n" // MPU - we need it, otherwise it will disable the caches
		"ORR    R1, R1, #0x04       \n" // D Cache - w/o this the data is slow
		"ORR    R1, R1, #0x08       \n" // reserved - OFW requested
		"ORR    R1, R1, #0x10       \n" // reserved - OFW requested
		"ORR    R1, R1, #0x20       \n" // reserved - OFW requested
		"ORR    R1, R1, #0x40       \n" // reserved - OFW requested
		"ORR    R1, R1, #0x1000     \n" // I Cache - we wont have cache hacks w/o this
		"ORR    R1, R1, #0x10000    \n" // D TCM - these would be set by the OFW later
		"ORR    R1, R1, #0x40000    \n" // I TCM - these would be set by the OFW later
		"MCR    p15, 0, R1,c1,c0, 0 \n"
	);
}
#endif

