/*
 * Copyright (C) 2001,2002 IDEALX (http://www.idealx.com/).
 * Written by Gilles Chanteperdrix <gilles.chanteperdrix@xenomai.org>.
 * Copyright (C) 2003 Philippe Gerum <rpm@xenomai.org>.
 *
 * Xenomai is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Xenomai is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xenomai; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * This file satisfies the references within the emulator code
 * mimicking a VxWorks-like API built upon the XENOMAI nanokernel.
 *
 * VxWorks is a registered trademark of Wind River Systems, Inc.
 *
 *
 *
 *
 *
 * http://svn.gna.org/svn/xenomai/trunk/include/vxworks/
 * modified for 400plus convenience
 *
 */

#ifndef _XENO_VXWORKS_VXWORKS_H
#define _XENO_VXWORKS_VXWORKS_H

#define XNOBJECT_NAME_LEN 32

#define VXWORKS_SKIN_VERSION_STRING  "5"
#define VXWORKS_SKIN_VERSION_CODE    0x00000005
#define VXWORKS_SKIN_MAGIC           0x57494E44

#undef STATUS
typedef int STATUS;
typedef int BOOL;

#define OK    (0)
#define ERROR (-1)

/* errno values in some functions */
#define WIND_MEM_ERR_BASE   0x00110000
#define WIND_OBJ_ERR_BASE   0x003d0000
#define WIND_INT_ERR_BASE   0x00430000

#define S_objLib_OBJ_ID_ERROR                   (WIND_OBJ_ERR_BASE + 0x0001)
#define S_objLib_OBJ_UNAVAILABLE                (WIND_OBJ_ERR_BASE + 0x0002)
#define S_objLib_OBJ_DELETED                    (WIND_OBJ_ERR_BASE + 0x0003)
#define S_objLib_OBJ_TIMEOUT                    (WIND_OBJ_ERR_BASE + 0x0004)

#define S_intLib_NOT_ISR_CALLABLE               (WIND_INT_ERR_BASE + 0x0001)

#define S_memLib_NOT_ENOUGH_MEMORY              (WIND_MEM_ERR_BASE + 0x0001)

/* defines for basic tasks handling */
/* Task Options: */

/* do not allow breakpoint debugging. */
#define VX_UNBREAKABLE   0x0002
/* execute with floating-point coprocessor support. */
#define VX_FP_TASK       0x0008
/* include private environment support (see envLib). */
#define VX_PRIVATE_ENV   0x0080
/* do not fill the stack for use by checkStack(). */
#define VX_NO_STACK_FILL 0x0100

/* timeouts when waiting for semaphores */
#define NO_WAIT (0)
#define WAIT_FOREVER (-1)

typedef short SEM_ID;
/*for binary semaphores */
typedef enum {
	SEM_EMPTY =0,
	SEM_FULL =1
} SEM_B_STATE;
typedef short WDOG_ID;
typedef short TASK_ID;

typedef unsigned int  UINT;
typedef unsigned long ULONG;

typedef int  (*FUNCPTR)     (void);
typedef void (*VOIDFUNCPTR) (void);

typedef struct WIND_TCB_PLACEHOLDER {
	TASK_ID handle;
} WIND_TCB_PLACEHOLDER;

#define WIND_READY   0x0
#define WIND_SUSPEND 0x1
#define WIND_PEND    0x2
#define WIND_DELAY   0x4
#define WIND_DEAD    0x8
#define WIND_STOP    0x10 /* Never reported. */

typedef struct _TASK_DESC {
	TASK_ID td_tid;
	char    td_name[XNOBJECT_NAME_LEN];
	int	td_priority;
	int	td_status;
	int	td_flags;
	FUNCPTR	td_entry;
	int	td_stacksize;
	char	*td_pStackBase;
	char	*td_pStackEnd;
	char	*td_pExcStackBase;
	char	*td_pExcStackEnd;
	int	td_errorStatus;
	unsigned long td_opaque;
} TASK_DESC;

typedef void (*wind_timer_t)(long);
typedef struct wind_wd_utarget {
	wind_timer_t handler;
	long arg;
} wind_wd_utarget_t;
typedef void (*wind_tick_handler_t)(long);


STATUS sysClkConnect(wind_tick_handler_t routine, long arg);
void tickAnnounce(void);
int *wind_current_context_errno(void);

/*
 * The following macros return normalized or native VxWorks priority
 * values. The core scheduler uses an ascending [0-257] priority scale
 * (include/nucleus/sched.h), whilst the VxWorks personality exhibits
 * a decreasing scale [255-0]; normalization is done in the [1-256]
 * range so that priority 0 is kept for non-realtime shadows.
 */
#define wind_normalized_prio(prio)  \
	({ int __p = (prio) ? XNSCHED_RT_MAX_PRIO - (prio) - 1 : 0; __p; })
#define wind_denormalized_prio(prio) \
	({ int __p = (prio) ? 256 - (prio) : 0; __p; })

STATUS taskRestart(TASK_ID task_id);
TASK_ID	taskSpawn(const char *name,
			int prio,
			int flags,
			int stacksize,
			FUNCPTR entry,
			long arg0, long arg1, long arg2, long arg3, long arg4,
			long arg5, long arg6, long arg7, long arg8, long arg9);
STATUS	taskActivate(TASK_ID task_id);
STATUS	taskDelete(TASK_ID task_id);
STATUS	taskDeleteForce(TASK_ID task_id);
STATUS	taskSuspend(TASK_ID task_id);
STATUS	taskResume(TASK_ID task_id);
STATUS	taskPrioritySet(TASK_ID task_id, int prio);
STATUS	taskPriorityGet(TASK_ID task_id, int *pprio);
void	taskExit(int code);
STATUS	taskLock(void);
STATUS	taskUnlock(void);
TASK_ID	taskIdSelf(void);
STATUS	taskSafe(void);
STATUS	taskUnsafe(void);
STATUS	taskDelay(int ticks);
STATUS	taskIdVerify(TASK_ID task_id);

STATUS semGive(SEM_ID sem_id);
STATUS semTake(SEM_ID sem_id, int timeout);

WDOG_ID wdCreate(void);
STATUS wdDelete(WDOG_ID wdog_id);
STATUS wdStart(WDOG_ID wdog_id, int timeout, wind_timer_t handler, long arg);
STATUS wdCancel(WDOG_ID wdog_id);

void sysClkDisable(void);
void sysClkEnable(void);
int sysClkRateGet(void);
STATUS sysClkRateSet(int ticksPerSecond);
ULONG tickGet(void);
void tickSet(ULONG ticks);

#endif /* !_XENO_VXWORKS_VXWORKS_H */
