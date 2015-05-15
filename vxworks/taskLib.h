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

STATUS  taskOptionsSet  (int tid, int mask, int newOptions);
STATUS  taskOptionsGet  (int tid, int *pOptions);
STATUS  taskRegsGet     (int tid, REG_SET *pRegs);
STATUS  taskRegsSet     (int tid, REG_SET *pRegs);
char   *taskName        (int tid);
int     taskNameToId    (char *name);
int     taskIdDefault   (int tid);
BOOL    taskIsReady     (int tid);
BOOL    taskIsSuspended (int tid);
int     taskIdListGet   (int idList[], int maxTasks);

#endif /* VXWORKS_TASKLIB_H_ */
