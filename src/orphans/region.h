#ifndef ORPHANS_Region
#define ORPHANS_Region


#include <stdlib.h>


struct Dot;

struct Orphans_Region {
	struct Dot *vertices;
	unsigned int vertices_length;
	unsigned int vertices_allocation;

	unsigned short *neighbors;
	unsigned int neighbors_length;
	unsigned int neighbors_allocation;
};


static inline void Orphans_Region_reset(struct Orphans_Region *self)
{
	if (self == NULL) {
		return;
	}

	if (self->vertices != NULL) {
		free(self->vertices);
	}
	if (self->neighbors != NULL) {
		free(self->neighbors);
	}
}


#endif
