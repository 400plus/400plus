#include "main.h"
#include "firmware.h"

#include "languages.h"
#include "settings.h"
#include "utils.h"

#include "debug.h"

int ev_normalize(int ev);

static char *av_strings[][4] = {
	{"1.0", "1.1", "1.2", "1.3"},
	{"1.4", "1.5", "1.7", "1.8"},
	{"2.0", "2.2", "2.5", "2.5"},
	{"2.8", "3.2", "3.5", "3.5"},
	{"4.0", "4.5", "4.5", "5.0"},
	{"5.6", "6.3", "6.7", "7.1"},
	{"8.0", "9.0", "9.5",  "10"},
	{ "11",  "13",  "13",  "14"},
	{ "16",  "18",  "19",  "20"},
	{ "22",  "25",  "27",  "29"},
	{ "32",  "36",  "38",  "40"},
	{ "45",  "48",  "52",  "60"},
};

static char *tv_strings[][4] = {
	{   "32'",       "",       "",       ""},
	{   "16'",       "",       "",       ""},
	{    "8'",       "",       "",       ""},
	{    "4'",       "",       "",       ""},
	{    "2'",       "",       "",       ""},
	{    "1'",       "",       "",       ""},
	{  "30\"",   "25\"",   "20\"",   "20\""},
	{  "15\"",   "13\"",   "10\"",   "10\""},
	{   "8\"",    "6\"",    "6\"",    "5\""},
	{   "4\"",   "3\"2",    "3\"",   "2\"5"},
	{   "2\"",   "1\"6",   "1\"5",   "1\"3"},
	{   "1\"",   "0\"8",   "0\"7",   "0\"6"},
	{  "0\"5",   "0\"4",   "0\"3",   "0\"3"},
	{   "1/4",    "1/5",    "1/6",    "1/6"},
	{   "1/8",   "1/10",   "1/10",   "1/13"},
	{  "1/15",   "1/20",   "1/20",   "1/25"},
	{  "1/30",   "1/40",   "1/45",   "1/50"},
	{  "1/60",   "1/80",   "1/90",  "1/100"},
	{ "1/125",  "1/160",  "1/180",  "1/200"},
	{ "1/250",  "1/320",  "1/350",  "1/400"},
	{ "1/500",  "1/640",  "1/750",  "1/800"},
	{"1/1000", "1/1250", "1/1500", "1/1600"},
	{"1/2000", "1/2500", "1/3000", "1/3200"},
	{"1/4000",  "",            "",       ""},
};


// Precise F numbers, 1/8 EV resolution, F=2^(n/2)
static float f_number[][8] = {
	{ 1.000f,  1.044f,  1.091f,  1.139f,  1.189f,  1.242f,  1.297f,  1.354f},
	{ 1.414f,  1.477f,  1.542f,  1.610f,  1.682f,  1.756f,  1.834f,  1.915f},
	{ 2.000f,  2.089f,  2.181f,  2.278f,  2.378f,  2.484f,  2.594f,  2.709f},
	{ 2.828f,  2.954f,  3.084f,  3.221f,  3.364f,  3.513f,  3.668f,  3.830f},
	{ 4.000f,  4.177f,  4.362f,  4.555f,  4.757f,  4.967f,  5.187f,  5.417f},
	{ 5.657f,  5.907f,  6.169f,  6.442f,  6.727f,  7.025f,  7.336f,  7.661f},
	{ 8.000f,  8.354f,  8.724f,  9.110f,  9.514f,  9.935f, 10.375f, 10.834f},
	{11.314f, 11.815f, 12.338f, 12.884f, 13.454f, 14.050f, 14.672f, 15.322f},
	{16.000f, 16.708f, 17.448f, 18.221f, 19.027f, 19.870f, 20.749f, 21.668f},
	{22.627f, 23.629f, 24.675f, 25.768f, 26.909f, 28.100f, 29.344f, 30.643f},
	{32.000f, 33.417f, 34.896f, 36.441f, 38.055f, 39.739f, 41.499f, 43.336f},
	{45.255f, 47.258f, 49.351f, 51.536f, 53.817f, 56.200f, 58.688f, 61.287f},
	{64.000f, 66.834f, 69.792f, 72.882f, 76.109f, 79.479f, 82.998f, 86.672f}
};

void display_float(char *dest, float value);

int ev_sgn(int ev) {
	return 0x100 - ev;
}

