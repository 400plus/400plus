#include <vxworks.h>
#include <string.h>
#include <clock.h>
#include <time.h>
#include <ioLib.h>

#include "firmware.h"
#include "firmware/gui.h"
#include "firmware/eventproc.h"

#include "main.h"
#include "macros.h"

#include "float.h"
#include "languages.h"
#include "settings.h"
#include "debug.h"
#include "intercom.h"

#include "utils.h"

void display_float(char *dest, float value);

void calculate_dof(int focal_length, int focus_distance, int av, char *min, char *max) {
	float fl =    1.0f * focal_length;
	float fd = 1000.0f * focus_distance;

	float fn = float_pow2(((float)av / 8.0f - 1) / 2.0f); // Precise F-Number = 2^(n/2), 1/8 EV resolution
	float cof = 0.019f; // Circle of confusion

	// Hyperfocal
	float hf  = fl + fl * fl / (fn * cof);
	float aux = fd * (hf - fl) / 1000.0f;

	// Min distance
	display_float(min, aux / (hf + fd - 2.0f * fl));

	// Max distance
	if (hf >= fd)
		display_float(max, aux / (hf - fd));
	else
		sprintf(max, "%s", LP_WORD(L_S_INFINITE));
}

void display_float(char *dest, float value) {
	if (value > 9999.0f)
		sprintf(dest, "%i.",     9999);
	else if (value > 999.9f)
		sprintf(dest, "%i.",     (int)value);
	else if (value > 99.99f)
		sprintf(dest, "%i.%01i", (int)value, (int)(10.0f * value) % 10);
	else if (value > 9.999f)
		sprintf(dest, "%i.%02i", (int)value, (int)(100.0f * value) % 100);
	else
		sprintf(dest, "%i.%03i", (int)value, (int)(1000.0f * value) % 1000);
}

void beep() {
	if (DPData.beep) {
		eventproc_RiseEvent("RequestBuzzer");
		SleepTask(EVENT_WAIT);
	}

	led_flash(BEEP_LED_LENGTH);
}

void enter_factory_mode() {
	EnterFactoryMode();
}

void exit_factory_mode() {
	ExitFactoryMode();
	beep();
}

int print_icu_info() {
	int result = eventproc_PrintICUInfo();
	SleepTask(EVENT_WAIT);

	return result;
}

int press_button(int button) {
	int result = IntercomHandlerButton(button, 0); // takes 2 args...
	SleepTask(EVENT_WAIT);

	return result;
}

int remote_on() {
	int result = eventproc_RemOn();
	// disable MLU, since it's not working correctly with IR
	send_to_intercom(IC_SET_CF_MIRROR_UP_LOCK, 0);
	SleepTask(EVENT_WAIT);

	return result;
}

int remote_off() {
	int result = eventproc_RemOff();
	SleepTask(EVENT_WAIT);

	return result;
}

void remote_delay(int x) {
	if (x) {
		RemReleaseSelfMax = 4500;
		RemReleaseInstMin = 5560;
	} else {
		RemReleaseSelfMax = 6160;
		RemReleaseInstMin = 7410;
	}
}

int display_on() {
	int result = SetTurnDisplayEvent_1_after_2();
	SleepTask(EVENT_WAIT);

	return result;
}

int display_off() {
	int result = SetTurnDisplayEvent_2_after_1();
	SleepTask(EVENT_WAIT);

	return result;
}

void led_flash(int duration) {
	eventproc_EdLedOn();
	SleepTask(EVENT_WAIT);

	SleepTask(duration);

	eventproc_EdLedOff();
	SleepTask(EVENT_WAIT);
}

int strlen_utf8(const char *s) {
	int i = 0, j = 0;

	while (s[i])
		if ((s[i++] & 0xc0) != 0x80)
			j++;

	return j;
}

// convert string to upper case in-place
void stoupper(char *s) {
	while (*s) {
		if(('a' <= *s) && (*s <= 'z')) {
			*s = 'A' + (*s - 'a');
		}
		s++;
	}
}

int timestamp() {
	static long long base = 0;
	struct timespec now_ts;
	long long now_ms;

	clock_gettime(0, &now_ts);

	now_ms = (long long)now_ts.tv_sec * 1000LL + (long long)now_ts.tv_nsec / 1000000LL;

	if (base == 0) {
		base = now_ms;
	}

	return (int)(now_ms - base);
}

// comes from ini.c
/* Version of strncpy that ensures dest (size bytes) is null-terminated. */
char* strncpy0(char* dest, const char* src, size_t size) {
	strncpy(dest, src, size);
	dest[size - 1] = '\0';
	return dest;
}

// so basically this is a speed-up version which reads 255 bytes at a time
// and use local buffer and local position pointer, sort of mmap'ed part of file.
// the benefit is obvious: speed
// the drawbacks are:
// 1.the routine needs to be informed when a new file
// is being parsed, so it will reset the local buffer
// this is done by calling the routine with FD == -1, it is sort of init call.
// you will have to init everytime you open a new file, before the first real call
// 2. cannot use it in multi-thread/multi-task. use it only at one place in one time.
char *hack_fgets_faster(char *s, int n, int fd) {
	register char *cs;

	// TODO: Do not explicitly overflow an unsigned char
	static char buf[256]; // local buffer
	static unsigned char bpos = 0; // position in the buffer
	int rc = 0;                    // last return code from read()

	if (fd == -1) { // init
		buf[0] = 0;
		bpos = 0;
		return NULL;
	}

	cs = s;
	while (--n > 0 && ( bpos || (rc = read(fd, buf, 255)) ) ) {
		unsigned char c;
		if (rc < 255)
			buf[rc] = '\0';

		if ((c = buf[bpos++]) == 0) {
			if (!bpos) // bpos was 255, continue to the next read()
				continue;
			else  // bpos was not 255, it's the end of the file
				break;
		}

		if (c != '\r')
			*cs++ = c;

		if (c == '\n')
			break;

	}
	*cs = '\0';

	if (cs == s)
		return NULL;

	return s;
}

#ifdef FGETS_USE_SLOW
char * hack_fgets_simple_but_slow(char *s, int n, int fd) {
	register char *cs;
	unsigned char c;

	cs = s;
	while (--n > 0 && read_(fd, &c, 1)) {
		if (c != '\r')
			*cs++ = c;

		if (c == '\n')
			break;
	}
	*cs = '\0';

	if (cs == s)
		return NULL;

	return s;
}
#endif
