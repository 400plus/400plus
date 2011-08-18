#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include "main.h"
#include "vxworks.h"
#include "types.h"

// Variables, Flags, Pointers, Handlers
extern unsigned int   BodyID;
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

// Memory management
extern void * AllocateMemory( unsigned int len );

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern int   strlen(const char *);
extern char *strncpy(const char *destination, const char *source, int length);
extern void  sprintf(const char*, const char*, ...);
extern int   isspace(int c);


// Queue management

extern int *CreateMessageQueue(const char *nameMessageQueue, int param);
extern int  ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  PostMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  TryPostMessageQueue(void *hMessageQueue, void *pMessage, int forever);

// File management
extern int open(const char *name, int flags, int mode);
extern int read(int fd, void *buffer, size_t nbytes);
extern int write(int fd, void *buffer, size_t nbytes);
extern int close(int fd);

extern int printf(const char *format, ...);         // printf to stdout
extern int printErr(const char *, ...);             // printf to stderr
extern int printf_log(int, int, const char *, ...); // printf to the log system
extern int fprintf (FILE *fp, const char *fmt, ...);// printf to FILE stream
extern int fdprintf(int fd, char *format, ...);     // printf to FD

// FIO
extern long fdConsole; // fd of stdout
extern FILE *fopen(const char *file, const char *mode);
extern FILE *freopen(const char * file, const char * mode, FILE * fp);
extern FILE *fdopen(int fd, char * mode);
extern int   fclose(FILE *fp);
extern int   fileno(FILE *fp); // return FD for the FILE stream
extern int   fread(void *buffer, size_t size, size_t count, FILE *fp);
extern int   fwrite(const void *buffer, size_t size, size_t count, FILE *fp);
extern int   fseek(FILE * fp, long offset, int whence);
extern long  ftell(FILE * fp);
extern int   feof(FILE *fp);   // test for EOF
extern int   ferror(FILE *fp); // test for error
extern int   fflush(FILE *fp);
extern int   fgetc(FILE *fp);
extern int   fgets(char * buf, size_t n, FILE *fp);
extern int   fscanf(FILE * fp, char const * fmt, ...);
extern int   fputs (const char * s, FILE * fp);

// we do not have fpos_t
//extern int   fgetpos(FILE *fp, fpos_t *pos);
//extern int   fsetpos(FILE *iop, const fpos_t * pos);
//extern int   fioFormatV(const char *fmt, va_list vaList, FUNCPTR outRoutine, int outarg); // convert a format string


// Time functions
extern time_t time(time_t *t); // returns timestamp, and sets arg1 if pointer is provided
extern int clock_gettime(int clock_id/* 0 */, struct timespec *tp); // return 0 on success
extern struct tm * localtime_r(time_t *time, struct tm*);

// File IO
extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);
extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);
extern void FIO_GetFileSize(char * file, int * size);
extern void FIO_SeekFile(int fd, long offset, int whence); // whence: SEEK_SET=0, SEEK_CUR=1, SEEK_END=2

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
extern SEM_ID hMainCtrlMonoSem;

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

extern int PaletteChange(int color);

// Factory mode and debugging

extern int EnterFactoryMode();
extern int ExitFactoryMode();

extern int ioGlobalStdSet(int handle, int file);

// Shutter stuff

extern int *hRelSem;	// semaphore handle, used for Camera Busy Flag too
extern char aRelSem[];   // semaphore name

// Remote shutter stuff -- this variables can help us detect any remote (may be)

extern int RemPulseWidthMin;
extern int RemPulseWidthMax;
extern int RemPulseDiffMin;
extern int RemPulseDiffMax;
extern int RemReleaseInstMin;
extern int RemReleaseInstMax;
extern int RemReleaseSelfMin;
extern int RemReleaseSelfMax;

extern int eventproc_RemOn();
extern int eventproc_RemOff();

// Language

extern void GetLanguageStr(int lang_id, char * lang_str);

// MainCtrl
extern int MC_dword_2A520;
extern int MC_dword_259C0;
extern int MC_State;
extern int MC_dword_26940;
extern int MC_dword_27BE0;
extern int dword_1C78;
extern int SendToMC_T_28();
extern int proc_CardDoor_Emergency();
extern int ErrorDetectActSweep();
extern int * hMainMessQueue;
extern int * hMainDataQueue;
extern int GetMainPreserveData_field_1C();
extern void task_MainCtrl();
// task_MainCtrl
extern int err_MC_T;
extern void sub_FF825078();
extern int MC_T_Table[];
extern char aMcT04dS04xD[];
extern char aMainMessQueue[];
extern char aMainDataQueue[];
extern int  DriveNotifyCallBack();
extern int  ChangeNotifyCallback_MC();
extern char aMainCannotPowo[];
extern char aMainCtrl[];
extern char aMonoSem[];
// mc_button
extern char asw04d04d[];
extern int PowerFlag;
extern int *some_important_structure;
extern int unk_258A0;
extern void DDD_Capture(int);
extern void set_2A0E0_to_1();


#endif /* FIRMWARE_H_ */