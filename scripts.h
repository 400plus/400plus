#ifndef SCRIPTS_H_
#define SCRIPTS_H_

// Time between tries while waiting for camera
#define WAIT_CAMERA_BUSY 250

// Time between tries while waiting for user
#define WAIT_USER_ACTION 250

// Feedback timing
#define FEEDBACK_LENGTH    25
#define FEEDBACK_INTERVAL 475

// One second while delaying script
#define SCRIPT_DELAY_REPEAT   4
#define SCRIPT_DELAY_TIME   250

void script_extended_aeb();
void script_interval();
void script_wave();

#endif /* SCRIPTS_H_ */
