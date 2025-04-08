#ifndef ATOLL_DEBUG_paint
#define ATOLL_DEBUG_paint

#include <stdio.h>


struct atoll_diagram;
struct atoll_coast;


int atoll_DEBUG_initSDL(void);
void atoll_DEBUG_endSDL(void);

void atoll_DEBUG_setscale(double scale, double offset);

static inline int atoll_DEBUG_wait(void)
{
	return fgetc(stdin);
}

void atoll_DEBUG_paint(struct atoll_diagram *diagram, struct atoll_coast *coast);

#endif
