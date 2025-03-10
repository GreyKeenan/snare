#ifndef ORPHANS_edgeEvent
#define ORPHANS_edgeEvent


#include "dot/dot.h"

#include "gu/echo.h"
#include "gu/list.h"


static inline /*heap*/ struct gu_echo *Orphans_edgeEvent(
	struct Dot event,

	/*heap*/ struct Dot * restrict /*nonull*/ edgeQ[restrict static 1],
	unsigned int edgeQ_length[restrict static 1],
	unsigned int edgeQ_allocation[restrict static 1],

	/*heap*/ struct Orphans_sand * restrict /*nonull*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1],

	/*heap*/ struct Dot * restrict edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
)
{
	(void)event;
	(void)edgeQ;
	(void)edgeQ_length;
	(void)edgeQ_allocation;
	(void)beachline;
	(void)beachline_length;
	(void)beachline_allocation;
	(void)edges;
	(void)edges_length;
	(void)edges_allocation;
	return NULL;
}


#endif
