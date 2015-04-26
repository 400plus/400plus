#ifndef DIRENT_H_
#define DIRENT_H_

/* We do not really care what is inside DIR */
typedef struct __dirstream DIR;

struct dirent {
	/* No other info available */
	char d_name[256];
};

DIR           *opendir (const char *);
struct dirent *readdir (DIR *);
int            closedir(DIR *);

#endif /* DIRENT_H_ */
