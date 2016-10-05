#include <vxworks.h>

#include "firmware.h"
#include "firmware/gui.h"

#include "main.h"
#include "macros.h"

#include "actions.h"
#include "autoiso.h"
#include "af_patterns.h"
#include "button.h"
#include "cmodes.h"
#include "fexp.h"
#include "qexp.h"
#include "languages.h"
#include "menu.h"
#include "menu_main.h"
#include "menu_rename.h"
#include "msm.h"
#include "persist.h"
#include "shortcuts.h"
#include "viewfinder.h"
#include "debug.h"

#include "intercom.h"

// Proxy listeners
int proxy_script_restore (char *message);
int proxy_script_stop    (char *message);
int proxy_set_language   (char *message);
int proxy_dialog_enter   (char *message);
int proxy_dialog_exit    (char *message);
int proxy_dialog_afoff   (char *message);
int proxy_measuring      (char *message);
int proxy_measurement    (char *message);
int proxy_shoot_start    (char *message);
int proxy_shoot_finish   (char *message);
int proxy_settings0      (char *message);
int proxy_settings3      (char *message);
int proxy_button         (char *message);
int proxy_wheel          (char *message);
int proxy_initialize     (char *message);
int proxy_tv             (char *message);
int proxy_av             (char *message);
int proxy_aeb            (char *message);

typedef int (*proxy_t) (char*);

proxy_t listeners_script[0x100] = {
	[IC_SHUTDOWN]    = proxy_script_restore,
	[IC_SHOOT_START] = proxy_shoot_start,
	[IC_BUTTON_DP]   = proxy_script_stop,
};

proxy_t listeners_menu[0x100] = {
	[IC_DIALOGOFF]     = proxy_dialog_exit,
	[IC_BUTTON_WHEEL]  = proxy_wheel,
	[IC_BUTTON_DISP]   = proxy_button,
	[IC_BUTTON_SET]    = proxy_button,
	[IC_BUTTON_RIGHT]  = proxy_button,
	[IC_BUTTON_LEFT]   = proxy_button,
	[IC_BUTTON_DP]     = proxy_button,
	[IC_BUTTON_AV]     = proxy_button,
};

proxy_t listeners_main[0x100] = {
	[IC_SET_TV_VAL]    = proxy_tv,
	[IC_SET_AV_VAL]    = proxy_av,
	[IC_SET_AE_BKT]    = proxy_aeb,
	[IC_SET_LANGUAGE]  = proxy_set_language,
	[IC_DIALOGON]      = proxy_dialog_enter,
	[IC_MEASURING]     = proxy_measuring,
	[IC_MEASUREMENT]   = proxy_measurement,
	[IC_SHOOT_FINISH]  = proxy_shoot_finish,
	[IC_UNKNOWN_8D]    = proxy_initialize,
	[IC_SETTINGS_0]    = proxy_settings0,
	[IC_SETTINGS_3]    = proxy_settings3,
	[IC_AFPDLGOFF]     = proxy_dialog_afoff,
	[IC_BUTTON_WHEEL]  = proxy_wheel,
	[IC_BUTTON_DISP]   = proxy_button,
	[IC_BUTTON_SET]    = proxy_button,
	[IC_BUTTON_UP]     = proxy_button,
	[IC_BUTTON_DOWN]   = proxy_button,
	[IC_BUTTON_RIGHT]  = proxy_button,
	[IC_BUTTON_LEFT]   = proxy_button,
	[IC_BUTTON_DP]     = proxy_button,
	[IC_BUTTON_AV]     = proxy_button,
};

button_t message2button[0x100] = {
	[IC_BUTTON_DISP]   = BUTTON_DISP,
	[IC_BUTTON_SET]    = BUTTON_SET,
	[IC_BUTTON_UP]     = BUTTON_UP,
	[IC_BUTTON_DOWN]   = BUTTON_DOWN,
	[IC_BUTTON_RIGHT]  = BUTTON_RIGHT,
	[IC_BUTTON_LEFT]   = BUTTON_LEFT,
	[IC_BUTTON_DP]     = BUTTON_DP,
	[IC_BUTTON_AV]     = BUTTON_AV,
};

void message_logger (char *message);

int send_to_intercom(int message, int parm) {
	int result, length = 1;

	switch (message) {
	case IC_SET_AE:
		status.ignore_msg = IC_SETTINGS_0;
		break;
	case IC_SET_AV_VAL:
	case IC_SET_TV_VAL:
		status.ignore_msg = message;
		break;
	case IC_RELEASE:
	case IC_SET_REALTIME_ISO_0:
	case IC_SET_REALTIME_ISO_1:
		length = 0;
		break;
	case IC_SET_ISO:
	case IC_SET_AF_POINT:
	case IC_SET_COLOR_TEMP:
		length = 2;
		break;
	}

	result = SendToIntercom(message, length, parm);
	SleepTask(INTERCOM_WAIT);

	return result;
}

