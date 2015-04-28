#ifndef VXWORKS_DIRENT_H_
#define VXWORKS_DIRENT_H_

/* We do not really care what is inside DIR */
typedef DIR;

struct dirent {
	/* No other info available */
	char *d_name;
};

DIR           *opendir   (const char *);
struct dirent *readdir   (DIR *);
extern void    rewinddir (DIR *);
int            closedir  (DIR *);

#endif /* VXWORKS_DIRENT_H_ */
