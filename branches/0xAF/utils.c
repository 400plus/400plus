#include "main.h"
#include "settings.h"
#include "firmware.h"

#include "utils.h"

// Translation from ISO codes to text displayed
const char iso_text[][5] = {" 100", " 125", " 160", " 200", " 250", " 320", " 400", " 500", " 640", " 800", "1000", "1250", "1600", "2000", "2500", "3200"};
const int  iso_code[]    = {  0x48,   0x4C,   0x4E,   0x50,   0x53,   0x56,   0x58,   0x5C,   0x5D,   0x60,   0x64,   0x66,   0x68,   0x6C,   0x6D,   0x6F};

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
	switch(iso) {
	case 0x6F: return 0x68; // 3200-> 1600
	case 0x6D: return 0x6F; // 2500-> 3200
	case 0x6C: return 0x6D; // 2000-> 2500
	case 0x68: return 0x6C; // 1600-> 2000
	case 0x66: return 0x60; // 1250->  800
	case 0x64: return 0x66; // 1000-> 1250
	case 0x60: return 0x64; //  800-> 1000
	case 0x5D: return 0x58; //  640->  400
	case 0x5C: return 0x5D; //  500->  640
	case 0x58: return 0x5C; //  400->  500
	case 0x56: return 0x50; //  320->  200
	case 0x53: return 0x56; //  250->  320
	case 0x50: return 0x53; //  200->  250
	case 0x4E: return 0x48; //  160->  100
	case 0x4C: return 0x4E; //  125->  160
	case 0x48: return 0x4C; //  100->  125
	default  : return 0x48; //  100... just in case
	}
}

int iso_prev(int iso) {
	switch(iso) {
	case 0x6F: return 0x6D; // 3200-> 2500
	case 0x6D: return 0x6C; // 2500-> 2000
	case 0x6C: return 0x68; // 2000-> 1600
	case 0x68: return 0x66; // 1600-> 1250
	case 0x66: return 0x64; // 1250-> 1000
	case 0x64: return 0x60; // 1000->  800
	case 0x60: return 0x5D; //  800->  640
	case 0x5D: return 0x5C; //  640->  500
	case 0x5C: return 0x58; //  500->  400
	case 0x58: return 0x56; //  400->  320
	case 0x56: return 0x53; //  320->  250
	case 0x53: return 0x50; //  250->  200
	case 0x50: return 0x4E; //  200->  160
	case 0x4E: return 0x4C; //  160->  125
	case 0x4C: return 0x48; //  125->  100
	default  : return 0x6F; // 3200... just in case
	}
}

int iso_next(int iso) {
	switch(iso) {
	case 0x6F: return 0x48; // 3200-> 100
	case 0x6D: return 0x6F; // 2500-> 3200
	case 0x6C: return 0x6D; // 2000-> 2500
	case 0x68: return 0x6C; // 1600-> 2000
	case 0x66: return 0x68; // 1250-> 1600
	case 0x64: return 0x66; // 1000-> 1250
	case 0x60: return 0x64; //  800-> 1000
	case 0x5D: return 0x60; //  640->  800
	case 0x5C: return 0x5D; //  500->  640
	case 0x58: return 0x5C; //  400->  500
	case 0x56: return 0x58; //  320->  400
	case 0x53: return 0x56; //  250->  320
	case 0x50: return 0x53; //  200->  250
	case 0x4E: return 0x50; //  160->  200
	case 0x4C: return 0x4E; //  125->  160
	case 0x48: return 0x4C; //  100->  125
	default  : return 0x48; //  100... just in case
	}
}

int iso_inc(int iso) {
	if      (iso < 0x48) return 0x48; //  100
	else if (iso < 0x50) return 0x50; //  200
	else if (iso < 0x58) return 0x58; //  400
	else if (iso < 0x60) return 0x60; //  800
	else if (iso < 0x68) return 0x68; // 1600
	else                 return 0x6F; // 3200

}

int iso_dec(int iso) {
	if      (iso > 0x68) return 0x68; // 1600
	else if (iso > 0x60) return 0x60; //  800
	else if (iso > 0x58) return 0x58; //  400
	else if (iso > 0x50) return 0x50; //  200
	else                 return 0x48; //  100
}

const char *iso_display(int iso) {
	int i;

	for (i = 0; i < LENGTH(iso_code); i++) {
		if (iso_code[i] == iso) {
			return iso_text[i];
		}
	}

	return NULL;
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
