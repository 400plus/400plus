#include "vxworks/vxworks.h"
#include "vxworks/stdint.h"

#include "bmp.h"
#include "ptp.h"
#include "state_object.h"
#include "utils.h"

extern manager_t *hPtpMgr; // defined in camera.S

static int (*StateTransition)(void*,void*,int,int,int) = 0;

int hack_state_transition(state_object_t * self, manager_t *manager, int input, int event_flag_func, int some_struct);

int hack_state_transition(
	state_object_t * self,
	manager_t *manager,
	int input,
	int event_flag_func,  // some function to set event flag
	int some_struct // some struct for transition maybe ???
) {
	static int l=0;
	int old_state = self->current_state;
	int res = StateTransition(self, manager, input, event_flag_func, some_struct);
	int new_state = self->current_state;

	//UILock(0, 2);
	//PTP_SetUILock(0, 2);
	//PTP_ResetUILock(0);

	lcd_printf(0, l % 20, "[%03d] O:%08X R:%08X N:%08X", l, old_state, res, new_state);
	printf_log(8,8, "[400Plus-PTP] [%03d] O:%08X R:%08X N:%08X", l, old_state, res, new_state);
	//bmp_hexdump(VramAddress, FONT_SMALL, 0, l*16, a4, 64);

	l++;

	return res;
}

void ptp_dump_info(void) {

	state_object_t *so = hPtpMgr->state_object;

	if (!StateTransition) {
		StateTransition = (void *)so->state_object_handler;
	} else if ((void*)StateTransition != (void*)so->state_object_handler) { // check if all states use the same function (they do, in theory)
		beep(); beep(); beep(); beep(); beep();
	}

	so->state_object_handler = (void *)&hack_state_transition;



	/*
	if ((uint32_t)(ptp_state_object->state_matrix) & 0xFF000000) // that's in ROM, make a copy to allow patching
		state_object_matrix_copy_for_patching(ptp_state_object);

	lcd_printf(0,0, "matrix @ 0x%08X, %d inputs, %d states ", ptp_state_object->state_matrix, ptp_state_object->max_inputs, ptp_state_object->max_states);
	int i, s, x, y, cnt = 0;
	for (i=0; i<ptp_state_object->max_inputs; i++) {
		for (s=0; s<ptp_state_object->max_states; s++) {
			if (STATE_FUNC(ptp_state_object, i, s) == &PTP_Actions) {
				state_object_install_hook(ptp_state_object, i, s, &hack_ptp_actions);

				y = ((cnt) % 19)+1;
				x = ((float)((cnt) / 19)<1) ? 0 : 22;
				cnt++;
				lcd_printf(x,y, "%02d:%02d/%d:0x%08X[%d]", cnt, i, s, STATE_FUNC(ptp_state_object, i, s), STATE_NEXT(ptp_state_object, i, s));
			}
		}
	}
	*/
}

/*
state_object_t * hack_ptp_actions(
	state_object_t * self,
	void * arg1, // some functoin @ 0xff9e6638
	void * arg2, // point to 0x4af2dc
	void * arg3, // this function address
	void * arg4  // point to 0x241a0
) {

	int old_state = self->current_state;

	//lcd_printf(0,0, "ptpmgr: 0x%08X", hPtpMgr);
	lcd_printf(0, 1, "[0x%08X]=%08X [0x%08X]=%08X", arg1, *((uint32_t*)arg1), arg2, *((uint32_t*)arg2));
	lcd_printf(0, 2, "[0x%08X]=%08X [0x%08X]=%08X", arg3, *((uint32_t*)arg3), arg4, *((uint32_t*)arg4));
	bmp_hexdump(VramAddress, FONT_SMALL, 0, 3*16, arg4, 64);
	return PTP_Actions(self, arg1, arg2, arg3, arg4);
}
*/
