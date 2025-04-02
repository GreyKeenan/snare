#ifndef ATOLL_diagram
#define ATOLL_diagram


#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


#define atoll_INDULL UINT_MAX
	// index null


struct atoll_point { uint16_t x, y; };

struct atoll_hedge {
	unsigned int previous;
	unsigned int next;

	unsigned int cell;

	unsigned int head;
	unsigned int tail;
};

struct atoll_diagram {
	/*heap*/ struct atoll_point * /*nonull*/ sites;
	unsigned int site_count;

	/*heap*/ unsigned int * /*nonull*/ cells;
	// cells[n] corresponds to sites[n]
	// BUT length is site_count + 1
	// cells[site_count] is the border /or/ outside-cell

	/*heap*/ struct atoll_point * /*nonull*/ vertices;
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
	struct atoll_point * /*nonull*/ sites,
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

int atoll_diagram_newedge(struct atoll_diagram self[static 1], unsigned int cell_1, unsigned int cell_2);
/*
	assumes:
		self->hedges_allocation > 1
			So gu_intlist_grow() will fit 2 more hedges.
			This will be true if diagram was initialized with _diagram_init().
	
	returns 0 on success
*/


#endif
