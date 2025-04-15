#ifndef ATOLL_hedge
#define ATOLL_hedge


struct atoll_hedge {
	unsigned int vertex[2];
	unsigned int nigh[2];
	unsigned int cell;
};


void atoll_hedge_append(struct atoll_hedge * /*nonull*/ hedges, unsigned int first, unsigned int new_hedge);
/*
Appends the new hedge to the first-hedge's linked list.
*/

// ==========

// the `edge` functions operate on both associated half-edges, rather than just one

int atoll_edge_create(
	struct atoll_hedge * /*nonull*/ hedges[static 1],
	unsigned int length[static 1],
	unsigned int allocation[static 1],

	unsigned int * cells,

	unsigned int vertex_0,
	unsigned int vertex_1,

	unsigned int cell_1,
	unsigned int cell_2
);
/*
Allocates & initializes two half-edges, linked as a single edge.

If `cells` or `cell_0`/`cell_1` respectively are not NULL/NADA,
updates the `cell[cell_#]` with an index to the respective new hedge.
If `cell[cell_#]` is NADA, overwrites it with a new index.
If `cell[cell_#]` is not NADA, appends the new hedge to that cell's hedge's linked list.

returns 0 on success
*/

int atoll_edge_replaceVertex(struct atoll_hedge * /*nonull*/ hedges, unsigned int self, unsigned int old_vertex, unsigned int new_vertex);
/*
For both half-edges which make up the edge,
replaces their vertex `old_vertex` with `new_vertex`.

returns 0 if the replacement is successful.
returns nonzero if the `old_vertex` was not found to be replaced.
*/

void atoll_edge_insertAfter(struct atoll_hedge * /*nonull*/ hedges, unsigned int afterme, unsigned int new_hedge);
/*
*/


#endif
