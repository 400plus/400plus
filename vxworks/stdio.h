#ifndef VXWORKS_STDIO_H_
#define VXWORKS_STDIO_H_

#include "vxworks.h"

void    clearerr      (FILE *fp);
int     fclose        (FILE *fp);
FILE   *fdopen        (int fd, const char *mode);
int     feof          (FILE *fp);
int     ferror        (FILE *fp);
int     fflush        (FILE *fp);
int     fgetc         (FILE *fp);
int     fgetpos       (FILE *fp, fpos_t *pos);
char   *fgets         (char *buf, size_t n, FILE *fp);
int     fileno        (FILE *fp);
FILE   *fopen         (const char *file, const char *mode);
int     fprintf       (FILE *fp, const char *fmt, ...);
int     fputc         (int c, FILE *fp);
int     fputs         (const char *s, FILE *fp);
int     fread         (void *buf, size_t size, size_t count, FILE *fp);
FILE   *freopen       (const char *file, const char *mode, FILE *fp);
int     fscanf        (FILE *fp, char const *fmt, ...);
int     fseek         (FILE *fp, long offset, int whence);
int     fsetpos       (FILE *iop, const fpos_t *pos);
long    ftell         (FILE *fp);
int     fwrite        (const void *buf, size_t size, size_t count, FILE *fp);
int     getc          (FILE *fp);
int     getchar       (void);
char   *gets          (char *buf);
int     getw          (FILE *fp);
void    perror        (const char *__s);
int     putc          (int c, FILE *fp);
int     putchar       (int c);
int     puts          (char const *s);
int     putw          (int w, FILE *fp);
void    rewind        (FILE *fp);
int     scanf         (char const *fmt, ...);
void    setbuf        (FILE *fp, char *buf);
void    setbuffer     (FILE *fp, char *buf, int size);
int     setlinebuf    (FILE *fp);
int     setvbuf       (FILE *fp, char *buf, int mode, size_t size);
STATUS  stdioInit     (void);
FILE   *stdioFp       (int stdFd);
STATUS  stdioShowInit (void);
STATUS  stdioShow     (FILE *fp, int level);
FILE   *tmpfile       (void);
char   *tmpnam        (char *s);
int     ungetc        (int c, FILE *fp);
int     vfprintf      (FILE *fp, const char *fmt, va_list vaList);

#endif /*VXWORKS_STDIO_H_ */
