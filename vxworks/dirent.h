#ifndef VXWORKS_DIRENT_H_
#define VXWORKS_DIRENT_H_

#include "vxworks.h"

/* We do not really care what is inside DIR */
typedef struct {} DIR;

struct dirent {
	/* No other info available */
	char *d_name;
};

extern DIR           *opendir   (const char *);
extern struct dirent *readdir   (DIR *);
extern void           rewinddir (DIR *);
extern STATUS         closedir  (DIR *);

#endif /* VXWORKS_DIRENT_H_ */
