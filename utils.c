#include "main.h"
#include "firmware.h"
#include "settings.h"

#include "utils.h"

int ev_normalize(int ev);

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
	iso = iso + 0x01;;

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

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("::::: %04d-%02d-%02d %02d:%02d:%02d :::::\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

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

void led_flash(int duration) {
	eventproc_EdLedOn();
	SleepTask(EVENT_WAIT);

	SleepTask(duration);

	eventproc_EdLedOff();
	SleepTask(EVENT_WAIT);
}
