#ifndef DOT_triangle
#define DOT_triangle


#include "./dot.h"
#include <stdlib.h>


static inline unsigned int Dot_area_triangle(
	const struct Dot a,
	const struct Dot b,
	const struct Dot c
)
{
	return abs(
		( ((int)a.x - c.x) * ((int)b.y - c.y) )
		- ( ((int)b.x - c.x) * ((int)a.y - c.y) )
	) / 2;
}

static inline struct Dot Dot_barycenter(
	const struct Dot a,
	const struct Dot b,
	const struct Dot c,
	const double refa, const double refb, const double refc
)
/*
a,b,c is a triangle
0 < abs(ra + rb + rc) <= 1
*/
{
	return (struct Dot) {
		.x = (a.x * refa + b.x * refb + c.x * refc),
		.y = (a.y * refa + b.y * refb + c.y * refc)
	};
}


#endif
