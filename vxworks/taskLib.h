#ifndef VXWORKS_TASKLIB_H_
#define VXWORKS_TASKLIB_H_

/* status */
#define M_taskLib                           0x00030000
#define S_taskLib_NAME_NOT_FOUND            (M_taskLib | 101)
#define S_taskLib_TASK_HOOK_TABLE_FULL      (M_taskLib | 102)
#define S_taskLib_TASK_HOOK_NOT_FOUND       (M_taskLib | 103)
#define S_taskLib_TASK_SWAP_HOOK_REFERENCED (M_taskLib | 104)
#define S_taskLib_TASK_SWAP_HOOK_SET        (M_taskLib | 105)
#define S_taskLib_TASK_SWAP_HOOK_CLEAR      (M_taskLib | 106)
#define S_taskLib_TASK_VAR_NOT_FOUND        (M_taskLib | 107)
#define S_taskLib_TASK_UNDELAYED            (M_taskLib | 108)
#define S_taskLib_ILLEGAL_PRIORITY          (M_taskLib | 109)

/* options */
#define VX_SUPERVISOR_MODE 0x0001
#define VX_UNBREAKABLE     0x0002
#define VX_DEALLOC_STACK   0x0004
#define VX_FP_TASK         0x0008
#define VX_STDIO           0x0010
#define VX_ADA_DEBUG       0x0020
#define VX_FORTRAN         0x0040
#define VX_PRIVATE_ENV     0x0080
#define VX_NO_STACK_FILL   0x0100

typedef struct {} REG_SET;
typedef struct {} WIND_TCB;

typedef struct {
	int      td_id;
	char    *td_name;
	int      td_priority;
	int      td_status;
	int      td_options;
	FUNCPTR  td_entry;
	char    *td_sp;
	char    *td_pStackBase;
	char    *td_pStackLimit;
	char    *td_pStackEnd;
	int      td_stackSize;
	int      td_stackCurrent;
	int      td_stackHigh;
	int      td_stackMargin;
	int      td_errorStatus;
	int      td_delay;
} TASK_DESC;

/* taskLib.S */
extern int       taskSpawn       (char *name, int priority, int options, int stackSize, FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
extern STATUS    taskInit        (WIND_TCB *pTcb, char *name, int priority, int options, char *pStackBase, int stackSize, FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10);
extern STATUS    taskActivate    (int tid);
extern void      exit            (int code);
extern STATUS    taskDelete      (int tid);
extern STATUS    taskDeleteForce (int tid);
extern STATUS    taskSuspend     (int tid);
extern STATUS    taskResume      (int tid);
extern STATUS    taskRestart     (int tid);
extern STATUS    taskPrioritySet (int tid, int newPriority);
extern STATUS    taskPriorityGet (int tid, int *pPriority);
extern STATUS    taskLock        (void);
extern STATUS    taskUnlock      (void);
extern STATUS    taskSafe        (void);
extern STATUS    taskUnsafe      (void);
extern STATUS    taskDelay       (int ticks);
extern int       taskIdSelf      (void);
extern STATUS    taskIdVerify    (int tid);
extern WIND_TCB *taskTcb         (int tid);

/* taskInfo.S */
extern STATUS  taskOptionsSet  (int tid, int mask, int newOptions);
extern STATUS  taskOptionsGet  (int tid, int *pOptions);
extern STATUS  taskRegsGet     (int tid, REG_SET *pRegs);
extern STATUS  taskRegsSet     (int tid, REG_SET *pRegs);
extern char   *taskName        (int tid);
extern int     taskNameToId    (char *name);
extern int     taskIdDefault   (int tid);
extern BOOL    taskIsReady     (int tid);
extern BOOL    taskIsSuspended (int tid);
extern int     taskIdListGet   (int idList[], int maxTasks);

/* taskShow.S */

extern void   taskShowInit(void);
extern STATUS taskInfoGet(int tid, TASK_DESC *pTaskDesc);
extern STATUS taskShow(int tid, int level);
extern void   taskRegsShow(int tid);
extern STATUS taskStatusString(int tid, char *pString);

#endif /* VXWORKS_TASKLIB_H_ */
