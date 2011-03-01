#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "scripts.h"
#include "settings.h"

#include "main.h"

int *message_queue;

void task_dispatcher();

void initialize() {
	message_queue = (int*)CreateMessageQueue("message_queue", 0x40);
	CreateTask("task_dispatcher", 0x19, 0x2000, task_dispatcher, 0);

	ENQUEUE_TASK(start_up);
}

void initialize_display() {
	ENQUEUE_TASK(restore_display);
}

void message_proxy(int handler, char *message) {
	do {
		// Status-independent events
		switch (message[1]) {
		case EVENT_SETTINGS: // Mode dial moved, settings changed
			// Restore display
			ENQUEUE_TASK(restore_display);
			continue;
		}

		if (FLAG_FACE_SENSOR) { // User has camera "on the face", display is blank
			switch(message[1]) {
			case BUTTON_UP:
				if(message[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_DOWN:
				if(message[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_RIGHT:
				if(message[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and increase ISO
						ENQUEUE_TASK(viewfinder_iso_inc);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					ENQUEUE_TASK(viewfinder_iso_end);
					return;
				}
				break;
			case BUTTON_LEFT:
				if(message[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and decrease ISO
						ENQUEUE_TASK(viewfinder_iso_dec);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					ENQUEUE_TASK(viewfinder_iso_end);
					return;
				}
				break;
			}
		} else {	
			switch (FLAG_GUI_MODE) {
			case GUI_OFF:
			case GUI_MODE_MAIN:
				switch (message[1]) {
				case BUTTON_UP:
					if (message[2]) { // Button down
						// Restore ISO to nearest standard value
						ENQUEUE_TASK(restore_iso);
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (message[2]) { // Button down
						// Restore WB to AWB
						ENQUEUE_TASK(restore_wb);
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (message[2]) { // Button down
						 // Restore metering mode to EVALUATIVE
						ENQUEUE_TASK(restore_metering);
					} else {      // Button up
					}
					break;
				case BUTTON_DP:
					ENQUEUE_TASK(dp_action);
					return;
				}
				break;
			case GUI_MODE_MENU:
				switch (message[1]) {
				case BUTTON_DISP:
					// Initialize menu
					ENQUEUE_TASK(menu_initialize);
					break;;
				case BUTTON_DP:
					ENQUEUE_TASK(show_factory_menu);
					return;
				}
				break;
			case GUI_MODE_INFO:
				switch (message[1]) {
				case BUTTON_SET:
					// Save menu settings
					ENQUEUE_TASK(menu_set);
					return;
				case BUTTON_DRIVE:
					// Cancel menu settings
					ENQUEUE_TASK(menu_esc);
					return;
				case BUTTON_UP:
					if (message[2]) { // Button down
						// Perform menu action
						ENQUEUE_TASK(menu_up);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (message[2]) { // Button down
						// Perform menu action
						ENQUEUE_TASK(menu_down);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_RIGHT:
					if (message[2]) { // Button down
						// Perform menu action
						ENQUEUE_TASK(menu_right);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (message[2]) { // Button down
						// Perform menu action
						ENQUEUE_TASK(menu_left);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_AV:
					if (message[2]) { // Button down
						// Perform menu action
						ENQUEUE_TASK(menu_swap);
						return;
					} else {      // Button up
					}
					break;
				}
				break;
			case GUI_MODE_METER:
				switch (message[1]) {
				case BUTTON_DP:
					ENQUEUE_TASK(set_metering_spot);
					return;
				}
				break;
			}
		}
	} while(FALSE);

	IntercomHandler(handler, message);
}

void task_dispatcher () {
	void(*task)();

	// Loop while receiving messages
	while (TRUE) {
		ReceiveMessageQueue(message_queue, &task, 0);
		task();
	}
}

