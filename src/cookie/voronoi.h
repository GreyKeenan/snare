#ifndef COOKIE_Voronoi
#define COOKIE_Voronoi

#include <stdlib.h>

struct Chalk_Point;

struct Cookie_VoronoiRegion {
	struct Chalk_Point *vertices;
	unsigned int vertices_length;
	unsigned int vertices_allocation;

	unsigned short *neighbors;
	unsigned int neighbors_length;
	unsigned int neighbors_allocation;
};


static inline void Cookie_VoronoiRegion_reset(struct Cookie_VoronoiRegion *self)
{
	if (self->vertices != NULL) {
		free(self->vertices);
	}
	if (self->neighbors != NULL) {
		free(self->neighbors);
	}

	*self = (struct Cookie_VoronoiRegion) {0};
}

#endif
