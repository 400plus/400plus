#ifndef VXWORKS_STDIO_H_
#define VXWORKS_STDIO_H_

#include "vxworks.h"
#include "stdarg.h"

#define	EOF	(-1)

#define	SEEK_SET 0
#define	SEEK_CUR 1
#define	SEEK_END 2

typedef struct _file *FILE;

/* fioLib.S */
extern int printf    (const char *fmt, ...);
extern int printErr  (const char *fmt, ...);
extern int fdprintf  (int fd, const char *fmt, ...);
extern int sprintf   (char *buffer, const char *fmt, ...);
extern int vprintf   (const char *fmt, va_list vaList);
extern int vfdprintf (int fd, const char *fmt, va_list vaList);
extern int vsprintf  (char *buffer, const char *fmt, va_list vaList);
extern int sscanf    (const char *str, const char *fmt, ...);

/* ansiStdio.S */
extern void    clearerr      (FILE *fp);
extern int     fclose        (FILE *fp);
extern FILE   *fdopen        (int fd, const char *mode);
extern int     feof          (FILE *fp);
extern int     ferror        (FILE *fp);
extern int     fflush        (FILE *fp);
extern int     fgetc         (FILE *fp);
extern int     fgetpos       (FILE *fp, fpos_t *pos);
extern char   *fgets         (char *buf, size_t n, FILE *fp);
extern int     fileno        (FILE *fp);
extern FILE   *fopen         (const char *file, const char *mode);
extern int     fprintf       (FILE *fp, const char *fmt, ...);
extern int     fputc         (int c, FILE *fp);
extern int     fputs         (const char *s, FILE *fp);
extern int     fread         (void *buf, size_t size, size_t count, FILE *fp);
extern FILE   *freopen       (const char *file, const char *mode, FILE *fp);
extern int     fscanf        (FILE *fp, char const *fmt, ...);
extern int     fseek         (FILE *fp, long offset, int whence);
extern int     fsetpos       (FILE *fp, const fpos_t *pos);
extern long    ftell         (FILE *fp);
extern int     fwrite        (const void *buf, size_t size, size_t count, FILE *fp);
extern int     getc          (FILE *fp);
extern int     getchar       (void);
extern char   *gets          (char *buf);
extern void    perror        (const char *__s);
extern int     putc          (int c, FILE *fp);
extern int     putchar       (int c);
extern int     puts          (char const *s);
extern void    rewind        (FILE *fp);
extern int     scanf         (char const *fmt, ...);
extern void    setbuf        (FILE *fp, char *buf);
extern int     setvbuf       (FILE *fp, char *buf, int mode, size_t size);
extern FILE   *tmpfile       (void);
extern char   *tmpnam        (char *s);
extern int     ungetc        (int c, FILE *fp);
extern int     vfprintf      (FILE *fp, const char *fmt, va_list vaList);

/* stdioLib.S */
extern STATUS   stdioInit     (void);
extern FILE    *stdioFp       (int stdFd);
extern STATUS   stdioShowInit (void);
extern STATUS   stdioShow     (FILE *fp, int level);
extern FILE   **__stdin       (void);
extern FILE   **__stdout      (void);
extern FILE   **__stderr      (void);

#define stdin	(*__stdin())
#define stdout	(*__stdout())
#define stderr	(*__stderr()

#endif /*VXWORKS_STDIO_H_ */
