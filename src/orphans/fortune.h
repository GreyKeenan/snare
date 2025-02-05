#ifndef ORPHANS_fortune
#define ORPHANS_fortune


struct Orphans_Region;
struct Dot;
struct gu_echo;


/*heap*/ struct gu_echo *Orphans_fortune(
	struct Orphans_Region * restrict /*nonull*/ diagram,
	const struct Dot * restrict /*nonull*/ sites,
	unsigned int site_count,
	struct Dot lower_bound, struct Dot upper_bound
);
/*
	assumes:
		lower_bound < sites[n] < upper_bound
		site_count > 1
		sites is sorted by ascending X


	Creates a Voronoi Diagram using (scuffed) Fortune's Algorithm.


	$diagram is a $site_count length array.
	Created regions will overwrite this memory.
	*diagram may be modified if the function exits with an error,
	but memory allocated within the function will be cleaned up.
	It is the caller's responsibility to free Orphan_Region allocations
	if the functions exits without an error.

	$sites is a $site_count length array
	which provides the sites to construct the diagram.

	$lower_bound and $upper_bound define the bounding box of the diagram.
	All sites are assumed to be within this boundary.


	returns NULL on success or an allocated gu_echo ptr on failure
*/


#endif
