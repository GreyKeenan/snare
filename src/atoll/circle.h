#ifndef ATOLL_circles
#define ATOLL_circles


#include "./point.h"


struct atoll_coast;


struct atoll_circle {
	struct atoll_podouble center;
	double radius;

	unsigned int arc; // the closing arc
};


int atoll_circle_identify(struct atoll_coast * /*nonull*/ coast, struct atoll_point * /*nonull*/ sites, unsigned int arc, double directix);
/*
	Checks the arc to see if it is converging.
	If it is, it creates a new circle event.
*/


#endif
