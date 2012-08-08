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

typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned long    uint32_t;

typedef long FILE;

typedef long unsigned int size_t;
typedef long unsigned int fpos_t;
typedef long unsigned int off_t;

typedef      unsigned int time_t;

struct timespec {
	time_t tv_sec;   /* seconds */
	long   tv_nsec;  /* nanoseconds */
};

struct tm {
	int tm_sec;         /* seconds */
	int tm_min;         /* minutes */
	int tm_hour;        /* hours */
	int tm_mday;        /* day of the month */
	int tm_mon;         /* month */
	int tm_year;        /* year */
	int tm_wday;        /* day of the week */
	int tm_yday;        /* day in the year */
	int tm_isdst;       /* daylight saving time */
};

struct lens_info {
	short id;
	short max_mm;
	short min_mm;
	short not_used;
	char *name;
} __attribute__((packed));

#endif // TYPES_H_
