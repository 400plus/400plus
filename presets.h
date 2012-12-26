/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef PRESETS_H_
#define PRESETS_H_

#include <camera.h>

#include "settings.h"

#define FILENAME_LENGTH 16

#define PRESETS_VERSION 0x06
#define PRESETS_MAX       16
#define PRESETS_MODES      7

#define PRESETS_CONFIG  "A:/PRESETS"
#define PRESETS_FILE    "A:/PRESET_%X"
#define MODES_FILE      "A:/MODE_%c"

#define PRESET_NONE -1

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
	int  order[PRESETS_MAX];
	char names[PRESETS_MAX][32];
	int  assign[PRESETS_MODES];
} presets_config_t;

extern presets_config_t presets_config;

extern void presets_read    ();
extern void presets_write   ();
extern void presets_restore ();
extern void presets_delete  ();

extern int  preset_read   (int id, snapshot_t *preset);
extern int  preset_write  (int id);
extern int  preset_delete (int id);

extern int  mode_read   (AE_MODE ae_mode, snapshot_t *snapshot);
extern int  mode_write  (AE_MODE ae_mode);
extern int  mode_delete (AE_MODE ae_mode);

extern void snapshot_recall ();
extern void snapshot_apply  ();

extern void preset_recall ();
extern void preset_apply  ();

extern int  get_current_preset();
extern void set_current_preset(int preset);

#endif /* PRESETS_H_ */
