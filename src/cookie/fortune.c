#include "./fortune.h"

#include "./voronoi.h"

#include "chalk/point.h"

#include "gunc/list.h"

#include <stddef.h>

struct Cookie_Sand {
	unsigned short site_index;
	struct Chalk_Point *destinations[2];
	// one per half-edge
};


static inline int Cookie_siteEvent(
	struct Chalk_Point eventPoint,

	struct Chalk_Point **edgeQ,
	unsigned int *edgeQ_length,
	unsigned int *edgeQ_allocation,

	struct Cookie_Sand **beachline,
	unsigned int *beachline_length,
	unsigned int *beachline_allocation

);
static inline int Cookie_edgeEvent(
	struct Chalk_Point eventPoint,

	struct Chalk_Point **edgeQ,
	unsigned int *edgeQ_length,
	unsigned int *edgeQ_allocation,

	struct Cookie_Sand **beachline,
	unsigned int *beachline_length,
	unsigned int *beachline_allocation

);

static inline _Bool Cookie_Sand_isNull(const struct Cookie_Sand *restrict self)
{
	return self->destinations[0] == NULL;
}

int Cookie_addEdgeEvent(struct Chalk_Point point, struct Chalk_Point **list, unsigned int *length, unsigned int *allocation);


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

static inline int Cookie_siteEvent(
	struct Chalk_Point eventPoint,

	struct Chalk_Point **edgeQ,
	unsigned int *edgeQ_length,
	unsigned int *edgeQ_allocation,

	struct Cookie_Sand **beachline,
	unsigned int *beachline_length,
	unsigned int *beachline_allocation

)
{

	// identify position in beachline to insert
	// insert
	// add vertices & destinations
	// check for circle events

	return 1;
}
static inline int Cookie_edgeEvent(
	struct Chalk_Point eventPoint,

	struct Chalk_Point **edgeQ,
	unsigned int *edgeQ_length,
	unsigned int *edgeQ_allocation,

	struct Cookie_Sand **beachline,
	unsigned int *beachline_length,
	unsigned int *beachline_allocation

)
{
	return 1;
}

int Cookie_addEdgeEvent(struct Chalk_Point point, struct Chalk_Point **list, unsigned int *length, unsigned int *allocation)
{

	int e = Gunc_push(list, length, allocation, &point);
	if (e) {
		return 2;
	}

	for (int i = *length - 1; i > 0; --i) {
		if ((*list)[i].x <= (*list)[i - 1].x) {
			break;
		}
		(*list)[i] = (*list)[i - 1];
		(*list)[i - 1] = point;
	}

	return 0;
}
