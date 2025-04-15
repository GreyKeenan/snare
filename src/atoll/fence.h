#ifndef ATOLL_fence
#define ATOLL_fence


struct atoll_diagram;
struct gumetry_point;
struct gu_echo;


/*heap*/ struct gu_echo *atoll_fence(
	struct atoll_diagram * /*nonull*/ diagram,

	struct gumetry_point * /*nonull*/ polygon,
	unsigned int vertex_count
);
/*
vertex_count > 2

`polygon` is a sequence of `vertex_count` points defining a *convex* polygon.
`diagram` has been generated with atoll_treasure()

returns NULL on success, or an echo describing the error

The border of the diagram can be found as the half-edges starting at hedges[cells[site_count]].
The border is equivalent to the given bounding polygon, although it will be split into more vertices.

*/


#endif
