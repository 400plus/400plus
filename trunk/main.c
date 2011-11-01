#include "firmware.h"

#include "af_patterns.h"
#include "display.h"
#include "languages.h"
#include "menu.h"
#include "menu_main.h"
#include "menu_rename.h"
#include "presets.h"
#include "tasks.h"
#include "utils.h"
#include "viewfinder.h"

#include "main.h"

// Camera data
type_CAMERA_MODE *cameraMode = (type_CAMERA_MODE*)&DPData;

// Main message queue
int *message_queue;

// Global status
type_STATUS status = {
	button_down       : FALSE,
	script_running    : FALSE,
	iso_in_viewfinder : FALSE,
	afp_dialog        : FALSE,
	last_preset       : FALSE,
	ignore_ae_change  : FALSE,
	booting           : TRUE,
	measuring         : FALSE,
	ev_comp           : 0x00,
};

// Action definitions
type_ACTION actions_main[]  = {
	{IC_BUTTON_UP,    TRUE,  FALSE,  {restore_iso}},
	{IC_BUTTON_DOWN,  TRUE,  FALSE,  {restore_wb}},
	{IC_BUTTON_LEFT,  TRUE,  FALSE,  {restore_metering}},
	{IC_BUTTON_DP,    FALSE, TRUE,   {menu_main_start}},
	{IC_BUTTON_AV,    TRUE,  FALSE,  {toggle_img_format}},
	END_OF_LIST
};

type_ACTION actions_400plus[]  = {
	{IC_BUTTON_SET,        FALSE, TRUE,  {menu_event_set}},
	{IC_BUTTON_DIAL_LEFT,  FALSE, TRUE,  {menu_event_prev}},
	{IC_BUTTON_DIAL_RIGHT, FALSE, TRUE,  {menu_event_next}},
	{IC_BUTTON_RIGHT,      TRUE,  TRUE,  {menu_event_right}},
	{IC_BUTTON_LEFT,       TRUE,  TRUE,  {menu_event_left}},
	{IC_BUTTON_DP,         FALSE, TRUE,  {menu_event_dp}},
	{IC_BUTTON_AV,         TRUE,  TRUE,  {menu_event_av, menu_event_av_up}},
	{IC_DIALOGOFF,         FALSE, FALSE, {menu_event_close}},
	END_OF_LIST
};

type_ACTION actions_meter[] = {
	{IC_BUTTON_DP,    FALSE, TRUE, {set_metering_spot}},
	END_OF_LIST
};

type_ACTION actions_wb[] = {
	{IC_BUTTON_DP,    FALSE, TRUE, {set_whitebalance_colortemp}},
	END_OF_LIST
};

type_ACTION actions_iso[] = {
	{IC_BUTTON_DP,    FALSE, TRUE,  {autoiso_enable}},
	{IC_BUTTON_SET,   FALSE, FALSE, {autoiso_disable}},
	END_OF_LIST
};

type_ACTION actions_face[] = {
	{IC_BUTTON_UP,    TRUE, TRUE, {}},
	{IC_BUTTON_DOWN,  TRUE, TRUE, {}},
	{IC_BUTTON_RIGHT, TRUE, TRUE, {viewfinder_right, viewfinder_end}},
	{IC_BUTTON_LEFT,  TRUE, TRUE, {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_ACTION actions_af[] = {
	{IC_BUTTON_SET,   FALSE, TRUE, {afp_center}},
	{IC_BUTTON_UP,    TRUE,  TRUE, {afp_top}},
	{IC_BUTTON_DOWN,  TRUE,  TRUE, {afp_bottom}},
	{IC_BUTTON_RIGHT, TRUE,  TRUE, {afp_right}},
	{IC_BUTTON_LEFT,  TRUE,  TRUE, {afp_left}},
	END_OF_LIST
};

type_CHAIN intercom_chains[] = {
	{GUIMODE_OLC,       actions_main},
	{GUIMODE_MAIN,      actions_main},
	{GUIMODE_400PLUS,   actions_400plus},
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
	case IC_SETTINGS_0: // Settings changed (begin of sequence)
		if (status.ignore_ae_change) {
			// Ignore first AE change after loading a preset, as it generates this same event
			status.ignore_ae_change = FALSE;
		} else {
			// Handle preset recall when dial moved to A-DEP
			status.last_preset  = FALSE;
			status.main_dial_ae = param;

			if (presets_config.use_adep && status.main_dial_ae == AE_MODE_ADEP) {
				if (status.booting) {
					ENQUEUE_TASK(preset_recall);
				} else {
					ENQUEUE_TASK(preset_recall_full);
				}
			}
		}

	case IC_SETTINGS_3: // Settings changed (end of sequence)
		// Restore display
		ENQUEUE_TASK(restore_display);
		goto pass_message;
	case IC_DIALOGON: // Entering a dialog
		status.afp_dialog = (param == IC_SET_AF);
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
		// TODO: Use a special status and take this out of here
		if (status.script_running) {
			status.script_running = FALSE;
			goto block_message;
		}
		break;
	case IC_MEASURING:
		status.measuring = param;
		ENQUEUE_TASK(restore_display);
		break;
	case IC_MEASUREMENT:
		if (status.measuring) {
			// TODO: Generalize this
			status.measured_tv = message[2];
			status.measured_av = message[3];
			status.measured_ev = message[4];

			if (settings.autoiso_enable)
				ENQUEUE_TASK(autoiso);
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
		if (status.button_up_block)
			goto block_message;
		else
			goto pass_message;
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
						status.button_down     = event;
						status.button_up_task  = action->task[1];
						status.button_up_block = action->block;
					}

					// Launch the defined task
					if (action->task[0])
						ENQUEUE_TASK(action->task[0]);

					// Decide how to respond to this button
					if (action->block)
						goto block_message;
					else
						goto pass_message;
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

