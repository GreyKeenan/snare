#ifndef ORPHANS_siteEvent
#define ORPHANS_siteEvent


#include "dot/dot.h"

#include "gu/echo.h"
#include "gu/list.h"


static inline /*heap*/ struct gu_echo *Orphans_siteEvent(
	struct Dot event,

	struct Dot * restrict /*nonull heap*/ edgeQ[restrict static 1],
	unsigned int edgeQ_length[restrict static 1],
	unsigned int edgeQ_allocation[restrict static 1],

	unsigned int * restrict /*nonull heap*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1],

	struct Dot * restrict /*heap*/ edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
)
{
	return NULL;
}


#endif
