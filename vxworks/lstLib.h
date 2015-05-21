#ifndef VXWORKS_LSTLIB_H_
#define VXWORKS_LSTLIB_H_

#include "vxworks.h"

typedef struct {
	struct node *next;
	struct node *previous;
} NODE;

typedef struct {} LIST;

extern void  lstLibInit  (void);
extern void  lstInit     (LIST *pList);
extern void  lstAdd      (LIST *pList, NODE *pNode);
extern void  lstConcat   (LIST *pDstList, LIST *pAddList);
extern int   lstCount    (LIST *pList);
extern void  lstDelete   (LIST *pList, NODE *pNode);
extern void  lstExtract  (LIST *pSrcList, NODE *pStartNode, NODE *pEndNode, LIST *pDstList);
extern NODE *lstFirst    (LIST *pList);
extern NODE *lstGet      (LIST *pList);
extern void  lstInsert   (LIST *pList, NODE *pPrev, NODE *pNode);
extern NODE *lstLast     (LIST *pList);
extern NODE *lstNext     (NODE *pNode);
extern NODE *lstNth      (LIST *pList, int nodenum);
extern NODE *lstPrevious (NODE *pNode);
extern NODE *lstNStep    (NODE *pNode, int nStep);
extern int   lstFind     (LIST *pList, NODE *pNode);
extern void  lstFree     (LIST *pList);

#endif /* VXWORKS_LSTLIB_H_ */
