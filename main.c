#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "shortcuts.h"
#include "viewfinder.h"
#include "af_patterns.h"
#include "settings.h"
#include "firmware.h"

#include "main.h"

// Main message queue
int *message_queue;

// Global status
type_STATUS status = {
	button_down    : FALSE,
	script_running : FALSE,
	afp_dialog     : FALSE
};

// Action definitions
type_ACTION actions_main[]  = {
	{BUTTON_UP,    TRUE,  RESP_PASS,  {restore_iso}},
	{BUTTON_DOWN,  TRUE,  RESP_PASS,  {restore_wb}},
	{BUTTON_LEFT,  TRUE,  RESP_PASS,  {restore_metering}},
	{BUTTON_DP,    FALSE, RESP_BLOCK, {shortcuts_initialize}},
	{BUTTON_AV,    TRUE,  RESP_PASS,  {toggle_raw_jpeg}},
	END_OF_LIST
};

type_ACTION actions_menu[]  = {
	{BUTTON_DP  ,  FALSE, RESP_BLOCK, {menu_initialize}},
	END_OF_LIST
};

type_ACTION actions_400plus[]  = {
	{BUTTON_SET,   FALSE, RESP_BLOCK,   {menu_save}},
	{BUTTON_MENU,  FALSE, RESP_BLOCK,   {menu_submenu}},
	{BUTTON_UP,    TRUE,  RESP_RELEASE, {menu_up}},
	{BUTTON_DOWN,  TRUE,  RESP_RELEASE, {menu_down}},
	{BUTTON_RIGHT, TRUE,  RESP_BLOCK,   {menu_right}},
	{BUTTON_LEFT,  TRUE,  RESP_BLOCK,   {menu_left}},
	{BUTTON_AV,    TRUE,  RESP_BLOCK,   {menu_cycle}},
	{BUTTON_DP,    FALSE, RESP_BLOCK,   {factory_or_debug}},
	END_OF_LIST
};

type_ACTION actions_shortcuts[]  = {
	{BUTTON_UP,    TRUE,  RESP_BLOCK, {shortcuts_launch_0}},
	{BUTTON_LEFT,  TRUE,  RESP_BLOCK, {shortcuts_launch_1}},
	{BUTTON_SET,   FALSE, RESP_BLOCK, {shortcuts_launch_2}},
	{BUTTON_RIGHT, TRUE,  RESP_BLOCK, {shortcuts_launch_3}},
	{BUTTON_DOWN,  TRUE,  RESP_BLOCK, {shortcuts_launch_4}},
	{BUTTON_AV,    TRUE,  RESP_BLOCK, {shortcuts_config_start}},
	{BUTTON_MENU,  FALSE, RESP_BLOCK, {shortcuts_close}},
	END_OF_LIST
};

type_ACTION actions_scedit[]  = {
	{BUTTON_UP,    TRUE,  RESP_RELEASE, {shortcuts_up}},
	{BUTTON_LEFT,  TRUE,  RESP_BLOCK,   {shortcuts_left}},
	{BUTTON_SET,   FALSE, RESP_BLOCK,   {shortcuts_set}},
	{BUTTON_RIGHT, TRUE,  RESP_BLOCK,   {shortcuts_right}},
	{BUTTON_DOWN,  TRUE,  RESP_RELEASE, {shortcuts_down}},
	{BUTTON_AV,    TRUE,  RESP_BLOCK,   {shortcuts_config_end}},
	{BUTTON_MENU,  FALSE, RESP_BLOCK,   {shortcuts_close}},
	END_OF_LIST
};

type_ACTION actions_meter[] = {
	{BUTTON_DP,    FALSE, RESP_BLOCK, {set_metering_spot}},
	END_OF_LIST
};

type_ACTION actions_wb[] = {
	{BUTTON_DP,    FALSE, RESP_BLOCK, {set_whitebalance_colortemp}},
	END_OF_LIST
};

