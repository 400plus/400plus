#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "scripts.h"
#include "viewfinder.h"
#include "settings.h"

#include "main.h"

// Main message queue
int *message_queue;

// Action definitions
type_ACTION actions_main[]  = {
	{BUTTON_UP,    FALSE, restore_iso},
	{BUTTON_DOWN,  FALSE, restore_wb},
	{BUTTON_LEFT,  FALSE, restore_metering},
	{BUTTON_DP,    TRUE,  dp_action},
	END_OF_LIST
};

type_ACTION actions_menu[]  = {
	{BUTTON_DISP,  FALSE, menu_initialize},
	{BUTTON_DP,    TRUE,  show_factory_menu},
	END_OF_LIST
};

type_ACTION actions_info[]  = {
	{BUTTON_SET,   TRUE, menu_set},
	{BUTTON_DRIVE, TRUE, menu_esc},
	{BUTTON_UP,    TRUE, menu_up},
	{BUTTON_DOWN,  TRUE, menu_down},
	{BUTTON_RIGHT, TRUE, menu_right},
	{BUTTON_LEFT,  TRUE, menu_left},
	{BUTTON_AV,    TRUE, menu_swap},
	END_OF_LIST
};

type_ACTION actions_meter[] = {
	{BUTTON_DP,    TRUE, set_metering_spot},
	END_OF_LIST
};

type_CHAIN chains[] = {
	{GUI_MODE_OFF,   actions_main},
	{GUI_MODE_MAIN,  actions_main},
	{GUI_MODE_MENU,  actions_menu},
	{GUI_MODE_INFO,  actions_info},
	{GUI_MODE_METER, actions_meter},
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
	type_CHAIN  *chain;
	type_ACTION *action;

	// Status-independent events
	switch (message[1]) {
	case EVENT_SETTINGS: // Mode dial moved, settings changed
		// Restore display
		ENQUEUE_TASK(restore_display);
		goto pass_message;
	}

	if (FLAG_FACE_SENSOR) { // User has camera "on the face", display is blank
		switch(message[1]) {
		case BUTTON_UP:
			if(message[2]) { // Button down
				// Ignore nose-activated event
				goto block_message;
			} else {     // Button up
			}
			break;
		case BUTTON_DOWN:
			if(message[2]) { // Button down
				// Ignore nose-activated event
				goto block_message;
			} else {     // Button up
			}
			break;
		case BUTTON_RIGHT:
			if(message[2]) { // Button down
				// Start ISO display on viewfinder and increase ISO
				ENQUEUE_TASK(viewfinder_iso_inc);
				goto block_message;
			} else {     // Button up
				// End ISO display on viewfinder
				ENQUEUE_TASK(viewfinder_iso_end);
				goto block_message;
			}
			break;
		case BUTTON_LEFT:
			if(message[2]) { // Button down
				// Start ISO display on viewfinder and decrease ISO
				ENQUEUE_TASK(viewfinder_iso_dec);
				goto block_message;
			} else {     // Button up
				// End ISO display on viewfinder
				ENQUEUE_TASK(viewfinder_iso_end);
				goto block_message;
			}
			break;
		}
	} else {
		// Loop over all the action chains
		for(chain = chains; ! IS_EOL(chain); chain++) {

			// Chech whether this action chain corresponds to the current GUI mode
			if (chain->gui_mode == FLAG_GUI_MODE) {

				// Loop over all the actions from this action chain
				for (action = chain->actions; ! IS_EOL(action); action++) {

					// Check whether this action corresponds to the event received
					if (action->event == message[1]) {

						// Only "button pressed" events are considered
						if (message[0] == 3 || (message[0] == 4 && message[2] == 1)) {

							// Launch the defined task
							ENQUEUE_TASK(action->task);

							// If this action blocks the event, we do not pass it along
							if(action->block)
								goto block_message;
						}

						// Once we find a matching action, we look no futher
						goto pass_message;
					}
				}

				// Once we find a matching action chain, we look no futher
				goto pass_message;
			}
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

