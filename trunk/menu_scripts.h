/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MENU_SCRIPTS_H_
#define MENU_SCRIPTS_H_

extern menupage_t menupage_scripts;

#define MENU_SCRIPTS_FL 50 // DOF calculator: initial focal length (mm)
#define MENU_SCRIPTS_FD 10 // DOF calculator: initial focusing distance (m)

typedef enum {
	VIDEO_FORMAT_25FPS,
	VIDEO_FORMAT_30FPS,
	VIDEO_FORMAT_50FPS,
	VIDEO_FORMAT_60FPS,
	VIDEO_FORMAT_COUNT,
	VIDEO_FORMAT_FIRST = 0,
	VIDEO_FORMAT_LAST  = VIDEO_FORMAT_COUNT - 1
} type_VIDEO_FORMAT;

#endif /* MENU_SCRIPTS_H_ */
