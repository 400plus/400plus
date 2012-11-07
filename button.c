/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdbool.h>

#include "firmware.h"
#include "main.h"
#include "macros.h"

#include "af_patterns.h"
#include "display.h"
#include "menu.h"
#include "menu_main.h"
#include "tasks.h"
#include "utils.h"
#include "viewfinder.h"

#include "button.h"

type_ACTION button_actions_main[] = {
	{BUTTON_DP,    true,  {menu_main_start}},
	{BUTTON_DISP,  true,  {display_brightness}},
	{BUTTON_JUMP,  true,  {button_jump_task}},
	{BUTTON_TRASH, true,  {button_trash_task}},
	{BUTTON_AV,    false, {toggle_img_format}},
	{BUTTON_UP,    false, {restore_iso}},
	{BUTTON_DOWN,  false, {restore_wb}},
	{BUTTON_LEFT,  false, {restore_metering}},
	END_OF_LIST
};

type_ACTION button_actions_400plus[] = {
	{BUTTON_DP,         true,  {menu_event_dp}},
//	{BUTTON_DISP,       true,  {menu_event_disp}},
	{BUTTON_MENU,       true,  {menu_event_menu}},
	{BUTTON_JUMP,       true,  {menu_event_jump}},
	{BUTTON_PLAY,       true,  {menu_event_play}},
	{BUTTON_TRASH,      true,  {menu_event_trash}},
	{BUTTON_DIAL_LEFT,  true,  {menu_event_prev}},
	{BUTTON_DIAL_RIGHT, true,  {menu_event_next}},
	{BUTTON_ZOOM_OUT,   true,  {menu_event_out}},
	{BUTTON_ZOOM_IN,    true,  {menu_event_in}},
	{BUTTON_AV,         true,  {menu_event_av, menu_event_av_up}},
	{BUTTON_SET,        true,  {menu_event_set}},
	{BUTTON_UP,         true,  {menu_event_up}},
	{BUTTON_DOWN,       true,  {menu_event_down}},
	{BUTTON_RIGHT,      true,  {menu_event_right}},
	{BUTTON_LEFT,       true,  {menu_event_left}},
	END_OF_LIST
};

type_ACTION button_actions_meter[] = {
	{BUTTON_DP,    true, {set_metering_spot}},
	END_OF_LIST
};

type_ACTION button_actions_wb[] = {
	{BUTTON_DP,    true, {set_whitebalance_colortemp}},
	END_OF_LIST
};

type_ACTION button_actions_iso[] = {
	{BUTTON_DP,    true,  {autoiso_enable}},
	{BUTTON_SET,   false, {autoiso_disable}},
	END_OF_LIST
};

type_ACTION button_actions_face[] = {
	{BUTTON_UP,    true, {viewfinder_up,    viewfinder_end}},
	{BUTTON_DOWN,  true, {}},
	{BUTTON_RIGHT, true, {viewfinder_right, viewfinder_end}},
	{BUTTON_LEFT,  true, {viewfinder_left,  viewfinder_end}},
	END_OF_LIST
};

type_ACTION button_actions_af[] = {
	{BUTTON_SET,   true, {afp_center}},
	{BUTTON_UP,    true, {afp_top}},
	{BUTTON_DOWN,  true, {afp_bottom}},
	{BUTTON_RIGHT, true, {afp_right}},
	{BUTTON_LEFT,  true, {afp_left}},
	{BUTTON_DISP,  true, {}},
	END_OF_LIST
};

type_CHAIN button_chains[] = {
	{GUIMODE_OLC,       button_actions_main},
	{GUIMODE_OFF,       button_actions_main},
	{GUIMODE_400PLUS,   button_actions_400plus},
	{GUIMODE_METER,     button_actions_meter},
	{GUIMODE_WB,        button_actions_wb},
	{GUIMODE_ISO,       button_actions_iso},
	{GUIMODE_FACE,      button_actions_face},
	{GUIMODE_AFPATTERN, button_actions_af},
	END_OF_LIST
};

int can_hold[BUTTON_COUNT] = {
	[BUTTON_AV]    = true,
	[BUTTON_UP]    = true,
	[BUTTON_DOWN]  = true,
	[BUTTON_RIGHT] = true,
	[BUTTON_LEFT]  = true,
};

int button_handler(type_BUTTON button, int is_button_down) {
	static type_TASK   button_up_task  = NULL;         // Task that must be executed when the current button is released
	static int         button_up_block = false;        // Response when the current button is released

	int gui_mode;

	type_CHAIN  *chain;
	type_ACTION *action;

	// Check first for button-down events
	if (is_button_down) {
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

						// Consider buttons with "button down" and "button up" events
						// and save "button up" parameters for later use
						if (can_hold[button]) {
							status.button_down = button;

							button_up_task  = action->task[1];
							button_up_block = action->block;
						}

						// Launch the defined task
						if (action->task[0])
							ENQUEUE_TASK(action->task[0]);

						// Decide how to respond to this button
						return action->block;
					}
				}

				// Once we find a matching action chain, we look no further
				break;
			}
		}

		// If no action was found, do not block it
		return false;
	} else {
		// Check for button-up events and act immediately
		if (status.button_down == button) {
			status.button_down = BUTTON_NONE;

			// Launch the defined task
			if (button_up_task)
				ENQUEUE_TASK(button_up_task);

			// Decide how to respond to this button
			return button_up_block;
		}

		// If no action was found, do not block it
		return false;
	}
}
