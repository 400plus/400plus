#include "menu.h"
#include "tasks.h"
#include "display.h"
#include "scripts.h"
#include "settings.h"

#include "main.h"

int* hMyTaskMessQue;

void  MyTask();
void  SendMyMessage(int param0, int param1);

void CreateMyTask() {
	hMyTaskMessQue = (int*)CreateMessageQueue("MyTaskMessQue", 0x40);
	CreateTask("MyTask", 0x19, 0x2000, MyTask, 0);
}

void my_IntercomHandler(int r0, char* ptr) {
	do {
		// Status-independent events
		switch (ptr[1]) {
		case EVENT_SETTINGS: // Mode dial moved, settings changed
			// Restore display
			SendMyMessage(RESTORE_DISPLAY, 0);
			continue;
		}

		if (FLAG_FACE_SENSOR) { // User has camera "on the face", display is blank
			switch(ptr[1]) {
			case BUTTON_UP:
				if(ptr[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_DOWN:
				if(ptr[2]) { // Button down
					// Ignore nose-activated event
					return;
				} else {     // Button up
				}
				break;
			case BUTTON_RIGHT:
				if(ptr[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and increase ISO
						SendMyMessage(VIEWFINDER_ISO_INC, 0);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					SendMyMessage(VIEWFINDER_ISO_END, 0);
					return;
				}
				break;
			case BUTTON_LEFT:
				if(ptr[2]) { // Button down
					if (settings.iso_in_viewfinder) {
						// Start ISO display on viewfinder and decrease ISO
						SendMyMessage(VIEWFINDER_ISO_DEC, 0);
						return;
					}
				} else {     // Button up
					// End ISO display on viewfinder
					SendMyMessage(VIEWFINDER_ISO_END, 0);
					return;
				}
				break;
			}
		} else if (FLAG_FACTORY_DIALOG) {
				switch (ptr[1]) {
				case BUTTON_DP:
					SendMyMessage(START_DEBUG_MODE, 0);
					return;
				}
				break;
		} else {	
			switch (FLAG_GUI_MODE) {
			case GUI_OFF:
			case GUI_MODE_MAIN:
				switch (ptr[1]) {
				case BUTTON_UP:
					if (ptr[2]) { // Button down
						// Restore ISO to nearest standard value
						SendMyMessage(RESTORE_ISO, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (ptr[2]) { // Button down
						// Restore WB to AWB
						SendMyMessage(RESTORE_WB, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (ptr[2]) { // Button down
						 // Restore metering mode to EVALUATIVE
						SendMyMessage(RESTORE_METERING, 0);
					} else {      // Button up
					}
					break;
				case BUTTON_DP:
					if (cameraMode.AEMode > 6) { // Non-creative modes
						SendMyMessage(SWITCH_RAW_JPEG, 0);
						return;
					} else {
						switch (settings.dp_action) {
							case DP_ACTION_INTERMEDIATE_ISO:
								// Set intermediate ISO
								SendMyMessage(SET_INTERMEDIATE_ISO, 0);
								return;
							case DP_ACTION_EXTENDED_AEB:
								// Start extended AEB script
								SendMyMessage(E_AEB, 0);
								return;
							case DP_ACTION_INTERVAL:
								// Start interval script
								SendMyMessage(INTERVAL, 0);
								return;
						}
					}
					break;
				}
				break;
			case GUI_MODE_MENU:
				switch (ptr[1]) {
				case BUTTON_DISP:
					// Initialize menu
					SendMyMessage(MENU_INIT, 0);
					break;;
				case BUTTON_DP:
					SendMyMessage(SHOW_FACTORY_MENU, 0);
					return;
				}
				break;
			case GUI_MODE_INFO:
				switch (ptr[1]) {
				case BUTTON_SET:
					// Save menu settings
					SendMyMessage(MENU_SET, 0);
					return;
				case BUTTON_DRIVE:
					// Cancel menu settings
					SendMyMessage(MENU_ESC, 0);
					return;
				case BUTTON_UP:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_UP, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_DOWN:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_DOWN, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_RIGHT:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_RIGHT, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_LEFT:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_LEFT, 0);
						return;
					} else {      // Button up
					}
					break;
				case BUTTON_AV:
					if (ptr[2]) { // Button down
						// Perform menu action
						SendMyMessage(MENU_SWAP, 0);
						return;
					} else {      // Button up
					}
					break;
				}
				break;
			case GUI_MODE_METER:
				switch (ptr[1]) {
				case BUTTON_DP:
					SendMyMessage(SET_METERING_SPOT, 0);
					return;
				}
				break;
			}
		}
	} while(FALSE);

	IntercomHandler(r0, ptr);
}

void MyTask () {
	int *pMessage;

	// Wait for camera to settle down
	SleepTask(1000);

	// Enable (hidden) CFn.8 for ISO H
	if (!cameraMode.CfExtendIso)
		SendToIntercom(0x31, 1, 1);

	// Enable realtime ISO change
	SendToIntercom(0xF0, 0, 0);
	SendToIntercom(0xF1, 0, 0);

	// Read (and apply) settings from file
	settings_read();
	settings_apply();

	// Loop while receiving messages
	while (TRUE) {
		ReceiveMessageQueue(hMyTaskMessQue, &pMessage, 0);

		switch (pMessage[0]) {
		case RESTORE_ISO:
			restore_iso();
			break;
		case RESTORE_WB:
			restore_wb();
			break;
		case RESTORE_METERING:
			restore_metering();
			break;
		case SWITCH_RAW_JPEG:
			switch_raw_jpeg();
			break;
		case RESTORE_DISPLAY:
			restore_display();
			break;
		case SET_INTERMEDIATE_ISO:
			set_intermediate_iso();
			break;
		case START_DEBUG_MODE:
			start_debug_mode();
		case SHOW_FACTORY_MENU:
			show_factory_menu();
			break;
		case SET_METERING_SPOT:
			set_metering_spot();
			break;
		case VIEWFINDER_ISO_INC:
			viewfinder_iso_inc();
			break;
		case VIEWFINDER_ISO_DEC:
			viewfinder_iso_dec();
			break;
		case VIEWFINDER_ISO_END:
			viewfinder_iso_end();
			break;
		case MENU_INIT:
			menu_initialize();
			break;
		case MENU_SWAP:
			menu_swap();
			break;
		case MENU_UP:
			menu_up();
			break;
		case MENU_DOWN:
			menu_down();
			break;
		case MENU_RIGHT:
			menu_right();
			break;
		case MENU_LEFT:
			menu_left();
			break;
		case MENU_SET:
			menu_set();
			break;
		case MENU_ESC:
			menu_esc();
			break;
		case E_AEB:
			script_extended_aeb();
			break;
		case INTERVAL:
			script_interval();
			break;
		}
	}
}

void SendMyMessage(int param0, int param1)
{
	int *pMessage = (int*)MainHeapAlloc(8);

	pMessage[0] = param0;
	pMessage[1] = param1;

	TryPostMessageQueue(hMyTaskMessQue, pMessage, 0);
}

void initialize_display() {
	SendMyMessage(RESTORE_DISPLAY, 0);
}

//SendToIntercom(0x1,1,1); //(0x0,1,2);  Zonedial mode P TV AV....
//SendToIntercom(0x2,1,1); //(0x2,1,0);  Meter mode Eval, Center...
//SendToIntercom(0x3,1,1); //(0x3,1,0);  Flash ex comp
//SendToIntercom(0x4,1,1); //(0x4,1,0);  drive mode
//SendToIntercom(0x5,1,1); //(0x5,1,0);  WB chose
//SendToIntercom(0x6,1,1); //(0x6,1,0);  MF manual focus
//SendToIntercom(0x7,1,1); // AF point selecttion: can extend some special: 7, 27, 41,47, 49, 73, 81,87, 97, 101, 105,113, 120,121, 116, 127, 135,
//					139,165,168,169, 175, 185,
//SendToIntercom(0x8,2,1); //Tv value:
//SendToIntercom(0xA,1,1); //AV comp ex selecttion: can extend some special
//SendToIntercom(0xB,1,1); // ISO set
//SendToIntercom(0xC,1,1); // Red eye
//SendToIntercom(0xD,1,1); //AEB BRK
//SendToIntercom(0xE,1,1); //WB BRK
//SendToIntercom(0xF,1,1); // Beep
//SendToIntercom(22,1,1); // LCDBrightness
//SendToIntercom(34,1,1); // RAW only, L+RAW, L only
//SendToIntercom(35,1,1); // S,M,L. Combine no.34 to M+RAW OK, S+RAW not ok
//SendToIntercom(36,1,1); // JPG Fine or Medium quality.
//SendToIntercom(43,1,1); // wb+-
//SendToIntercom(44~~>49,1,1); // Cf1-->6
//SendToIntercom(54,1,1); // Cf7
//SendToIntercom(56,1,1); // Cf8
//SendToIntercom(0x3C,1,0); //(0x3C,1,1); Cfn10
//SendToIntercom(0x3B,1,1); //(0x3B,1,0); Cfn11
//SendToIntercom(0x39,1,1); //(0x39,1,0);  Cfn9
//SendToIntercom(0x59,1,1); // Clear camera seting
//SendToIntercom(0x61,1,1); // Start update firmware
//SendToIntercom(0x6B,1,1); // Full CF viewfinder message
//SendToIntercom(0x6C,1,1); // Change Battery dialog
//SendToIntercom(0x6D,1,1); // Burst counter set

