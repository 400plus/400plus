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

typedef enum {
	VF_STATUS_NONE,
	VF_STATUS_MSM,
	VF_STATUS_ISO,
} vf_status_t;

// Global status
typedef struct {
	int         button_down;       // A button is down, and which one
	int         script_running;    // A script is running
	int         script_stopping;   // The currently running script mist stop
	int         menu_running;      // A menu is running
	int         afp_dialog;        // The last active dialog was the AF Point selection dialog
	int         main_dial_ae;      // AE mode selected in the main dial
	int         cmode_active;      // There is a custom mode currently active
	int         measuring;         // Camera is measuring the scene
	tv_t        measured_tv;       // Shutter speed as proposed by the metering
	av_t        measured_av;       // Aperture as proposed by the metering
	ec_t        measured_ec;       // Exposure deviation as measured by the camera (M) or set by the user (P, Tv, Av)
	tv_t        last_shot_tv;      // Shutter speed of the last shot taken
	av_t        last_shot_av;      // Aperture of the last shot taken
	int         last_shot_fl;      // Focal length during last shot
	int         fexp;              // Fixed exposure is active
	int         fexp_ev;           // Combined exposure value for fixed exposure
	int         msm_count;         // Multi-spot metering: count of registered points
	int         msm_tv;            // Multi-spot metering: sum of all Tv values registered
	int         msm_av;            // Multi-spot metering: sum of all Av values registered
	int         msm_active;        // Multi-spot metering: is active and in M mode
	ic_event_t  ignore_msg;        // Event to be ignored at intercom
	vf_status_t vf_status;         // Status of viewfinder
} status_t;

// Our own code
extern void initialize(void);
extern void intercom_proxy(const int handler, char *message);
extern void enqueue_action(action_t action);
extern void hack_MainCtrlInit(void);
extern void hack_GUIInit(void);

// Shared globals
extern status_t status;

#endif /* MAIN_H_ */
