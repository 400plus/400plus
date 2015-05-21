.text
.org 0

#define DEF(addr, name) \
	.globl name;        \
	name = addr

#define NSTUB(addr, name) \
	.globl name;          \
	.weak name;           \
	name:;                \
	ldr  pc, = addr
