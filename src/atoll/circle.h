#ifndef ATOLL_circles
#define ATOLL_circles


#include "./point.h"

#include <stdbool.h>


struct atoll_coast;


struct atoll_circle {
	struct atoll_podouble center;
	double radius;

	unsigned int arc; // the closing arc
};

int atoll_circle_identify(struct atoll_coast *coast, struct atoll_podouble *sites, unsigned int arc, double directix);
/*
*/

int atoll_arcIsntConverging(
	struct atoll_circle *destination,
	unsigned int forarc,

	double directix,
	struct atoll_podouble focus_a,
	struct atoll_podouble focus_b,
	struct atoll_podouble focus_c
);
/*
`a`, `b`, and `c` are sequential foci from the beachline.
Identifies whether the arc `b` is converging.
Order matters.
If it *is* converging, returns 0
and writes the convergence-point (circumcenter) to *destination.
*/


#endif
