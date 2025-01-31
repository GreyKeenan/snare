#ifndef COOKIE_edgeEvent
#define COOKIE_edgeEvent

#include "./sand.h"

#include "chalk/point.h"

#include "gunc/list.h"

static inline int Cookie_addEdgeEvent(struct Chalk_Point point, struct Chalk_Point **list, unsigned int *length, unsigned int *allocation)
{

	int e = Gunc_push(list, length, allocation, &point);
	if (e) {
		return 2;
	}

	for (int i = *length - 1; i > 0; --i) {
		if ((*list)[i].x <= (*list)[i - 1].x) {
			break;
		}
		(*list)[i] = (*list)[i - 1];
		(*list)[i - 1] = point;
	}

	return 0;
}

static inline int Cookie_edgeEvent(
	struct Chalk_Point eventPoint,

	struct Chalk_Point **edgeQ,
	unsigned int *edgeQ_length,
	unsigned int *edgeQ_allocation,

	struct Cookie_Sand **beachline,
	unsigned int *beachline_length,
	unsigned int *beachline_allocation

)
{
	return 1;
}

#endif
