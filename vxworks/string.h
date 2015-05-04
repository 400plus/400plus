#ifndef VXWORKS_STRING_H_
#define VXWORKS_STRING_H_

#include "vxworks.h"

int   bcmp       (char *buf1, char *buf2, int nbytes);
void  binvert    (char *buf, int nbytes);
void  bswap      (char *buf1, char *buf2, int nbytes);
void  swab       (char *source, char *destination, int nbytes);
void  uswab      (char *source, char *destination, int nbytes);
void  bzero      (char *buffer, int nbytes);
void  bcopy      (const char *source, char *destination, int nbytes);
void  bcopyBytes (char *source, char *destination, int nbytes);
void  bcopyWords (char *source, char *destination, int nwords);
void  bcopyLongs (char *source, char *destination, int nlongs);
void  bfill      (char *buf, int nbytes, int ch);
void  bfillBytes (char *buf, int nbytes, int ch);
char *index      (const char *s, int c);
char *rindex     (const char *s, int c);

#endif /*VXWORKS_STRING_H_ */
