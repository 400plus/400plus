#include "main.h"
#include "firmware.h"

#include "info.h"

int  info_option = INFO_OPTION_FIRST;
char message[32] = "";

void info_refresh();

void info_switch() {
	if (info_option == INFO_OPTION_LAST)
		info_option = INFO_OPTION_FIRST;
	else
		info_option++;

	info_refresh();
}

void info_refresh() {
  sub_FF837FA8(hInfoCreative, 0x11, info_display());
  do_some_with_dialog(hInfoCreative);
}

char *info_display() {
	SleepTask(50);

	switch (info_option) {
	case INFO_OPTION_CAPACITY:
		return sub_FF83A640();
	case INFO_OPTION_RELEASE_COUNT:
		sprintf(message, "Release count   : %u", FLAG_RELEASE_COUNT);
		break;
	case INFO_OPTION_400PLUS:
		sprintf(message, "400plus version : %u", VERSION);
		break;
	default:
		break;
	}

	return message;
}
