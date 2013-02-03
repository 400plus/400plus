/**
 * $Revision$
 * $Date$
 * $Author$
 *
 * Multi-spot metering
 *
 */

#ifndef MSM_H_
#define MSM_H_

#define MSM_TIMEOUT 2000 // Time (ms) for the DOWN button to become a DELETE

void msm_register();
void msm_release ();
void msm_start   ();
void msm_stop    ();

#endif
