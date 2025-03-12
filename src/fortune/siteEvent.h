#ifndef FORTUNE_siteEvent
#define FORTUNE_siteEvent

#include "./voronoi.h"
#include "./beach.h"
#include "./half.h"
#include "./point.h"

#include "gu/echo.h"
#include "gu/list.h"

// ==========

static inline /*heap*/ struct gu_echo *Fortune_siteEvent_empty(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1]
);
static inline /*heap*/ struct gu_echo *Fortune_siteEvent_noBreakpoints(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1]
);
static inline /*heap*/ struct gu_echo *Fortune_siteEvent_yesBreakpoints(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1],

	unsigned int new_parabola[static 1]
);

// ==========

static inline /*heap*/ struct gu_echo *Fortune_siteEvent(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1],

	struct Fortune_point * /*nonull*/ circles,
	unsigned int * /*nonull*/ circles_length,
	unsigned int * /*nonull*/ circles_allocation
)
{

	/*heap*/ struct gu_echo *echo = NULL;

	// ==========

	if (beach->focuses_length == 0) {
		beach->first_directix = diagram->sites[event_index].y;
		return Fortune_siteEvent_empty(event_index, diagram, beach);
	} else if (diagram->sites[event_index].y == beach->first_directix) {
		return Fortune_siteEvent_noBreakpoints(event_index, diagram, beach);
	}

	unsigned int new_parabola_index = 0;
	echo = Fortune_siteEvent_yesBreakpoints(event_index, diagram, beach, &new_parabola_index);
	if (echo != NULL) {
		return echo;
	}

	// ==========

	return gu_echo_new(1, "TODO: identify circle events");

	// ==========

	return echo;
}

static inline /*heap*/ struct gu_echo *Fortune_siteEvent_empty(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1]
)
{
	beach->focuses[0] = event_index;
	beach->focuses_length = 1;

	return gu_echo_new(0, "TODO");
}

static inline /*heap*/ struct gu_echo *Fortune_siteEvent_noBreakpoints(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1]
)
{
	return gu_echo_new(0, "TODO");
}

static inline /*heap*/ struct gu_echo *Fortune_siteEvent_yesBreakpoints(
	unsigned int event_index,

	struct Fortune_voronoi diagram[static 1],
	struct Fortune_beach beach[static 1],

	unsigned int new_parabola[static 1]
)
{

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;
	
	// find where in the beachline to interrupt
	unsigned int at = 0;
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
	*new_parabola = at;
	beach->focuses[at] = event_index;

	// pry() to make space for the new intersections. They will be set below.
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

	echo = Fortune_voronoi_initializeEdge(diagram);
	if (echo != NULL) {
		return gu_echo_wrap(echo, 0, "failed to initialize elements for a new edge");
	}

	beach->intersections[at] = diagram->vertices_length - 2;
	beach->intersections[at + 1] = diagram->vertices_length - 1;

	diagram->halves[diagram->halves_length - 2].cell = event_index;
	diagram->cells[event_index] = diagram->halves_length - 2;

	diagram->halves[diagram->halves_length - 1].cell = beach->focuses[at - 1];
	Fortune_half_append(diagram->halves, diagram->cells[beach->focuses[at - 1]], diagram->halves_length - 2);

	return echo;
}

#endif
