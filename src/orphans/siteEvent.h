#ifndef ORPHANS_siteEvent
#define ORPHANS_siteEvent


#include "./sand.h"
#include "./half.h"
#include "./beachline.h"

#include "dot/dot.h"

#include "gu/echo.h"
#include "gu/list.h"


static inline /*heap*/ struct gu_echo *Orphans_siteEvent(
	unsigned int event,

	const struct Dot * /*nonull*/ sites,
	unsigned int * /*nonull*/ cells,

	/*heap*/ struct Orphans_sand * /*nonull*/ beach[static 1],
	unsigned int beach_length[static 1],
	unsigned int beach_allocation[static 1],

	/*heap*/ struct Dot * /*nonull*/ circles[static 1],
	unsigned int circles_length[static 1],
	unsigned int circles_allocation[static 1],

	/*heap*/ struct Orphans_half * /*nonull*/ halves[static 1],
	unsigned int halves_length[static 1],
	unsigned int halves_allocation[static 1],

	/*heap*/ struct Orphans_edge * /*nonull*/ edges[static 1],
	unsigned int edges_length[static 1],
	unsigned int edges_allocation[static 1],

	/*heap*/ struct Dot * /*nonull*/ vertices[static 1],
	unsigned int vertices_length[static 1],
	unsigned int vertices_allocation[static 1]
)
/*
	assumes:
		beach_allocation > 0
		halves_allocation > 0
		vertices_allocation > 0
*/
{

	(void)circles;
	(void)circles_length;
	(void)circles_allocation;

	// ==========

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	// ==========

	// no breakpoints exist

	if (beach_length == 0) {
	} else if (/*TODO*/1) { // if all focuses & directix are equal
		//return gu_echo_new(0, "TODO: special cases");
	}

	// ==========

	// breakpoints exist, so need to bisect a parabola

	unsigned int at = 0;
	if (*beach_length != 1) {
		echo = Orphans_beachline_searchbetween(&at, (void*)sites, sites + event, *beach, *beach_length);
		if (echo != NULL) {
			return gu_echo_wrap(echo, 0, "couldnt identify parabola to bisect.");
		}
	}

	e = gu_list_pry(beach, beach_length, beach_allocation, at, 2);
	if (e) {
		return gu_echo_new(e, "Unable to pry() the beachline at %u.", at);
	}

	(*beach)[at + 1].site = event;

	// ==========

	// initialize 2 vertices, 1 edge, 2 halves

	const struct Dot dummy_dot = {0};
	e = gu_list_push(vertices, vertices_length, vertices_allocation, &dummy_dot);
	if (e) {
		return gu_echo_new(e, "unable to push() for 1/2 vertices.");
	}
	e = gu_list_push(vertices, vertices_length, vertices_allocation, &dummy_dot);
	if (e) {
		return gu_echo_new(e, "unable to push() for 2/2 vertices\nlist:%p length:%u allocation:%u", *vertices, *vertices_length, *vertices_allocation);
	}

	// ----------

	struct Orphans_edge dummy_edge = {0};
	dummy_edge.vertex[0] = *vertices_length - 2;
	dummy_edge.vertex[1] = *vertices_length - 1;

	e = gu_list_push(edges, edges_length, edges_allocation, &dummy_edge);
	if (e) {
		return gu_echo_new(e, "unable to push new edge.");
	}

	// ----------

	struct Orphans_half dummy_half = {
		.cell = event,
		.prev = *halves_length, // points to itself so that appending is simpler later
		.next = *halves_length,
		.edge = *edges_length - 1
	};
	e = gu_list_push(halves, halves_length, halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "unable to push new half, 1/2");
	}
	cells[event] = *halves_length - 1;

	dummy_half.cell = (*beach)[at].site,
	e = gu_list_push(halves, halves_length, halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "unable to push new half, 2/2");
	}
	Orphans_half_append(*halves, cells[(*beach)[at].site], *halves_length - 1);

	// ==========

	// identify circle events

	// ==========

	return echo;
}


#endif
