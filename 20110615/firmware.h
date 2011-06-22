#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include "main.h"
#include "vxworks.h"

// Variables, Flags, Pointers, Handlers
extern unsigned int	  BodyID;
extern unsigned short ModelID;

extern int BurstCounter;  // remaining shots in burst mode (displayed in VF's bottom right corner)
extern type_DIALOG * hInfoCreative; // dialog handle for info screen
#define hMainDialog (type_DIALOG*)(*(int*)(0x47F0))
extern int FaceStatus;    // 0 = no face, 1 = face (disp off)... see #32, this could give some solution
extern int GUIMode;       // Current GUI Mode
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
extern char *strncpy(const char *destination, const char *source, int length);
extern void  sprintf(const char*, const char*, ...);

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

extern int printErr(const char *, ...);
extern int printf_log(int, int, const char *, ...);

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

extern int* CreateTask(const char *name, int prio, int stack_size, void (*entry)(), long parm);
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
extern int IntercomHandlerButton(int button);

// Semaphores

extern SEM_ID CreateBinarySemaphore(char * name, SEM_B_STATE state); // SEM_EMPTY (0), SEM_FULL (1)
extern int TakeSemaphore(SEM_ID sem, int time);
extern int GiveSemaphore(SEM_ID sem);
extern int DeleteSemaphore(int* sem);

// Event generation

extern int eventproc_PrintICUInfo();
extern int eventproc_RiseEvent(const char *event);
extern int eventproc_Release();

// Display

// Handler for buttons in dialogs
typedef int(*type_BTN_HANDLER)(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

extern type_DIALOG *CreateDialogBox(int parm1, int parm2, type_BTN_HANDLER, int template);
extern int DeleteDialogBox(type_DIALOG *dialog);

extern int do_some_with_dialog(type_DIALOG *dialog);

extern int sub_FF8382DC(type_DIALOG *dialog, const int code, const int   data);
extern int sub_FF837FA8(type_DIALOG *dialog, const int code, const char *text);

#define dialog_create(template, handler) CreateDialogBox(0, 0, handler, template)

#define dialog_redraw do_some_with_dialog

#define dialog_set_property_int sub_FF8382DC
#define dialog_set_property_str sub_FF837FA8

extern int InfoCreativeAppProc(type_DIALOG * dialog, int r1, gui_event_t event, int r3, int r4, int r5, int r6, int code);

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
