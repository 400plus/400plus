#ifndef VXWORKS_SIGLIB_H_
#define VXWORKS_SIGLIB_H_

#include "vxworks.h"

extern void (*signal(int signo, void (*pHandler)()))();

extern int    sigInit      (void);
extern int    sigqueueInit (int nQueues);
extern int    sigemptyset  (sigset_t *pSet);
extern int    sigfillset   (sigset_t *pSet);
extern int    sigaddset    (sigset_t *pSet, int signo);
extern int    sigdelset    (sigset_t *pSet, int signo);
extern int    sigismember  (const sigset_t *pSet, int signo);
extern int    sigaction    (int signo, const struct sigaction *pAct, struct sigaction *pOact);
extern int    sigprocmask  (int how, const sigset_t *pSet, sigset_t *pOset);
extern int    sigpending   (sigset_t *pSet);
extern int    sigsuspend   (const sigset_t *pSet);
extern int    pause        (void);
extern int    sigtimedwait (const sigset_t *pSet, struct siginfo *pInfo, const struct timespec *pTimeout);
extern int    sigwaitinfo  (const sigset_t *pSet, struct siginfo *pInfo);
extern int    sigwait      (const sigset_t *pSet, int *pSig);
extern int    sigvec       (int sig, const struct sigvec *pVec, struct sigvec *pOvec);
extern int    sigsetmask   (int mask);
extern int    sigblock     (int mask);
extern int    raise        (int signo);
extern int    kill         (int tid, int signo);
extern int    sigqueue     (int tid, int signo, const union sigval value);

#endif /* VXWORKS_SIGLIB_H_ */
