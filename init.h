#ifndef INIT_H_
#define INIT_H_

extern void COPY();

extern void my_romStart(int startType);
extern int  my_usrInit(int startType);
extern int  my_usrRoot(char* pMemPoolStart, unsigned int memPoolSize);

extern void my_taskcreate_Startup();
void        my_task_Startup();
int         my_InitializeIntercom();

#endif /* INIT_H_ */
