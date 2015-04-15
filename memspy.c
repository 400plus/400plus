// memspy tool ported from MagicLantern.
#ifdef MEMSPY
#include "debug.h"
#include "bmp.h"

/*
 * Copyright (C) 2009 Trammell Hudson <hudson+ml@osresearch.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */



int mem_spy = 0; // 1==enable

int mem_spy_start = 0xC0220100;	// start from here
int mem_spy_bool = 0;		// only display booleans (0,1,-1)
int mem_spy_start_time = 3;  // ignore values changing early (these are noise)
int mem_spy_fixed_addresses = 0; // only look from a list of fixed addresses
const int mem_spy_addresses[] = {0xC0220130, 0xC0220134};//0xc0000044, 0xc0000048, 0xc0000057, 0xc00011cf, 0xc02000a8, 0xc02000ac, };
int mem_spy_len = 0x40/4;    // look at ### int32's; use only when mem_spy_fixed_addresses = 0
//int mem_spy_len = ((int)(sizeof(mem_spy_addresses)/sizeof((mem_spy_addresses)[0]))); // use this when mem_spy_fixed_addresses = 1

int mem_spy_count_lo = 0; // how many times is a value allowed to change
int mem_spy_count_hi = 0; // (limits)
int mem_spy_freq_lo = 0;
int mem_spy_freq_hi = 0;  // or check frequecy between 2 limits (0 = disable)
int mem_spy_value_lo = 0;
//int mem_spy_value_hi = 50;  // or look for a specific range of values (0 = disable)
int mem_spy_value_hi = 0;  // or look for a specific range of values (0 = disable)

static int* dbg_memmirror = 0;
static int* dbg_memchanges = 0;
//static int* dbg_memlogged = 0;

static int dbg_memspy_get_addr(int i)
{
	if (mem_spy_fixed_addresses)
		return mem_spy_addresses[i];
	else
		return mem_spy_start + i*4;
}

// for debugging purpises only
time_t _t = 0;
int _get_timestamp(struct tm * t) {
	return t->tm_sec + t->tm_min * 60 + t->tm_hour * 3600 + t->tm_mday * 3600 * 24;
}

void _tic() {
	time(&_t);
}

int _toc() {
	time_t t;
	time(&t);
	return t - _t;
}

static void dbg_memspy_init() { // initial state of the analyzed memory
	bmp_printf(FONT_MED, 10,10, "memspy init @ f:%x ... (l:+%x) ... t:%x", mem_spy_start, mem_spy_len, mem_spy_start + mem_spy_len * 4);
	SleepTask(1000);

	//debug_log("memspy init @ from:%x ... (len:%x) ... to:%x", mem_spy_start, mem_spy_len, mem_spy_start + mem_spy_len * 4);
	//mem_spy_len is number of int32's
	if (!dbg_memmirror) dbg_memmirror = AllocateMemory(mem_spy_len*4 + 100); // local copy of mem area analyzed
	if (!dbg_memmirror) return;
	if (!dbg_memchanges) dbg_memchanges = AllocateMemory(mem_spy_len*4 + 100); // local copy of mem area analyzed
	if (!dbg_memchanges) return;
	//if (!dbg_memlogged) dbg_memlogged = AllocateMemory(mem_spy_len*4 + 100); // is this change logged
	//if (!dbg_memlogged) return;
	int i;
	int crc = 0;
	for (i = 0; i < mem_spy_len; i++) {
		unsigned int addr = dbg_memspy_get_addr(i);
		dbg_memmirror[i] = MEMX(addr);
		dbg_memchanges[i] = 0;
		//dbg_memlogged[i] = 0;
		crc += dbg_memmirror[i];
	}
	bmp_printf(FONT_MED, 10,10, "memspy OK: %x", crc);
	//debug_log("memspy OK: %x", crc);
	_tic();
	SleepTask(1000);
}

static void dbg_memspy_update()
{
	//int printed_elapsed=0;
	static int init_done = 0;
	if (!init_done) dbg_memspy_init();
	init_done = 1;

	if (!dbg_memmirror) return;
	if (!dbg_memchanges) return;
	//if (!dbg_memlogged) return;

	int elapsed_time = _toc();
	bmp_printf(FONT_MED, 50, 200, "[%d] ", elapsed_time);

	int i;
	int k=0;
	for (i = 0; i < mem_spy_len; i++) {
		int fnt = FONT_SMALL;
		unsigned int addr = dbg_memspy_get_addr(i);
		int oldval = dbg_memmirror[i];
		int newval = MEMX(addr);
		if (oldval != newval) {
			dbg_memmirror[i] = newval;
			if (dbg_memchanges[i] < 1000000) dbg_memchanges[i]++;
			//dbg_memlogged[i]=0;
			fnt = FONT(FONT_SMALL,5, COLOR_BG);
			if (elapsed_time < mem_spy_start_time) dbg_memchanges[i] = 1000000; // so it will be ignored
		}

		if (mem_spy_bool && newval != 0 && newval != 1 && newval != -1) continue;

		if (mem_spy_value_lo && newval < mem_spy_value_lo) continue;
		if (mem_spy_value_hi && newval > mem_spy_value_hi) continue;

		if (mem_spy_count_lo && dbg_memchanges[i] < mem_spy_count_lo) continue;
		if (mem_spy_count_hi && dbg_memchanges[i] > mem_spy_count_hi) continue;

		int freq = dbg_memchanges[i] / elapsed_time;
		if (mem_spy_freq_lo && freq < mem_spy_freq_lo) continue;
		if (mem_spy_freq_hi && freq > mem_spy_freq_hi) continue;

		//if (dbg_memlogged[i]) return;

		//if (!printed_elapsed) {
		//	debug_log("memspy: elapsed: %d sec ", elapsed_time);
		//	printed_elapsed = 1;
		//}
		//debug_log("%8x:%2d:%8x", addr, dbg_memchanges[i], newval);
		//dbg_memlogged[i] = 1;
		//SleepTask(10);

		int x = 10 + 8 * 22 * (k % 2);
		int y = 10 + 12 * (k / 2);
		bmp_printf(fnt, x, y, "[%8x:%2d:%8x]", addr, dbg_memchanges[i], newval);
		k = (k + 1) % 120;

	}
	//printed_elapsed=0;
	//SleepTask(10);
	//for (i = 0; i < 10; i++) {
	//	int x = 10 + 8 * 13 * (k % 3);
	//	int y = 10 + 12 * (k / 3);
	//	bmp_printf(FONT_SMALL, x, y, "          ");
	//	k = (k + 1) % 120;
	//}

}

void memspy_task( void* unused )
{
	debug_log("memspy task starting.");
	while ( 1 ) {
		if (mem_spy) {
			SleepTask(10);
			LEDBLUE ^= 2;
			dbg_memspy_update();
		} else {
			SleepTask(1000);
		}
	}
	debug_log("memspy task finishing.");
}

void memspy_enable() {
	mem_spy=1;
}

void memspy_disable() {
	mem_spy=0;
	SleepTask(100);
	LEDBLUE = LEDOFF;
}

#endif
