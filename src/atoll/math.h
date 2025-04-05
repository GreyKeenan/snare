#ifndef ATOLL_math
#define ATOLL_math


#include "./point.h"


double atoll_parabola_y(
	double x,
	double h, // = vertex.x = focus.x
	double f, // = focus.y
	double d  // = directixY
);
/*
	for a *vertical* parabola
	returns infinity when f == d
*/

struct atoll_podouble atoll_circumcenter(
	struct atoll_point p0,
	struct atoll_point p1,
	struct atoll_point p2
);
/*
	returns (NAN, NAN) is no circumcenter exists
*/


#endif
