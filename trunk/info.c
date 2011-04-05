#include "main.h"
#include "firmware.h"

#include "info.h"

char message[32];

char *release_count() {
	SleepTask(50);

	sprintf(message, "Release count : %u", FLAG_RELEASE_COUNT);

	return message;
}
