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


#endif
