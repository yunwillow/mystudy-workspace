#ifndef MY_FRAC_H
#define MY_FRAC_H

#include <stdio.h>
#include <my_ioq.h>
#include <stdlib.h>

typedef struct {
	int a;
	int b;
	char c[32];
}frac;

void simpy(frac*);
void frscan(frac*);
frac frac_add(frac,frac);
frac frac_mis(frac,frac);
frac frac_mul(frac,frac);
frac frac_div(frac,frac);

#endif
