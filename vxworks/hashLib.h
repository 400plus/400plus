#ifndef VXWORKS_HASHLIB_H_
#define VXWORKS_HASHLIB_H_

#include "sllLib.h"
#include "vxworks.h"

typedef struct {} *HASH_ID;
typedef struct {}  HASH_TBL;
typedef struct {}  HASH_NODE;
typedef struct {}  H_NODE_INT;
typedef struct {}  H_NODE_STRING;

extern STATUS     hashLibInit       (void);
extern HASH_ID    hashTblCreate     (int sizeLog2, FUNCPTR keyCmpRtn, FUNCPTR keyRtn, int keyArg);
extern STATUS     hashTblInit       (HASH_TBL *pHashTbl, SL_LIST *pTblMem, int sizeLog2, FUNCPTR keyCmpRtn, FUNCPTR keyRtn, int keyArg);
extern STATUS     hashTblDelete     (HASH_ID hashId);
extern STATUS     hashTblTerminate  (HASH_ID hashId);
extern STATUS     hashTblDestroy    (HASH_ID hashId, BOOL dealloc);
extern STATUS     hashTblPut        (HASH_ID hashId, HASH_NODE *pHashNode);
extern HASH_NODE *hashTblFind       (HASH_ID hashId, HASH_NODE *pMatchNode, int keyCmpArg);
extern STATUS     hashTblRemove     (HASH_ID hashId, HASH_NODE *pHashNode);
extern HASH_NODE *hashTblEach       (HASH_ID hashId, FUNCPTR routine, int routineArg);
extern int        hashFuncIterScale (int elements, H_NODE_STRING *pHNode, int seed);
extern int        hashFuncModulo    (int elements, H_NODE_INT *pHNode, int divisor);
extern int        hashFuncMultiply  (int elements, H_NODE_INT *pHNode, int multiplier);
extern BOOL       hashKeyCmp        (H_NODE_INT *pMatchHNode, H_NODE_INT *pHNode, int keyCmpArg);
extern BOOL       hashKeyStrCmp     (H_NODE_STRING *pMatchHNode, H_NODE_STRING *pHNode, int keyCmpArg);

#endif /* VXWORKS_HASHLIB_H_ */
