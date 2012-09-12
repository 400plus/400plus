/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef TYPES_H_
#define TYPES_H_

#ifndef EOF
#define EOF -1
#define O_RDONLY  0x0000
#define O_WRONLY  0x0001
#define O_RDWR    0x0002
#define O_CREAT   0x0200
#define O_TRUNC   0x0400
#endif

typedef unsigned int     uint_t;
typedef unsigned long    ulong_t;

typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned long    uint32_t;

typedef long FILE;

typedef long unsigned int size_t;
typedef long unsigned int fpos_t;
typedef long unsigned int off_t;

typedef uint_t mode_t;

typedef int  clockid_t;
typedef	long clock_t;
typedef	long time_t;

#endif // TYPES_H_
