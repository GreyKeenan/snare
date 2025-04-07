#ifndef ATOLL_circleEvent
#define ATOLL_circleEvent


#include "./diagram.h"
#include "./coast.h"
#include "./circle.h"

#include "gu/echo.h"


/*heap*/ struct gu_echo *atoll_circleEvent(struct atoll_diagram diagram[static 1], struct atoll_coast coast[static 1], struct atoll_circle event)
{

	/*

	join converging edges
		init a new edge at event.center
		set as a vertex for both of the converging edges (4 hedges)
	cut old arc & one of the old breaks[] edges indices
		update the remaining circle event indices
	create new edge and overwrite the remaining old edge with it
	set 1 vertex of the new edge to the same as the converged-at vertex

	check for new circle events with the arcs adjacent to the changed-edge?

	*/

	if (event.arc == 0 || event.arc >= coast->foci_length) {
		return gu_echo_new(event.arc, "event.arc shouldn't be the first/last item ever");
	}

	int e = 0;


	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc - 1);
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc    );
	atoll_coast_removeCirclesWithArc(&coast->circles, &coast->circles_length, event.arc + 1);


	unsigned int vertidx = diagram->vertices_length;
	const struct atoll_point vtx = {
		.x = event.center.x,
		.y = event.center.y
	};
	e = gu_unstable_intlist_push(&diagram->vertices, &diagram->vertices_length, &diagram->vertices_allocation, &vtx);
	if (e) return gu_echo_new(e, "unable to push new vertex");

	e = atoll_edge_giveVertex(diagram->hedges, coast->breaks[event.arc - 1], vertidx);
	if (e) return gu_echo_new(e, "unable to give vertex (1/2)");
	e = atoll_edge_giveVertex(diagram->hedges, coast->breaks[event.arc], vertidx);
	if (e) return gu_echo_new(e, "unable to give vertex (2/2)");


	gu_intlist_cut(&coast->foci, &coast->foci_length, event.arc, 1);
	gu_intlist_cut(&coast->breaks, &coast->breaks_length, event.arc - 1, 1);

	atoll_coast_updateCircles(coast->circles, coast->circles_length, event.arc, -1);

	e = atoll_diagram_newedge(diagram, coast->foci[event.arc], coast->foci[event.arc - 1]);
	if (e) return gu_echo_new(e, "failed to create new edge");

	e = atoll_edge_giveVertex(diagram->hedges, diagram->hedges_length - 2, vertidx);
	if (e) return gu_echo_new(e, "unable to give vertex to the new edge");
	coast->breaks[event.arc - 1] = diagram->hedges_length - 2;

	

	e = atoll_circle_identify(coast, diagram->sites, event.arc, event.center.y + event.radius);
	if (e) return gu_echo_new(e, "failed when identifying circle events (1/2)");

	e = atoll_circle_identify(coast, diagram->sites, event.arc - 1, event.center.y + event.radius);
	if (e) return gu_echo_new(e, "failed when identifying circle events (2/2)");


	return NULL;
}


#endif
