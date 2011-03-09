#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "scripts.h"
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
	{BUTTON_UP,    TRUE,  FALSE, {restore_iso}},
	{BUTTON_DOWN,  TRUE,  FALSE, {restore_wb}},
	{BUTTON_LEFT,  TRUE,  FALSE, {restore_metering}},
	{BUTTON_DP,    FALSE, TRUE,  {dp_action}},
	END_OF_LIST
};

type_ACTION actions_menu[]  = {
	{BUTTON_DISP,  FALSE, FALSE, {menu_initialize}},
	{BUTTON_DP,    FALSE, TRUE,  {show_factory_menu}},
	END_OF_LIST
};

type_ACTION actions_info[]  = {
	{BUTTON_SET,   FALSE, TRUE,  {menu_set}},
	{BUTTON_DRIVE, FALSE, TRUE,  {menu_esc}},
	{BUTTON_UP,    TRUE,  TRUE,  {menu_up}},
	{BUTTON_DOWN,  TRUE,  TRUE,  {menu_down}},
	{BUTTON_RIGHT, TRUE,  TRUE,  {menu_right}},
	{BUTTON_LEFT,  TRUE,  TRUE,  {menu_left}},
	{BUTTON_AV,    TRUE,  TRUE,  {menu_swap}},
	END_OF_LIST
};

type_ACTION actions_meter[] = {
	{BUTTON_DP,    FALSE, TRUE,  {set_metering_spot}},
	END_OF_LIST
};

type_ACTION actions_wb[] = {
	{BUTTON_DP,    FALSE, TRUE,  {set_whitebalance_colortemp}},
	END_OF_LIST
};

type_ACTION actions_iso[] = {
	{BUTTON_DP,    FALSE, TRUE,  {set_iso_high}},
	END_OF_LIST
};

type_ACTION actions_face[] = {
	{BUTTON_UP,    TRUE,  TRUE,  {}},
	{BUTTON_DOWN,  TRUE,  TRUE,  {}},
	{BUTTON_RIGHT, TRUE,  TRUE,  {viewfinder_right, viewfinder_end}},
	{BUTTON_LEFT,  TRUE,  TRUE,  {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_ACTION actions_factory[] = {
	{BUTTON_DP,    FALSE, TRUE,  {start_debug_mode}},
	END_OF_LIST
};

type_ACTION actions_af[] = {
	{BUTTON_SET,   FALSE,  TRUE,  {afp_center}},
	{BUTTON_UP,    TRUE,   TRUE,  {afp_top}},
	{BUTTON_DOWN,  TRUE,   TRUE,  {afp_bottom}},
	{BUTTON_RIGHT, TRUE,   TRUE,  {afp_right}},
	{BUTTON_LEFT,  TRUE,   TRUE,  {afp_left}},
	END_OF_LIST
};

type_CHAIN chains[] = {
	{GUI_MODE_OFF,       actions_main},
	{GUI_MODE_MAIN,      actions_main},
	{GUI_MODE_MENU,      actions_menu},
	{GUI_MODE_INFO,      actions_info},
	{GUI_MODE_METER,     actions_meter},
	{GUI_MODE_WB,        actions_wb},
	{GUI_MODE_ISO,       actions_iso},
	{GUI_MODE_FACE,      actions_face},
	{GUI_MODE_FACTORY,   actions_factory},
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

	type_TASK    task;
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
	}

	// Use fictitious GUI mode so everything else fits nicely
	if (FLAG_FACE_SENSOR)
		gui_mode = GUI_MODE_FACE;
	else if (FLAG_FACTORY_DIALOG)
		gui_mode = GUI_MODE_FACTORY;
	else
		gui_mode = FLAG_GUI_MODE;

	// Loop over all the action chains
	for(chain = chains; ! IS_EOL(chain); chain++) {

		// Chech whether this action chain corresponds to the current GUI mode
		if (chain->gui_mode == gui_mode) {

			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {

				// Check whether this action corresponds to the event received
				if (action->event == message[1]) {

					// Consider buttons with "button down and "button up" events
					if (action->check && message[0] == 4) {
						if (message[2]) {
							// Button down
							task = action->task[0];
							status.button_down = message[1];
						} else {
							// Button up
							task = action->task[1];
							status.button_down = FALSE;
						}
					} else {
						task = action->task[0];
					}

					// Launch the defined task
					if (task)
						ENQUEUE_TASK(task);

					// If this action blocks the event, we do not pass it along
					if(action->block)
						goto block_message;

					// Once we find a matching action, we look no futher
					goto pass_message;
				}
			}

			// Once we find a matching action chain, we look no futher
			goto pass_message;
		}
	}

pass_message:
	IntercomHandler(handler, message);

block_message:
	return;
}

void task_dispatcher () {
	void (*task)();

	// Loop while receiving messages
	for (;;) {
		ReceiveMessageQueue(message_queue, &task, 0);
		task();
	}
}
