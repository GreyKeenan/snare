#ifndef ATOLL_coast
#define ATOLL_coast


#include "gumetry/point.h"
#include "./circle.h"

#include "gu/intlist.h"


struct atoll_diagram;

struct gu_echo;


struct atoll_sand {
	unsigned int focus; // site index
	unsigned int edge;
	// index of a half-edge of the edge being traced by
	// the breakpoint *before* this focus
};

struct atoll_coast {

	/*heap*/ unsigned int * /*nonull*/ foci;
	unsigned int foci_length;
	unsigned int foci_allocation;

	/*heap*/ unsigned int * /*nonull*/ breaks;
	unsigned int breaks_length;                 // should always be foci_length - 1
	unsigned int breaks_allocation;

	unsigned int nextSite;

	/*heap*/ struct atoll_circle * /*nonull*/ circles;
	unsigned int circles_length;
	unsigned int circles_allocation;
	// whenever you add/remove from beachline,
	// must update circles' indices to the beachline elements
};

int atoll_coast_init(struct atoll_coast self[static 1], unsigned int site_count);
void atoll_coast_reset(struct atoll_coast *self);


/*heap*/ struct gu_echo *atoll_coast_prime(struct atoll_coast coast[static 1], struct atoll_diagram * /*nonull*/ diagram);
/*
MUST Be called before the fortun's alg event-loop.
Handles the case of adding to beachline when it is empty,
and the case of horizontally-aligned first `n` sites,
where there are no breakpoints yet.
*/

int atoll_coast_arcAtX(const unsigned int * /*nonull*/ foci, unsigned int foci_length, const struct gumetry_point * /*nonull*/ sites, double directix, double x, unsigned int arcidx[static 1]);
/*
Assumes breakpoints exist.
Binary searches the beachline, based on breakpoints,
the arc which a new site at `x` would bisect.
*/

void atoll_coast_updateCircles(struct atoll_circle * /*nonull*/ circles, unsigned int circles_length, unsigned int from, int by);
/*
	adds `by` to `circle.arc` for each circle where `circle.arc` >= from`.
*/

void atoll_coast_removeCirclesWithArc(struct atoll_circle * /*nonull*/ circles[static 1], unsigned int circles_length[static 1], unsigned int arc);


#endif
