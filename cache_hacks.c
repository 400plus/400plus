/*
 * This file comes from Magic Lantern.
 * Thanks to g3gg0 for the idea and implementation.
 * Thanks to Sergei for porting it.
 */

#include <vxworks.h>
#include <stdint.h>

#include "cache_hacks.h"

static inline uint32_t cli(void)
{
	uint32_t old_cpsr = 0;
	uint32_t new_cpsr = 0;
	asm volatile (
		"MRS %0, CPSR\n"
		"ORR %1, %0, #0x80\n" // set I flag to disable IRQ
		"MSR CPSR_c, %1\n"

		: "=r"(old_cpsr)
		: "r"(new_cpsr)
	);
	return old_cpsr & 0x80; // return true if the flags are set
}

static inline void sei( uint32_t old_cpsr )
{
	uint32_t new_cpsr = 0;
	asm volatile (
		"MRS %0, CPSR\n"
		"BIC %0, %0, #0x80\n"
		"ORR %0, %0, %1\n"
		"MSR CPSR_c, %0"

		:
		: "r"(new_cpsr), "r"(old_cpsr)
	);
}

/* return cache size in bits (13 -> 2^13 -> 8192 -> 8KiB) */
static uint32_t cache_get_size(uint32_t type)
{
	uint32_t cache_info = 0;

	// get cache type register
	// On a 550D: 0x0F112112. 8KB I/D Cache. 4 way set associative.
	asm volatile (
		"MRC p15, 0, %0, c0, c0, 1\n"

		: "=r"(cache_info)
	);

	/* dcache is described at bit pos 12 */
	if (type == TYPE_DCACHE) {
		cache_info >>= 12;
	}

	/* check if size is invalid, or absent flag is set */
	uint32_t size = (cache_info >> 6) & 0x0F;
	uint32_t absent = (cache_info >> 2) & 0x01;

	if((size < 3) || absent) {
		return 0;
	}

	/* return as 2^x */
	return size + 9;
}

static uint32_t cache_patch_single_word(uint32_t address, uint32_t data, uint32_t type)
{
	uint32_t cache_seg_index_word = (address & (CACHE_INDEX_ADDRMASK(type) | CACHE_WORD_ADDRMASK(type)));
	uint32_t cache_tag_index = (address & (CACHE_TAG_ADDRMASK(type) | CACHE_INDEX_ADDRMASK(type))) | 0x10;

	if(type == TYPE_ICACHE) {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, %1, c15, c1, 0\n"
			/* write instruction */
			"MCR p15, 3, %2, c15, c3, 0\n"

			:
			: "r"(cache_seg_index_word), "r"(cache_tag_index), "r"(data)
		);
	} else {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, %1, c15, c2, 0\n"
			/* write data */
			"MCR p15, 3, %2, c15, c4, 0\n"

			:
			: "r"(cache_seg_index_word), "r"(cache_tag_index), "r"(data));
	}

	return 1;
}

/*	fetch all the instructions in that temp_cacheline the given address is in.
	this is *required* before patching a single address.
	if you omit this, only the patched instruction will be correct, the
	other instructions around will simply be crap.
	warning - this is doing a data fetch (LDR) so DCache patches may cause
	unwanted or wanted behavior. make sure you know what you do :)

	same applies to dcache routines
*/
static void cache_fetch_line(uint32_t address, uint32_t type)
{
	uint32_t base = (address & ~0x1F);
	uint32_t temp_cacheline[8];

	// our ARM946 has 0x20 byte temp_cachelines. fetch the current line
	// thanks to unified memories, we can do LDR on instructions.
	uint32_t pos;
	for(pos = 0; pos < 8; pos++) {
		temp_cacheline[pos] = ((uint32_t *)base)[pos];
	}

	/* and nail it into locked cache */
	for(pos = 0; pos < 8; pos++) {
		cache_patch_single_word(base + pos * 4, temp_cacheline[pos], type);
	}
}

/* return the tag and content at given index (segment+index+word) */
static void cache_get_content(uint32_t segment, uint32_t index, uint32_t word, uint32_t type, uint32_t *tag, uint32_t *data)
{
	uint32_t cache_seg_index_word = 0;
	uint32_t stored_tag_index = 0;
	uint32_t stored_data = 0;

	cache_seg_index_word |= ((segment & CACHE_SEGMENT_BITMASK(type)) << CACHE_SEGMENT_TAGOFFSET(type));
	cache_seg_index_word |= ((index & CACHE_INDEX_BITMASK(type)) << CACHE_INDEX_TAGOFFSET(type));
	cache_seg_index_word |= ((word & CACHE_WORD_BITMASK(type)) << CACHE_WORD_TAGOFFSET(type));

	if(type == TYPE_ICACHE) {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %2, c15, c0, 0\n"
			/* get TAG at given index */
			"MRC p15, 3, %0, c15, c1, 0\n"
			/* get DATA at given index */
			"MRC p15, 3, %1, c15, c3, 0\n"

			: "=r"(stored_tag_index), "=r"(stored_data)
			: "r"(cache_seg_index_word)
		);
	} else {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %2, c15, c0, 0\n"
			/* get TAG at given index */
			"MRC p15, 3, %0, c15, c2, 0\n"
			/* get DATA at given index */
			"MRC p15, 3, %1, c15, c4, 0\n"

			: "=r"(stored_tag_index), "=r"(stored_data)
			: "r"(cache_seg_index_word)
		);
	}

	*tag = stored_tag_index;
	*data = stored_data;
}

