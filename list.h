/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef LIST_H_
#define LIST_H_

typedef struct {
	int    length;
	char **data;
} list_t;

#define LIST_T(strings) {length : LENGTH(strings), data : (void*)strings}

#endif
