#ifndef ATOLL_siteEvent
#define ATOLL_siteEvent


#include "./diagram.h"
#include "./coast.h"
#include "./circle.h"

#include "gu/echo.h"
#include "gu/intlist.h"

#include <stddef.h>


static inline /*heap*/ struct gu_echo *atoll_siteEvent(
	struct atoll_diagram diagram[static 1],
	struct atoll_coast coast[static 1],
	unsigned int event
)
{
	int e = 0;

	// find the index of the parabola to bisect
	unsigned int at = 0;
	e = atoll_coast_arcAtX(coast->foci, coast->foci_length, diagram->sites, diagram->sites[event].y, diagram->sites[event].x, &at);
	if (e) return gu_echo_new(e, "failed to identify parabola to bisect");

	// create the new edge
	const unsigned int newedge = diagram->hedges_length;
	//e = atoll_diagram_newedge(diagram, coast->foci[at], event);
	e = atoll_edge_create(
		&diagram->hedges, &diagram->hedges_length, &diagram->hedges_allocation,
		atoll_NADA, atoll_NADA,
		coast->foci[at], event
	);
	if (e) return gu_echo_new(e, "failed to create the half edges");
	diagram->cells[event] = newedge^1; // make sure this lines up with the proper half

	// remove the invalidated circle events
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, at);


	// TODO: because using pry() & pry() uses fit(), are re-allocating for each pry after a point.
	// should update in gu_list to use some sort of growfit()


	// add the new foci
	e = gu_intlist_pry(&coast->foci, &coast->foci_length, &coast->foci_allocation, at, 2);
	if (e) return gu_echo_new(e, "failed to pry for foci");
	coast->foci[at + 1] = event; // assumes foci[at] is unchanged after prying
	
	// update the circle indices-to-foci with the offset from newly added foci
	atoll_coast_updateCircles(coast->circles, coast->circles_length, at, 2);

	// add the new breakpoint-to-edges
	if (at == coast->foci_length - 1) {
		e = gu_unstable_intlist_push(&coast->breaks, &coast->breaks_length, &coast->breaks_allocation, &newedge);
		if (e) return gu_echo_new(e, "failed to push breakpoint-edge 1/2");

		e = gu_unstable_intlist_push(&coast->breaks, &coast->breaks_length, &coast->breaks_allocation, &newedge);
		if (e) return gu_echo_new(e, "failed to push breakpoint-edge 2/2");
	} else {
		e = gu_intlist_pry(&coast->breaks, &coast->breaks_length, &coast->breaks_allocation, at, 2);
		if (e) return gu_echo_new(e, "failed to pry for breakpoint-edges");

		coast->breaks[at] = newedge; // remember that (at) is the index below the new parabola
		coast->breaks[at + 1] = newedge;
	}


	// find & add circle events
	e = atoll_circle_identify(coast, diagram->sites, at, diagram->sites[event].y);
	if (e) return gu_echo_new(e, "failed when identifying circle events (1/2)");
	e = atoll_circle_identify(coast, diagram->sites, at + 2, diagram->sites[event].y);
	if (e) return gu_echo_new(e, "failed when identifying circle events (2/2)");

	return NULL;
}


#endif
