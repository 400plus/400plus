#ifndef FIRMWARE_H_
#define FIRMWARE_H_

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern int  strlen(const char *);
extern void sprintf(const char*, char*, ...);

// Queue management

extern int *CreateMessageQueue(const char *nameMessageQueue, int param);
extern int  ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  PostMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  TryPostMessageQueue(void *hMessageQueue, void *pMessage, int forever);

// File management

#define O_RDONLY  0x0000
#define O_WRONLY  0x0001
#define O_RDWR    0x0002
#define O_CREAT   0x0200
#define O_TRUNC   0x0400

typedef long FILE;

extern int open(const char *name, int flags, int mode);
extern int read(int fd, void *buffer, long nbytes);
extern int write(int fd, void *buffer, long nbytes);
extern int close(int fd);

extern FILE* fopen(const char *file, const char *mode);
extern int   fread(void *buffer, long size, long count, FILE *fp);
extern int   fwrite(const void *buffer, long size, long count, FILE *fp);
extern int   fclose(FILE *fp);

extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);

extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);

extern void *OpenLogFile(char *name);
extern void  CloseLogFile(void *logFile);

// Task management

extern void RiseEvent(char *name);

extern int  CreateTask(const char *name, int prio, int stack_size, void *entry, long parm);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void SuspendTask(int *task);
extern void UnSuspendTask(int *task);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

// Task intercommunication

extern int IntercomHandler(const int handler, const char *message);
extern int SendToIntercom(int message, int length, int parm);

// Event generation

extern int eventproc_PrintICUInfo();
extern int eventproc_RiseEvent(const char *event);
extern int eventproc_SetMesMode(const int *metering);
extern int eventproc_SetIsoValue(const int *iso);
extern int eventproc_Release();

extern int pressButton_(int button);

// Display

extern int do_some_with_dialog(int handle);

extern int sub_FF8382DC(int handle, const int code, const int data);
extern int sub_FF837FA8(int handle, const int code, const char *text);

// Factory mode and debugging

extern int EnterFactoryMode();
extern int ExitFactoryMode();

extern int ioGlobalStdSet(int handle, int file);

#endif /* FIRMWARE_H_ */
