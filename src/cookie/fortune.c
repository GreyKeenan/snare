#include <stdio.h>

#include "./fortune.h"

#include "./voronoi.h"

#include "chalk/point.h"
#include "chalk/compare_point.h"

#include "gunc/list.h"

#include <stddef.h>
#include <limits.h>
#include <stdbool.h>


static inline int Cookie_fortune_siteEvent(struct Chalk_Point eventPoint);
static inline int Cookie_fortune_edgeEvent(struct Chalk_Point eventPoint);


int Cookie_fortune(struct Cookie_VoronoiRegion *diagram, const struct Chalk_Point *sites, unsigned short site_count, const struct Chalk_Point *bounds_vertices, unsigned int bounds_vertex_count)
{
	if (
		diagram == NULL || sites == NULL
			|| site_count < 2
		|| bounds_vertices == NULL
			|| bounds_vertex_count < 3
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
		} else if (edgeQ_length == 0 || sites[nextSite].y > edgeQ[edgeQ_length - 1].y) {

			e = Cookie_fortune_siteEvent(sites[nextSite]);
			if (e) {
				e = Cookie_fortune_SITE;
				goto fin_clean;
			}
			
			nextSite++;
			continue;
		}

		Gunc_pop(&edgeQ, &edgeQ_length, &nextEdge);
		e = Cookie_fortune_edgeEvent(nextEdge);
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


	return e;
}

static inline int Cookie_fortune_siteEvent(struct Chalk_Point eventPoint)
{
	return 0;
}
static inline int Cookie_fortune_edgeEvent(struct Chalk_Point eventPoint)
{
	return 0;
}
