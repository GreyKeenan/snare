#include "./fortune.h"

#include "./half.h"
#include "./sand.h"

#include "./siteEvent.h"
#include "./circleEvent.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/list.h"


/*heap*/ struct gu_echo *Orphans_fortune(
	const struct Dot * /*nonull*/ sites,
	unsigned int site_count,

	const struct Dot * bounds,
	unsigned int bounds_length,

	unsigned int * /*nonull*/ cells,

	/*heap*/ struct Orphans_half *halves[static 1],
	unsigned int halves_length[static 1],
	unsigned int halves_allocation[static 1],

	/*heap*/ struct Orphans_edge *edges[static 1],
	unsigned int edges_length[static 1],
	unsigned int edges_allocation[static 1],

	/*heap*/ struct Dot *vertices[static 1],
	unsigned int vertices_length[static 1],
	unsigned int vertices_allocation[static 1]
)
{
	(void)bounds;
	(void)bounds_length;

	// ==========

	/*heap*/ struct gu_echo *e = NULL;
	int ie = 0;

	/*heap*/ struct Orphans_sand *beach = NULL;
	unsigned int beach_length = 0;
	unsigned int beach_allocation = 0;

	/*heap*/ struct Dot *circles = NULL;
	unsigned int circles_length = 0;
	unsigned int circles_allocation = 0;

	// ==========

	// initialize the beachline & circle event queue

	ie = gu_list_fit(&beach, &beach_length, &beach_allocation, site_count);
	if (ie) {
		e = gu_echo_new(ie, "fit() for beach failed: %u", site_count);
		goto fin;
	}
	ie = gu_list_fit(&circles, &circles_length, &circles_allocation, site_count);
	if (ie) {
		e = gu_echo_new(ie, "fit() for circles failed: %u", site_count);
		goto fin;
	}

	// ==========

	// event-handling functions assume these allocations > 0 for push()

	if (*halves_allocation == 0) {
		ie = gu_list_fit(halves, halves_length, halves_allocation, site_count);
		if (ie) {
			e = gu_echo_new(ie, "fit() for halves failed: %u", site_count);
			goto fin;
		}
	}

	if (*edges_allocation == 0) {
		ie = gu_list_fit(edges, edges_length, edges_allocation, site_count);
		if (ie) {
			e = gu_echo_new(ie, "fit() for edges failed: %u", site_count);
			goto fin;
		}
	}

	if (*vertices_allocation == 0) {
		ie = gu_list_fit(vertices, vertices_length, vertices_allocation, site_count);
		if (ie) {
			e = gu_echo_new(ie, "fit() for vertices failed: %u", site_count);
			goto fin;
		}
	}

	// ==========

	unsigned int next_site = 0;
	struct Dot circle_event = {0};
	while (1) {
		if (next_site >= site_count && circles_length == 0) {
			break;
		}

		if (next_site >= site_count) {
		} else if (circles_length == 0 || sites[next_site].y < circles[circles_length - 1].y) {
			e = Orphans_siteEvent(
				next_site, sites, cells,
				&beach, &beach_length, &beach_allocation,
				&circles, &circles_length, &circles_allocation,
				halves, halves_length, halves_allocation,
				edges, edges_length, edges_allocation,
				vertices, vertices_length, vertices_allocation
			);
			if (e != NULL) {
				e = gu_echo_wrap(e, 0, "Orphans_siteEvent() failed.");
				goto fin;
			}

			next_site++;
			continue;
		}

		gu_list_pop(&circles, &circles_length, &circle_event);
		e = Orphans_circleEvent(
				circle_event, sites, cells,
				&beach, &beach_length, &beach_allocation,
				&circles, &circles_length, &circles_allocation,
				halves, halves_length, halves_allocation,
				edges, edges_length, edges_allocation,
				vertices, vertices_length, vertices_allocation
		);
		if (e != NULL) {
			e = gu_echo_wrap(e, 0, "Orphans_circleEvent() failed.");
			goto fin;
		}
	}

	// ==========

	if (bounds == NULL || bounds_length == 0) {
		goto fin;
	}
	// clip unterminated edges

	// ==========


	fin:

	gu_free(beach);
	gu_free(circles);

	return e;
}