type_ACTION actions_iso[] = {
	{BUTTON_DP,    FALSE, RESP_BLOCK, {set_iso_high}},
	END_OF_LIST
};

type_ACTION actions_face[] = {
	{BUTTON_UP,    TRUE,  RESP_BLOCK, {}},
	{BUTTON_DOWN,  TRUE,  RESP_BLOCK, {}},
	{BUTTON_RIGHT, TRUE,  RESP_BLOCK, {viewfinder_right, viewfinder_end}},
	{BUTTON_LEFT,  TRUE,  RESP_BLOCK, {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_ACTION actions_af[] = {
	{BUTTON_SET,   FALSE,  RESP_BLOCK, {afp_center}},
	{BUTTON_UP,    TRUE,   RESP_BLOCK, {afp_top}},
	{BUTTON_DOWN,  TRUE,   RESP_BLOCK, {afp_bottom}},
	{BUTTON_RIGHT, TRUE,   RESP_BLOCK, {afp_right}},
	{BUTTON_LEFT,  TRUE,   RESP_BLOCK, {afp_left}},
	END_OF_LIST
};

type_CHAIN chains[] = {
	{GUI_MODE_OFF,       actions_main},
	{GUI_MODE_MAIN,      actions_main},
	{GUI_MODE_MENU,      actions_menu},
	{GUI_MODE_400PLUS,   actions_400plus},
	{GUI_MODE_SHORTCUTS, actions_shortcuts},
	{GUI_MODE_SCEDIT,    actions_scedit},
	{GUI_MODE_METER,     actions_meter},
	{GUI_MODE_WB,        actions_wb},
	{GUI_MODE_ISO,       actions_iso},
	{GUI_MODE_FACE,      actions_face},
	{GUI_MODE_AFPATTERN, actions_af},
	END_OF_LIST
};

void task_dispatcher();

void initialize() {
	message_queue = (int*)CreateMessageQueue("message_queue", 0x40);
	CreateTask("Task Dispatcher", 0x19, 0x2000, task_dispatcher, 0);

	ENQUEUE_TASK(start_up);
}

void initialize_display() {
	ENQUEUE_TASK(restore_display);
}

void message_proxy(const int handler, char *message) {
	int gui_mode;

	type_CHAIN  *chain;
	type_ACTION *action;

	// Status-independent events and special cases
	switch (message[1]) {
	case EVENT_SETTINGS: // Mode dial moved, settings changed
		// Restore display
		ENQUEUE_TASK(restore_display);
		goto pass_message;
	case EVENT_DIALOGON: // Entering a dialog
		status.afp_dialog = (message[2] == 0x06);
		goto pass_message;
	case EVENT_AFPDLGOFF: // Exiting AF-Point selection dialog
		if (status.afp_dialog) {
			// Open Extended AF-Point selection dialog
			message[1] = EVENT_AFPDLGON;
			status.afp_dialog = FALSE;
			ENQUEUE_TASK(afp_enter);
		}
		goto pass_message;
	case BUTTON_DP: // DP Button while a script is running
		if (status.script_running) {
			status.script_running = FALSE;
			goto block_message;
		}
	}

	// Check for button-up events, even if the current GUI mode does not match
	if (status.button_down && status.button_down == message[1] && !message[2]) {
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
	if (FLAG_FACE_SENSOR)
		gui_mode = GUI_MODE_FACE;
	else
		gui_mode = FLAG_GUI_MODE;

	// Loop over all the action chains
	for(chain = chains; ! IS_EOL(chain); chain++) {

		// Chech whether this action chain corresponds to the current GUI mode
		if (chain->gui_mode == gui_mode) {

			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {

				// Check whether this action corresponds to the event received
				if (action->button == message[1]) {

					// Consider buttons with "button down" and "button up" events
					// and save "button up" parameters for later use
					if (action->holds && message[2]) {
						status.button_down    = message[1];
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
