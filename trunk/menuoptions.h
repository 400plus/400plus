/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MENUOPTIONS_H_
#define MENUOPTIONS_H_

typedef struct {
	int    length;
	char **data;
} type_LIST;

extern type_LIST menuoptions_bool;
extern type_LIST menuoptions_flash;
extern type_LIST menuoptions_action;
extern type_LIST menuoptions_logfile;
extern type_LIST menuoptions_btnactn;
extern type_LIST menuoptions_direction;
extern type_LIST menuoptions_languages;
extern type_LIST menuoptions_vformat;
extern type_LIST menuoptions_scrind;
extern type_LIST menuoptions_scrlcd;

#endif
