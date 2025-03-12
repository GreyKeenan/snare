#ifndef FORTUNE_siteEvent
#define FORTUNE_siteEvent

#include "./voronoi.h"
#include "./beach.h"
#include "./half.h"
#include "./point.h"

#include "gu/echo.h"
#include "gu/list.h"

static inline /*heap*/ struct gu_echo *Fortune_siteEvent(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1],

	struct Fortune_point * /*nonull*/ circles,
	unsigned int * /*nonull*/ circles_length,
	unsigned int * /*nonull*/ circles_allocation
)
{
	
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	// ----------

	unsigned int at = 0;

	// ==========
	// no breakpoints exist yet

	// ----------
	// because the beachline is empty

	if (beach->focuses_length == 0) {
		return gu_echo_new(1, "TODO: empty beachline case");
	}

	// ----------
	// because all parabolas are vertical lines
	
	if (!beach->breakpointsExist) {
		return gu_echo_new(1, "TODO: no breakpoints case");
	}

	// ==========
	// breakpoints exist. Must bisect a parabola.
	
	// ----------
	// find where in the beachline to interrupt

	at = 0;
	if (beach->focuses_length > 1) {
		echo = Fortune_beach_parabolaBelowPoint(
			beach->focuses,
			beach->focuses_length,
			diagram->sites,
			diagram->sites + event_index,
			&at
		);
		if (echo != NULL) {
			return gu_echo_wrap(echo, 0, "failed to find the parabola to bisect.");
		}
	}

	// ----------
	// pry() & set the new focus

	e = gu_list_pry(
		&beach->focuses,
		&beach->focuses_length,
		&beach->focuses_allocation,
		at, 2
	);
	if (e) {
		return gu_echo_new(e, "failed to pry() beach->focuses. gap_start:%u gap_length:2 focuses_length:%u", at, beach->focuses_length);
	}

	at += 1;
	beach->focuses[at] = event_index;

	// ----------
	// pry() to make space for the new intersections.
	// They will be set below.

	e = gu_list_pry(
		&beach->intersections,
		&beach->intersections_length,
		&beach->intersections_allocation,
		at, 2
	);
	if (e) {
		return gu_echo_new(e, "failed to pry() beach->intersections. gap_start:%u gap_length:2 intersections_length:%u", at, beach->intersections_length);
	}

	// ==========
	// initialize 2 vertices, 1 edge, and 2 halves

	// ----------

	struct Fortune_point dummy_point = {0};

	e = gu_list_push(&diagram->vertices, &diagram->vertices_length, &diagram->vertices_allocation, &dummy_point);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 vertices");
	}
	e = gu_list_push(&diagram->vertices, &diagram->vertices_length, &diagram->vertices_allocation, &dummy_point);
	if (e) {
		return gu_echo_new(e, "failed to push() 2/2 vertices");
	}

	// ----------

	struct Fortune_edge dummy_edge = {
		.head = diagram->vertices_length - 2,
		.tail = diagram->vertices_length - 1
	};

	e = gu_list_push(&diagram->edges, &diagram->edges_length, &diagram->edges_allocation, &dummy_edge);
	if (e) {
		return gu_echo_new(e, "failed to push() new edge");
	}

	// ----------

	struct Fortune_half dummy_half = {
		.cell = event_index,
		.previous = diagram->halves_length, //pointing to itself initially makes later-appending easier
		.next = diagram->halves_length,
		.edge = diagram->edges_length - 1
	};

	e = gu_list_push(&diagram->halves, &diagram->halves_length, &diagram->halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 halves");
	}

	diagram->cells[event_index] = diagram->halves_length - 1;


	dummy_half.cell = beach->focuses[at - 1];

	e = gu_list_push(&diagram->halves, &diagram->halves_length, &diagram->halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 halves");
	}

	Fortune_half_append(diagram->halves, diagram->cells[beach->focuses[at - 1]], diagram->halves_length - 1);

	// ==========

	return gu_echo_new(1, "TODO: identify circle events");

	// ==========

	return echo;
}

#endif
