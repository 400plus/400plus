    .text
    .org 0
    .globl _start, start

start:
_start:
                BL      COPY
                LDR     R0, =0xC0220000
                LDR     R1, =0x46
                STR     R1, [R0]

                LDR     R0, =0xC0100000
                LDR     R1, =0x4D3
                STR     R1, [R0]
                LDR     R0, =0xC0400000
                LDR     R1, =0x410005
                STR     R1, [R0,#8]
                MOV     R0, #0xC0000000
                LDR     R1, =0xD9C50000
                STR     R1, [R0,#0x10]
                LDR     SP, =0x1900
                MOV     R11, #0
                LDR     PC, =my_romStart


.align 2
fin:
