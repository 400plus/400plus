#include <vxworks.h>

#include "macros.h"
#include "main.h"
#include "firmware.h"

#include "display.h"
#include "exposure.h"
#include "languages.h"
#include "menu.h"
#include "menupage.h"
#include "menuitem.h"
#include "settings.h"
#include "scripts.h"
#include "utils.h"
#include "intercom.h"
#include "float.h"

#include "menu_scripts.h"

int menu_scripts_ev;  // Long-exposure calculator: calculated EV
int menu_scripts_tv;  // Long-exposure calculator: initial Tv
int menu_scripts_av;  // Long-exposure calculator: initial Av
int menu_scripts_iso; // Long-exposure calculator: initial Av

int menu_scripts_fl = MENU_SCRIPTS_FL; // DOF calculator: initial focal length
int menu_scripts_fd = MENU_SCRIPTS_FD; // DOF calculator: initial focusing distance

char menu_scripts_dof_min[LP_MAX_WORD], menu_scripts_dof_max[LP_MAX_WORD];

int menu_scripts_vformat = VIDEO_FORMAT_25FPS;
int menu_scripts_rectime = 0, menu_scripts_playtime = 0;

void menu_lexp_calc_open(menu_t *menu);
void menu_dof_calc_open (menu_t *menu);

void menu_scripts_apply_eaeb_tvmin (const menuitem_t *item);
void menu_scripts_apply_eaeb_tvmax (const menuitem_t *item);
void menu_scripts_apply_calc_ev    (const menuitem_t *item);
void menu_scripts_apply_calc_tv    (const menuitem_t *item);
void menu_scripts_apply_calc       (const menuitem_t *item);

void menu_scripts_apply_dof_av(const menuitem_t *item);
void menu_scripts_apply_dof   (const menuitem_t *item);

void menu_scripts_open_timelapse  (menu_t *menu);
void menu_scripts_update_timelapse(const menuitem_t *item);
void menu_scripts_calc_timelapse  (void);

void menu_scripts_ext_aeb      (const menuitem_t *item);
void menu_scripts_efl_aeb      (const menuitem_t *item);
void menu_scripts_apt_aeb      (const menuitem_t *item);
void menu_scripts_iso_aeb      (const menuitem_t *item);
void menu_scripts_interval     (const menuitem_t *item);
void menu_scripts_bramp        (const menuitem_t *item);
void menu_scripts_wave         (const menuitem_t *item);
void menu_scripts_self_timer   (const menuitem_t *item);
void menu_scripts_long_exp     (const menuitem_t *item);

void menu_scripts_launch (action_t script);

menuitem_t ext_aeb_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),     &settings.eaeb_delay,     NULL),
	MENUITEM_BRACKET(0, LP_WORD(L_I_FRAMES),    &settings.eaeb_frames,    NULL),
	MENUITEM_EVEAEB (0, LP_WORD(L_I_STEP_EV),   &settings.eaeb_ev,        NULL),
	MENUITEM_EAEBDIR(0, LP_WORD(L_I_DIRECTION), &settings.eaeb_direction, NULL),
	MENUITEM_BULB   (0, LP_WORD(L_I_MANUAL_L),  &settings.eaeb_tv_min,    menu_scripts_apply_eaeb_tvmin),
	MENUITEM_BULB   (0, LP_WORD(L_I_MANUAL_R),  &settings.eaeb_tv_max,    menu_scripts_apply_eaeb_tvmax)
};

menuitem_t efl_aeb_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),     &settings.efl_aeb_delay,     NULL),
	MENUITEM_BRACKET(0, LP_WORD(L_I_FRAMES),    &settings.efl_aeb_frames,    NULL),
	MENUITEM_EVEAEB (0, LP_WORD(L_I_STEP_EV),   &settings.efl_aeb_ev,        NULL),
	MENUITEM_EAEBDIR(0, LP_WORD(L_I_DIRECTION), &settings.efl_aeb_direction, NULL),
};

menuitem_t apt_aeb_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),     &settings.apt_aeb_delay,     NULL),
	MENUITEM_BRACKET(0, LP_WORD(L_I_FRAMES),    &settings.apt_aeb_frames,    NULL),
	MENUITEM_EVEAEB (0, LP_WORD(L_I_STEP_EV),   &settings.apt_aeb_ev,        NULL),
	MENUITEM_EAEBDIR(0, LP_WORD(L_I_DIRECTION), &settings.apt_aeb_direction, NULL),
};

menuitem_t iso_aeb_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY), &settings.iso_aeb_delay, NULL),
	MENUITEM_BOOLEAN(0, " 100",             &settings.iso_aeb[0],    NULL),
	MENUITEM_BOOLEAN(0, " 200",             &settings.iso_aeb[1],    NULL),
	MENUITEM_BOOLEAN(0, " 400",             &settings.iso_aeb[2],    NULL),
	MENUITEM_BOOLEAN(0, " 800",             &settings.iso_aeb[3],    NULL),
	MENUITEM_BOOLEAN(0, "1600",             &settings.iso_aeb[4],    NULL),
};

menuitem_t interval_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),    &settings.interval_delay,  NULL),
	MENUITEM_ACTION (0, LP_WORD(L_I_ACTION),   &settings.interval_action, NULL),
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_INTERVAL), &settings.interval_time,   menu_scripts_update_timelapse),
	MENUITEM_COUNTER(0, LP_WORD(L_I_SHOTS),    &settings.interval_shots,  menu_scripts_update_timelapse),
	MENUITEM_VFORMAT(0, LP_WORD(L_I_VFORMAT),  &menu_scripts_vformat,     menu_scripts_update_timelapse),
	MENUITEM_INFTIME(0, LP_WORD(L_I_RECTIME),  &menu_scripts_rectime),
	MENUITEM_INFTIME(0, LP_WORD(L_I_PLAYTIME), &menu_scripts_playtime),
};

menuitem_t bramp_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),        &settings.bramp_delay,     NULL),
	MENUITEM_COUNTER(0, LP_WORD(L_I_SHOTS),        &settings.bramp_shots,     NULL),
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_INTERVAL),     &settings.bramp_time,      NULL),
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_EXPOSURE),     &settings.bramp_exp,       NULL),
	MENUITEM_BRTIME( 0, LP_WORD(L_I_RAMP_T),       &settings.bramp_ramp_t,    NULL),
	MENUITEM_BRSHOTS(0, LP_WORD(L_I_RAMP_S),       &settings.bramp_ramp_s,    NULL),
	MENUITEM_EVCOMP (0, LP_WORD(L_I_RAMPING_TIME), &settings.bramp_ramp_time, NULL),
	MENUITEM_EVCOMP (0, LP_WORD(L_I_RAMPING_EXP),  &settings.bramp_ramp_exp,  NULL),
};

menuitem_t wave_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),   &settings.wave_delay,   NULL),
	MENUITEM_ACTION (0, LP_WORD(L_I_ACTION),  &settings.wave_action,  NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_REPEAT),  &settings.wave_repeat,  NULL),
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_INSTANT), &settings.wave_instant, NULL)
};

menuitem_t timer_items[] = {
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_TIME),   &settings.timer_timeout, NULL),
	MENUITEM_ACTION (0, LP_WORD(L_I_ACTION), &settings.timer_action,  NULL)
};

menuitem_t lexp_calc_items[] = {
	MENUITEM_BASEISO(0, LP_WORD(L_I_ISO),    &menu_scripts_iso,        menu_scripts_apply_calc_ev),
	MENUITEM_AV     (0, LP_WORD(L_I_AV_VAL), &menu_scripts_av,         menu_scripts_apply_calc_ev),
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_TV_VAL), &menu_scripts_tv,         menu_scripts_apply_calc_ev),
	MENUITEM_EVINFO (0, LP_WORD(L_I_EV_VAL), &menu_scripts_ev,         menu_scripts_apply_calc_tv),
	MENUITEM_LAUNCH (0, LP_WORD(L_I_APPLY),   menu_scripts_apply_calc),
};

menuitem_t dof_calc_items[] = {
	MENUITEM_FLENGTH(0, LP_WORD(L_I_FLENGTH), &menu_scripts_fl,        menu_scripts_apply_dof),
	MENUITEM_AV     (0, LP_WORD(L_I_AV_VAL),  &menu_DPData.av_val,     menu_scripts_apply_dof_av),
	MENUITEM_FDIST  (0, LP_WORD(L_I_FDIST),   &menu_scripts_fd,        menu_scripts_apply_dof),
	MENUITEM_INFO   (0, LP_WORD(L_I_DOFMIN),   menu_scripts_dof_min),
	MENUITEM_INFO   (0, LP_WORD(L_I_DOFMAX),   menu_scripts_dof_max),
};

menupage_t lexp_calc_page = {
	name    : LP_WORD(L_S_CALCULATOR),
	items   : LIST(lexp_calc_items),
	actions : {
		[MENU_EVENT_OPEN] = menu_lexp_calc_open,
		[MENU_EVENT_AV]   = menu_return,
	}
};

menuitem_t lexp_items[] = {
	MENUITEM_BOOLEAN(0, LP_WORD(L_I_DELAY),      &settings.lexp_delay, NULL),
	MENUITEM_TIMEOUT(0, LP_WORD(L_I_EXPOSURE),   &settings.lexp_time,  NULL),
	MENUITEM_SUBMENU(0, LP_WORD(L_S_CALCULATOR), &lexp_calc_page,      NULL),
};

menupage_t ext_aeb_page = {
	name    : LP_WORD(L_S_EXT_AEB),
	items   : LIST(ext_aeb_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t efl_aeb_page = {
	name    : LP_WORD(L_S_EFL_AEB),
	items   : LIST(efl_aeb_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t apt_aeb_page = {
	name    : LP_WORD(L_S_APT_AEB),
	items   : LIST(apt_aeb_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t iso_aeb_page = {
	name    : LP_WORD(L_S_ISO_AEB),
	items   : LIST(iso_aeb_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t interval_page = {
	name    : LP_WORD(L_S_INTERVAL),
	items   : LIST(interval_items),
	actions : {
		[MENU_EVENT_OPEN] = menu_scripts_open_timelapse,
		[MENU_EVENT_AV]   = menu_return,
	}
};

menupage_t bramp_page = {
	name    : LP_WORD(L_S_BRAMP),
	items   : LIST(bramp_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t wave_page = {
	name    : LP_WORD(L_S_HANDWAVE),
	items   : LIST(wave_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t timer_page = {
	name    : LP_WORD(L_S_TIMER),
	items   : LIST(timer_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t lexp_page = {
	name    : LP_WORD(L_S_LEXP),
	items   : LIST(lexp_items),
	actions : {
		[MENU_EVENT_AV] = menu_return,
	}
};

menupage_t dof_calc_page = {
	name    : LP_WORD(L_S_DOF_CALC),
	items   : LIST(dof_calc_items),
	actions : {
		[MENU_EVENT_OPEN] = menu_dof_calc_open,
		[MENU_EVENT_AV]   = menu_return,
	}
};

menuitem_t menupage_scripts_items[] = {
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_EXTAEB,   LP_WORD(L_S_EXT_AEB),   &ext_aeb_page,   menu_scripts_ext_aeb),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_EFLAEB,   LP_WORD(L_S_EFL_AEB),   &efl_aeb_page,   menu_scripts_efl_aeb),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_APTAEB,   LP_WORD(L_S_APT_AEB),   &apt_aeb_page,   menu_scripts_apt_aeb),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_ISOAEB,   LP_WORD(L_S_ISO_AEB),   &iso_aeb_page,   menu_scripts_iso_aeb),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_INTERVAl, LP_WORD(L_S_INTERVAL),  &interval_page,  menu_scripts_interval),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_BRAMP,    LP_WORD(L_S_BRAMP),     &bramp_page,     menu_scripts_bramp),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_HANDWAVE, LP_WORD(L_S_HANDWAVE),  &wave_page,      menu_scripts_wave),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_TIMER,    LP_WORD(L_S_TIMER),     &timer_page,     menu_scripts_self_timer),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_LEXP,     LP_WORD(L_S_LEXP),      &lexp_page,      menu_scripts_long_exp),
	MENUITEM_SUBMENU(MENUPAGE_SCRIPTS_DOFC,     LP_WORD(L_S_DOF_CALC),  &dof_calc_page,  NULL),
};

menupage_t menupage_scripts = {
	name      : LP_WORD(L_P_SCRIPTS),
	sibilings : TRUE,
	items     : LIST(menupage_scripts_items),
	ordering  : menu_order.scripts,
};

void menu_lexp_calc_open (menu_t *menu) {
	// Copy current parameters from camera to menu
	menu_scripts_iso = DPData.iso;
	menu_scripts_av  = DPData.av_val;

	// Start with a common exposure time
	menu_scripts_tv = settings.lexp_time;

	// Adjust exposure compensation
	menu_scripts_ev = ec_normalize(8.0f * (float_log2(menu_scripts_tv) + (DPData.tv_val - TV_SEC) / 8.0f));
}

void menu_dof_calc_open (menu_t *menu) {
	if (status.last_shot_fl != 0x00)
		menu_scripts_fl = status.last_shot_fl;

	calculate_dof(menu_scripts_fl, menu_scripts_fd, menu_DPData.av_val, menu_scripts_dof_min, menu_scripts_dof_max);
}

void menu_scripts_apply_eaeb_tvmin(const menuitem_t *item) {
	settings.eaeb_tv_max = MIN(settings.eaeb_tv_min, settings.eaeb_tv_max);
	menu_event_display();
}

void menu_scripts_apply_eaeb_tvmax(const menuitem_t *item) {
	settings.eaeb_tv_min = MAX(settings.eaeb_tv_min, settings.eaeb_tv_max);
	menu_event_display();
}

void menu_scripts_apply_calc_ev(const menuitem_t *item) {
	float camera_ev = (DPData.iso       - ISO_100) / 8.0f - (DPData.av_val   - AV_MIN) / 8.0f - (DPData.tv_val - TV_SEC) / 8.0f;
	float script_ev = (menu_scripts_iso - ISO_100) / 8.0f - (menu_scripts_av - AV_MIN) / 8.0f + float_log2(menu_scripts_tv);

	int ev = 8.0f * (script_ev - camera_ev);

	ev = CLAMP(ev, EC_MIN_EXT, EC_MAX_EXT);

	menu_scripts_ev = ec_normalize(ev);
	menu_event_display();
}

void menu_scripts_apply_calc_tv(const menuitem_t *item) {
	float camera_ev = (DPData.iso       - ISO_100) / 8.0f - (DPData.av_val   - AV_MIN) / 8.0f + (DPData.tv_val - TV_SEC) / 8.0f;
	float script_ev = (menu_scripts_iso - ISO_100) / 8.0f - (menu_scripts_av - AV_MIN) / 8.0f;

	menu_scripts_tv = float_pow2(menu_scripts_ev / 8.0f - (camera_ev - script_ev));

	if (menu_scripts_tv == 0) {
		menu_scripts_tv = 1;
		menu_scripts_apply_calc_ev(item);
	} else if (menu_scripts_tv > 18000) {
		menu_scripts_tv = 18000;
		menu_scripts_apply_calc_ev(item);
	} else {
		menu_event_display();
	}
}

void menu_scripts_apply_calc(const menuitem_t *item) {
	settings.lexp_time = menu_scripts_tv;

	send_to_intercom(IC_SET_AV_VAL, menu_scripts_av);
	send_to_intercom(IC_SET_ISO,    menu_scripts_iso);

	menu_scripts_ev = EV_ZERO;
	menu_return(NULL); //TODO:FixMe
}

void menu_scripts_apply_dof_av(const menuitem_t *item) {
	send_to_intercom(IC_SET_AV_VAL, *item->parm.menuitem_av.value);
	menu_scripts_apply_dof(item);
}

void menu_scripts_apply_dof(const menuitem_t *item) {
	calculate_dof(menu_scripts_fl, menu_scripts_fd, menu_DPData.av_val, menu_scripts_dof_min, menu_scripts_dof_max);
	menu_event_display();
}

void menu_scripts_open_timelapse(menu_t *menu) {
	menu_scripts_calc_timelapse();
}

void menu_scripts_update_timelapse(const menuitem_t *item) {
	menu_scripts_calc_timelapse();
	menu_event_display();
}

void menu_scripts_calc_timelapse() {
	menu_scripts_rectime  = settings.interval_shots * settings.interval_time;

	switch (menu_scripts_vformat) {
	case VIDEO_FORMAT_25FPS:
		menu_scripts_playtime = settings.interval_shots / 25;
		break;
	case VIDEO_FORMAT_30FPS:
		menu_scripts_playtime = settings.interval_shots / 30;
		break;
	case VIDEO_FORMAT_50FPS:
		menu_scripts_playtime = settings.interval_shots / 50;
		break;
	case VIDEO_FORMAT_60FPS:
		menu_scripts_playtime = settings.interval_shots / 60;
		break;
	default:
		menu_scripts_playtime = 0;
		break;
	}
}

void menu_scripts_ext_aeb(const menuitem_t *item) {
	menu_scripts_launch(script_ext_aeb);
}

void menu_scripts_efl_aeb(const menuitem_t *item) {
	menu_scripts_launch(script_efl_aeb);
}

void menu_scripts_apt_aeb(const menuitem_t *item) {
	menu_scripts_launch(script_apt_aeb);
}

void menu_scripts_iso_aeb(const menuitem_t *item) {
	menu_scripts_launch(script_iso_aeb);
}

void menu_scripts_interval(const menuitem_t *item) {
	menu_scripts_launch(script_interval);
}

void menu_scripts_bramp(const menuitem_t *item) {
	menu_scripts_launch(script_bramp);
}

void menu_scripts_wave(const menuitem_t *item) {
	menu_scripts_launch(script_wave);
}

void menu_scripts_self_timer(const menuitem_t *item) {
	menu_scripts_launch(script_self_timer);
}

void menu_scripts_long_exp(const menuitem_t *item) {
	menu_scripts_launch(script_long_exp);
}

void menu_scripts_launch(action_t script) {
	enqueue_action(menu_close);
	enqueue_action(script);
}
