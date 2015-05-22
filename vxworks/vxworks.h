#ifndef VXWORKS_VXWORKS_H
#define VXWORKS_VXWORKS_H

typedef int BOOL;
typedef int STATUS;

#define OK    (0)
#define ERROR (-1)

#define FALSE 0
#define TRUE  1

typedef unsigned int      UINT;
typedef unsigned long     ULONG;

typedef long unsigned int size_t;

typedef int  (*FUNCPTR)     (void);
typedef void (*VOIDFUNCPTR) (void);

#endif /* VXWORKS_VXWORKS_H */
