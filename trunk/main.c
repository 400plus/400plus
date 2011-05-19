#include "main.h"

#include "menu.h"
#include "menu_rename.h"
#include "menu_settings.h"
#include "menu_shortcuts.h"
#include "info.h"
#include "tasks.h"
#include "settings.h"
#include "presets.h"
#include "display.h"
#include "viewfinder.h"
#include "af_patterns.h"
#include "languages.h"
#include "firmware.h"

// Main message queue
int *message_queue;

// Global status
type_STATUS status = {
	button_down       : FALSE,
	script_running    : FALSE,
	iso_in_viewfinder : FALSE,
	afp_dialog        : FALSE
};

// Action definitions
type_ACTION actions_main[]  = {
	{IC_BUTTON_UP,    TRUE,  RESP_PASS,  {restore_iso}},
	{IC_BUTTON_DOWN,  TRUE,  RESP_PASS,  {restore_wb}},
	{IC_BUTTON_LEFT,  TRUE,  RESP_PASS,  {restore_metering}},
	{IC_BUTTON_DP,    FALSE, RESP_BLOCK, {dp_action}},
	{IC_BUTTON_AV,    TRUE,  RESP_PASS,  {toggle_raw_jpeg}},
	END_OF_LIST
};

type_ACTION actions_menu[]  = {
	{IC_BUTTON_DP,    FALSE, RESP_BLOCK, {menu_settings_start}},
	END_OF_LIST
};

type_ACTION actions_info[]  = {
	{IC_BUTTON_SET,   FALSE, RESP_BLOCK, {info_option_next}},
	{IC_BUTTON_DOWN,  TRUE,  RESP_BLOCK, {info_option_next}},
	{IC_BUTTON_RIGHT, TRUE,  RESP_BLOCK, {info_option_next}},
	{IC_BUTTON_UP,    TRUE,  RESP_BLOCK, {info_option_prev}},
	{IC_BUTTON_LEFT,  TRUE,  RESP_BLOCK, {info_option_prev}},
	END_OF_LIST
};

type_ACTION actions_400plus[]  = {
	{IC_BUTTON_RIGHT,      TRUE,  RESP_BLOCK,   {menu_right}},
	{IC_BUTTON_LEFT,       TRUE,  RESP_BLOCK,   {menu_left}},
	{IC_BUTTON_AV,         TRUE,  RESP_BLOCK,   {menu_cycle}},
	{IC_BUTTON_SET,        FALSE, RESP_BLOCK,   {menu_action}},
	{IC_BUTTON_DP,         FALSE, RESP_BLOCK,   {menu_dp_action}},
	{IC_BUTTON_DIAL_LEFT,  FALSE, RESP_BLOCK,   {menu_submenu_prev}},
	{IC_BUTTON_DIAL_RIGHT, FALSE, RESP_BLOCK,   {menu_submenu_next}},
	END_OF_LIST
};

type_ACTION actions_rename[]  = {
	{IC_BUTTON_UP,         TRUE,  RESP_RELEASE, {rename_up}},
	{IC_BUTTON_DOWN,       TRUE,  RESP_RELEASE, {rename_down}},
	{IC_BUTTON_RIGHT,      TRUE,  RESP_BLOCK,   {rename_right}},
	{IC_BUTTON_LEFT,       TRUE,  RESP_BLOCK,   {rename_left}},
	{IC_BUTTON_AV,         TRUE,  RESP_BLOCK,   {rename_cycle}},
	{IC_BUTTON_SET,        FALSE, RESP_BLOCK,   {rename_action}},
	{IC_BUTTON_MENU,       FALSE, RESP_BLOCK,   {rename_clear}},
	{IC_BUTTON_DIAL_LEFT,  FALSE, RESP_BLOCK,   {rename_prev}},
	{IC_BUTTON_DIAL_RIGHT, FALSE, RESP_BLOCK,   {rename_next}},
	END_OF_LIST
};

type_ACTION actions_meter[] = {
	{IC_BUTTON_DP,    FALSE, RESP_BLOCK, {set_metering_spot}},
	END_OF_LIST
};

type_ACTION actions_wb[] = {
	{IC_BUTTON_DP,    FALSE, RESP_BLOCK, {set_whitebalance_colortemp}},
	END_OF_LIST
};

type_ACTION actions_iso[] = {
	{IC_BUTTON_DP,    FALSE, RESP_BLOCK, {set_iso_high}},
	END_OF_LIST
};

