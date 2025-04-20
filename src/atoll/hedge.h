#ifndef ATOLL_hedge
#define ATOLL_hedge


#include <stdbool.h>


struct atoll_hedge {
	unsigned int vertex[2];
	unsigned int nigh[2];
	unsigned int cell;
};


bool atoll_hedge_join(struct atoll_hedge * /*nonull*/ hedges, unsigned int a, unsigned int b, bool priority);
// "priority" prioritizes one or the other when everything is NADA
// Using different priority in circleEvent() is important to
// maintain a balance between unused previous-ends and unused next-ends.

// ==========

// the `edge` functions operate on both associated half-edges, rather than just one

int atoll_edge_create(
	struct atoll_hedge * /*nonull*/ hedges[static 1],
	unsigned int length[static 1],
	unsigned int allocation[static 1],

	unsigned int vertex_0,
	unsigned int vertex_1,

	unsigned int cell_1,
	unsigned int cell_2
);
/*
Allocates & initializes two half-edges, linked as a single edge.
returns 0 on success
*/

int atoll_edge_replaceVertex(struct atoll_hedge * /*nonull*/ hedges, unsigned int self, unsigned int old_vertex, unsigned int new_vertex);
/*
For both half-edges which make up the edge,
replaces their vertex `old_vertex` with `new_vertex`.

returns 0 if the replacement is successful.
returns nonzero if the `old_vertex` was not found to be replaced.
*/

int atoll_edge_join(struct atoll_hedge * /*nonull*/ hedges, unsigned int a, unsigned int b, bool priority);


#endif
