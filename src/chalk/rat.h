#ifndef CHALK_Rat_H
#define CHALK_Rat_H

#include "./point.h"

struct Chalk_Rat {
/*
	line-drawing algorithm data container
*/
	struct Chalk_Point abs_slope;
	struct Chalk_Point at;
	short d;
	signed char x_increment;
	signed char y_increment;
};

static inline void Chalk_Rat_init(struct Chalk_Rat *self, struct Chalk_Point south, struct Chalk_Point north)
{
	*self = (struct Chalk_Rat) {
		.abs_slope = (struct Chalk_Point) {
			.x = north.x - south.x,
			.y = north.y - south.y
		},
		.at = south,
		.x_increment = 1,
		.y_increment = 1
	};

	if (self->abs_slope.x < 0) {
		self->x_increment = -1;
		self->abs_slope.x *= -1;
	}
	if (self->abs_slope.y < 0) {
		self->y_increment = -1;
		self->abs_slope.y *= -1;
	}

	if (self->abs_slope.y < self->abs_slope.x) {
		self->d = 2 * self->abs_slope.y - self->abs_slope.x;
	} else {
		self->d = 2 * self->abs_slope.x - self->abs_slope.y;
	}
}
static inline void Chalk_Rat_step(struct Chalk_Rat *self)
{
	if (self->abs_slope.x > self->abs_slope.y) {
		self->at.x += self->x_increment;
		if (self->d > 0) {
			self->at.y += self->y_increment;
			self->d += 2 * (self->abs_slope.y - self->abs_slope.x);
		} else {
			self->d += 2 * self->abs_slope.y;
		}
	} else {
		self->at.y += self->y_increment;
		if (self->d > 0) {
			self->at.x += self->x_increment;
			self->d += 2 * (self->abs_slope.x - self->abs_slope.y);
		} else {
			self->d += 2 * self->abs_slope.x;
		}
	}
}


static inline short Chalk_Rat_pixelsPerPin(const struct Chalk_Rat *self)
/*
	returns the number of pixels that occur between each pin
	in a line of the given abs_slope, plus '1' to include the pin.

	The below code is for Bresenham's Line Algorithm.
	
	If I use something that fills in 1 corner always,
	it will be abs_slope.x + abs_slope.y
*/
{
	return (self->abs_slope.x > self->abs_slope.y)? self->abs_slope.x : self->abs_slope.y;
}


#endif
