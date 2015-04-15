#include <stdbool.h>

#include "firmware.h"
#include "main.h"
#include "macros.h"
#include "debug.h"

#include "actions.h"
#include "autoiso.h"
#include "af_patterns.h"
#include "display.h"
#include "fexp.h"
#include "qexp.h"
#include "menu.h"
#include "menu_main.h"
#include "settings.h"
#include "utils.h"
#include "viewfinder.h"

#include "button.h"

typedef struct {
	int      block;
	action_t action_press;
	action_t action_release;
} reaction_t;

typedef struct  {
	reaction_t **reaction;
	int         *condition;
} chain_t;

reaction_t
	reaction_main_dp    = {true,  menu_main_start},
	reaction_main_disp  = {true,  display_brightness} ,
	reaction_main_jump  = {true,  button_jump_action},
	reaction_main_trash = {true,  button_trash_action},
	reaction_main_av    = {false, toggle_img_format},
	reaction_main_up    = {false, restore_iso},
	reaction_main_down  = {false, restore_wb},
	reaction_main_left  = {false, restore_metering}
;

reaction_t *button_actions_main[BUTTON_COUNT] = {
	[BUTTON_DP]    = &reaction_main_dp,
	[BUTTON_DISP]  = &reaction_main_disp,
	[BUTTON_JUMP]  = &reaction_main_jump,
	[BUTTON_TRASH] = &reaction_main_trash,
	[BUTTON_AV]    = &reaction_main_av,
	[BUTTON_UP]    = &reaction_main_up,
	[BUTTON_DOWN]  = &reaction_main_down,
	[BUTTON_LEFT]  = &reaction_main_left,
};

reaction_t
	reaction_400plus_dp          = {true,  menu_event_dp},
//	reaction_400plus_disp        = {true,  menu_event_disp},
	reaction_400plus_menu        = {true,  menu_event_menu},
	reaction_400plus_jump        = {true,  menu_event_jump},
	reaction_400plus_play        = {true,  menu_event_play},
	reaction_400plus_trash       = {true,  menu_event_trash},
	reaction_400plus_wheel_left  = {true,  menu_event_prev},
	reaction_400plus_wheel_right = {true,  menu_event_next},
	reaction_400plus_zoom_out    = {true,  menu_event_out},
	reaction_400plus_zoom_in     = {true,  menu_event_in},
	reaction_400plus_av          = {true,  menu_event_av, menu_event_av_up},
	reaction_400plus_set         = {true,  menu_event_set},
	reaction_400plus_up          = {true,  menu_event_up},
	reaction_400plus_down        = {true,  menu_event_down},
	reaction_400plus_right       = {true,  menu_event_right},
	reaction_400plus_left        = {true,  menu_event_left}
;


reaction_t *button_actions_400plus[BUTTON_COUNT] = {
	[BUTTON_DP]          = &reaction_400plus_dp,
//	[BUTTON_DISP]        = &reaction_400plus_disp,
	[BUTTON_MENU]        = &reaction_400plus_menu,
	[BUTTON_JUMP]        = &reaction_400plus_jump,
	[BUTTON_PLAY]        = &reaction_400plus_play,
	[BUTTON_TRASH]       = &reaction_400plus_trash,
	[BUTTON_WHEEL_LEFT]  = &reaction_400plus_wheel_left,
	[BUTTON_WHEEL_RIGHT] = &reaction_400plus_wheel_right,
	[BUTTON_ZOOM_OUT]    = &reaction_400plus_zoom_out,
	[BUTTON_ZOOM_IN]     = &reaction_400plus_zoom_in,
	[BUTTON_AV]          = &reaction_400plus_av,
	[BUTTON_SET]         = &reaction_400plus_set,
	[BUTTON_UP]          = &reaction_400plus_up,
	[BUTTON_DOWN]        = &reaction_400plus_down,
	[BUTTON_RIGHT]       = &reaction_400plus_right,
	[BUTTON_LEFT]        = &reaction_400plus_left,
};

reaction_t
	reaction_meter_dp = {true, set_metering_spot}
;

reaction_t *button_actions_meter[BUTTON_COUNT] = {
	[BUTTON_DP] = &reaction_meter_dp,
};

reaction_t
	reaction_wb_dp = {true, set_whitebalance_colortemp}
;

reaction_t *button_actions_wb[BUTTON_COUNT] = {
	[BUTTON_DP] = &reaction_wb_dp,
};

reaction_t
	reaction_iso_dp  = {true,  autoiso_enable},
	reaction_iso_set = {false, autoiso_disable}
;

reaction_t *button_actions_iso[BUTTON_COUNT] = {
	[BUTTON_DP]  = &reaction_iso_dp,
	[BUTTON_SET] = &reaction_iso_set,
};

reaction_t
	reaction_face_set   = {true, viewfinder_set},
	reaction_face_up    = {true, viewfinder_up,    viewfinder_end},
	reaction_face_down  = {true, viewfinder_down,  viewfinder_end},
	reaction_face_right = {true, viewfinder_right, viewfinder_end},
	reaction_face_left  = {true, viewfinder_left,  viewfinder_end}
;

