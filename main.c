/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include <stdio.h>
#include <stdbool.h>

#include "macros.h"
#include "firmware.h"

#include "af_patterns.h"
#include "button.h"
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

// Main queues
int *task_queue;

// Global status
type_STATUS status = {
	button_down       : BUTTON_NONE,
	script_running    : false,
	script_stopping   : false,
	iso_in_viewfinder : false,
	afp_dialog        : false,
	last_preset       : false,
	ignore_ae_change  : false,
	booting           : true,
	measuring         : false,
	ev_comp           : 0x00,
};

void task_dispatcher();
void message_logger (char *message);

void initialize() {
	task_queue = (int*)CreateMessageQueue("task_queue", 0x40);
	CreateTask("Task Dispatcher", 25, 0x2000, task_dispatcher, 0);

	ENQUEUE_TASK(start_up);
}

void initialize_display() {
	if (!status.script_running)
		ENQUEUE_TASK(restore_display);
}

void intercom_proxy(const int handler, char *message) {
	int button_down = true;

	type_BUTTON button;

#ifdef ENABLE_DEBUG
	message_logger(message);
#endif

	// Fast path for the case of a running script
	if (status.script_running)
		switch(message[1]) {
		case IC_SHUTDOWN: // Camera has shut down
			script_restore();
			goto pass_message;
		case IC_SHOOTING: // Shot taken while script is running
			status.last_shot_tv = message[2];
			status.last_shot_av = message[3];
			goto pass_message;
		case IC_BUTTON_DP: // DP Button stops the script
			status.script_stopping = true;
			goto block_message;
		default:
			goto pass_message;
		}
	else
		// Status-independent events and special cases
		switch (message[1]) {
		case IC_SET_LANGUAGE:
			ENQUEUE_TASK(lang_pack_config);
			goto pass_message;
		case IC_DIALOGON: // Entering a dialog
			status.afp_dialog = (message[2] == IC_SET_AF);
			goto pass_message;
		case IC_DIALOGOFF:
			if (status.menu_running)
				ENQUEUE_TASK(menu_event_finish);
			goto pass_message;
		case IC_MEASURING:
			status.measuring = message[2];
			ENQUEUE_TASK(restore_display);
			goto pass_message;
		case IC_MEASUREMENT:
			if (status.measuring) {
				status.measured_tv = message[2];
				status.measured_av = message[3];
				status.measured_ev = message[4];

				if (settings.autoiso_enable)
					ENQUEUE_TASK(autoiso);
			}
			goto pass_message;
		case IC_SETTINGS_0: // Settings changed (begin of sequence)
			if (status.ignore_ae_change) {
				// Ignore first AE change after loading a preset, as it generates this same event
				status.ignore_ae_change = false;
			} else {
				// Handle preset recall when dial moved to A-DEP
				status.last_preset  = false;
				status.main_dial_ae = message[2];

				if (presets_config.use_adep && status.main_dial_ae == AE_MODE_ADEP) {
					if (status.booting) {
						ENQUEUE_TASK(preset_recall);
					} else {
						ENQUEUE_TASK(preset_recall_full);
					}
				}
			}
			goto pass_message;
		case IC_SETTINGS_3: // Settings changed (end of sequence)
			// Restore display
			ENQUEUE_TASK(restore_display);
			goto pass_message;
		case IC_AFPDLGOFF: // Exiting AF-Point selection dialog
			if (status.afp_dialog) {
				// Open Extended AF-Point selection dialog
				message[1] = IC_AFPDLGON;
				status.afp_dialog = false;
				ENQUEUE_TASK(afp_enter);
			}
			goto pass_message;
		case IC_BUTTON_DIAL: // Front Dial, we should detect direction and use our BTN IDs
			button = (message[2] & 0x80) ? BUTTON_DIAL_LEFT : BUTTON_DIAL_RIGHT;
			goto handle_button;
		case IC_BUTTON_DISP:
			button = BUTTON_DISP;
			goto handle_button;
		case IC_BUTTON_SET:
			button = BUTTON_SET;
			goto handle_button;
		case IC_BUTTON_UP:
			if (!status.menu_running) {
				button = BUTTON_UP;
				button_down = message[2];
			}
			goto handle_button;
		case IC_BUTTON_DOWN:
			if (!status.menu_running) {
				button = BUTTON_DOWN;
				button_down = message[2];
			}
			goto handle_button;
		case IC_BUTTON_RIGHT:
			button = BUTTON_RIGHT;
			button_down = message[2];
			goto handle_button;
		case IC_BUTTON_LEFT:
			button = BUTTON_LEFT;
			button_down = message[2];
			goto handle_button;
		case IC_BUTTON_DP:
			button = BUTTON_DP;
			goto handle_button;
		case IC_BUTTON_AV:
			button = BUTTON_AV;
			button_down = message[2];
			goto handle_button;
		default:
			goto pass_message;
		}

handle_button:
	if (button != BUTTON_NONE)
		if (button_handler(button, button_down))
			goto block_message;

pass_message:
	IntercomHandler(handler, message);

block_message:
	return;
}

void task_dispatcher () {
	type_TASK task;

	// Loop while receiving messages
	for (;;) {
		ReceiveMessageQueue(task_queue, &task, false);
		task();
	}
}

void message_logger(char *message) {
	int i;
	char text[256];
	static int id = 0;

	for (i = 0; i < message[0]; i++)
		sprintf(text + 3 * i, "%02X ", message[i]);

	printf_log(8, 8, "[400plus-MSG%04d-%02X]: %s", id++, FLAG_GUI_MODE, text);
}
