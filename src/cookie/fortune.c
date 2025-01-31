#include "./fortune.h"

#include "./voronoi.h"
#include "./sand.h"
#include "./siteEvent.h"
#include "./edgeEvent.h"

#include "chalk/point.h"

#include "gunc/list.h"

#include <stddef.h>

int Cookie_fortune(struct Cookie_VoronoiRegion *diagram, const struct Chalk_Point *sites, unsigned short site_count, struct Chalk_Point lower_bounds, struct Chalk_Point upper_bounds)
{
	if (
		diagram == NULL || sites == NULL
			|| site_count < 2
	) {
		return Cookie_fortune_INPUTS;
	}

	int e = 0;

	unsigned short created_regions = 0;


	// make queue with sites
	// loop through queue
		// site events
			// ...
		// edge events
			// ...
	// cleanup


	unsigned int beachline_length = 0;
	unsigned int beachline_allocation = site_count * 2;
	struct Cookie_Sand *beachline = malloc(sizeof(*beachline) * beachline_allocation);


	unsigned int edgeQ_length = 0;
	unsigned int edgeQ_allocation = site_count;
	struct Chalk_Point *edgeQ = malloc(sizeof(*edgeQ) * edgeQ_allocation);
	if (edgeQ == NULL) {
		e = Cookie_fortune_ALLOCATION;
		goto fin;
	}

	unsigned int nextSite = 0;
	struct Chalk_Point nextEdge = {0};

	while (1) {

		if (edgeQ_length == 0 && nextSite >= site_count) {
			break;
		}

		if (nextSite >= site_count) {
		} else if (edgeQ_length == 0 || sites[nextSite].x < edgeQ[edgeQ_length - 1].x) {

			e = Cookie_siteEvent(
				sites[nextSite],
				&edgeQ, &edgeQ_length, &edgeQ_allocation,
				&beachline, &beachline_length, &beachline_allocation
			);
			if (e) {
				e = Cookie_fortune_SITE;
				goto fin_clean;
			}
			
			nextSite++;
			continue;
		}

		Gunc_pop(&edgeQ, &edgeQ_length, &nextEdge);
		e = Cookie_edgeEvent(
			nextEdge,
			&edgeQ, &edgeQ_length, &edgeQ_allocation,
			&beachline, &beachline_length, &beachline_allocation
		);
		if (e) {
			e = Cookie_fortune_EDGE;
			goto fin_clean;
		}
	}






	goto fin;


	fin_clean:

	for (unsigned short i = 0; i < created_regions; ++i) {
		Cookie_VoronoiRegion_reset(diagram + i);
	}


	fin:

	if (edgeQ != NULL) {
		free(edgeQ);
	}
	if (beachline != NULL) {
		free(beachline);
	}


	return e;
}
