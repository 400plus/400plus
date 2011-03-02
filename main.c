#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "scripts.h"
#include "viewfinder.h"
#include "settings.h"
#include "firmware.h"

#include "main.h"

// Main message queue
int *message_queue;

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

type_ACTION actions_face[] = {
	{BUTTON_UP,    TRUE,  TRUE,  {}},
	{BUTTON_DOWN,  TRUE,  TRUE,  {}},
	{BUTTON_RIGHT, TRUE,  TRUE,  {viewfinder_right, viewfinder_end}},
	{BUTTON_LEFT,  TRUE,  TRUE,  {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_CHAIN chains[] = {
	{GUI_MODE_OFF,   actions_main},
	{GUI_MODE_MAIN,  actions_main},
	{GUI_MODE_MENU,  actions_menu},
	{GUI_MODE_INFO,  actions_info},
	{GUI_MODE_METER, actions_meter},
	{GUI_MODE_FACE,  actions_face},
	END_OF_LIST
};

void task_dispatcher();

void initialize() {
	message_queue = (int*)CreateMessageQueue("message_queue", 0x40);
	CreateTask("task_dispatcher", 0x19, 0x2000, task_dispatcher, 0);

	ENQUEUE_TASK(start_up);
}

void initialize_display() {
	ENQUEUE_TASK(restore_display);
}

void message_proxy(const int handler, const char *message) {
	type_TASK    task;
	type_CHAIN  *chain;
	type_ACTION *action;

	// Use fictitious GUI mode so everything else fits nicely
	int gui_mode = FLAG_FACE_SENSOR ? GUI_MODE_FACE : FLAG_GUI_MODE;

	// Status-independent events
	switch (message[1]) {
	case EVENT_SETTINGS: // Mode dial moved, settings changed
		// Restore display
		ENQUEUE_TASK(restore_display);
		goto pass_message;
	}

	// Loop over all the action chains
	for(chain = chains; ! IS_EOL(chain); chain++) {

		// Chech whether this action chain corresponds to the current GUI mode
		if (chain->gui_mode == gui_mode) {

			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {

				// Check whether this action corresponds to the event received
				if (action->event == message[1]) {

					// Consider buttons with "button down and "button up" events
					if (action->check) {
						task = message[2] ? action->task[0] : action->task[1];
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
	while (TRUE) {
		ReceiveMessageQueue(message_queue, &task, 0);
		task();
	}
}

