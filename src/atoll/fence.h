#ifndef ATOLL_fence
#define ATOLL_fence


struct atoll_diagram;
struct gumetry_point;

struct gu_echo;


/*heap*/ struct gu_echo *atoll_fence(
	struct atoll_diagram *diagram,
	struct gumetry_point *polygon,
	unsigned int vertex_count
);
/*
polygon != NULL, diagram != NULL, vertex_count > 2

`polygon` is a sequence ov `vertex_count` points defining a *convex* polygon.
`diagram` has been generated with atoll_treasure()

returns NULL on success, or an echo describing the error

Terminates the infinite-edges remaining after running atoll_treasure().
As opposed to other bounding-functions,
the resulting diagram is contained entirely within the given polygon.

The border of the diagram can be found as the half-edges starting at hedges[cells[site_count]].
The border is equivalent to the given bounding polygon,
although it almost certainly contains more vertices.

*/


#endif
