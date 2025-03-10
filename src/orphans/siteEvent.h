#ifndef ORPHANS_siteEvent
#define ORPHANS_siteEvent


#include "./beachline.h"
#include "./sand.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/order.h"
#include "gu/list.h"


static inline /*heap*/ struct gu_echo *Orphans_addToBeachline(
	const struct Dot * restrict /*nonull*/ sites,
	unsigned int event_index,

	/*heap*/ struct Orphans_sand * /*nonull*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1],

	/*heap*/ struct Dot * edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
);


static inline /*heap*/ struct gu_echo *Orphans_siteEvent(
	const struct Dot * restrict /*nonull*/ sites,
	unsigned int event_index,

	/*heap*/ struct Dot * restrict /*nonull*/ edgeQ[restrict static 1],
	unsigned int edgeQ_length[restrict static 1],
	unsigned int edgeQ_allocation[restrict static 1],

	/*heap*/ struct Orphans_sand * /*nonull*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1],

	/*heap*/ struct Dot * edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
)
{
	//TODO
	(void)edgeQ;
	(void)edgeQ_length;
	(void)edgeQ_allocation;

	// ==========

	/*
	insert into beachline
		find the breakpoints it is between
		CANT binary search the beachline by sites,
		 becausee its not sorted by siteX.
		 It's sorted by breakpointX.
	update beachline edges to reflect change
	...
	*/

	// ==========

	/*heap*/ struct gu_echo *echo = Orphans_addToBeachline(
		sites, event_index,
		beachline, beachline_length, beachline_allocation,
		edges, edges_length, edges_allocation
	);
	if (echo != NULL) {
		return echo;
	}

	// ==========

	return NULL;
}

static inline /*heap*/ struct gu_echo *Orphans_addToBeachline(
	const struct Dot * restrict /*nonull*/ sites,
	unsigned int event_index,

	/*heap*/ struct Orphans_sand * /*nonull*/ beachline[restrict static 1],
	unsigned int beachline_length[restrict static 1],
	unsigned int beachline_allocation[restrict static 1],

	/*heap*/ struct Dot * edges[restrict static 1],
	unsigned int edges_length[restrict static 1],
	unsigned int edges_allocation[restrict static 1]
)
{

	(void)edges;
	(void)edges_length;
	(void)edges_allocation;

	int e = 0;

	gu_sneeze("adding to beachline with index:%d\n", event_index);
	gu_sneeze("beachline: { ");
	for (unsigned int i = 0; i < *beachline_length; ++i) {
		gu_sneeze("(%u %u) ", (*beachline)[i].site, (*beachline)[i].edge);
	}
	gu_sneeze("}\n");

	// ==========

	unsigned int at = 0;
	switch (*beachline_length) {
		case 0:
			if (*beachline_allocation == 0) {
				e = gu_list_fit(beachline, beachline_length, beachline_allocation, 8);
				if (e) {
					return gu_echo_new(e, "unable to fit(beachline, length:%u, allocation:%u, 8)", *beachline_length, *beachline_allocation);
				}
			}
			(*beachline)[0] = (struct Orphans_sand){event_index, 0};
			*beachline_length = 1;

			//TODO: modify edge-index value

			gu_sneeze("zero beachline length.\n\n");
			return NULL;
		case 1:
			break;
		default:
			e = Orphans_beachline_searchbetween(&at, sites, event_index, *beachline, *beachline_length);
			if (e) {
				return gu_echo_new(e, "breakpoint calculation resulted in NaN or inf. Failed when checking beachline[%u]:site(%d, %d) to beachline[%u]:site(%d, %d) against key:(%d, %d).",
					at, sites[beachline[at].site].x, sites[beachline[at].site].y,
					at + e, sites[beachline[at + e].site].x, sites[beachline[at + e].site].y,
					sites[event_index].x, sites[event_index].y);
			}
			at -= (at == *beachline_length);
			break;
	}

	// ==========

	e = gu_list_pry(beachline, beachline_length, beachline_allocation, at, 2);
	if (e) {
		return gu_echo_new(e, "failed to pry(beachline, length:%u, allocation:%u, %u, 2)", *beachline_length, *beachline_allocation, at);
	}
	(*beachline)[at] = (*beachline)[at + 2];
	(*beachline)[at + 1] = (struct Orphans_sand){event_index, 0};

	//TODO: modify their edge-index values

	// ==========

	gu_sneeze("peacefule end of %s\n", __func__);
	gu_sneeze("beachline: { ");
	for (unsigned int i = 0; i < *beachline_length; ++i) {
		gu_sneeze("(%u %u) ", (*beachline)[i].site, (*beachline)[i].edge);
	}
	gu_sneeze("}\n");
	gu_sneeze("\n");

	return NULL;
}


#endif
