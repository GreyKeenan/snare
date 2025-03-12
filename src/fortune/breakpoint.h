#ifndef FORTUNE_breakpoint
#define FORTUNE_breakpoint
// ==========

#include "./point.h"

// ==========

double Fortune_breakpoint_x(const double directix, const struct Fortune_point a, const struct Fortune_point b);
/*
	assumes:
		a != b

		a.y <= directix
		b.y <= directix
		!(a.y == directix && b.y == directix)
			As long as the beachline is built properly,
			this can only occur when all sites so far, including the site event, have the same y.
			I'll want to handle that case separately, because there are *no* breakpoints to calc.

	given 2 points and a horizontal line, (focuses and a directix)
	with both points below that line,
	this function identifies the point(s) equidistant to all 3.
	If a is higher-y than b,
	it returns the higher-x solution
	If b is higher-y, it returns the lower-x.
	(If equal, there is only 1 solution.)

	In the general case, done by creating a perpendicular line
	directly between the given focuses,
	and finding the collisions between the perpendicular line
	and one of the parabolas.
*/

// ==========
#endif
