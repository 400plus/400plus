#ifndef UTILS_H_
#define UTILS_H_

int ev_sgn(int ev);
int ev_inc(int ev);
int ev_dec(int ev);
int ev_add(int ying, int yang);
int ev_sub(int ying, int yang);

void ev_print(const char *dest, int ev);

int iso_next(int iso);
int iso_inc(int iso);
int iso_dec(int iso);

#endif /* UTILS_H_ */
