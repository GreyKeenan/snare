#ifndef ATOLL_circleEvent
#define ATOLL_circleEvent


#include "./diagram.h"
#include "./coast.h"
#include "./circle.h"

#include "gu/echo.h"


/*heap*/ struct gu_echo *atoll_circleEvent(struct atoll_diagram diagram[static 1], struct atoll_coast coast[static 1], struct atoll_circle event)
{
	int e = 0;

	// create the vertex at the convergence point
	const unsigned int newvertex = diagram->vertices_length;
	e = gu_unstable_intlist_push(&diagram->vertices, &diagram->vertices_length, &diagram->vertices_allocation, &event.center);
	if (e) return gu_echo_new(e, "unable to push new vertex");

	// create the new edge
	const unsigned int newedge = diagram->hedges_length;
	e = atoll_edge_create(
		&diagram->hedges, &diagram->hedges_length, &diagram->hedges_allocation,
		newvertex, atoll_NADA,
		coast->foci[event.arc - 1], coast->foci[event.arc + 1]
	);
	if (e) return gu_echo_new(e, "unable to create new half edges");

	// update the linked lists
	e = atoll_edge_join(diagram->hedges, newedge, coast->breaks[event.arc - 1], 0);
	if (e != 1) return gu_echo_new(e, "failed to join newedge & left: %d", e);
	e = atoll_edge_join(diagram->hedges, newedge, coast->breaks[event.arc], 1);
	if (e != 1) return gu_echo_new(e, "failed to join newedge & right: %d", e);
	e = atoll_edge_join(diagram->hedges, coast->breaks[event.arc - 1], coast->breaks[event.arc], 0);
	if (e != 1) return gu_echo_new(e, "failed to join the converging edges: %d", e);

	/*
	gu_sneeze("new edge: (1):(%u)(%u) (2):(%u)(%u)\n",
		diagram->hedges[newedge].nigh[0], diagram->hedges[newedge].nigh[1],
		diagram->hedges[newedge^1].nigh[0], diagram->hedges[newedge^1].nigh[1]
	); //aaaahhh thats it! It's setting the *next* for both, since thats the default when *everythings* NADA
	*/

	// set the convergence as a vertex for the the converging edges
	// (is already set for the new edge)
	e = atoll_edge_replaceVertex(diagram->hedges, coast->breaks[event.arc - 1], atoll_NADA, newvertex);
	if (e) return gu_echo_new(e, "failed to set vertex for the left bp");
	e = atoll_edge_replaceVertex(diagram->hedges, coast->breaks[event.arc], atoll_NADA, newvertex);
	if (e) return gu_echo_new(e, "failed to set vertex for the right bp");

	// remove the invalidated circle events
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc - 1);
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc    );
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc + 1);

	// remove the focus & 1 breakpoint
	gu_intlist_cut(&coast->foci, &coast->foci_length, event.arc, 1);
	gu_intlist_cut(&coast->breaks, &coast->breaks_length, event.arc - 1, 1);
	// overwrite the remaining breakpoint w/ the new edge
	coast->breaks[event.arc - 1] = newedge;

	// update the circle-event-indices since the foci-list was changed
	atoll_coast_updateCircles(coast->circles, coast->circles_length, event.arc, -1);
		// TODO: maybe this is breaking somehow?

	// identify new circle events, checking the neighbors of the removed arc
	e = atoll_circle_identify(coast, diagram->sites, event.arc, event.center.y + event.radius);
	if (e) return gu_echo_new(e, "failed when identifying circle events (1/2)");
	e = atoll_circle_identify(coast, diagram->sites, event.arc - 1, event.center.y + event.radius);
	if (e) return gu_echo_new(e, "failed when identifying circle events (2/2)");
	
	return NULL;
}


#endif
