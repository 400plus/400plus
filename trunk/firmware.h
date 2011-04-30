#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include "vxworks.h"

// Variables, Flags, Pointers, Handlers
extern unsigned int	  BodyID;
extern unsigned short ModelID;

extern int BurstCounter;  // remaining shots in burst mode (displayed in VF's bottom right corner)
extern int hInfoCreative; // dialog handler for info screen
extern int FaceStatus;    // 0 = no face, 1 = face (disp off)... see #32, this could give some solution
extern int GUIMode;
extern int hFaMain;       // Factory Dialog
extern int hMnBg;         // Menu Dialog

extern void *DPData; // CameraMode

extern int logMsg(char *, ...);

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern int   strlen(const char *);
extern char *strncpy(char *destination, const char *source, int length);
extern void  sprintf(const char*, char*, ...);

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
extern int printErr(char * fmt, ...); // like printf but prints to stderr

extern FILE *fopen(const char *file, const char *mode);
extern FILE *fdopen(int fd, char * mode);
extern int   fread(void *buffer, long size, long count, FILE *fp);
extern int   fwrite(const void *buffer, long size, long count, FILE *fp);
extern int   fclose(FILE *fp);

extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);
extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);

// free space is reported in KB, drvltr is "A:"
extern int FP_GetDriveFreeSpace(char * drv_letter, int * result);

extern void *OpenLogFile(char *name);
extern void  CloseLogFile(void *logFile);

// Task management

extern void RiseEvent(char *name);

extern int* CreateTask(const char *name, int prio, int stack_size, void *entry, long parm);
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

// Semaphores

extern SEM_ID CreateBinarySemaphore(char * name, SEM_B_STATE state); // SEM_EMPTY (0), SEM_FULL (1)
extern int TakeSemaphore(SEM_ID sem, int time);
extern int GiveSemaphore(SEM_ID sem);
extern int DeleteSemaphore(int* sem);

// Event generation

extern int eventproc_PrintICUInfo();
extern int eventproc_RiseEvent(const char *event);
extern int eventproc_Release();

extern int pressButton_(int button);

// Display

extern int CreateDialogBox(int parm1, int parm2, void (*btn_handler), int template);
extern int DeleteDialogBox(int dialog);
#define dialog_redraw do_some_with_dialog
extern int do_some_with_dialog(int dialog);
#define dialog_set_property_int sub_FF8382DC
extern int   sub_FF8382DC(int dialog, const int code, const int data);
#define dialog_set_property_str sub_FF837FA8
extern int   sub_FF837FA8(int dialog, const int code, const char *text);

extern void InfoCreativeAppProc();

extern char *sub_FF83A640(); // cf free space - reports wrong ?

// Factory mode and debugging

extern int EnterFactoryMode();
extern int ExitFactoryMode();

extern int ioGlobalStdSet(int handle, int file);

// Shutter stuff

extern int *hRelSem;	// semaphore handle, used for Camera Busy Flag too
extern char *aRelSem;   // semaphore name
// Remote shutter stuff -- this variables can help us detect any remote (may be)
extern int RemPulseWidthMin;
extern int RemPulseWidthMax;
extern int RemPulseDiffMin;
extern int RemPulseDiffMax;
extern int RemReleaseInstMin;
extern int RemReleaseInstMax;
extern int RemReleaseSelfMin;
extern int RemReleaseSelfMax;

// Language

extern void GetLanguageStr(int lang_id, char * lang_str);

#endif /* FIRMWARE_H_ */
