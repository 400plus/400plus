#include <stdlib.h>
#include <stdio.h>

#include "float.h"
#include "macros.h"
#include "settings.h"

#include "firmware/camera.h"

#include "exposure.h"

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
	{ "64",   "",     "",    ""},
};

static char *tv_strings[][4] = {
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
	{"1/4000",       "",       "",       ""},
};


char ev_normalization[2][8] = {
	// 1/3 EV
	{
		 0, // 0/8 => 0/8
		-1, // 1/8 => 0/8
		+1, // 2/8 => 3/8
		 0, // 3/8 => 3/8
		+1, // 4/8 => 5/8
		 0, // 5/8 => 5/8
		-1, // 6/8 => 5/8
		+1  // 7/8 => 8/8
	},
	// 1/2 EV
	{
		 0, // 0/8 => 0/8
		+3, // 1/8 => 4/8
		+2, // 2/8 => 4/8
		+1, // 3/8 => 4/8
		 0, // 4/8 => 4/8
		-1, // 5/8 => 4/8
		+2, // 6/8 => 8/8
		+1  // 7/8 => 8/8
	},
};

/* EV related --------------------------------------------------------- */

ev_t ev_time(int s) {
	return EV_CODE(7, 0) - 8.0f * float_log(s) / float_log(2);
}

ev_t ev_normalize(ev_t ec) {
	return ec + SIGN(ec) * ev_normalization[DPData.cf_explevel_inc_third][abs(EV_SUB(ec))];
}

/* EC related --------------------------------------------------------- */

ec_t ec_normalize(ec_t ec) {
	return ec + SIGN(ec) * ev_normalization[DPData.cf_explevel_inc_third][abs(EV_SUB(ec))];
}

ec_t ec_inc(ec_t ec, int extended) {
	ec = ec_normalize(ec_normalize(ec) + EV_STEP);

	return MIN(ec, extended ? EC_MAX_EXT : EC_MAX);
}

ec_t ec_dec(ec_t ec, int extended) {
	ec = ec_normalize(ec_normalize(ec) - EV_STEP);

	return MAX(ec, extended ? EC_MIN_EXT : EC_MIN);
}

ec_t ec_add(ec_t ying, ec_t yang) {
	ec_t ec = ying + yang;

	switch (ec & 0x07) {
	case 0x02:
		ec++;
		break;
	case 0x06:
		ec--;
		break;
	}

	return ec;
}

ec_t ec_sub(ec_t ying, ec_t yang) {
	return ec_add(ying, -yang);
}

void ec_print(char *dest, ec_t ec) {
	char dsp_sgn = ' ';

	if (ec < 0)
		dsp_sgn = '-';
	else if (ec > 0)
		dsp_sgn = '+';

	ec = abs(ec);

	int   dsp_int = EV_VAL(ec);
	char *dsp_dec = " ?/?";

	switch (EV_SUB(ec)) {
	case 0x00:
		dsp_dec = " -/-";
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
	}

	sprintf(dest, "%c%i%s", dsp_sgn, dsp_int, dsp_dec);
}

/* AV related --------------------------------------------------------- */

av_t av_add(av_t ying, av_t yang) {
	av_t  av = ev_normalize(ying + yang);
	av_t max = DPData.ef_lens_exist ? ev_normalize(DPData.avmax) : AV_MAX;

	return MIN(av, max);
}

av_t av_sub(av_t ying, av_t yang) {
	av_t av  = ev_normalize(ying - yang);
	av_t min = DPData.ef_lens_exist ? ev_normalize(DPData.avo) : AV_MIN;

	return MAX(av, min);
}

av_t av_inc(av_t av) {
	return av_add(av, EV_STEP);
}

av_t av_dec(av_t av) {
	return av_sub(av, EV_STEP);
}

void av_print(char *dest, av_t av) {
	int base = EV_VAL(av);
	int frac = 0;

	switch (EV_SUB(av)) {
	case 0000:
	case 0001:
		frac = 0;
		break;
	case 0002:
	case 0003:
		frac = 1;
		break;
	case 0004:
		frac = 2;
		break;
	case 0005:
	case 0006:
	case 0007:
		frac = 3;
		break;
	default:
		break;
	}

	sprintf(dest, "f/%s", av_strings[base - 1][frac]);
}

/* TV related --------------------------------------------------------- */

tv_t tv_add(tv_t ying, tv_t yang) {
	tv_t tv = ev_normalize(ying + yang);

	return MIN(tv, TV_MAX); // 1/4000s
}

tv_t tv_sub(tv_t ying, tv_t yang) {
	tv_t tv = ev_normalize(ying - yang);

	return MAX(tv, TV_MIN); // 30s
}

tv_t tv_inc(tv_t tv) {
	return tv_add(tv, EV_STEP);
}

tv_t tv_dec(tv_t tv) {
	return tv_sub(tv, EV_STEP);
}

tv_t bulb_next(tv_t tv) {
	tv += EV_CODE(1, 0);

	return MIN(tv, BULB_MAX);
}

tv_t bulb_prev(tv_t tv) {
	tv -= EV_CODE(1, 0);

	return MAX(tv, BULB_MIN);
}

void tv_print(char *dest, tv_t tv) {
	int base = EV_VAL(tv);
	int frac = 0;

	switch (EV_SUB(tv)) {
	case 0000:
	case 0001:
		frac = 0;
		break;
	case 0002:
	case 0003:
		frac = 1;
		break;
	case 0004:
		frac = 2;
		break;
	case 0005:
	case 0006:
	case 0007:
		frac = 3;
		break;
	default:
		break;
	}

	sprintf(dest, "%s", tv_strings[base - 2][frac]);
}

void bulb_print(char *dest, tv_t tv) {
	if (tv < BULB_VAL)
		sprintf(dest, "%2i'", BULB_MN(tv));
	else
		tv_print(dest, BULB_TV(tv));
}

/* ISO related --------------------------------------------------------- */

iso_t iso_next(iso_t iso) {
	iso = EV_CODE(EV_VAL(iso) + 1, 0);

	return MIN(iso, ISO_MAX);
}

iso_t iso_prev(iso_t iso) {
	iso = EV_CODE(EV_VAL(iso) - 1, 0);

	return MAX(iso, ISO_MIN);
}

iso_t iso_inc(iso_t iso) {
	int step = (1 << settings.digital_iso_step);
	int mask = 0x100 - step;

	iso = (iso + step) & mask;

	return MIN(iso, ISO_EXT);
}

iso_t iso_dec(iso_t iso) {
	int step = (1 << settings.digital_iso_step);
	int mask = 0x100 - step;

	iso = (iso - step) & mask;

	return MAX(iso, ISO_MIN);
}

/**
 * For intermediate ISOs, we are doing a linear approximation
 * between two base ISOs; as pointed out by Sergei, we should
 * use an exponential calculation, but I decided to keep this
 * version, as the correct algorithm yields _uglier_ numbers.
 */

void iso_print(char *dest, iso_t code) {
	int iso;

	int base = EV_VAL(code) - 9;
	int mult = EV_SUB(code);

	iso  = 100 * (1 << base);
	iso += iso * mult / 8;

	sprintf(dest, "%d", iso);
}
