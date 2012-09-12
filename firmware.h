/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include <vxworks.h>
#include <types.h>

#include "main.h"

// Variables, Flags, Pointers, Handlers
extern /*unsigned*/ int   BodyID;
extern unsigned short ModelID;

extern int BurstCounter;  // remaining shots in burst mode (displayed in VF's bottom right corner)
extern dialog_t * hInfoCreative; // dialog handle for info screen
extern dialog_t * hMainDialog; // the main OLC dialog (white screen)
//#define hMainDialog (dialog_t*)(*(int*)(0x47F0))
extern int FaceStatus;    // 0 = no face, 1 = face (disp off)... see #32, this could give some solution
extern int GUIMode;       // Current GUI Mode
extern int hFaMain;       // Factory Dialog
extern int hMnBg;         // Menu Dialog
extern void *OlcInfoData; // OLC data

extern int logMsg(char *, ...);

// Memory management
extern void * AllocateMemory( unsigned int len );

// LED management

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedOff(void);
extern long eventproc_EdLedBlink(void);

// String management

extern int   Run_UnicodeString_Dataset_c(char *dest, const char *src, size_t size);

// Queue management

extern int *CreateMessageQueue(const char *nameMessageQueue, int param);
extern int  ReceiveMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  PostMessageQueue(void *hMessageQueue, void *pMessage, int forever);
extern int  TryPostMessageQueue(void *hMessageQueue, void *pMessage, int forever);

// StdIO

extern int read(int fd, void *buffer, size_t nbytes);
extern int write(int fd, void *buffer, size_t nbytes);
extern int close(int fd);

extern int printErr(const char *, ...);             // printf to stderr
extern int printf_log(int, int, const char *, ...); // printf to the log system
extern int fdprintf(int fd, char *format, ...);     // printf to FD

// these are wrappers over stdio
extern int FIO_CreateFile(const char *name);
extern int FIO_RemoveFile(const char *name);
extern int FIO_OpenFile(const char *name, int flags, int mode);
extern int FIO_ReadFile(int fd, void *buffer, long nbytes);
extern int FIO_WriteFile(int fd, void *buf, long nbytes);
extern int FIO_CloseFile(int fd);
extern void FIO_GetFileSize(char * file, int * size);
extern void FIO_SeekFile(int fd, long offset, int whence); // whence: SEEK_SET=0, SEEK_CUR=1, SEEK_END=2

// File IO

extern long fdConsole; // fd of stdout

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
extern int IntercomHandlerButton(int button, int unknown);

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

extern dialog_t *CreateDialogBox(int parm1, int parm2, event_handler_t, int template, int is_busy_maybe);
extern int DeleteDialogBox(dialog_t *dialog);
extern int dialog_redraw(dialog_t *dialog);

extern int dialog_item_set_int(dialog_t *dialog, const int code, const int   data);
extern int dialog_item_set_str(dialog_t *dialog, const int code, const char *text);

#define dialog_create(template, handler) CreateDialogBox(0, 0, handler, template, 0)

#define dialog_set_property_int dialog_item_set_int
#define dialog_set_property_str dialog_item_set_str

extern int InfoCreativeAppProc(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);
extern int olc_event_handler(dialog_t * dialog, int *r1, gui_event_t event, int *r3, int r4, int r5, int r6, int code);

extern char *sub_FF83A640(); // cf free space - reports wrong ?

extern int PaletteChange(int color);

extern void GUI_Select_Item  (void *menu_handle, int menu_item);
extern void GUI_Highlight_Sub(void *menu_handle, int menu_item, int enable);
extern void GUI_Disable_Item (void *menu_handle, int menu_item, int enable);

/*PaletteChange(1); //changes menu to blue
// 0 red
// 1 blue
// 2 yelolw
// 0x12 black and white
// other numbers possible
*/

// Factory mode and debugging

extern int EnterFactoryMode();
extern int ExitFactoryMode();
extern int hDbgMgr;
// info on dmSet[Print|Store]Level() routines:
// second arg is bits field, i guess the debug classes has their own bits
// the 3rd arg is the level - 0 == max, 0xff == min
extern int dmSetPrintLevel(int DbgMgr, int dwFlag, int dwLevel);
extern int dmSetStoreLevel(int DbgMgr, int dwFlag, int dwLevel);

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

// gui / idle handler
extern int m_pSendDisplayModeToMC;
extern int GUIIdleFlag;
extern int GUIMode;
extern int m_pSendStartModeToMC;
extern int hGuiSwSem;
extern char aGuiSwSem[];
extern int off_1EE0;
extern int hGUIWindowInstance;
extern int sub_FF92ADD8();
extern int sub_FF92AF8C();
extern int sub_FF92AFD8();
extern int sub_FF92AF58();
extern int GUIWindowInstanceProc();
extern int GUI_IDLEHandler();
extern int * hGuiMainQueue;
extern char aGuiMainQueue[];
extern char aGuiMainTask[];
extern void task_GuiMainTask();
extern void OlcTftNotifyChange();
extern int * hTurnDisplayEventFlag;
extern char aTurndisplayeve[];
extern char aTurndisplaytas[];
extern void task_TurnDisplayTask();



#endif /* FIRMWARE_H_ */
