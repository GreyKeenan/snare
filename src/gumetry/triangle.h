#ifndef GUMETRY_triangle
#define GUMETRY_triangle


#include "./point.h"

#include <math.h>


// for all of these, they may assume that the 3 points given as a triangle are not equal to each other


struct gumetry_point gumetry_circumcenter(
	struct gumetry_point p0,
	struct gumetry_point p1,
	struct gumetry_point p2
);
/*
returns {NAN, NAN} when the 3 points are collinear
*/


static inline double gumetry_triangle_area(
	struct gumetry_point a,
	struct gumetry_point b,
	struct gumetry_point c
)
{ return fabs( (a.x - c.x)*(b.y - c.y) - (b.x - c.x)*(a.y - c.y) ) / 2; }

static inline struct gumetry_point gumetry_barycenter(
	struct gumetry_point a,
	struct gumetry_point b,
	struct gumetry_point c,
	double aw, double bw, double cw
)
// 0 < (ar + br + cr) <= 1
{
	return (struct gumetry_point) {
		a.x*aw + b.x*bw + c.x*cw,
		a.y*aw + b.y*bw + c.y*cw
	};
}

static inline struct gumetry_point gumetry_triangle_rpoint(
	struct gumetry_point a,
	struct gumetry_point b,
	struct gumetry_point c,
	double sqrt_random1, double random2
)
/*
	0 < random1 <= 1 // (pre-sqrt)
	0 < random2 <= 1

	given the square root of a random (0, 1] value & a random (0, 1] value,
	gives a random point within the triangle.
*/
{
	return gumetry_barycenter(a, b, c,
		(1 - sqrt_random1),
		(sqrt_random1 * (1 - random2)),
		(sqrt_random1 * random2)
	);
}


#endif