int ev_inc(int ev) {
	ev = ev_normalize(ev);

	if (cameraMode->cf_explevel_inc_third)
		ev = ev_add(ev, 0x04); // +0 1/2
	else
		ev = ev_add(ev, 0x03); // +0 1/3

	return (ev & 0x80) ? ev : MIN(ev, 0x30);
}

int ev_dec(int ev) {
	ev = ev_normalize(ev);

	if (cameraMode->cf_explevel_inc_third)
		ev = ev_add(ev, 0xFC); // -0 1/2
	else
		ev = ev_add(ev, 0xFD); // -0 1/3

	return (ev & 0x80) ? MAX(ev, 0xD0) : ev;
}

int ev_add(int ying, int yang) {
	int ev = (ying + yang) & 0xFF;

	switch (ev & 0x07) {
	case 0x02:
		ev += 0x01;
		break;
	case 0x06:
		ev -= 0x01;
		break;
	}

	return ev;
}

int ev_sub(int ying, int yang) {
	return ev_add(ying, ev_sgn(yang));
}

int av_inc(int av) {
	av = ev_normalize(av);

	if (cameraMode->cf_explevel_inc_third)
		av = ev_add(av, 0x04); // +0 1/2
	else
		av = ev_add(av, 0x03); // +0 1/3

	return MIN(av, 0x67); // f/60.0
}

int av_dec(int av) {
	av = ev_normalize(av);

	if (cameraMode->cf_explevel_inc_third)
		av = ev_add(av, 0xFC); // -0 1/2
	else
		av = ev_add(av, 0xFD); // -0 1/3

	return MAX(av, 0x08); // f/1.0
}

int av_add(int ying, int yang) {
	int av = ev_add(ying, yang);

	return MIN(av, cameraMode->avmax);
}

int av_sub(int ying, int yang) {
	int av = ev_sub(ying, yang);

	return MAX(av, cameraMode->avo);
}

int tv_next(int tv) {
	return MIN(tv + 0x08, 0x98);
}

int tv_prev(int tv) {
	return MAX(tv - 0x08, -0x20);
}

int tv_inc(int tv) {
	tv = ev_normalize(tv);

	if (cameraMode->cf_explevel_inc_third)
		tv = ev_add(tv, 0x04); // +0 1/2
	else
		tv = ev_add(tv, 0x03); // +0 1/3

	return MIN(tv, 0x98); // 1/4000s
}

int tv_dec(int tv) {
	tv = ev_normalize(tv);

	if (cameraMode->cf_explevel_inc_third)
		tv = ev_add(tv, 0xFC); // -0 1/2
	else
		tv = ev_add(tv, 0xFD); // -0 1/3

	return MAX(tv, 0x10); // 30s
}

int tv_add(int ying, int yang) {
	int ev = ev_add(ying, yang);

	return MIN(ev, 0xA0);
}

int tv_sub(int ying, int yang) {
	int ev = ev_sub(ying, yang);

	return MAX(ev, 0x10);
}

int ev_normalize(int ev) {
	if (cameraMode->cf_explevel_inc_third)
		ev &= 0xFC;
	else switch (ev & 0x07) {
	case 0x01:
	case 0x02:
		ev = (ev & 0xF8) | 0x03;
		break;
	case 0x06:
	case 0x07:
		ev = (ev & 0xF8) | 0x05;
		break;
	}

	return ev;
}

int iso_roll(int iso) {
	iso = (iso & 0xF8) | ((iso + 1) & 0x07);

	return MIN(iso, 0x70);
}

int iso_next(int iso) {
	iso = (iso & 0xF8) + 0x08;

	return MIN(iso, 0x68);
}

int iso_prev(int iso) {
	iso = (iso & 0xF8) - 0x08;

	return MAX(iso, 0x48);
}

int iso_inc(int iso) {
	iso = iso + 0x01;

	return MIN(iso, 0x6F);
}

int iso_dec(int iso) {
	iso = iso - 0x01;

	return MAX(iso, 0x48);
}

