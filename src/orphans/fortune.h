#ifndef ORPHANS_fortune
#define ORPHANS_fortune


#include "dot/sort.h"

struct Orphans_half;
struct Orphans_edge;
struct Dot;
struct gu_echo;

#define Orphans_sortforme Dot_sort_y_ascending

/*heap*/ struct gu_echo *Orphans_fortune(
	const struct Dot * /*nonull*/ sites,
	unsigned int site_count,

	const struct Dot * bounds,
	unsigned int bounds_length,

	unsigned int * /*nonull*/ cells,

	/*heap*/ struct Orphans_half *halves[static 1],
	unsigned int halves_length[static 1],
	unsigned int halves_allocation[static 1],

	/*heap*/ struct Orphans_edge *edges[static 1],
	unsigned int edges_length[static 1],
	unsigned int edges_allocation[static 1],

	/*heap*/ struct Dot *vertices[static 1],
	unsigned int vertices_length[static 1],
	unsigned int vertices_allocation[static 1]
);
/*
	assumes:
		`sites` is sorted by ascending y

		site_count > 2
		bounds_length > 2

		`halves`-list and `vertices`-list are in a valid state, whether initialized or not

	`sites` is a `site_count`-length array.

	`bounds` is a `bounds_length`-length array
	defining a polygon that all sites are assumed to fall within.
	It will be used to clip unterminated voronoi edges.
	The final bound is assumed to be one end of a line with the first bound.

	If `bounds == NULL` or `bounds_length == 0`,
	unterminated edges will not be clipped.

	`cells` is a `site_count`-length array, to be overwritten.
	It will contain indices for `(*halves)[]`.
	`cells[x]` will be the index for some half-edge of `site[x]`.

	`halves` and its associated values are a list.
	`vertices` and its associated values are a list.

	For `halves`,  `edges`, and `vertices`,
	it is assumed that the input values are already in a valid list configuration,
	whether initialized or not.
	If already initialized,
	the existing elements will not be modified,
	though their absolute addresses may change from reallocation.

	If the function returns with an error,
	`halves`, `vertices`, and `cells` may have still been modified.

	returns NULL on success or a gu_echo on failure.
*/

#endif
