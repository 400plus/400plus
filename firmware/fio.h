#ifndef FIO_H_
#define FIO_H_

/* whence value for FIO_SeekSkipFile */

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* File mode attributes, for FindFirst/FindNext */

#define ATTR_NORMAL    0x00  /* normal file */
#define ATTR_READONLY  0x01  /* file is readonly */
#define ATTR_HIDDEN    0x02  /* file is hidden */
#define ATTR_SYSTEM    0x04  /* file is a system file */
#define ATTR_VOLUME    0x08  /* entry is a volume label */
#define ATTR_DIRECTORY 0x10  /* entry is a directory name */
#define ATTR_ARCHIVE   0x20  /* file is new or modified */

extern int  FIO_OpenFile        (const char *filename, int mode);
extern int  FIO_CreateFile      (const char *filename);
extern int  FIO_RemoveFile      (const char *filename);
extern int  FIO_ReadFile        (int fd, void *buffer, size_t count);
extern void FIO_SeekFile        (int fd, long offset, int whence);
extern int  FIO_WriteFile       (int fd, void *buffer, size_t count);
extern void FIO_CloseFile       (int fd);
extern void FIO_GetFileSize     (const char *filename, int *size);
extern int  FIO_CreateDirectory (const char *dirname);

//FIO_GetFileAttributes
//FIO_SetFileAttributes
//FIO_GetFileTime
//FIO_SetFileTime
//FIO_GetFileInfo

#endif
