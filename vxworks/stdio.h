#ifndef VXWORKS_STDIO_H_
#define VXWORKS_STDIO_H_

#include "vxworks.h"

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
extern int     fsetpos       (FILE *iop, const fpos_t *pos);
extern long    ftell         (FILE *fp);
extern int     fwrite        (const void *buf, size_t size, size_t count, FILE *fp);
extern int     getc          (FILE *fp);
extern int     getchar       (void);
extern char   *gets          (char *buf);
extern int     getw          (FILE *fp);
extern void    perror        (const char *__s);
extern int     putc          (int c, FILE *fp);
extern int     putchar       (int c);
extern int     puts          (char const *s);
extern int     putw          (int w, FILE *fp);
extern void    rewind        (FILE *fp);
extern int     scanf         (char const *fmt, ...);
extern void    setbuf        (FILE *fp, char *buf);
extern void    setbuffer     (FILE *fp, char *buf, int size);
extern int     setlinebuf    (FILE *fp);
extern int     setvbuf       (FILE *fp, char *buf, int mode, size_t size);
extern STATUS  stdioInit     (void);
extern FILE   *stdioFp       (int stdFd);
extern STATUS  stdioShowInit (void);
extern STATUS  stdioShow     (FILE *fp, int level);
extern FILE   *tmpfile       (void);
extern char   *tmpnam        (char *s);
extern int     ungetc        (int c, FILE *fp);
extern int     vfprintf      (FILE *fp, const char *fmt, va_list vaList);

#endif /*VXWORKS_STDIO_H_ */
