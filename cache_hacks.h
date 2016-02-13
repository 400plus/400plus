/*
 * This file comes from Magic Lantern.
 * Thanks to g3gg0 for the idea and implementation.
 * Thanks to Sergei for porting it.
 */

#ifndef _CACHE_HACKS_H_
#define _CACHE_HACKS_H_

#include <vxworks.h>
#include <stdint.h>

#include "asm.h"

/*
 * Canon cameras appear to use the ARMv5 946E.
 * (Confirmed on: 550D, ... )
 *
 * This processor supports a range of cache sizes from no cache (0KB) or
 * 4KB to 1MB in powers of 2. Instruction(icache) and data(dcache) cache sizes
 * can be independent and can not be changed at run time.
 *
 * A cache line is 32 bytes / 8 words / 8 instructions.
 * 	byte address 	(Addr[1:0] = 2 bits)
 * 	word address 	(Addr[4:2] = 2 bits)
 * 	index 			(Addr[i+4:5] = i bits)
 * 	address TAG 	(Addr[31:i+5] = 27 - i bits)
 * Where 'i' is the size of the cache index in bits.
 *
 * There are 2^i cache lines.
 * The index bits from the address select the cache line. The tag bits from the
 * address are compared with the tag of the cache line and if the cache line is
 * valid the byte and word bits extract the data from that cache line.
 *
 * The CP15 Control Register controls cache operation:
 * bit 2  = dcache enable
 * bit 12 = icache enable
 *
 * Self modifying code and reprogramming the protection regions requires a
 * flush of the icache. Writing to CP15 register 7 flushes the
 * cache. Writing a 0 flushes the entire icache. Writing the "FlushAddress"
 * flushes that cache line. Icache automatically flushed on reset. Never needs
 * to be cleaned because it cannot be written to.
 *
 * Dcache is automatically disabled and flushed on reset.
 */

#define TYPE_DCACHE 0
#define TYPE_ICACHE 1

/* get cache size depending on cache type and processor setup (13 -> 2^13 -> 8192 -> 8KiB) */
#define CACHE_SIZE_BITS(t)          cache_get_size(t)

/* depending on cache size, INDEX has different length */
#define CACHE_INDEX_BITS(t)         (CACHE_SIZE_BITS(t)-7)
/* INDEX in tag field starts at bit 5 */
#define CACHE_INDEX_TAGOFFSET(t)    5
/* bitmask that matches the INDEX value bits */
#define CACHE_INDEX_BITMASK(t)      ((1U<<CACHE_INDEX_BITS(t)) - 1)
/* bitmask to mask out the INDEX field in a tag */
#define CACHE_INDEX_ADDRMASK(t)     (CACHE_INDEX_BITMASK(t)<<CACHE_INDEX_TAGOFFSET(t))

/* depending on cache size, TAG has different length */
#define CACHE_TAG_BITS(t)           (27-CACHE_INDEX_BITS(t))
/* TAG in tag field starts at bit 5 plus INDEX size */
#define CACHE_TAG_TAGOFFSET(t)      (5+CACHE_INDEX_BITS(t))
/* bitmask that matches the TAG value bits */
#define CACHE_TAG_BITMASK(t)        ((1U<<CACHE_TAG_BITS(t)) - 1)
/* bitmask to mask out the TAG field in a tag */
#define CACHE_TAG_ADDRMASK(t)       (CACHE_TAG_BITMASK(t)<<CACHE_TAG_TAGOFFSET(t))

/* the WORD field in tags is always 3 bits */
#define CACHE_WORD_BITS(t)          3
/* WORD in tag field starts at this bit position */
#define CACHE_WORD_TAGOFFSET(t)     2
/* bitmask that matches the WORD value bits */
#define CACHE_WORD_BITMASK(t)       ((1U<<CACHE_WORD_BITS(t)) - 1)
/* bitmask to mask out the WORD field in a tag */
#define CACHE_WORD_ADDRMASK(t)      (CACHE_WORD_BITMASK(t)<<CACHE_WORD_TAGOFFSET(t))

/* the SEGMENT field in tags is always 2 bits */
#define CACHE_SEGMENT_BITS(t)       2
/* SEGMENT in tag field starts at this bit position */
#define CACHE_SEGMENT_TAGOFFSET(t)  30
/* bitmask that matches the SEGMENT value bits */
#define CACHE_SEGMENT_BITMASK(t)    ((1U<<CACHE_SEGMENT_BITS(t)) - 1)
/* bitmask to mask out the SEGMENT field in a tag */
#define CACHE_SEGMENT_ADDRMASK(t)   (CACHE_SEGMENT_BITMASK(t)<<CACHE_SEGMENT_TAGOFFSET(t))

extern        uint32_t cache_locked (void);
extern inline void     cache_lock   (void);
extern        void     cache_unlock (void);

extern uint32_t    cache_fake    (uint32_t address, uint32_t data, uint32_t type);

extern void        flush_caches  (void);
extern inline void clean_d_cache (void);

#endif