void ev_print(char *dest, int ev) {
	char dsp_sgn, *dsp_dec;
	int  dsp_int;

	if (ev & 0x80) {
		dsp_sgn = '-';
		ev = 0x80 - (ev & 0x7F);
	} else if (ev & 0x7F) {
		dsp_sgn = '+';
	} else {
		dsp_sgn = ' ';
	}

	dsp_int = ((ev & 0x78) >> 3);

	switch (ev & 0x07) {
	case 0x00:
		dsp_dec = " ·/·";
		break;
	case 0x03:
		dsp_dec = " 1/3";
		break;
	case 0x04:
		dsp_dec = " 1/2";
		break;
	case 0x05:
		dsp_dec = " 2/3";
		break;
	default:
		dsp_dec = " ?/?";
		break;
	}

	sprintf(dest, "%c%i%s", dsp_sgn, dsp_int, dsp_dec);
}

void av_print(char *dest, int av) {
	int base = (av >> 3) - 0x01;
	int frac = 0;

	switch (av & 0x07) {
	case 0x00:
	case 0x01:
		frac = 0;
		break;
	case 0x02:
	case 0x03:
		frac = 1;
		break;
	case 0x04:
		frac = 2;
		break;
	case 0x05:
	case 0x06:
	case 0x07:
		frac = 3;
		break;
	default:
		break;
	}

	sprintf(dest, "f/%s", av_strings[base][frac]);
}

void tv_print(char *dest, int tv) {
	int base = (tv >> 3) + 0x04;
	int frac = 0;

	switch (tv & 0x07) {
	case 0x03:
		frac = 1;
		break;
	case 0x04:
		frac = 2;
		break;
	case 0x05:
		frac = 3;
		break;
	default:
		break;
	}

	sprintf(dest, "%s", tv_strings[base][frac]);
}

/**
 * For intermediate ISOs, we are doing a linear approximation
 * between two base ISOs; as pointed out by Sergei, we should
 * use an exponential calculation, but I decided to keep this
 * version, as the correct algorithm yields _uglier_ numbers.
 */

void iso_print(char *dest, int code) {
	int iso;

	int base = ((code & 0x38) >> 3) - 1;
	int mult =  (code & 0x07);

	iso  = 100 * (1 << base);
	iso += iso * mult / 8;

	sprintf(dest, "%d", iso);
}

void calculate_dof(int focal_length, int focus_distance, int av, char *min, char *max) {
    float fl =    1.0f * focal_length;
    float fd = 1000.0f * focus_distance;

    float fn  = f_number[(av >> 3) - 1][av & 0x07]; // F-Number
    float cof = 0.019f; // Circle of confusion

    // Hyperfocal
    float hf  = fl + fl * fl / (fn * cof);
    float aux = fd * (hf - fl) / 1000.0f;

    // Min distance
    display_float(min, aux / (hf + fd - 2.0f * fl));

    // Max distance
    if (hf >= fd) {
        display_float(max, aux / (hf - fd));
    } else {
    	sprintf(max, "%s", LP_WORD(L_S_INFINITE));
    }
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
	if (cameraMode->beep) {
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
		int power_off_state = cameraMode->auto_power_off;

		send_to_intercom(IC_SET_AUTO_POWER_OFF, 1, FALSE);

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

		send_to_intercom(IC_SET_AUTO_POWER_OFF, 1, power_off_state);
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

	if (settings.logfile_mode == 1) // new
		sprintf(filename, "A:/%02d%02d%02d%02d.LOG", tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);

	// O_APPEND is not working in VxWorks, so we seek to the end later
	file = FIO_OpenFile(filename, O_CREAT | O_WRONLY , 644);
	if(file > 0) {
		if (settings.logfile_mode == 2) // append
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

int send_to_intercom(int message, int length, int parm) {
	int result = SendToIntercom(message, length, parm);
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

void wait_for_camera() {
	while (! able_to_release())
		SleepTask(RELEASE_WAIT);
}

void wait_for_capture() {
	while (hRelSem)
		SleepTask(RELEASE_WAIT);
}

int shutter_release() {
	wait_for_camera();

	int result = eventproc_Release();
	SleepTask(RELEASE_WAIT);

	wait_for_capture();

	return result;
}

int shutter_release_bulb(int time) {
	wait_for_camera();

	press_button(IC_BUTTON_HALF_SHUTTER);
	SleepTask(1000 * time + SHUTTER_LAG);

	press_button(IC_BUTTON_HALF_SHUTTER);
	SleepTask(RELEASE_WAIT);

	wait_for_capture();

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
	while (--n > 0 && ( bpos || (rc = read_(fd, &buf, 255)) ) ) {
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