type_ACTION actions_face[] = {
	{IC_BUTTON_UP,    TRUE,  RESP_BLOCK, {}},
	{IC_BUTTON_DOWN,  TRUE,  RESP_BLOCK, {}},
	{IC_BUTTON_RIGHT, TRUE,  RESP_BLOCK, {viewfinder_right, viewfinder_end}},
	{IC_BUTTON_LEFT,  TRUE,  RESP_BLOCK, {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_ACTION actions_af[] = {
	{IC_BUTTON_SET,   FALSE,  RESP_BLOCK, {afp_center}},
	{IC_BUTTON_UP,    TRUE,   RESP_BLOCK, {afp_top}},
	{IC_BUTTON_DOWN,  TRUE,   RESP_BLOCK, {afp_bottom}},
	{IC_BUTTON_RIGHT, TRUE,   RESP_BLOCK, {afp_right}},
	{IC_BUTTON_LEFT,  TRUE,   RESP_BLOCK, {afp_left}},
	END_OF_LIST
};

type_CHAIN intercom_chains[] = {
	{GUIMODE_OLC,       actions_main},
	{GUIMODE_MAIN,      actions_main},
	{GUIMODE_MENU,      actions_menu},
	{GUIMODE_INFO,      actions_info},
	{GUIMODE_400PLUS,   actions_400plus},
	{GUIMODE_RENAME,    actions_rename},
	{GUIMODE_METER,     actions_meter},
	{GUIMODE_WB,        actions_wb},
	{GUIMODE_ISO,       actions_iso},
	{GUIMODE_FACE,      actions_face},
	{GUIMODE_AFPATTERN, actions_af},
	END_OF_LIST
};

void task_dispatcher();

void initialize() {
	message_queue = (int*)CreateMessageQueue("message_queue", 0x40);
	CreateTask("Task Dispatcher", 25, 0x2000, task_dispatcher, 0);

	ENQUEUE_TASK(start_up);
}

void initialize_display() {
	ENQUEUE_TASK(restore_display);
}

void intercom_proxy(const int handler, char *message) {
	int gui_mode;
	int message_len = message[0];
	int event       = message[1];
	int param       = message_len > 1 ? message[2] : FALSE;
	int holds       = param;

	type_CHAIN  *chain;
	type_ACTION *action;

	// Status-independent events and special cases
	switch (event) {
	case IC_MAIN_DIAL: // Mode dial moved
		status.main_dial_ae = param;
		if (presets_config.use_adep && status.main_dial_ae == AE_MODE_ADEP)
			ENQUEUE_TASK(preset_recall);
		goto pass_message;
	case IC_SETTINGS: // Settings changed
		// Restore display
		ENQUEUE_TASK(restore_display);
		goto pass_message;
	case IC_DIALOGON: // Entering a dialog
		status.afp_dialog = (param == 0x06);
		goto pass_message;
	case IC_AFPDLGOFF: // Exiting AF-Point selection dialog
		if (status.afp_dialog) {
			// Open Extended AF-Point selection dialog
			message[1] = IC_AFPDLGON;
			status.afp_dialog = FALSE;
			ENQUEUE_TASK(afp_enter);
		}
		goto pass_message;
	case IC_SET_LANGUAGE:
		ENQUEUE_TASK(lang_pack_config);
		goto pass_message;
	case IC_BUTTON_DIAL: // Front Dial, we should detect direction and use our BTN IDs
		event = (param & 0x80) ? IC_BUTTON_DIAL_LEFT : IC_BUTTON_DIAL_RIGHT;
		holds = FALSE;
		break;
	case IC_BUTTON_DP: // DP Button while a script is running
		if (status.script_running) {
			status.script_running = FALSE;
			goto block_message;
		}
		break;
	}

	// Check for button-up events, even if the current GUI mode does not match
	if (status.button_down && status.button_down == event && !holds) {
		status.button_down = FALSE;

		// Launch the defined task
		if (status.button_up_task)
			ENQUEUE_TASK(status.button_up_task);

		// Decide how to respond to this button
		switch(status.button_up_resp) {
		case RESP_RELEASE:
		case RESP_PASS:
			goto pass_message;
		case RESP_BLOCK:
			goto block_message;
		}
	}

	// Use fictitious GUI modes so everything else fits nicely
	if (FLAG_FACE_SENSOR && FLAG_GUI_MODE == GUIMODE_MAIN)
		gui_mode = GUIMODE_FACE;
	else
		gui_mode = FLAG_GUI_MODE;

	// Loop over all the action chains
	for(chain = intercom_chains; ! IS_EOL(chain); chain++) {

		// Check whether this action chain corresponds to the current GUI mode
		if (chain->type == gui_mode) {

			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {

				// Check whether this action corresponds to the event received
				if (action->button == event) {

					// Consider buttons with "button down" and "button up" events
					// and save "button up" parameters for later use
					if (action->holds && holds) {
						status.button_down    = event;
						status.button_up_task = action->task[1];
						status.button_up_resp = action->resp;
					}

					// Launch the defined task
					if (action->task[0])
						ENQUEUE_TASK(action->task[0]);

					// Decide how to respond to this button
					switch(action->resp) {
					case RESP_RELEASE:
						IntercomHandler(handler, message);
						message[2] = FALSE;
					case RESP_PASS:
						goto pass_message;
					case RESP_BLOCK:
						goto block_message;
					}
				}
			}

			// Once we find a matching action chain, we look no futher
			break;
		}
	}

pass_message:
	IntercomHandler(handler, message);

block_message:
	return;
}

void task_dispatcher () {
	type_TASK task;

	// Loop while receiving messages
	for (;;) {
		ReceiveMessageQueue(message_queue, &task, 0);
		task();
	}
}
