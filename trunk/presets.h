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

#define PRESETS_VERSION 0x04
#define PRESETS_CONFIG  "A:/PRESETS"

#define PRESETS_FILE    "A:/PRESET_%u"
#define MODES_FILE      "A:/MODE_%c"

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
	int  order[9];
	char names[9][32];
	int  last_preset;
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

#endif /* PRESETS_H_ */
