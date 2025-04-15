#include "./hedge.h"

#include "./nada.h"

#include "gu/intlist.h"

#include <stdlib.h>


bool atoll_hedge_join(struct atoll_hedge * /*nonull*/ hedges, unsigned int a, unsigned int b, bool priority)
{
	if (hedges[a].nigh[priority] == atoll_NADA && hedges[b].nigh[1^priority] == atoll_NADA) {
		hedges[a].nigh[priority] = b;
		hedges[b].nigh[1^priority] = a;
		return 0;
	}
	if (hedges[a].nigh[1^priority] == atoll_NADA && hedges[b].nigh[priority] == atoll_NADA) {
		hedges[a].nigh[1^priority] = b;
		hedges[b].nigh[priority] = a;
		return 0;
	}
	return 1;
}

// ==========

int atoll_edge_create(
	struct atoll_hedge * /*nonull*/ hedges[static 1],
	unsigned int length[static 1],
	unsigned int allocation[static 1],

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

	(*hedges)[*length] = (struct atoll_hedge) {
		.cell = cell_1,
		.vertex[0] = vertex_0,
		.vertex[1] = vertex_1,
		.nigh[0] = atoll_NADA,
		.nigh[1] = atoll_NADA
	};
	*length += 1;
	(*hedges)[*length] = (struct atoll_hedge) {
		.cell = cell_2,
		.vertex[0] = vertex_0,
		.vertex[1] = vertex_1,
		.nigh[0] = atoll_NADA,
		.nigh[1] = atoll_NADA
	};
	*length += 1;

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



int atoll_edge_join(struct atoll_hedge * /*nonull*/ hedges, unsigned int a, unsigned int b, bool priority)
{
	int hedges_joined = 0;

	int e = 0;

	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < 2; ++i) {
			if (hedges[a^j].cell != hedges[b^i].cell) continue;
			e = atoll_hedge_join(hedges, a^j, b^i, priority);
			if (e) continue;
			hedges_joined += 1;
		}
	}

	return hedges_joined;
}
