#include "./fortune.h"

#include "./region.h"
#include "./siteEvent.h"
#include "./edgeEvent.h"
#include "./sand.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/list.h"


/*heap*/ struct gu_echo *Orphans_fortune(
	unsigned int site_count,
	const struct Dot * restrict /*nonull*/ sites,

	struct Dot lower_bound, struct Dot upper_bound,

	struct Orphans_Region * restrict /*nonull*/ regions,
	struct Dot * /*heap*/ edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
)
{

	//TODO
	(void)lower_bound;
	(void)upper_bound;

	// ==========

	if (regions == NULL || sites == NULL || site_count < 2) {
		return gu_echo_new(0, "Bad inputs: regions:%p sites:%p site_count:%u", (void*)regions, (void*)sites, site_count);
	}

	// ==========

	// initialize empty beachline
	// initialize queue
	// loop through queue
		// site events
			// ...
		// edge events
			// ...
	// cleanup

	// ==========

	/*heap*/ struct gu_echo *e = NULL;
	unsigned int created_regions = 0;

	/*heap*/ struct Orphans_sand *beachline = NULL;
	/*heap*/ struct Dot *edgeQ = NULL;
	
	// ==========

	unsigned int beachline_length = 0;
	unsigned int beachline_allocation = site_count;
	if (beachline_allocation > SIZE_MAX / sizeof(*beachline)) {
		return gu_echo_new(0, "Beachline allocation failed. Max size:%zu. Attempted:(%zu * %u)", SIZE_MAX, sizeof(*beachline), beachline_allocation);
	}
	beachline = malloc(sizeof(*beachline) * beachline_allocation);
	if (beachline == NULL) {
		return gu_echo_new(0, "Beachline allocation failed. Attempted size:%zu * allocation:%u", sizeof(*beachline), beachline_allocation);
	}
	/*
		The beachline is an array of unsigned ints.
		Even (and 0) elements are site-indexes.
		Odd elements are $edges indexes.
		before the first element and after the last are implied null $edges indexes.

		this does mean I'll need a specific searching function though :/
	*/

	unsigned int edgeQ_length = 0;
	unsigned int edgeQ_allocation = site_count;
	if (edgeQ_allocation > SIZE_MAX / sizeof(*edgeQ)) {
		e = gu_echo_new(0, "edgeQ allocation failed. Max size:%zu. Attempted:(%zu * %u)", SIZE_MAX, sizeof(*edgeQ), edgeQ_allocation);
		goto fin;
	}
	edgeQ = malloc(sizeof(*edgeQ) * edgeQ_allocation);
	if (edgeQ == NULL) {
		e = gu_echo_new(0, "edgeQ allocation failed. Attempted size:%zu * allocation:%u", sizeof(*edgeQ), edgeQ_allocation);
		goto fin;
	}

	// ==========


	unsigned int next_site = 0;
	struct Dot next_edge = {0};

	while (1) {
		if (next_site >= site_count && edgeQ_length == 0) {
			break;
		}

		if (next_site >= site_count) {
		} else if (edgeQ_length == 0 || sites[next_site].y < edgeQ[edgeQ_length - 1].y) {
			e = Orphans_siteEvent(
				sites, next_site,
				&edgeQ, &edgeQ_length, &edgeQ_allocation,
				&beachline, &beachline_length, &beachline_allocation,
				edges, edges_length, edges_allocation
			);
			if (e != NULL) {
				e = gu_echo_wrap(e, 0, "Orphans_siteEvent() failed.");
				goto fin_clean;
			}

			next_site++;
			continue;
		}

		gu_list_pop(&edgeQ, &edgeQ_length, &next_edge);
		e = Orphans_edgeEvent(
			next_edge,
			&edgeQ, &edgeQ_length, &edgeQ_allocation,
			&beachline, &beachline_length, &beachline_allocation,
			edges, edges_length, edges_allocation
		);
		if (e != NULL) {
			e = gu_echo_wrap(e, 0, "Orphans_edgeEvent() failed.");
			goto fin_clean;
		}
	}


	// ==========

	goto fin;

	fin_clean:

	for (unsigned int i = 0; i < created_regions; ++i) {
		Orphans_Region_reset(regions + i);
	}

	if (*edges != NULL) {
		free(*edges);
	}
	*edges_length = 0;
	*edges_allocation = 0;


	fin:

	gu_free(beachline);
	gu_free(edgeQ);

	return e;
}
