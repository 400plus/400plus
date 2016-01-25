#ifndef SNAPSHOTS_H_
#define SNAPSHOTS_H_

#include "settings.h"

#include "firmware/camera.h"

#define FILENAME_LENGTH 32

#define SNAPSHOT_VERSION 0x06

typedef struct {
	dpr_data_t   DPData;
	settings_t   settings;
	menu_order_t menu_order;
} snapshot_t;

extern int snapshot_read  (char names[][FILENAME_LENGTH], snapshot_t *snapshot);
extern int snapshot_write (char names[][FILENAME_LENGTH]);
extern int snapshot_delete(char names[][FILENAME_LENGTH]);

extern void snapshot_recall(snapshot_t *snapshot);
extern void snapshot_apply (snapshot_t *snapshot);

#endif /* SNAPSHOTS_H_ */
