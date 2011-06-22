#ifndef DEBUG_H_
#define DEBUG_H_

#include "firmware.h"

#define debug_log(f, p...) printf_log(8, 8, "[400Plus] %s[%d]: " f, __FILE__, __LINE__, ##p);

#endif // DEBUG_H_
