#ifndef VXWORKS_SIOLIB_H_
#define VXWORKS_SIOLIB_H_

typedef struct {} SIO_DRV_FUNCS;

typedef struct sio_chan {
	SIO_DRV_FUNCS * pDrvFuncs;
} SIO_CHAN;

#endif /* VXWORKS_SIOLIB_H_ */
