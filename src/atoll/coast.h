#ifndef ATOLL_coast
#define ATOLL_coast


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
	/*heap*/ struct atoll_sand * /*nonull*/ beach;
	unsigned int beach_length;
	unsigned int beach_allocation;
	// whenever you add/remove from beachline,
	// must update circles' indices to the beachline elements

	/*heap*/ struct atoll_circle * /*nonull*/ circles;
	unsigned int circles_length;
	unsigned int circles_allocation;
};


static inline int atoll_coast_init(struct atoll_coast self[static 1], unsigned int site_count)
{
	*self = (struct atoll_coast){0};
	return gu_intlist_fit(&self->beach, NULL, &self->beach_allocation, site_count);
}

void atoll_coast_reset(struct atoll_coast *self);


void atoll_coast_updateCircleIndices(struct atoll_coast self[static 1], unsigned int from, int by);

static inline double atoll_circle_eventY(struct atoll_circle self)
{ return self.center.y + radius; }


#endif
