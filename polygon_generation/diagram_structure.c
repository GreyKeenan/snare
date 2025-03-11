
struct point {
	int x, y;
};

struct sand { //element on the beachline
	size_t site;
	size_t vertex;
};

struct halfEdge {
	size_t site; //associated site/region index

	size_t neighbor[2]; //previous/next
	size_t vertex[2];
};
static inline size_t halfEdge_getPartner(size_t partner_of)
{
	return partner_of + (partner_of & 1)? -1 : 1;
}


size_t site_count;
struct point sites[site_count];

struct sand beachline[];

struct point vertices[];
struct halfEdge half_edges[];
// A half edge is always adjacent to its corresponding half

size_t regions[site_count]; //halfEdge indices
// regions[x] is the index of a half-edge for site[x]


// ===========================================================================

/*
WAIT:
Eventually I want to merge adjacent voronoi diagrams with each other.
So, whatever edge system I use needs to be flexible enough
that new edges and neighbors can be added,
and that regions' data can reference external diagrams.

So, it seems like my options are:

* make regions more self-contained,
  so they can be modified to add stuff without
  messing each other up.
* make half-edges more complex,
  since they're the only part that needs to
  have references to external diagram components?

I prefer the latter I think?

*/

struct cell {
	struct point site;
	size_t edge;
};

struct voronoi {
	/*heap*/ struct cell *cells;
	/*heap*/ struct point *vertices;
	/*heap*/ struct halfedge *halves;

	size_t bounds; //halves index

	size_t cell_count;
	size_t vertices_length, vertices_allocation;
	size_t halves_length, halves_allocation;
};

struct error *voronoi_fortune(
	struct voronoi *diagram,
	const struct point *sites,
	size_t site_count,
	const struct point *bounds,
	size_t bound_count
);

struct error *voronoi_join(struct voronoi *destination, const struct voronoi *a, const struct voronoi *b);
