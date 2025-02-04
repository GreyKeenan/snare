#ifndef DOT_random
#define DOT_random


#include "./triangle.h"


struct Bagel_xorshiftr128plus;


static inline struct Dot Dot_randomDotInTriangle(
	const struct Dot a,
	const struct Dot b,
	const struct Dot c,
	const double sqrt_r1, const double r2 // 0 <= r <= 1
)
{
	return Dot_barycenter(a, b, c,
		(1 - sqrt_r1),
		(sqrt_r1 * (1 - r2)),
		(sqrt_r1 * r2)
	);
}

int Dot_randomDotsInCvpoly(
	const struct Dot * restrict /*nonull*/ poly,
	unsigned int vertices,
	struct Dot * restrict /*nonull*/ destination, //where to write points to
	unsigned int points, //how many points to generate
	struct Bagel_xorshiftr128plus * /*nonull*/ randomizer
);
/*
	assumes:
		vertices >= 3
		poly is a convex polygon
		randomizer to be seeded

	poly:
		pointer to vertices-length array of Dots
		represents a polygon bounding box for the random points
		must be convex for simple triangulation used
	destination:
		pointer to a points-length array of Dots
		Dots will be written there as they are generated
		May be modified even if the function exits with an error
	randomizer:
		an already-seeded Bagel_xorshiftr128plus

	returns 0 on success
*/


#endif
