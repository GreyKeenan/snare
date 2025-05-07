#include "./treasure.h"

#include "./diagram.h"
#include "./coast.h"

#include "./debug_paint.h"

#include "gu/echo.h"
#include "gu/debug.h"


#define gu_DEBUGIF ATOLL_DEBUG_treasure


static inline /*heap*/ struct gu_echo *atoll_siteEvent(
	struct atoll_diagram diagram[static 1],
	struct atoll_coast coast[static 1],
	unsigned int event
);
/*heap*/ struct gu_echo *atoll_circleEvent(struct atoll_diagram diagram[static 1], struct atoll_coast coast[static 1], struct atoll_circle event);


/*heap*/ struct gu_echo *atoll_treasure(struct atoll_diagram * /*nonull*/ diagram, struct atoll_coast * /*nonull*/ coast)
{
	int e = 0; (void)e;
	/*heap*/ struct gu_echo *echo = NULL;


	echo = atoll_coast_prime(coast, diagram);
	if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to prime the beachline");


	// handle the lesser-y site between coast->circles & diagram->sites[coast->nextSite]
	// if both are empty, end the alg
	// if one is empty, use the other

	while (1) {

		gu_debug( atoll_DEBUG_paint(diagram, coast); )

		if (coast->nextSite >= diagram->site_count && coast->circles_length == 0) {
			break;
		}

		if (coast->nextSite >= diagram->site_count) {
		} else if (coast->circles_length == 0
			|| diagram->sites[coast->nextSite].y
			< coast->circles[coast->circles_length - 1].center.y
			+ coast->circles[coast->circles_length - 1].radius
		) {
			// handle site event
			echo = atoll_siteEvent(diagram, coast, coast->nextSite);
			if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to process site event #%u", coast->nextSite);
			coast->nextSite += 1;
			continue;
		}

		// handle circle event
		coast->circles_length -= 1;
		echo = atoll_circleEvent(diagram, coast, coast->circles[coast->circles_length]);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to process circle event");

	}

	return NULL;
}

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


