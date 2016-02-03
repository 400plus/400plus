#ifndef VRAM_H_
#define VRAM_H_

// VRAM Semaphore

int  TakeVRAMSemaphore(int *address);
void GiveVRAMSemaphore(int *address);

// VRAM Transfer Screen

extern int(*TransferScreen)         (int r0, int r1, int r2, int r3);

extern int TransferNormalScreen     (int r0, int r1, int r2, int r3);
extern int TransferUpsideDownScreen (int r0, int r1, int r2, int r3);
extern int TransferMirrorScreen     (int r0, int r1, int r2, int r3);
extern int TransferRotatedScreen    (int r0, int r1, int r2, int r3);

// Internal to transfer screen

extern int sub_FF92E704 (int r0, int r1, int r2, int r3);
extern int sub_FF92E4C4 (int r0, int r1, int r2, int r3);

#endif
