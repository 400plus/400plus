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

#define CMODES_MAX       16 // Max number of custom modes available
#define CMODES_MODES      7 // Number of auto modes where a custom mode may be used

#define CMODES_CONFIG  "A:/CMODES"    // File that contains custom modes configuration
#define CMODES_FILE    "A:/CMODES_%X" // Each file containing a snapshot for a custom mode
#define AMODES_FILE    "A:/AMODES_%c" // Each file containing a snapshot for an auto mode

#define CMODE_NONE -1

typedef struct {
	dpr_data_t   DPData;
	settings_t   settings;
	menu_order_t menu_order;
} snapshot_t;

typedef struct {
	int  recall_camera;
	int  recall_400plus;
	int  recall_ordering;
	int  recall_settings;
	int  recall_image;
	int  recall_cfn;
	int  order[CMODES_MAX];
	char names[CMODES_MAX][32];
	int  assign[CMODES_MODES];
} cmodes_config_t;

extern cmodes_config_t cmodes_config;

extern void cmodes_read    ();
extern void cmodes_write   ();
extern void cmodes_restore ();
extern void cmodes_delete  ();

extern int  cmode_read   (int id, snapshot_t *cmode);
extern int  cmode_write  (int id);
extern int  cmode_delete (int id);

extern int  amode_read   (AE_MODE ae_mode, snapshot_t *snapshot);
extern int  amode_write  (AE_MODE ae_mode);
extern int  amode_delete (AE_MODE ae_mode);

extern void snapshot_recall ();
extern void snapshot_apply  ();

extern void cmode_recall ();
extern void cmode_apply  ();

extern int  get_current_cmode();
extern void set_current_cmode(int cmode_id);

#endif /* SNAPSHOTS_H_ */
