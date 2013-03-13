/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MACROS_H_
#define MACROS_H_

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define SIGN(x) (((x) > 0) - ((x) < 0))

#define SWAP(x, y) do {typeof(x) _SWAP_; _SWAP_=(x); (x)=(y); (y)=_SWAP_;} while (0)

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define LIST(  array) {size : LENGTH(array), data : (array)}

#define END_OF_LIST  {_eol_ : true}
#define IS_EOL(item) (item->_eol_)

#endif
