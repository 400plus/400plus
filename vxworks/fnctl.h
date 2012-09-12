/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef FNCTL_H_
#define FNCTL_H_

#include <types.h>

extern int creat(const char *, mode_t);
extern int fcntl(int, int, ...);
extern int open(const char *, int, ...);

#endif
