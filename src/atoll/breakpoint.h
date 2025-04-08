#ifndef ATOLL_breakpoint
#define ATOLL_breakpoint

#include "./point.h"


struct atoll_podouble atoll_breakpoint(double directix, struct atoll_podouble left, struct atoll_podouble right);
/*
assumes
	left != right
	directix >= left.y
	directix >= right.y
	!( directix == left.y && directix == right.y )
		If the beachline is constructed properly,
		this only occurs when *all sites so far and the current site event* have the same y,
		There are no breakpoints, so it needs to be a separate case anyways.

Given 2 points (foci) and a horizontal line (directix),
finds the intersection of the parabolas they form.
Specifically, the intersection that occurs *between* the two points.
This is the "breakpoint" between two arcs on the beachline in Fortune's Algorithm.

	If left is higher-y than right, that will be the higher-x intersection.
	If right is higher-y than left, that will be the lower-x intersection.
	(When equal, there is only 1 solution.)

In the general case,
the breakpoint is found by finding a perpendicular line directly between the two foci,
and finding where it intersects with one of the foci's parabolas.
*/



#endif
