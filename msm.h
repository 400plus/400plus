#ifndef MSM_H_
#define MSM_H_

#define MSM_TIMEOUT 2000 // Time (ms) for the DOWN button to become a DELETE
#define MSM_RETRY    100 // Time (ms) between each check for the DOWN button

void msm_register(void);
void msm_release (void);
void msm_start   (void);
void msm_stop    (void);

#endif
