#ifndef VXWORKS_TASKVARLIB_H_
#define VXWORKS_TASKVARLIB_H_

typedef struct taskVar {
	struct taskVar *next;
	int            *address;
	int             value;
} TASK_VAR;

extern STATUS taskVarInit   (void);
extern STATUS taskVarAdd    (int tid, int * pVar);
extern STATUS taskVarDelete (int tid, int * pVar);
extern int    taskVarGet    (int tid, int * pVar);
extern STATUS taskVarSet    (int tid, int * pVar, int value);
extern int    taskVarInfo   (int tid, TASK_VAR varList[], int maxVars);

#endif /* VXWORKS_TASKVARLIB_H_ */
