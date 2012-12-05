/**
 * $Revision$
 * $Date$
 * $Author$
 */

#ifndef MAIN_H_
#define MAIN_H_

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
	int         preset_active;     // There is a preset active
	int         main_dial_moved;   // Main dial has just moved
	int         measuring;         // Camera is measuring the scene
	tv_t        measured_tv;       // Shutter speed as proposed by the metering
	av_t        measured_av;       // Aperture as proposed by the metering
	ev_t        measured_ev;       // Exposure deviation as measured by the camera
	int         last_shot_tv;      // Shutter speed of the last shot taken
	int         last_shot_av;      // Aperture of the last shot taken
	ec_t        ev_comp;           // Exposure compensation for AutoISO + M
	type_SCRIPT last_script;       // Last executed script
} status_t;

// Our own code
extern void initialize();
extern void initialize_display();
extern void intercom_proxy(const int handler, char *message);
extern void enqueue_action(action_t action);

// Shared globals
extern status_t status;

#endif /* MAIN_H_ */
