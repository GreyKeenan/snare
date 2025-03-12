#ifndef FORTUNE_beach
#define FORTUNE_beach
// ==========

#include "./point.h"

#include "gu/gu.h"

#include <stdint.h>

// ==========

#define Fortune_beach_KEYLENGTH 4

// ==========

struct Fortune_beach {
	/*heap*/ unsigned int *focuses; // indices to sites
	unsigned int focuses_length;
	unsigned int focuses_allocation;

	/*heap*/ unsigned int *intersections; // indices to vertices
	unsigned int intersections_length;
	unsigned int intersections_allocation;
	//breakpoint[x] is the breakpoint before beach[x].
	//breapoint[x + 1] is the breakpoint after.
};

// ==========

int Fortune_beach_init(struct Fortune_beach self[static 1], unsigned int site_count);
/*
	assumes:
		site_count > 0

	returns 0 on success
	On error, calls `Fortune_beach_free()` on itself
*/

static inline void Fortune_beach_free(struct Fortune_beach *self)
{
	if (self == NULL) {
		return;
	}

	gu_free(self->focuses);
	gu_free(self->intersections);

	*self = (struct Fortune_beach){0};
}

// ----------

/*heap*/ struct gu_echo *Fortune_beach_parabolaBelowPoint(
	const unsigned int * /*nonull*/ focuses,
	unsigned int focuses_length,
	const struct Fortune_point * /*nonull*/ sites,
	const struct Fortune_point point[static 1],
	unsigned int returnto[static 1]
);
/*
	assumes:
		Assumes there a breakpoints exists between any two adjacent focuses in the beachline.
		aka, for every element n, !(focus[n].y == directix & focus[n + 1].y == directix),
			where directix = point.y
		This should be true for any properly constructed beachline,
		except when all sites on the beachline have y == directix.

		All focuses on the beachline are valid indices to `sites`.

		All focuses have a y value <= directix

	Given a new focus and the existing beachline,
	finds the existing parabola that the new focus would bisect.
	It gives the index of that existing parabola-arc to `returnto`.

	returns NULL on success,
	or an error when the breakpoint calculation resulted in inf/NaN.
*/

// ==========
#endif
