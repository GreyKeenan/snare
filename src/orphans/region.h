#ifndef ORPHANS_Region
#define ORPHANS_Region


#include <stdlib.h>


struct Dot;

struct Orphans_Region {
	unsigned int * /*heap*/ edges;
	unsigned int edges_length;
	unsigned int edges_allocation;

	unsigned short * /*heap*/ neighbors;
	unsigned int neighbors_length;
	unsigned int neighbors_allocation;
};


static inline void Orphans_Region_reset(struct Orphans_Region *self)
{
	if (self == NULL) {
		return;
	}

	if (self->edges != NULL) {
		free(self->edges);
	}
	if (self->neighbors != NULL) {
		free(self->neighbors);
	}
}


#endif
