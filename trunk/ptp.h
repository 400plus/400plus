/**
 * $Revision: $
 * $Date: $
 * $Author: $
 */

#ifndef _PTP_H_
#define _PTP_H_

#include "state_object.h"

typedef struct {
	char *name;
	void *stage_class;
	state_object_t *state_object;
	void *debug_class;
	void *unk_0x10;
	void *pmgr_sync_event;
	void *unk_0x18;
	void *unk_0x1C;
	void *unk_0x20;
	void *ptp_sync_data_event_flag_struct;
	void *unk_0x28;
	void *unk_0x2C;
	void *block_64kb;
	void *unk_0x34;
	void *unk_0x38;
} _PtpMgr_t;

void ptp_dump_info();

#endif // _PTP_H_