/* check if given address is already used or if it is usable for patching */
static uint32_t cache_is_patchable(uint32_t address, uint32_t type)
{
	uint32_t stored_tag_index = 0;
	uint32_t stored_data = 0;

	cache_get_content(
		0,
		(address & CACHE_INDEX_ADDRMASK(type)) >> CACHE_INDEX_TAGOFFSET(type),
		(address & CACHE_WORD_ADDRMASK(type)) >> CACHE_WORD_TAGOFFSET(type),
		type,
		&stored_tag_index,
		&stored_data
	);

	/* this line is free, so can be used for patching */
	if((stored_tag_index & 0x10) == 0) {
		return 1;
	}

	/* now check if the TAG RAM content matches with what we expect and valid bit is set */
	uint32_t tag_index_mask = CACHE_TAG_ADDRMASK(type) | CACHE_INDEX_ADDRMASK(type);
	uint32_t cache_tag_index = address & tag_index_mask;

	if((stored_tag_index & tag_index_mask) == cache_tag_index) {
		/* that line is used by the right address, now check data */

		if(stored_data == *(uint32_t*)address) { // data is original, so it is patchable
			return 1;
		}

		return 2; // its already patched. so return 2
	}

	/* oh, its already used by some other patch. sorry. */
	return 0;
}

/* check if given address is already in cache */
static uint32_t cache_get_cached(uint32_t address, uint32_t type)
{
	uint32_t cache_seg_index_word = (address & (CACHE_INDEX_ADDRMASK(type) | CACHE_WORD_ADDRMASK(type)));
	uint32_t stored_tag_index = 0;

	if(type == TYPE_ICACHE) {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %1, c15, c0, 0\n"
			/* get TAG at given index */
			"MRC p15, 3, %0, c15, c1, 0\n"

			: "=r"(stored_tag_index)
			: "r"(cache_seg_index_word)
		);
	} else {
		asm volatile (
			/* write index for address to write */
			"MCR p15, 3, %1, c15, c0, 0\n"
			/* get TAG at given index */
			"MRC p15, 3, %0, c15, c2, 0\n"

			: "=r"(stored_tag_index)
			: "r"(cache_seg_index_word)
		);
	}

	/* now check if the TAG RAM content matches with what we expect and valid bit is set */
	uint32_t tag_index_valid_mask = CACHE_TAG_ADDRMASK(type) | CACHE_INDEX_ADDRMASK(type) | 0x10;
	uint32_t cache_tag_index = (address & tag_index_valid_mask) | 0x10;

	if((stored_tag_index & tag_index_valid_mask) == cache_tag_index) {
		return 1;
	}

	return 0;
}

static inline void clean_d_cache(void)
{
	uint32_t segment = 0;

	do {
		uint32_t line = 0;
		for( ; line != 0x400 ; line += 0x20 ) {
			asm(
				"MCR p15, 0, %0, c7, c14, 2"

				:
				: "r"( line | segment )
			);
		}
	} while( segment += 0x40000000 );
}

static void icache_unlock(void)
{
	uint32_t old_int = cli();

	/* make sure all entries are set to invalid */
	uint32_t index;
	for(index = 0; index < (1U<<CACHE_INDEX_BITS(TYPE_ICACHE)); index++) {
		asm volatile (
			/* write index for address to write */
			"MOV R0, %0, LSL #5\n"
			"MCR p15, 3, R0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, R0, c15, c1, 0\n"

			:
			: "r"(index)
			: "r0"
		);
	}

	/* disable cache lockdown */
	asm volatile (
		"MOV R0, #0\n"
		"MCR p15, 0, R0, c9, c0, 1\n"

		:
		:
		: "r0"
	);

	/* and flush cache again to make sure its consistent */
	asm volatile (
		"MOV R0, #0\n"
		"MCR p15, 0, R0, c7, c5, 0\n"
		"MCR p15, 0, R0, c7, c10, 4\n"

		:
		:
		: "r0"
	);

	sei(old_int);
}

