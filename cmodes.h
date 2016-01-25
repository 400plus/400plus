#ifndef CMODES_H_
#define CMODES_H_

#include "snapshots.h"

#include "firmware/camera.h"

#define CMODES_MAX       16 // Max number of custom modes available
#define CMODES_MODES      7 // Number of auto modes where a custom mode may be used

#define CMODES_CONFIG  "CMODES"    // File that contains custom modes configuration
#define CMODES_FILE    "CMODES_%X" // Each file containing a snapshot for a custom mode
#define AMODES_FILE    "AMODES_%c" // Each file containing a snapshot for an auto mode

#define CMODE_NONE -1

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

extern void cmodes_read    (void);
extern void cmodes_write   (void);
extern void cmodes_restore (void);
extern void cmodes_delete  (void);

extern int  cmode_read   (int id, snapshot_t *cmode);
extern int  cmode_write  (int id);
extern int  cmode_delete (int id);

extern void cmode_recall (void);
extern void cmode_apply  (void);

extern int  get_current_cmode(void);
extern void set_current_cmode(int cmode_id);

#endif /* CMODES_H_ */
