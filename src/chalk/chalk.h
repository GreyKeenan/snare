#ifndef CHALK_Chalk_H
#define CHALK_Chalk_H

#include "./point.h"

static inline struct Chalk_Point Chalk_slope(const struct Chalk_Point south, const struct Chalk_Point north)
{
	return (struct Chalk_Point) { north.x - south.x, north.y - south.y };
}

#endif
