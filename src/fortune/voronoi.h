#ifndef FORTUNE_voronoi
#define FORTUNE_voronoi


#include "gu/gu.h"

#include <limits.h>

#define Fortune_INDEX_NULL UINT_MAX

struct Fortune_point;
struct Fortune_edge;
struct Fortune_half;

struct Fortune_voronoi {
	/*heap*/ struct Fortune_point *sites;
	unsigned int site_count;

	unsigned int border; //index to half

	/*heap*/ unsigned int *cells; //indices to halves
	//cell[x] corresponds to site[x]
	//is site_count long

	/*heap*/ struct Dot *vertices;
	unsigned int vertices_length;
	unsigned int vertices_allocation;

	/*heap*/ struct Fortune_edge *edges; // contain indices of vertices
	unsigned int edges_length;
	unsigned int edges_allocation;

	/*heap*/ struct Fortune_half *halves; // have indices of cells/sites, edges, and linked-list-indices to each other
	unsigned int halves_length;
	unsigned int halves_allocation;
	// half[x] and half[x + 1] are 2 sides of the same edge, (starting from 0)
};

int Fortune_voronoi_init(struct Fortune_voronoi self[static 1], struct Fortune_point * /*nonull*/ sites, unsigned int site_count, _Bool dontCopySites);
/*
	assumes:
		site_count > 1
		if dontCopySites == true, sites is a heap-pointer
		`sites` should be a *set*. No sites are identical.

	if dontCopySites is true, `self.sites == sites`.
	`Fortune_voronoi_free()` will assume it is a heap-pointer.
	Otherwise, `self.sites` is an allocated copy of `sites`.

	returns 0 on success
	On error, will call Fortune_voronoi_free() to release any allocated memory, EXCEPT
	`sites` if `dontCopySites == true`
*/

static inline void Fortune_voronoi_free(struct Fortune_voronoi *self)
{
	if (self == NULL) {
		return;
	}

	gu_free(self->sites);
	gu_free(self->cells);
	gu_free(self->vertices);
	gu_free(self->edges);
	gu_free(self->halves);

	*self = (struct Fortune_voronoi){0};
}

#endif
