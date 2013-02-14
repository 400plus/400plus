/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include <clock.h>
#include <camera.h>

#include "main.h"
#include "macros.h"

#include "float.h"
#include "languages.h"
#include "settings.h"
#include "debug.h"

#include "utils.h"

void lock_sutter     ();
void wait_for_shutter();

void display_float(char *dest, float value);

void calculate_dof(int focal_length, int focus_distance, int av, char *min, char *max) {
	float fl =    1.0f * focal_length;
	float fd = 1000.0f * focus_distance;

	float fn = float_pow(2.0f, ((float)av / 8.0f - 1) / 2.0f); // Precise F-Number = 2^(n/2), 1/8 EV resolution
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

void dump_log() {
	debug_log("Dumping the log.\n");
	dumpf();
	beep();
}

#ifdef MEM_DUMP
void dump_memory() {
	char filename[20] = "A:/12345678.MEM";
	time_t t;
	struct tm tm;

	time(&t);
	localtime_r(&t, &tm);

	sprintf(filename, "A:/%02d%02d%02d%02d.MEM", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	debug_log("Dumping memory to %s.\n", filename);
	int file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644);

	if (file == -1) {
		debug_log("ERROR: can't open file for writing (%s)", filename);
		beep();
		beep();
	} else {
		int addr=0;
		int power_off_state = DPData.auto_power_off;

		send_to_intercom(IC_SET_AUTO_POWER_OFF, false);

		while (addr<0x800000) { // dump 8MB of RAM
			char buf[0x800];
			// i don't know why, but if we try to pass the mem address (addr) directly to
			// FIO_WriteFile, we get zero-filled file... so we need local buffer as a proxy
			// note: do not increase the size of the local buffer too much, because it is in the stack
			LEDBLUE ^= 2;
			memcpy(buf, (void*)addr, 0x800);
			FIO_WriteFile(file, buf, 0x800);
			addr += 0x800;
		}
		FIO_CloseFile(file);

		send_to_intercom(IC_SET_AUTO_POWER_OFF, power_off_state);
	}
	beep();
}
static void mem_dumper_task() {
	int i;

	beep();

	for (i=0; i<10; i++) {
		LEDBLUE ^= 2;
		SleepTask(500);
	}

	dump_memory();
}
void dump_memory_after_5s() {
	CreateTask("memdumper", 0x1e, 0x1000, mem_dumper_task, 0);
}
#endif
void print_info() {
	// print some info to the log
	eventproc_RiseEvent("about");

	// print last errors to the log
	eventproc_RiseEvent("PrintICUInfo");

	// print current DP settings to the log
	eventproc_RiseEvent("PrintDPStatus");

	beep();
	debug_log("Info dumped.\n");
}

void start_debug_mode() {
	int file;
	char filename[20] = "A:/DEBUG.LOG"; // default name
	//int filesize;
	time_t t;
	struct tm tm;

	time(&t);
	localtime_r(&t, &tm);

	if (settings.logfile_mode == LOGFILE_MODE_NEW)
		sprintf(filename, "A:/%02d%02d%02d%02d.LOG", tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);

	// O_APPEND is not working in VxWorks, so we seek to the end later
	file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644);
	if(file > 0) {
		if (settings.logfile_mode == LOGFILE_MODE_APPEND)
			FIO_SeekFile(file, 0, 2/*SEEK_END*/);

		// redirect stdout and stderr to our file
		ioGlobalStdSet(1, file);
		ioGlobalStdSet(2, file);
	}

	char separator[] = "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
	printf(separator);
	printf("::::: %04d-%02d-%02d %02d:%02d:%02d :::::\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf(separator);
	printf("\n");

	beep();
}

int send_to_intercom(int message, int parm) {
	int result, length = 1;

	switch (message) {
	case IC_SET_AE:
		status.ignore_msg = IC_SETTINGS_0;
		break;
	case IC_SET_AV_VAL:
	case IC_SET_TV_VAL:
		status.ignore_msg = message;
		break;
	case IC_RELEASE:
	case IC_SET_REALTIME_ISO_0:
	case IC_SET_REALTIME_ISO_1:
		length = 0;
		break;
	case IC_SET_ISO:
	case IC_SET_AF_POINT:
	case IC_SET_COLOR_TEMP:
		length = 2;
		break;
	}

	result = SendToIntercom(message, length, parm);
	SleepTask(INTERCOM_WAIT);

	return result;
}

#if 0
// this is a disassembled version of eventproc_release()
int shutter_release_disasm() {

	extern char * aRelSem;

	if (hRelSem == 0) {
		hRelSem = CreateBinarySemaphore(aRelSem, 0);
	}

	SendToIntercom(IC_RELEASE, 0, 0);
	SendToIntercom(0x6D, 1, 1); // set burst counter

	TakeSemaphore(hRelSem, 30000);
	DeleteSemaphore(hRelSem);
	hRelSem = 0;

	SleepTask(EVENT_WAIT); // we added this
	return 0;
}
#endif

void lock_sutter() {
	shutter_lock = true;
}

void wait_for_shutter() {
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
	static int first = true;

	int  button;
	long delay;

	int shutter_lag, mirror_lag;

	if (first) {
		first = false;
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
	SleepTask(EVENT_WAIT);

	return result;
}

int remote_off() {
	int result = eventproc_RemOff();
	SleepTask(EVENT_WAIT);

	return result;
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
char * my_fgets_faster(char *s, int n, int fd) {
	register char *cs;

	static unsigned char buf[256]; // local buffer
	static unsigned char bpos = 0; // position in the buffer
	int rc = 0;                    // last return code from read()

	if (fd == -1) { // init
		buf[0] = 0;
		bpos = 0;
		return NULL;
	}

	cs = s;
	while (--n > 0 && ( bpos || (rc = read(fd, &buf, 255)) ) ) {
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
char * my_fgets_simple_but_slow(char *s, int n, int fd) {
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
