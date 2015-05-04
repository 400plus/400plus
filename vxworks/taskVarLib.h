#ifndef VXWORKS_TASKVARLIB_H_
#define VXWORKS_TASKVARLIB_H_

typedef struct taskVar {
	struct taskVar *next;
	int            *address;
	int             value;
} TASK_VAR;

STATUS taskVarInit   (void);
STATUS taskVarAdd    (int tid, int * pVar);
STATUS taskVarDelete (int tid, int * pVar);
int    taskVarGet    (int tid, int * pVar);
STATUS taskVarSet    (int tid, int * pVar, int value);
int    taskVarInfo   (int tid, TASK_VAR varList[], int maxVars);

#endif /* VXWORKS_TASKVARLIB_H_ */
