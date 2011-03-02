#include "main.h"
#include "settings.h"

#include "utils.h"

int ev_normalize(int ev);

int ev_sgn(int ev) {
	return 0x100 - ev;
}

int ev_inc(int ev) {
	ev = ev_normalize(ev);

	if (cameraMode.CfSettingSteps)
		ev = ev_add(ev, 0x04); // +0 1/2
	else
		ev = ev_add(ev, 0x03); // +0 1/3

	return (ev & 0x80) ? ev : MIN(ev, 0x30);
}

int ev_dec(int ev) {
	ev = ev_normalize(ev);

	if (cameraMode.CfSettingSteps)
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
	} else if (ev & 0x78) {
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

int ev_normalize(int ev) {
	if (cameraMode.CfSettingSteps)
		ev &= 0xFC;
	else if ((ev & 0x07) && !(ev & 0x03))
		ev -= 0x01;

	return ev;
}

int iso_next(int iso) {
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