static void dcache_unlock(void)
{
	uint32_t old_int = cli();

	/* first clean and flush dcache entries */
	uint32_t segment, index;
	for(segment = 0; segment < (1U<<CACHE_SEGMENT_BITS(TYPE_DCACHE)); segment++ ) {
		for(index = 0; index < (1U<<CACHE_INDEX_BITS(TYPE_DCACHE)); index++) {
			uint32_t seg_index = (segment << CACHE_SEGMENT_TAGOFFSET(TYPE_DCACHE)) | (index << CACHE_INDEX_TAGOFFSET(TYPE_DCACHE));
			asm volatile (
				"MCR p15, 0, %0, c7, c14, 2\n"

				:
				: "r"(seg_index)
			);
		}
	}

	/* make sure all entries are set to invalid */
	for(index = 0; index < (1U<<CACHE_INDEX_BITS(TYPE_ICACHE)); index++) {
		asm volatile (
			/* write index for address to write */
			"MOV R0, %0, LSL #5\n"
			"MCR p15, 3, R0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, R0, c15, c2, 0\n"

			:
			: "r"(index)
			: "r0"
		);
	}

	/* disable cache lockdown */
	asm volatile (
		"MOV R0, #0\n"
		"MCR p15, 0, R0, c9, c0, 0\n"

		:
		:
		: "r0"
	);

	/* and flush cache again to make sure its consistent */
	asm volatile (
		"MOV R0, #0\n"
		"MCR p15, 0, R0, c7, c6, 0\n"
		"MCR p15, 0, R0, c7, c10, 4\n"

		:
		:
		: "r0"
	);

	sei(old_int);
}

static inline void icache_lock(void)
{
	uint32_t old_int = cli();

	/* no need to clean entries, directly flush and lock cache */
	asm volatile (
		/* flush cache pages */
		"MCR p15, 0, R0, c7, c5, 0\n"

		/* enable cache lockdown for segment 0 (of 4) */
		"MOV R0, #0x80000000\n"
		"MCR p15, 0, R0, c9, c0, 1\n"

		/* finalize lockdown */
		"MOV R0, #1\n"
		"MCR p15, 0, R0, c9, c0, 1\n"

		:
		:
		: "r0"
	);

	/* make sure all entries are set to invalid */
	uint32_t index;
	for(index = 0; index < (1U<<CACHE_INDEX_BITS(TYPE_ICACHE)); index++) {
		asm volatile (
			/* write index for address to write */
			"MOV R0, %0, LSL #5\n"
			"MCR p15, 3, R0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, R0, c15, c1, 0\n"

			:
			: "r"(index)
			: "r0"
		);
	}

	sei(old_int);
}

static inline void dcache_lock(void)
{
	uint32_t index;
	uint32_t old_int = cli();

	clean_d_cache();

	/* then lockdown data cache */
	asm volatile (
		/* enable cache lockdown for segment 0 (of 4) */
		"MOV R0, #0x80000000\n"
		"MCR p15, 0, R0, c9, c0, 0\n"

		/* finalize lockdown */
		"MOV R0, #1\n"
		"MCR p15, 0, R0, c9, c0, 0\n"

		:
		:
		: "r0"
	);

	/* make sure all entries are set to invalid */
	for(index = 0; index < (1U<<CACHE_INDEX_BITS(TYPE_DCACHE)); index++) {
		asm volatile (
			/* write index for address to write */
			"MOV R0, %0, LSL #5\n"
			"MCR p15, 3, R0, c15, c0, 0\n"
			/* set TAG at given index */
			"MCR p15, 3, R0, c15, c2, 0\n"

			:
			: "r"(index)
			: "r0"
		);
	}

	sei(old_int);
}

/* these are the "public" functions. please use only these if you are not sure what the others are for */

uint32_t cache_locked(void)
{
	uint32_t status = 0;
	asm volatile (
		/* get lockdown status */
		"MRC p15, 0, %0, c9, c0, 1\n"

		: "=r"(status)
		:
		: "r0"
	);

	return status;
}

inline void cache_lock(void)
{
	icache_lock();
	dcache_lock();
}

void cache_unlock(void)
{
	icache_unlock();
	dcache_unlock();
}

uint32_t cache_fake(uint32_t address, uint32_t data, uint32_t type)
{
	/* that word is already patched? return failure */
	/* Disabled, as it always returns FALSE */
	if(FALSE && !cache_is_patchable(address, type)) {
		return 0;
	}

	/* is that line not in cache yet? */
	if(!cache_get_cached(address, type)) {
		/* no, then fetch it */
		cache_fetch_line(address, type);
	}

	return cache_patch_single_word(address, data, type);
}

void flush_caches(void)
{
	uint32_t reg = 0;

	asm(
		"MOV %0, #0\n"
		"MCR p15, 0, %0, c7, c5, 0\n" // entire I cache
		"MOV %0, #0\n"
		"MCR p15, 0, %0, c7, c6, 0\n" // entire D cache
		"MCR p15, 0, %0, c7, c10, 4\n" // drain write buffer

		:
		: "r"(reg)
	);
}

