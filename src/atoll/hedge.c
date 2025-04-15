#include "./hedge.h"

#include "./nada.h"

#include "gu/intlist.h"

#include <stdlib.h>


void atoll_hedge_append(struct atoll_hedge * /*nonull*/ hedges, unsigned int first, unsigned int new_hedge)
{
	hedges[new_hedge].nigh[0] = hedges[first].nigh[0];
	hedges[new_hedge].nigh[1] = first;

	hedges[hedges[first].nigh[0]].nigh[1] = new_hedge;
	hedges[first].nigh[0] = new_hedge;
}

// ==========

static inline void atoll_hedge_create(
	struct atoll_hedge * /*nonull*/ hedges,
	unsigned int length[static 1],

	unsigned int *cells,

	unsigned int vertex_0,
	unsigned int vertex_1,
	unsigned int cell
)
{
	hedges[*length] = (struct atoll_hedge) {
		.cell = cell,
		.vertex[0] = vertex_0,
		.vertex[1] = vertex_1,
		.nigh[0] = *length,
		.nigh[1] = *length
	};

	if (cells == NULL || cell == atoll_NADA);
	else if (cells[cell] == atoll_NADA) cells[cell] = *length;
	else atoll_hedge_append(hedges, cells[cell], *length);

	*length += 1;
}

int atoll_edge_create(
	struct atoll_hedge * /*nonull*/ hedges[static 1],
	unsigned int length[static 1],
	unsigned int allocation[static 1],

	unsigned int *cells,

	unsigned int vertex_0,
	unsigned int vertex_1,

	unsigned int cell_1,
	unsigned int cell_2
)
{
	if (*length > UINT_MAX - 2) return 200;
	int e = 0;
	if (*length + 2 > *allocation) {
		if (*length < 2) e = gu_intlist_fit(hedges, NULL, allocation, (*length) + 2);
		else e = gu_intlist_grow(hedges, allocation);
		if (e) return e;
	}

	atoll_hedge_create(*hedges, length, cells, vertex_0, vertex_1, cell_1);
	atoll_hedge_create(*hedges, length, cells, vertex_0, vertex_1, cell_2);

	return 0;
}



int atoll_edge_replaceVertex(struct atoll_hedge * /*nonull*/ hedges, unsigned int self, unsigned int old_vertex, unsigned int new_vertex)
{
	if (hedges[self].vertex[0] == old_vertex) hedges[self].vertex[0] = new_vertex;
	else if (hedges[self].vertex[1] == old_vertex) hedges[self].vertex[1] = new_vertex;
	else return 1;

	if (hedges[self^1].vertex[0] == old_vertex) hedges[self^1].vertex[0] = new_vertex;
	else if (hedges[self^1].vertex[1] == old_vertex) hedges[self^1].vertex[1] = new_vertex;
	else return 2;

	return 0;
}
