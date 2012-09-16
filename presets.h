/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef PRESETS_H_
#define PRESETS_H_

#include <camera.h>

#include "settings.h"

#define PRESETS_VERSION 0x02
#define PRESETS_CONFIG  "A:/PRESETS"
#define PRESETS_FILE    "A:/PRESET_%u"

typedef struct {
	dpr_data_t     camera_mode;
	type_SETTINGS  settings;
} type_PRESET;

typedef struct {
	int  use_adep;
	int  recall_camera;
	int  recall_400plus;
	int  recall_settings;
	int  recall_image;
	int  recall_cfn;
	int  order[9];
	char names[9][32];
} type_PRESETS_CONFIG;

extern type_PRESETS_CONFIG presets_config;

extern void presets_read();
extern void presets_write();

extern int  preset_read (int id);
extern int  preset_write(int id);
extern void preset_apply();
extern void preset_apply_full();
extern void preset_recall();
extern void preset_recall_full();

extern void get_preset_filename(char *filename, int id);

#endif /* PRESETS_H_ */
