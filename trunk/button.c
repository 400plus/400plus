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

typedef struct {
	int       block;
	type_TASK task_press;
	type_TASK task_release;
} reaction_r;

reaction_r button_actions_main[BUTTON_COUNT] = {
	[BUTTON_DP]    = {true,  menu_main_start},
	[BUTTON_DISP]  = {true,  display_brightness},
	[BUTTON_JUMP]  = {true,  button_jump_task},
	[BUTTON_TRASH] = {true,  button_trash_task},
	[BUTTON_AV]    = {false, toggle_img_format},
	[BUTTON_UP]    = {false, restore_iso},
	[BUTTON_DOWN]  = {false, restore_wb},
	[BUTTON_LEFT]  = {false, restore_metering},
};

reaction_r button_actions_400plus[BUTTON_COUNT] = {
	[BUTTON_DP]         = {true,  menu_event_dp},
//	[BUTTON_DISP]       = {true,  menu_event_disp},
	[BUTTON_MENU]       = {true,  menu_event_menu},
	[BUTTON_JUMP]       = {true,  menu_event_jump},
	[BUTTON_PLAY]       = {true,  menu_event_play},
	[BUTTON_TRASH]      = {true,  menu_event_trash},
	[BUTTON_DIAL_LEFT]  = {true,  menu_event_prev},
	[BUTTON_DIAL_RIGHT] = {true,  menu_event_next},
	[BUTTON_ZOOM_OUT]   = {true,  menu_event_out},
	[BUTTON_ZOOM_IN]    = {true,  menu_event_in},
	[BUTTON_AV]         = {true,  menu_event_av, menu_event_av_up},
	[BUTTON_SET]        = {true,  menu_event_set},
	[BUTTON_UP]         = {true,  menu_event_up},
	[BUTTON_DOWN]       = {true,  menu_event_down},
	[BUTTON_RIGHT]      = {true,  menu_event_right},
	[BUTTON_LEFT]       = {true,  menu_event_left},
};

reaction_r button_actions_meter[BUTTON_COUNT] = {
	[BUTTON_DP] = {true, set_metering_spot},
};

reaction_r button_actions_wb[BUTTON_COUNT] = {
	[BUTTON_DP] = {true, set_whitebalance_colortemp},
};

reaction_r button_actions_iso[BUTTON_COUNT] = {
	[BUTTON_DP]  = {true,  autoiso_enable},
	[BUTTON_SET] = {false, autoiso_disable},
};

reaction_r button_actions_face[BUTTON_COUNT] = {
	[BUTTON_UP]    = {true, viewfinder_up,    viewfinder_end},
	[BUTTON_DOWN]  = {true},
	[BUTTON_RIGHT] = {true, viewfinder_right, viewfinder_end},
	[BUTTON_LEFT]  = {true, viewfinder_left,  viewfinder_end},
};

reaction_r button_actions_af[BUTTON_COUNT] = {
	[BUTTON_SET]   = {true, afp_center},
	[BUTTON_UP]    = {true, afp_top},
	[BUTTON_DOWN]  = {true, afp_bottom},
	[BUTTON_RIGHT] = {true, afp_right},
	[BUTTON_LEFT]  = {true, afp_left},
	[BUTTON_DISP]  = {true},
};

reaction_r *button_chains[GUIMODE_COUNT] = {
	[GUIMODE_OLC]       = button_actions_main,
	[GUIMODE_OFF]       = button_actions_main,
	[GUIMODE_400PLUS]   = button_actions_400plus,
	[GUIMODE_METER]     = button_actions_meter,
	[GUIMODE_WB]        = button_actions_wb,
	[GUIMODE_ISO]       = button_actions_iso,
	[GUIMODE_FACE]      = button_actions_face,
	[GUIMODE_AFPATTERN] = button_actions_af,
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
	static int         button_up_block = false;        // reaction when the current button is released

	int gui_mode;

	reaction_r *chain;
	reaction_r *reaction;

	// Check first for button-down events
	if (is_button_down) {
		// Use fictitious GUI modes so everything else fits nicely
		if (FLAG_FACE_SENSOR && FLAG_GUI_MODE == GUIMODE_OFF)
			gui_mode = GUIMODE_FACE;
		else if(status.menu_running)
			gui_mode = GUIMODE_400PLUS;
		else
			gui_mode = FLAG_GUI_MODE;

		// Check whether this mode has an assigned chain
		if((chain = button_chains[gui_mode]) == NULL) {
			return false;
		} else {
			// Check that we have an action assigned to this button
			if ((reaction = &chain[button]) == NULL) {
				return false;
			} else {
				// Launch the defined task
				if (reaction->task_press)
					ENQUEUE_TASK(reaction->task_press);

				// Consider buttons with "button down" and "button up" events
				// and save "button up" parameters for later use
				if (can_hold[button]) {
					status.button_down = button;

					button_up_task  = reaction->task_release;
					button_up_block = reaction->block;
				}

				// Decide how to respond to this button
				return reaction->block;
			}
		}
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
