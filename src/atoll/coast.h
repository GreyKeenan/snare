#ifndef ATOLL_coast
#define ATOLL_coast


#include "./point.h"

#include "gu/intlist.h"


struct atoll_sand {
	unsigned int focus; // site index
	unsigned int edge;
	// index of a half-edge of the edge being traced by
	// the breakpoint *before* this focus
};

struct atoll_circle {
	struct atoll_point center;
	double radius;

	unsigned int closing_arc; // coast.beach index
};

struct atoll_coast {

	/*heap*/ unsigned int * /*nonull*/ foci;
	unsigned int foci_length;
	unsigned int foci_allocation;

	/*heap*/ unsigned int * /*nonull*/ breaks;
	unsigned int breaks_length;                 // should always be foci_length - 1
	unsigned int breaks_allocation;

	/*heap*/ struct atoll_circle * /*nonull*/ circles;
	unsigned int circles_length;
	unsigned int circles_allocation;
	// whenever you add/remove from beachline,
	// must update circles' indices to the beachline elements
};

int atoll_coast_init(struct atoll_coast self[static 1], unsigned int site_count);
void atoll_coast_reset(struct atoll_coast *self);


void atoll_coast_updateCircleIndices(struct atoll_coast self[static 1], unsigned int from, int by);


int atoll_coast_arcAtX(const unsigned int * /*nonull*/ foci, unsigned int foci_length, const struct atoll_point * /*nonull*/ sites, double directix, int16_t x, unsigned int arcidx[static 1]);
/*
Assumes breakpoints exist.
Binary searches the beachline, based on breakpoints,
the arc which a new site at `x` would bisect.
*/


#endif
