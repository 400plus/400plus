#ifndef VXWORKS_IOLIB_H_
#define VXWORKS_IOLIB_H_

/* IOCTL Functions */

#define FIONREAD        1
#define FIOFLUSH        2
#define FIOOPTIONS      3
#define FIOBAUDRATE     4
#define FIODISKFORMAT   5
#define FIODISKINIT     6
#define FIOSEEK         7
#define FIOWHERE        8
#define FIODIRENTRY     9
#define FIORENAME      10
#define FIOREADYCHANGE 11
#define FIODISKCHANGE  13
#define FIOCANCEL      14
#define FIOSQUEEZE     15
#define FIONBIO        16
#define FIONMSGS       17
#define FIOGETNAME     18
#define FIOGETOPTIONS  19
#define FIOSETOPTIONS  FIOOPTIONS
#define FIOISATTY      20
#define FIOSYNC        21
#define FIOPROTOHOOK   22
#define FIOPROTOARG    23
#define FIORBUFSET     24
#define FIOWBUFSET     25
#define FIORFLUSH      26
#define FIOWFLUSH      27
#define FIOSELECT      28
#define FIOUNSELECT    29
#define FIONFREE       30
#define FIOMKDIR       31
#define FIORMDIR       32
#define FIOLABELGET    33
#define FIOLABELSET    34
#define FIOATTRIBSET   35
#define FIOCONTIG      36
#define FIOREADDIR     37
#define FIOFSTATGET    38
#define FIOUNMOUNT     39
#define FIOSCSICOMMAND 40
#define FIONCONTIG     41
#define FIOTRUNC       42
#define FIOGETFL       43
#define FIOTIMESET     44
#define FIOINODETONAME 45
#define FIOFSTATFSGET  46

/* IOCTL Options */

#define OPT_RAW      0x00
#define OPT_ECHO     0x01
#define OPT_CRMOD    0x02
#define OPT_TANDEM   0x04
#define OPT_7_BIT    0x08
#define OPT_MON_TRAP 0x10
#define OPT_ABORT    0x20
#define OPT_LINE     0x40

#define OPT_TERMINAL (OPT_ECHO | OPT_CRMOD | OPT_TANDEM |  OPT_MON_TRAP | OPT_7_BIT | OPT_ABORT | OPT_LINE)

/* Filetypes */

#define FSTAT_DIR  0040000
#define FSTAT_CHR  0020000
#define FSTAT_BLK  0060000
#define FSTAT_REG  0100000
#define FSTAT_LNK  0120000
#define FSTAT_NON  0140000

int     creat          (const char *name, int flag);
int     open           (const char *name, int flags, int mode);
STATUS  unlink         (char *name);
STATUS  remove         (const char *name);
STATUS  close          (int fd);
int     rename         (const char *oldname, const char * newname);
int     read           (int fd, char *buffer, size_t maxbytes);
int     write          (int fd, char *buffer, size_t nbytes);
int     ioctl          (int fd, int function, int arg);
int     lseek          (int fd, long offset, int whence);
STATUS  ioDefPathSet   (char *name);
void    ioDefPathGet   (char *pathname);
STATUS  chdir          (char *pathname);
char   *getcwd         (char *buffer, int size);
char   *getwd          (char *pathname);
void    ioGlobalStdSet (int stdFd, int newFd);
int     ioGlobalStdGet (int stdFd);
void    ioTaskStdSet   (int taskId, int stdFd, int newFd);
int     ioTaskStdGet   (int taskId, int stdFd);
BOOL    isatty         (int fd);
