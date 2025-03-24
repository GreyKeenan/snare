#ifndef GUMETRY_cvpoly
#define GUMETRY_cvpoly


#include "gu/random.h"


double gumetry_cvpoly_area(const double * restrict /*nonull*/ vertices, unsigned int vertex_count);

int gumetry_cvpoly_rpoints(
	const double * restrict /*nonull*/ vertices,
	unsigned int vertex_count,
	double * restrict /*nonull*/ output,
	unsigned int points,
	void *rstate, gu_randomizer r
);
/*
	vertex_count > 2
	points > 0
	
	does *not* guarantee that the generated points are unique.

	`vertices` is a list of doubles,
	making up coordinate pairs, making up a list of vertices.
	Aka, it is an array of `vertex_count * 2` doubles.
	The polygon is assumed to be convex.

	`output` is a `points * 2`-length array of doubles to be overwritten.
	`points` is how many random points to generate.

	`r` is an already-seeded randomizer-function.

	returns 0 on success

	Uses areas of triangulated-triangles as weights to distribute points evenly.
	For excessively large polygons, attmepts to scale down their areas,
	so that the total area fits within a uint64_t.
	If unable to do so, fails.
	Attempts to scale down by (denominators):
	1<<0, 1<<1, 2<<2, 8<<4, 128<<8, 32768<<16, 2M<<32
	2^0 , 2^1 , 2^3 , 2^7 , 2^15  , 2^31     , 2^63
*/


#endif
