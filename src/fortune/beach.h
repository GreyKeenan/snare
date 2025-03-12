#ifndef FORTUNE_beach
#define FORTUNE_beach


#include "gu/gu.h"


struct Fortune_beach {
	/*heap*/ unsigned int *parabolas; // indices to sites
	unsigned int parabolas_length;
	unsigned int parabolas_allocation;

	/*heap*/ unsigned int *breakpoints; // indices to vertices
	unsigned int breakpoints_length;
	unsigned int breakpoints_allocation;
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

	gu_free(self->parabolas);
	gu_free(self->breakpoints);

	*self = (struct Fortune_beach){0};
}

#endif
