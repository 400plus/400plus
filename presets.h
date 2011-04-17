#ifndef PRESETS_H_
#define PRESETS_H_

#define PRESET_FILE     "A:/PRESET_%u"

extern int  preset_read (int id);
extern void preset_write(int id);
extern void preset_apply();

#endif /* PRESETS_H_ */
