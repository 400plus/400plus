#define LEDRED (*((int*)0xC02200A0))
#define LEDBLUE (*((int*)0xC0220000))
#define LEDON   0x46
#define LEDOFF  0x44


typedef long FILE;

#define O_RDONLY        0
#define O_WRONLY        1
#define O_RDWR          2
#define O_TRUNC         0x400
#define O_CREAT         0x200

extern int open (const char *name, int flags, int mode );
extern int close (int fd);
extern int write (int fd, void *buffer, long nbytes);
extern int read (int fd, void *buffer, long nbytes);

extern FILE* fopen ( const char *	file, const char *	mode );
extern int fclose ( FILE * fp );
extern int fwrite ( const void * buf, long size, long count, FILE * fp );
extern int fread  ( void * buf, long size, long count, FILE * fp );

extern int FIO_RemoveFile( const char *name );
extern int FIO_CreateFile( const char *name );
extern int FIO_WriteFile(int f, void *buf, long size);
extern int FIO_FileClose ( int f );

extern int CreateTask (const char *name, int prio, int stack_size /*?*/, void *entry, long parm /*?*/);
extern void SleepTask(long msec);
extern void ExitTask(void);

extern void RiseEvent(char *name);

extern long eventproc_EdLedOn(void);
extern long eventproc_EdLedBlink(void);

extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

extern int taskCreateHookAdd (void *createHook);
extern int taskDeleteHookAdd (void *deleteHook);

extern void* OpenLogFile(char* name);
extern void  CloseLogFile(void*);

extern void sprintf(char*, char*, ...);

extern int ReceiveMessageQueue(void* hMessageQueue, void* pMessage, int FOREVER);
extern int PostMessageQueue(void* hMessageQueue, void* pMessage, int FOREVER);

