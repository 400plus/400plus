#ifndef TASK_H_
#define TASK_H_

extern void RiseEvent(char *name);

extern int CreateTask(const char *name, int prio, int stack_size, void *entry, long parm);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

#endif /* TASK_H_ */
