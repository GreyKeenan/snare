#ifndef CHALK_random
#define CHALK_random

#include "./triangle.h"

struct Bagel_xorshiftr128plus;

static inline struct Chalk_Point Chalk_randomPointInTriangle(
	const struct Chalk_Point a,
	const struct Chalk_Point b,
	const struct Chalk_Point c,
	const double sqrt_r1, const double r2 // 0 <= r <= 1
)
{
	return Chalk_barycenter(a, b, c,
		(1 - sqrt_r1),
		(sqrt_r1 * (1 - r2)),
		(sqrt_r1 * r2)
	);
}

int Chalk_randomPoints_cvpoly(
	const struct Chalk_Point *poly,
	unsigned int vertices,
	struct Chalk_Point *destination, //where to write points to
	unsigned int points, //how many points to generate
	struct Bagel_xorshiftr128plus *randomizer
);


#endif
