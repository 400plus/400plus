/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef STDIO_H_
#define STDIO_H_

#include <types.h>
#include <stdarg.h>

extern void     clearerr(FILE *);

extern char    *ctermid(char *);

extern int      fclose(FILE *);

extern FILE    *fdopen(int, const char *);

extern int      feof(FILE *);
extern int      ferror(FILE *);
extern int      fflush(FILE *);
extern int      fgetc(FILE *);
extern int      fgetpos(FILE *, fpos_t *);
extern char    *fgets(char *, int, FILE *);

extern int      fileno(FILE *);

extern void     flockfile(FILE *);

extern FILE    *fopen(const char *, const char *);
extern int      fprintf(FILE *, const char *, ...);
extern int      fputc(int, FILE *);
extern int      fputs(const char *, FILE *);
extern size_t   fread(void *, size_t, size_t, FILE *);
extern FILE    *freopen(const char *, const char *, FILE *);
extern int      fscanf(FILE *, const char *, ...);
extern int      fseek(FILE *, long, int);

extern int      fseeko(FILE *, off_t, int);

extern int      fsetpos(FILE *, const fpos_t *);
extern long     ftell(FILE *);

extern off_t    ftello(FILE *);

extern int      ftrylockfile(FILE *);
extern void     funlockfile(FILE *);

extern size_t   fwrite(const void *, size_t, size_t, FILE *);
extern int      getc(FILE *);
extern int      getchar(void);

extern int      getc_unlocked(FILE *);
extern int      getchar_unlocked(void);

extern char    *gets(char *);

extern int      pclose(FILE *);

extern void     perror(const char *);

extern FILE    *popen(const char *, const char *);

extern int      printf(const char *, ...);
extern int      putc(int, FILE *);
extern int      putchar(int);

extern int      putc_unlocked(int, FILE *);
extern int      putchar_unlocked(int);

extern int      puts(const char *);
extern int      remove(const char *);
extern int      rename(const char *, const char *);
extern void     rewind(FILE *);
extern int      scanf(const char *, ...);
extern void     setbuf(FILE *, char *);
extern int      setvbuf(FILE *, char *, int, size_t);
extern int      snprintf(char *, size_t, const char *, ...);
extern int      sprintf(char *, const char *, ...);
extern int      sscanf(const char *, const char *, int, ...);

extern char    *tempnam(const char *, const char *);

extern FILE    *tmpfile(void);
extern char    *tmpnam(char *);
extern int      ungetc(int, FILE *);
extern int      vfprintf(FILE *, const char *, va_list);
extern int      vfscanf(FILE *, const char *, va_list);
extern int      vprintf(const char *, va_list);
extern int      vscanf(const char *, va_list);
extern int      vsnprintf(char *, size_t, const char *, va_list);
extern int      vsprintf(char *, const char *, va_list);
extern int      vsscanf(const char *, const char *, va_list);

#endif
