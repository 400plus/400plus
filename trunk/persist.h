/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef PERSIST_H_
#define PERSIST_H_

#define PERSIST_FILE    "A:/PERSIST"
#define PERSIST_VERSION 0x00

#include "exposure.h"
#include "scripts.h"

typedef struct {
	ec_t      ev_comp;     // Exposure compensation for AutoISO + M
	script_t  last_script; // Last executed script
	int       last_page;   // Last page visited in main menu
	int       aeb;         // Last AEB used
} persist_t;

extern persist_t persist;

extern int  persist_read ();
extern void persist_write();

#endif