reaction_t *button_actions_face[BUTTON_COUNT] = {
	[BUTTON_SET]   = &reaction_face_set,
	[BUTTON_UP]    = &reaction_face_up,
	[BUTTON_DOWN]  = &reaction_face_down,
	[BUTTON_RIGHT] = &reaction_face_right,
	[BUTTON_LEFT]  = &reaction_face_left,
};

reaction_t
	reaction_af_set   = {true, afp_center},
	reaction_af_up    = {true, afp_top},
	reaction_af_down  = {true, afp_bottom},
	reaction_af_right = {true, afp_right},
	reaction_af_left  = {true, afp_left},
	reaction_af_disp  = {true}
;

reaction_t *button_actions_af[BUTTON_COUNT] = {
	[BUTTON_SET]   = &reaction_af_set,
	[BUTTON_UP]    = &reaction_af_up,
	[BUTTON_DOWN]  = &reaction_af_down,
	[BUTTON_RIGHT] = &reaction_af_right,
	[BUTTON_LEFT]  = &reaction_af_left,
	[BUTTON_DISP]  = &reaction_af_disp,
};

reaction_t
	reaction_drive_set    = {false, drivemode_set};

reaction_t *button_actions_drive[BUTTON_COUNT] = {
	[BUTTON_SET]   = &reaction_drive_set,
};

chain_t
	chain_actions_main    = {button_actions_main},
	chain_actions_400plus = {button_actions_meter},
	chain_actions_meter   = {button_actions_wb},
	chain_actions_wb      = {button_actions_iso},
	chain_actions_iso     = {button_actions_af},
	chain_actions_drive   = {button_actions_drive},
	chain_actions_face    = {button_actions_400plus},
	chain_actions_af      = {button_actions_face, &settings.use_dpad}
;

chain_t *button_chains[GUIMODE_COUNT] = {
	[GUIMODE_OLC]       = &chain_actions_main,
	[GUIMODE_OFF]       = &chain_actions_main,
	[GUIMODE_METER]     = &chain_actions_400plus,
	[GUIMODE_WB]        = &chain_actions_meter,
	[GUIMODE_ISO]       = &chain_actions_wb,
	[GUIMODE_AFPATTERN] = &chain_actions_iso,
	[GUIMODE_DRIVE]     = &chain_actions_drive,
	[GUIMODE_400PLUS]   = &chain_actions_face,
	[GUIMODE_FACE]      = &chain_actions_af,
};

int can_hold[BUTTON_COUNT] = {
	[BUTTON_AV]    = true,
	[BUTTON_UP]    = true,
	[BUTTON_DOWN]  = true,
	[BUTTON_RIGHT] = true,
	[BUTTON_LEFT]  = true,
};

int button_handler(button_t button, int is_button_down) {
	static action_t   button_up_action = NULL;  // Action that must be executed when the current button is released
	static int        button_up_block  = false; // Reaction when the current button is released

	int gui_mode;

	chain_t    *chain;
	reaction_t *reaction;

	// Check first for button-down events
	if (is_button_down) {
		// Use fictitious GUI modes so everything else fits nicely
		if (FLAG_FACE_SENSOR && FLAG_GUI_MODE == GUIMODE_OFF)
			gui_mode = GUIMODE_FACE;
		else if(status.menu_running)
			gui_mode = GUIMODE_400PLUS;
		else
			gui_mode = FLAG_GUI_MODE;


		if((chain = button_chains[gui_mode]) == NULL) {
			// This mode does not have an assigned chain
			//debug_log("gui_mode[0x%X]: no btn chain", gui_mode);
			return false;
		} else if (!chain->condition || *chain->condition) {
			// Check that we have an action assigned to this button
			if ((reaction = chain->reaction[button]) == NULL) {
				//debug_log("gui_mode[0x%X]: btn[0x%X] no action", gui_mode, button);
				return false;
			} else {
				// Launch the defined action
				if (reaction->action_press)
					enqueue_action(reaction->action_press);

				// Consider buttons with "button down" and "button up" events
				// and save "button up" parameters for later use
				if (can_hold[button]) {
					status.button_down = button;

					button_up_action = reaction->action_release;
					button_up_block  = reaction->block;
				}

				// Decide how to respond to this button
				return reaction->block;
			}
		} else {
			// This mode is configured off
			return false;
		}
	} else {
		// Check for button-up events and act immediately
		if (status.button_down == button) {
			status.button_down = BUTTON_NONE;

			// Launch the defined action
			if (button_up_action)
				enqueue_action(button_up_action);

			// Decide how to respond to this button
			return button_up_block;
		}

		// If no action was found, do not block it
		return false;
	}
}

void hack_send_jump_and_trash_buttons(int r0, int r1, int button) {
#ifdef ENABLE_DEBUG
	printf_log(1, 6, "[400Plus-JMP-TRS] r0=%x, r1=%x, button=%x", r0, r1, button);
#endif
	switch (button) {
	case 4: // JUMP_UP
		break;
	case 5: // JUMP_DOWN
		button_handler(BUTTON_JUMP, true);
		break;
	case 8: // TRASH_UP
		break;
	case 9: // TRASH_DOWN
		button_handler(BUTTON_TRASH, true);
		break;
	}
}
