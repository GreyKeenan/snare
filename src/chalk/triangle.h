#ifndef CHALK_triangle
#define CHALK_triangle

#include "point.h"
#include <stdlib.h>

static inline unsigned int Chalk_area_triangle(
	const struct Chalk_Point a,
	const struct Chalk_Point b,
	const struct Chalk_Point c
)
{
	return abs(
		(((int)a.x - c.x) * ((int)b.y - c.y))
		- (((int)b.x - c.x) * ((int)a.y - c.y))
	) / 2;
}

static inline struct Chalk_Point Chalk_barycenter(
	const struct Chalk_Point a,
	const struct Chalk_Point b,
	const struct Chalk_Point c,
	const double refa, const double refb, const double refc
)
/*
a,b,c is a triangle
0 < abs(ra + rb + rc) <= 1
*/
{
	return (struct Chalk_Point) {
		.x = (a.x * refa + b.x * refb + c.x * refc),
		.y = (a.y * refa + b.y * refb + c.y * refc)
	};
}
#endif
