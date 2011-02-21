#include "main.h"

#include "utils.h"

int ev_inc(int ev) {
	if (cameraMode.CfSettingSteps)
		return ev_add(ev, 0x04); // +0 1/2
	else
		return ev_add(ev, 0x03); // +0 1/3

}

int ev_dec(int ev) {
	if (cameraMode.CfSettingSteps)
		return ev_add(ev, 0xFC); // -0 1/2
	else
		return ev_add(ev, 0xFD); // -0 1/3

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

	if (ev & 0x80)
		return MAX(ev, 0xD0);
	else
		return MIN(ev, 0x30);
}

void ev_print(char *dest, int ev) {
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
