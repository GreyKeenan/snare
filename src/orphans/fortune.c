#include "./fortune.h"

#include "./region.h"
#include "./sand.h"
#include "./siteEvent.h"
#include "./edgeEvent.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/list.h"


/*heap*/ struct gu_echo *Orphans_fortune(
	struct Orphans_Region * restrict /*nonull*/ diagram,
	const struct Dot * restrict /*nonull*/ sites,
	unsigned int site_count,
	struct Dot lower_bound, struct Dot upper_bound
)
{
	if (diagram == NULL || sites == NULL || site_count < 2) {
		return gu_echo_new(0, "Bad inputs: diagram:%p sites:%p site_count:%u", (void*)diagram, (void*)sites, site_count);
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

	struct gu_echo *e = NULL;
	unsigned int created_regions = 0;
	struct Orphans_Sand *beachline = NULL;
	struct Dot *edgeQ = NULL;

	// ==========

	unsigned int beachline_length = 0;
	unsigned int beachline_allocation = site_count * 2;
	//TODO check if can multiply:
	beachline = malloc(sizeof(*beachline) * beachline_allocation);
	if (beachline == NULL) {
		return gu_echo_new(0, "Beachline allocation failed. Attempted size:%zu * allocation:%u", sizeof(*beachline), beachline_allocation);
	}

	unsigned int edgeQ_length = 0;
	unsigned int edgeQ_allocation = site_count;
	//TODO check if can multiply:
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
		} else if (edgeQ_length == 0 || sites[next_site].x < edgeQ[edgeQ_length - 1].x) {
			e = Orphans_siteEvent(
				sites[next_site],
				&edgeQ, &edgeQ_length, &edgeQ_allocation,
				&beachline, &beachline_length, &beachline_allocation
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
			&beachline, &beachline_length, &beachline_allocation
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
		Orphans_Region_reset(diagram + i);
	}

	fin:

	gu_free(beachline);
	gu_free(edgeQ);

	return e;
}
