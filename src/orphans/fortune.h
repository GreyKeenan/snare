#ifndef ORPHANS_fortune
#define ORPHANS_fortune


struct Orphans_Region;
struct Dot;
struct gu_echo;


/*heap*/ struct gu_echo *Orphans_fortune(
	unsigned int site_count,
	const struct Dot * restrict /*nonull*/ sites,

	struct Dot lower_bound, struct Dot upper_bound,

	struct Orphans_Region * restrict /*nonull*/ regions,
	struct Dot * restrict /*heap*/ edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
);
/*
	assumes:
		site_count > 1
		sites is sorted by ascending Y

		lower_bound < sites[n] < upper_bound

		*edges = NULL
		*edges_length = 0
		*edges_allocation = 0


	Creates a Voronoi Diagram using Fortune's Algorithm.


	$sites is a $site_count length array
	which provides the sites to construct the diagram.

	$lower_bound and $upper_bound define the bounding box of the diagram.
	All sites are assumed to be within this boundary.

	$regions is a $site_count length array.
	Created regions will overwrite this memory.
	*regions may be modified if the function exits with an error,
	but their allocated memory will be freed in that case.
	It is the caller's responsibility to free Orphan_Region allocations
	if the functions exits without an error, though.

	$edges, $edges_length, and $edges_allocation are a list.
	It should not be initialized before calling.
	*($edges) will be freed if the function returns an error,
	and $edges_length & $edges_allocation will be reset to 0.
	It is the caller's responsibility to free $edges if
	the function exits without an error.


	returns NULL on success or an allocated gu_echo ptr on failure
*/


#endif
