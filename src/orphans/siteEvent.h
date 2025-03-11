#ifndef ORPHANS_siteEvent
#define ORPHANS_siteEvent


#include "./sand.h"
#include "./half.h"
#include "./beachline.h"

#include "dot/dot.h"

#include "gu/echo.h"


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
*/
{
	(void)event;
	(void)sites;
	(void)cells;
	(void)beach;
	(void)beach_length;
	(void)beach_allocation;
	(void)circles;
	(void)circles_length;
	(void)circles_allocation;
	(void)halves;
	(void)halves_length;
	(void)halves_allocation;
	(void)edges;
	(void)edges_length;
	(void)edges_allocation;
	(void)vertices;
	(void)vertices_length;
	(void)vertices_allocation;

	return NULL;
}


#endif
