#ifndef INFO_H_
#define INFO_H_

#define hInfoCreative (*(int*)(0x0000213C))

typedef enum {
	INFO_OPTION_CAPACITY,
	INFO_OPTION_RELEASE_COUNT,
	INFO_OPTION_400PLUS,
	INFO_OPTION_COUNT,
	INFO_OPTION_FIRST = 0,
	INFO_OPTION_LAST  = INFO_OPTION_COUNT - 1
} type_INFO_OPTION;

extern void  info_option_next();
extern void  info_option_prev();
extern char *info_display();

#endif /* INFO_H_ */
