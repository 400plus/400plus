/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include "main.h"
#include "firmware.h"
#include "tasks.h"

#include "button.h"

type_ACTION button_actions_main[] = {
	{BUTTON_JUMP,  TRUE, {button_jump_task}},
	{BUTTON_TRASH, TRUE, {button_trash_task}},
	END_OF_LIST
};

type_CHAIN button_chains[] = {
	{GUIMODE_OLC, button_actions_main},
	{GUIMODE_OFF, button_actions_main},
	END_OF_LIST
};

int button_handler(type_BUTTON button) {
	int gui_mode;

	type_CHAIN  *chain;
	type_ACTION *action;

	// Use fictitious GUI modes so everything else fits nicely
	if (FLAG_FACE_SENSOR && FLAG_GUI_MODE == GUIMODE_OFF)
		gui_mode = GUIMODE_FACE;
	else if(status.menu_running)
		gui_mode = GUIMODE_400PLUS;
	else
		gui_mode = FLAG_GUI_MODE;

	// Loop over all the action chains
	for(chain = button_chains; ! IS_EOL(chain); chain++) {

		// Check whether this action chain corresponds to the current GUI mode
		if (chain->type == gui_mode) {

			// Loop over all the actions from this action chain
			for (action = chain->actions; ! IS_EOL(action); action++) {

				// Check whether this action corresponds to the event received
				if (action->button == button) {
/*
					// Consider buttons with "button down" and "button up" events
					// and save "button up" parameters for later use
					if (button_down) {
						status.button_down     = button;
						status.button_up_task  = action->task[1];
						status.button_up_block = action->block;
					}
*/
					// Launch the defined task
					if (action->task[0])
						ENQUEUE_TASK(action->task[0]);

					// Decide how to respond to this button
					return action->block;
				}
			}

			// Once we find a matching action chain, we look no futher
			break;
		}
	}

	// If no action was found, do not block it
	return FALSE;
}
