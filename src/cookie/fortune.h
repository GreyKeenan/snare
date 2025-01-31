#ifndef COOKIE_fortune
#define COOKIE_fortune

struct Cookie_VoronoiRegion;
struct Chalk_Point;

enum Cookie_fortune_error {
	Cookie_fortune_ERROR
	, Cookie_fortune_INPUTS
	, Cookie_fortune_ALLOCATION
	, Cookie_fortune_SITE
	, Cookie_fortune_EDGE
};

int Cookie_fortune(struct Cookie_VoronoiRegion *diagram, const struct Chalk_Point *sites, unsigned short site_count, struct Chalk_Point lower_bounds, struct Chalk_Point upper_bounds);
/*
	Constructs a voronoi diagram using Fortune's algorithm.

	$diagram is where the voronoi diagram is constructed to.
	If the function returns an error, *diagram may already have been altered. However, any region's allocations will have been cleaned up.
	len(diagram) == site_count
	expects regions in diagram[] to be uninitialized
	the resulting diagram[] region indexes will correspond to sites[] point indexes

	$sites is the sites to construct the diagram from.
	len(sites) == site_count
	sites[n] are sorted in by ascending X

	$bounds_vertices define a polygon as the bounds around the diagram.
	TODO expectations?
	len(bounds_vertices) == bounds_vertex_count


	returns 0 on success

*/

#endif
