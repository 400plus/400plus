#ifndef SHUTTER_H
#define SHUTTER_H

#define RELEASE_WAIT    250

#define SHUTTER_LAG_1ST 250
#define SHUTTER_LAG_2ND 100

#define MIRROR_LAG_1ST 2000
#define MIRROR_LAG_2ND 2100

extern void wait_for_camera(void);

extern int  shutter_release      (void);
extern int  shutter_release_bulb (int time);

#endif /* UTILS_H_ */
