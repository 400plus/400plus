/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef SNAPSHOTS_H_
#define SNAPSHOTS_H_

#include <camera.h>

#include "settings.h"

#define FILENAME_LENGTH 16

#define SNAPSHOT_VERSION 0x06

typedef struct {
	dpr_data_t   DPData;
	settings_t   settings;
	menu_order_t menu_order;
} snapshot_t;

extern int snapshot_read  (char *name, snapshot_t *snapshot);
extern int snapshot_write (char *name);
extern int snapshot_delete(char *name);

extern void snapshot_recall ();
extern void snapshot_apply  ();

#endif /* SNAPSHOTS_H_ */
