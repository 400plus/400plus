/**
 * $Revision$
 * $Date$
 * $Author$
 */

.text
.org 0

#define DEF(n,a)\
	.globl n;\
	n = a

#define NSTUB(name, addr)\
	.globl name;\
	.weak name;\
	name:;\
	ldr  pc, = addr

#define NHSTUB(name, addr)\
	.globl name;\
	name:;\
	ldr  pc, = addr

#define STUB(addr)\
    .globl sub_ ## addr;\
    sub_ ## addr = 0x ## addr
