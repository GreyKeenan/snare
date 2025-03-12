#ifndef FORTUNE_beach
#define FORTUNE_beach


#include "gu/gu.h"


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

#endif
