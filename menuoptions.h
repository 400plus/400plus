#ifndef MENUOPTIONS_H_
#define MENUOPTIONS_H_

typedef struct {
	int    size;
	char **data;
} list_t;

extern list_t menuoptions_bool;
extern list_t menuoptions_flash;
extern list_t menuoptions_action;
extern list_t menuoptions_logfile;
extern list_t menuoptions_btnactn;
extern list_t menuoptions_direction;
extern list_t menuoptions_languages;
extern list_t menuoptions_vformat;
extern list_t menuoptions_scrind;
extern list_t menuoptions_scrlcd;
extern list_t menuoptions_qexp_weight;
extern list_t menuoptions_digiso_steps;
extern list_t menuoptions_olcinv_steps;

#endif
