#include "main.h"
#include "firmware.h"
#include "settings.h"

#include "utils.h"

#include "debug.h"

int ev_normalize(int ev);

static char *av_strings[][4] = {
	{"1.0", "1.1", "1.2", "1.2"},
	{"1.4", "1.6", "1.7", "1.8"},
	{"2.0", "2.2", "2.4", "2.5"},
	{"2.8", "3.2", "3.3", "3.5"},
	{"4.0", "4.5", "4.8", "5.0"},
	{"5.6", "6.3", "6.7", "7.1"},
	{"8.0", "9.0", "9.5",  "10"},
	{ "11",  "13",  "13",  "14"},
	{ "16",  "18",  "19",  "20"},
	{ "22",  "25",  "27",  "29"},
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

	return MIN(av, 0x58); // f/22.0
}

int av_dec(int av) {
	av = ev_normalize(av);

	if (cameraMode->cf_explevel_inc_third)
		av = ev_add(av, 0xFC); // -0 1/2
	else
		av = ev_add(av, 0xFD); // -0 1/3

	return MAX(av, 0x08); // f/1.0
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
	else if ((ev & 0x07) && !(ev & 0x03))
		ev -= 0x01;

	return ev;
}

int iso_roll(int iso) {
	iso = (iso & 0xF8) | ((iso + 1) & 0x07);

	return MIN(iso, 0x70);
}

int iso_next(int iso) {
	iso = iso + 0x01;

	return MIN(iso, 0x6F);
}

int iso_prev(int iso) {
	iso = iso - 0x01;

	return MAX(iso, 0x48);
}

int iso_inc(int iso) {
	iso = (iso & 0xF8) + 0x08;

	return MIN(iso, 0x68);
}

int iso_dec(int iso) {
	iso = (iso & 0xF8) - 0x08;

	return MAX(iso, 0x48);
}

void ev_print(const char *dest, int ev) {
	char dsp_sgn, dsp_int, *dsp_dec;

	if (ev & 0x80) {
		dsp_sgn = '-';
		ev = 0x80 - (ev & 0x7F);
	} else if (ev & 0x7F) {
		dsp_sgn = '+';
	} else {
		dsp_sgn = ' ';
	}

	dsp_int = '0' + ((ev & 0x78) >> 3);

	switch (ev & 0x07) {
	case 0x00:
		dsp_dec = "   ";
		break;
	case 0x03:
		dsp_dec = "1/3";
		break;
	case 0x04:
		dsp_dec = "1/2";
		break;
	case 0x05:
		dsp_dec = "2/3";
		break;
	default:
		dsp_dec = " - ";
		break;
	}

	sprintf(dest, "%c%c %s", dsp_sgn, dsp_int, dsp_dec);
}

void av_print(const char *dest, int av) {
	int base = (av >> 3) - 0x01;
	int frac = 0;

	switch (av & 0x07) {
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

	sprintf(dest, "%s", av_strings[base][frac]);
}

void tv_print(const char *dest, int tv) {
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

void iso_print(const char *string, int code) {
	int iso;

	int base = ((code & 0x38) >> 3) - 1;
	int mult =  (code & 0x07);

	iso  = 100 * (1 << base);
	iso += iso * mult / 8;

	sprintf(string, "%d", iso);
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
int shutter_release_disasm() {

	extern char * aRelSem;

	if (hRelSem == 0) {
		hRelSem = CreateBinarySemaphore(aRelSem, 0);
	}

	SendToIntercom(IC_RELEASE, 0, 0);
	SendToIntercom(0x6D, 1, 1);

	TakeSemaphore(hRelSem, 30000);
	DeleteSemaphore(hRelSem);
	hRelSem = 0;

	SleepTask(EVENT_WAIT);
	return 0;
}
#endif

int shutter_release() {
	int result = eventproc_Release();
	SleepTask(EVENT_WAIT);

	return result;
}

int print_icu_info() {
	int result = eventproc_PrintICUInfo();
	SleepTask(EVENT_WAIT);

	return result;
}

int press_button(int button) {
	int result = IntercomHandlerButton(button);
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

void led_flash(int duration) {
	eventproc_EdLedOn();
	SleepTask(EVENT_WAIT);

	SleepTask(duration);

	eventproc_EdLedOff();
	SleepTask(EVENT_WAIT);
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

