#ifndef VXWORKS_SETJMP_H_
#define VXWORKS_SETJMP_H_

#include "vxworks.h"

typedef struct _jmp_buf {
	REG_SET reg;
	int     extra[3];
} jmp_buf[1];

typedef struct _sigjmp_buf {
	REG_SET regs;
	int     extra[3];
} sigjmp_buf[1];

extern int  setjmp     (jmp_buf __env);
extern void longjmp    (jmp_buf __env, int __val);
extern int  sigsetjmp  (sigjmp_buf __env);
extern void siglongjmp (sigjmp_buf __env, int __val);

#endif /* VXWORKS_SETJMP_H_ */
