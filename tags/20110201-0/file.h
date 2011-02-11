#ifndef FILE_H_
#define FILE_H_

typedef long FILE;

#define O_RDONLY  0x0000
#define O_WRONLY  0x0001
#define O_RDWR    0x0002
#define O_CREAT   0x0200
#define O_TRUNC   0x0400

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

#endif /* FILE_H_ */
