#ifndef VXWORKS_SIGLIB_H_
#define VXWORKS_SIGLIB_H_

#include "vxworks.h"

int    sigInit      (void);
int    sigqueueInit (int nQueues);
int    sigemptyset  (sigset_t *pSet);
int    sigfillset   (sigset_t *pSet);
int    sigaddset    (sigset_t *pSet, int signo);
int    sigdelset    (sigset_t *pSet, int signo);
int    sigismember  (const sigset_t *pSet, int signo);

void (*signal(int signo, void (*pHandler)()))();

int    sigaction    (int signo, const struct sigaction *pAct, struct sigaction *pOact);
int    sigprocmask  (int how, const sigset_t *pSet, sigset_t *pOset);
int    sigpending   (sigset_t *pSet);
int    sigsuspend   (const sigset_t *pSet);
int    pause        (void);
int    sigtimedwait (const sigset_t *pSet, struct siginfo *pInfo, const struct timespec *pTimeout);
int    sigwaitinfo  (const sigset_t *pSet, struct siginfo *pInfo);
int    sigwait      (const sigset_t *pSet, int *pSig);
int    sigvec       (int sig, const struct sigvec *pVec, struct sigvec *pOvec);
int    sigsetmask   (int mask);
int    sigblock     (int mask);
int    raise        (int signo);
int    kill         (int tid, int signo);
int    sigqueue     (int tid, int signo, const union sigval value);

#endif
