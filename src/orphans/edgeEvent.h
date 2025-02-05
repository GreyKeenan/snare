#ifndef ORPHANS_edgeEvent
#define ORPHANS_edgeEvent


#include "./sand.h"

#include "dot/dot.h"

#include "gu/echo.h"
#include "gu/list.h"


/*heap*/ struct gu_echo *Orphans_edgeEvent(
	struct Dot event,

	struct Dot * restrict /*nonull*/ edgeQ[restrict static 1],
	unsigned int edgeQ_length[restrict static 1],
	unsigned int edgeQ_allocation[restrict static 1],

	struct Orphans_Sand * restrict /*nonull*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1]
)
{
	return NULL;
}


#endif
