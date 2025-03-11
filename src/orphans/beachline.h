#ifndef ORPHANS_beachline
#define ORPHANS_beachline


#include <stdint.h>


struct Orphans_sand;
struct Dot;
struct gu_echo;


double Orphans_breakpoint_x(double directix, struct Dot a, struct Dot b);
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

int Orphans_beachline_compare(void * /*nonull*/ context[static 4], const struct Dot * /*nonull*/ key, const struct Orphans_sand * /*nonull*/ b);
/*
	Conforms to `gu_comparer_withcontext` function-typedef.
	Meant to be used with _beachline_searchbetween to pass the context in.

	context = {
		int *error,
		const struct Dot *sites,
		const struct Orphans_sand *beachline,
		const unsigned int *beachline_length
	}

	context is used to access the sites by their Orphans_sand-stored indices,
	and to check the previous/next elements from 'b'.

	returns -1, 0, or 1 for sorting.
	-1 means site[key].x < b's left breakpoint.
	1 means site[key].x > b's right breakpoint.
	0 means site[key].x is between the two or equal.
		(it handles the first/last element case as well)

	If an error occurs, 0 is returned immediately
	so the sorting-function-calling function can know where the error occurred.
	*error will be set to -1 or 1,
	indicating whether the error occured when calculating the left (-1) or right (+1) breakpoint.
*/

/*heap*/ struct gu_echo *Orphans_beachline_searchbetween(unsigned int * /*nonull*/ position, struct Dot * /*nonull*/ sites, const struct Dot * /*nonull*/ key, struct Orphans_sand * /*nonull*/ beachline, unsigned int length);
/*
	wrapper for searching the beachline

	The output position will not be >= length.
	This is a fortunate side-effect of _beachline_compare,
	which handles the last element of the beachline specifically.
*/


#endif
