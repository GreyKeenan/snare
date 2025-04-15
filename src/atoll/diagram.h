#ifndef ATOLL_diagram
#define ATOLL_diagram


#include "./hedge.h"
#include "./nada.h"

#include "gumetry/point.h"

#include <stdbool.h>


struct atoll_diagram {
	/*heap*/ struct gumetry_point * /*nonull*/ sites;
	unsigned int site_count;

	/*heap*/ unsigned int * /*nonull*/ cells;
	// cells[n] corresponds to sites[n]
	// BUT length is site_count + 1
	// cells[site_count] is the border /or/ outside-cell

	/*heap*/ struct gumetry_point * /*nonull*/ vertices;
	unsigned int vertices_length;
	unsigned int vertices_allocation;

	/*heap*/ struct atoll_hedge * /*nonull*/ hedges;
	unsigned int hedges_length;
	unsigned int hedges_allocation;
	// the other-half of hedge[i] is hedge[i :xor: 1]
};


#define atoll_COPYSITES 0
#define atoll_DONTCOPYSITES 1
int atoll_diagram_init(
	struct atoll_diagram self[static 1],
	struct gumetry_point * /*nonull*/ sites,
	unsigned int site_count,
	bool dontCopySites
);
/*
	wants site_count > 2

	returns 0 on success
	On failure, frees internally-allocated memory.
	On failure, frees self->sites *only if* it was internally allocated,
	*not* if dontCopySites == true.
	However, on success, later calls to eame_diagram_reset()
	*will* free that location.
*/

void atoll_diagram_reset(struct atoll_diagram *self);

static inline int atoll_diagram_newedge(struct atoll_diagram self[static 1], unsigned int cell_1, unsigned int cell_2)
{
	return atoll_edge_create(
		&self->hedges,
		&self->hedges_length,
		&self->hedges_allocation,

		self->cells,

		atoll_NADA, atoll_NADA,
		cell_1, cell_2
	);
}


#endif
