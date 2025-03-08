#ifndef ORPHANS_beachline
#define ORPHANS_beachline


#include <stdint.h>


struct Dot;


double Orphans_breakpoint_x(double directix, struct Dot a, struct Dot b);
/*
	assumes:
		a != b

		a.y <= directix
		b.y <= directix
		!(a.y == directix && b.y == directix)

	given 2 points and a horizontal line, (focuses and a directix)
	with both points below that line,
	this function identifies the point(s) equidistant to all 3,
	and returns the `x` value of the highest-y solution.

	done by creating a perpendicular line
	directly between the given focuses,
	and finding the collisions between the perpendicular line
	and one of the parabolas (which means both).
*/


#endif
