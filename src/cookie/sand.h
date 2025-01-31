#ifndef COOKIE_Sand
#define COOKIE_Sand

#include "chalk/point.h"

#include <stddef.h>


struct Cookie_Sand {
	unsigned short site_index;
	struct Chalk_Point *destinations[2];
	// one per half-edge
};

static inline _Bool Cookie_Sand_isNull(const struct Cookie_Sand *restrict self)
{
	return self->destinations[0] == NULL;
}

#endif
