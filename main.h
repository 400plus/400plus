/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "firmware.h"
#include "exposure.h"
#include "scripts.h"

// Action definitions
typedef void(*action_t)(void);
typedef int (*proxy_t) (char*);

// Global status
typedef struct {
	int         button_down;       // A button is down, and which one
	int         script_running;    // A script is running
	int         script_stopping;   // The currently running script mist stop
	int         menu_running;      // A menu is running
	int         iso_in_viewfinder; // ISO is being displayed in the viewfinder
	int         afp_dialog;        // The last active dialog was the AF Point selection dialog
	int         main_dial_ae;      // AE mode selected in the main dial
	int         cmode_active;      // There is a custom mode currently active
	int         measuring;         // Camera is measuring the scene
	tv_t        measured_tv;       // Shutter speed as proposed by the metering
	av_t        measured_av;       // Aperture as proposed by the metering
	ec_t        measured_ec;       // Exposure deviation as measured by the camera (M) or set by the user (P, Tv, Av)
	tv_t        last_shot_tv;      // Shutter speed of the last shot taken
	av_t        last_shot_av;      // Aperture of the last shot taken
	int         fexp;              // Fixed exposure is active
	int       	fexp_ev;           // Combined exposure value for fixed exposure
	ec_t        ev_comp;           // Exposure compensation for AutoISO + M
	type_SCRIPT last_script;       // Last executed script
	intercom_event_t ignore_msg;   // Event to be ignored at intercom
} status_t;

// Our own code
extern void initialize();
extern void initialize_display();
extern void intercom_proxy(const int handler, char *message);
extern void enqueue_action(action_t action);

// Shared globals
extern status_t status;

#endif /* MAIN_H_ */