void intercom_proxy(const int handler, char *message) {
	proxy_t  listener;
	proxy_t *listeners;

#ifdef ENABLE_DEBUG
	message_logger(message);
#endif

	if (status.ignore_msg == message [1]) {
		status.ignore_msg = FALSE;
	} else {
		// Fast path for the case of a running script
		if (status.script_running)
			listeners = listeners_script;
		else if (status.menu_running)
			listeners = listeners_menu;
		else
			listeners = listeners_main;

		if ((listener = listeners[message[1]]) != NULL)
			if (listener(message))
				return;
	}

	IntercomHandler(handler, message);
}

#ifdef ENABLE_DEBUG
void message_logger(char *message) {
	int i;
	char text[256];
	static int id = 0;

	for (i = 0; i < message[0]; i++)
		sprintf(text + 3 * i, "%02X ", message[i]);

	debug_log("MSG%04d-%02X: %s", id++, FLAG_GUI_MODE, text);
}
#endif

int proxy_script_restore(char *message) {
	script_restore();

	return FALSE;
}

int proxy_script_stop(char *message) {
	status.script_stopping = TRUE;

	return TRUE;
}

int proxy_set_language(char *message) {
	enqueue_action(lang_pack_config);

	return FALSE;
}

int proxy_dialog_enter(char *message) {
	status.afp_dialog = (message[2] == IC_SET_AF);

	shortcut_stop();

	return FALSE;
}

int proxy_dialog_exit(char *message) {
	enqueue_action(menu_event_finish);

	return FALSE;
}

int proxy_dialog_afoff(char *message) {
	if (status.afp_dialog) {
		// Open Extended AF-Point selection dialog
		message[1] = IC_AFPDLGON;
		status.afp_dialog = FALSE;
		enqueue_action(afp_enter);
	}

	return FALSE;
}

int proxy_measuring(char *message) {
	status.measuring = message[2];

	if (! status.measuring)
		enqueue_action(viewfinder_end);

	return FALSE;
}

int proxy_measurement(char *message) {
	if (status.measuring) {
		status.measured_tv = message[2];
		status.measured_av = message[3];
		status.measured_ec = message[4];

		switch(status.vf_status) {
		case VF_STATUS_QEXP:
			enqueue_action(qexp_update);
			break;
		default:
			if (settings.autoiso_enable)
				enqueue_action(autoiso);
			break;
		}
	}

	return FALSE;
}

int proxy_shoot_start(char *message) {
	status.last_shot_tv = message[2];
	status.last_shot_av = message[3];

	return FALSE;
}

int proxy_shoot_finish(char *message) {
	status.last_shot_fl = message[2] | (message[3] << 8);

	shortcut_stop();

	if (status.msm_active)
		enqueue_action(msm_stop);

	return FALSE;
}

int proxy_initialize(char *message) {
	static int first = TRUE;

	if (first) {
		first = FALSE;

		enqueue_action(start_up);
	}

	return FALSE;
}

int proxy_settings0(char *message) {
	static int first = TRUE;

	if (!status.msm_active)
		status.main_dial_ae = message[2];

	if (first) {
		first = FALSE;
	} else {
		if (status.vf_status == VF_STATUS_FEXP)
			fexp_disable();

		if (!status.msm_active)
			enqueue_action(cmode_apply);
	}

	shortcut_stop();

	return FALSE;
}

int proxy_settings3(char *message) {
//	enqueue_action(restore_display);

	if (settings.autoiso_enable)
		enqueue_action(autoiso_restore);

	return FALSE;
}

int proxy_button(char *message) {
	return button_handler(message2button[message[1]], message[0] > 3 ? message[2] : TRUE);
}

int proxy_wheel(char *message) {
	return button_handler((message[2] & 0x80) ? BUTTON_WHEEL_LEFT : BUTTON_WHEEL_RIGHT, TRUE);
}

int proxy_av(char *message) {
	if (status.vf_status == VF_STATUS_FEXP)
		enqueue_action(fexp_update_tv);

	return FALSE;
}

int proxy_tv(char *message) {
	if (settings.autoiso_enable)
		enqueue_action(autoiso_restore);

	if (status.vf_status == VF_STATUS_FEXP)
		enqueue_action(fexp_update_av);

	return FALSE;
}

int proxy_aeb(char *message) {
	persist.aeb = message[2];

	if (persist.aeb)
		persist.last_aeb = persist.aeb;

	if (!status.shortcut_running)
		enqueue_action(persist_write);

	return FALSE;
}

