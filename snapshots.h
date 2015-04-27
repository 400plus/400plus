#ifndef SNAPSHOTS_H_
#define SNAPSHOTS_H_

#include "settings.h"

#include "firmware/camera.h"

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

extern void snapshot_recall(snapshot_t *snapshot);
extern void snapshot_apply (snapshot_t *snapshot);

#endif /* SNAPSHOTS_H_ */
