#ifndef CHALK_Rat_H
#define CHALK_Rat_H

#include "./point.h"

struct Chalk_Rat {
/*
	line-drawing algorithm data container
*/
	struct Chalk_Point slope;
	struct Chalk_Point at;
	short d;
};

static inline void Chalk_Rat_init(struct Chalk_Rat *self, const struct Chalk_Point origin, const struct Chalk_Point slope)
{
	*self = (struct Chalk_Rat) {
		.slope = slope,
		.at = origin,
		.d = 2 * slope.y - slope.x
	};
}
static inline void Chalk_Rat_step(struct Chalk_Rat *self)
{
	self->at.x++;
	if (self->d > 0) {
		self->at.y++;
		self->d -= 2 * self->slope.x;
	}
	self->d += 2 * self->slope.y;
}
static inline short Chalk_Rat_pixelsPerPin(const struct Chalk_Point slope)
/*
	returns the number of pixels that occur between each pin
	in a line of the given slope, plus '1' to include the pin.

	The below code is for Bresenham's Line Algorithm.
	
	If I use something that fills in 1 corner always,
	it will be slope.x + slope.y
*/
{
	return (slope.x > slope.y)? slope.x : slope.y;
}

#endif
