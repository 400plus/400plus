//#include <vxworks.h>
//#include <string.h>
//#include <ioLib.h>
//#include <clock.h>
//#include <time.h>

#include "main.h"
#include "macros.h"
#include "debug.h"

#include "firmware.h"
#include "firmware/camera.h"

#include "shutter.h"

void lock_sutter     (void);
void wait_for_shutter(void);

void lock_sutter(void) {
	shutter_lock = TRUE;
}

void wait_for_shutter(void) {
	while (shutter_lock)
		SleepTask(RELEASE_WAIT);
}

void wait_for_camera() {
	while (! able_to_release())
		SleepTask(RELEASE_WAIT);
}

int shutter_release() {
	wait_for_camera();
	lock_sutter    ();

	int result = press_button(IC_BUTTON_FULL_SHUTTER);

	if (DPData.drive == DRIVE_MODE_TIMER)
		SleepTask(SELF_TIMER_MS);

	wait_for_shutter();

	return result;
}

int shutter_release_bulb(int time) {
	static int first = TRUE;

	int  button;
	long delay;

	int shutter_lag, mirror_lag;

	if (first) {
		first = FALSE;
		shutter_lag = SHUTTER_LAG_1ST;
		mirror_lag  = MIRROR_LAG_1ST;
	} else {
		shutter_lag = SHUTTER_LAG_2ND;
		mirror_lag  = MIRROR_LAG_2ND;
	}

	if (DPData.drive == DRIVE_MODE_TIMER) {
		button = IC_BUTTON_FULL_SHUTTER;
		delay  = time + shutter_lag + mirror_lag;
	} else {
		button = IC_BUTTON_HALF_SHUTTER;
		delay  = time + shutter_lag;
	}

	wait_for_camera();
	lock_sutter    ();

	press_button(button);
	SleepTask   (delay);
	press_button(button);

	wait_for_shutter();

	return 0;
}
