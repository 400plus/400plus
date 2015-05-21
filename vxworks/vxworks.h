#ifndef VXWORKS_VXWORKS_H
#define VXWORKS_VXWORKS_H

#undef STATUS
typedef int STATUS;
typedef int BOOL;

#define OK    (0)
#define ERROR (-1)

typedef unsigned int  UINT;
typedef unsigned long ULONG;

typedef int  (*FUNCPTR)     (void);
typedef void (*VOIDFUNCPTR) (void);

#endif /* VXWORKS_VXWORKS_H */
