/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdint.h>

#include "ptp.h"
#include "state_object.h"

#include "bmp.h"

extern _PtpMgr_t *hPtpMgr; // defined in camera.S

void ptp_dump_info() {

	state_object_t *ptp_state_object = hPtpMgr->state_object;

	lcd_printf(0,0, "matrix @ 0x%08X, %d inputs, %d states ", ptp_state_object->state_matrix, ptp_state_object->max_inputs, ptp_state_object->max_states);
	int i;
	int s;
	int x, y;
	for (i=0; i<ptp_state_object->max_inputs; i++) {
		for (s=0; s<ptp_state_object->max_states; s++) {
			int idx = s+i*ptp_state_object->max_states;
			y = ((idx) % 19)+1;
			x = ((float)((idx) / 19)<1) ? 0 : 22;
			lcd_printf(x,y, "%02d:%02d/%d:0x%08X[%d]", idx, i, s, STATE_FUNC(ptp_state_object, i, s), STATE_NEXT(ptp_state_object, i, s));
			if (idx>=37) goto out;
		}
	}
out:
	return;
}

