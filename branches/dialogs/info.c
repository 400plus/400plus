#include "main.h"
#include "firmware.h"

#include "info.h"

int  info_option = INFO_OPTION_FIRST;
char message[32] = "";

void info_refresh();

void info_option_next() {
	if (info_option == INFO_OPTION_LAST)
		info_option = INFO_OPTION_FIRST;
	else
		info_option++;

	info_refresh();
}

void info_option_prev() {
	if (info_option == INFO_OPTION_FIRST)
		info_option = INFO_OPTION_LAST;
	else
		info_option--;

	info_refresh();
}

void info_refresh() {
	dialog_set_property_str(hInfoCreative, 0x11, info_display());
	dialog_redraw(hInfoCreative);
}

char *info_display() {
	int i;
	SleepTask(50);

	switch (info_option) {
	case INFO_OPTION_CAPACITY:
		// im not sure why but calling GetDriveFreeSpace() and then pressing
		// a button too fast will freeze the camera... perhaps GDFS() gets interrupted
		// by the btns ISR, perhaps we should cache the result somehow and refresh it
		// on timed basis or when we take photo.
		if (!FP_GetDriveFreeSpace("A:", &i)) {
			SleepTask(150);
			//sprintf(message, "<> Free Space  :%8u KB", i);
			sprintf(message, "<> Free Space  :%5u.%2u MB", i/1024, (i%1024)/10);
		} else {
			sprintf(message, "<> Can't get FreeSpace (A:)");
		}
		break;
	case INFO_OPTION_RELEASE_COUNT:
		sprintf(message, "<> ReleaseCount: %u", FLAG_RELEASE_COUNT);
		break;
	case INFO_OPTION_400PLUS:
		if (VERSION < 20110101) {
			sprintf(message, "<> 400plus ver.: svn-%04u", VERSION);
		} else {
			sprintf(message, "<> 400plus ver.: %08u", VERSION);
		}
		break;
	case INFO_OPTION_BODY_ID:
		sprintf(message, "<> Body ID     : %010lu", BodyID);
		break;
	default:
		break;
	}

	return message;
}
