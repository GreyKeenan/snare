#ifndef ATOLL_circles
#define ATOLL_circles


#include "gumetry/point.h"

#include <stdbool.h>


struct atoll_coast;


struct atoll_circle {
	struct gumetry_point center;
	double radius;

	unsigned int arc; // the closing arc
};

int atoll_circle_identify(struct atoll_coast *coast, struct gumetry_point *sites, unsigned int arc, double directix);
/*
*/

int atoll_arcIsntConverging(
	struct atoll_circle *destination,
	unsigned int forarc,

	double directix,
	struct gumetry_point focus_a,
	struct gumetry_point focus_b,
	struct gumetry_point focus_c
);
/*
`a`, `b`, and `c` are sequential foci from the beachline.
Identifies whether the arc `b` is converging.
Order matters.
If it *is* converging, returns 0
and writes the convergence-point (circumcenter) to *destination.
*/


#endif
