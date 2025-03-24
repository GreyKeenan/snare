#ifndef GUMETRY_triangle
#define GUMETRY_triangle


#include <math.h>


static inline double gumetry_triangle_area(
	const double a[static 2],
	const double b[static 2],
	const double c[static 2]
)
{ return fabs( (a[0] - c[0])*(b[1] - c[1]) - (b[0] - c[0])*(a[1] - c[1]) ) / 2; }

static inline void gumetry_barycenter(
	double output[static 2],
	const double a[static 2],
	const double b[static 2],
	const double c[static 2],
	double aw, double bw, double cw
)
// 0 < (ar + br + cr) <= 1
{
	output[0] = a[0]*aw + b[0]*bw + c[0]*cw;
	output[1] = a[1]*aw + b[1]*bw + c[1]*cw;
}

static inline void gumetry_triangle_rpoint(
	double output[static 2],
	const double a[static 2],
	const double b[static 2],
	const double c[static 2],
	double sqrt_random1, double random2
)
/*
	0 < random1 <= 1 // (pre-sqrt)
	0 < random2 <= 1

	given the square root of a random (0, 1] value & a random (0, 1] value,
	gives a random point within the triangle.
*/
{
	gumetry_barycenter(output, a, b, c,
		(1 - sqrt_random1),
		(sqrt_random1 * (1 - random2)),
		(sqrt_random1 * random2)
	);
}


#endif
