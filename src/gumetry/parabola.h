#ifndef GUMETRY_parabola
#define GUMETRY_parabola


#include "./point.h"


static inline double gumetry_parabolaV_y(double x, struct gumetry_point f, double d)
/*
	gives the `y` of a *vertical* parabola from the `x`

	`f` is the focus, `d` is the directix

	returns INFINITY when f == d
*/
{
	return ((x - f.x)*(x - f.x)) / (2*(f.y - d))  +  (f.y + d)/2;
}


#endif
