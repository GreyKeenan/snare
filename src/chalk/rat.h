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

	_Bool justCornered;
};

static inline void Chalk_Rat_init(struct Chalk_Rat *self, struct Chalk_Point south, struct Chalk_Point north)
/*
	initializes for Bresenham's Line Algorithm,
	modified to preserve south/north order.
*/
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
static inline struct Chalk_Point Chalk_Rat_step(struct Chalk_Rat *self)
/*
	steps through Bresenham's Line Algorithm (modified)

	The modified algorithm adds:
		* order of south/north pins preserved
		* corners are filled in with a single pixel
*/
{
	if (self->abs_slope.y < self->abs_slope.x) {
		if (self->d > 0) {
			self->at.y += self->y_increment;
			self->d += 2 * (self->abs_slope.y - self->abs_slope.x);
		} else {
			self->d += 2 * self->abs_slope.y;
		}

		self->at.x += self->x_increment;
		return self->at;
	}

	if (self->d > 0) {
		self->at.x += self->x_increment;
		self->d += 2 * (self->abs_slope.x - self->abs_slope.y);
	} else {
		self->d += 2 * self->abs_slope.x;
	}

	self->at.y += self->y_increment;
	return self->at;
}
static inline struct Chalk_Point Chalk_Rat_step_cardinal(struct Chalk_Rat *self)
/*
	Like _step, but it fills in the corners.
	* note that pixelsPerPin is different too.
*/
{
	if (self->abs_slope.y < self->abs_slope.x) {
		if (self->d > 0) {
			if (!self->justCornered) {
				self->justCornered = 1;
				return (struct Chalk_Point) {
					.x = self->at.x,
					.y = self->at.y + self->y_increment
				};
			}
			self->justCornered = 0;

			self->at.y += self->y_increment;
			self->d += 2 * (self->abs_slope.y - self->abs_slope.x);
		} else {
			self->d += 2 * self->abs_slope.y;
		}

		self->at.x += self->x_increment;
		return self->at;
	}

	if (self->d > 0) {
		if (!self->justCornered) {
			self->justCornered = 1;
			return (struct Chalk_Point) {
				.x = self->at.x + self->x_increment,
				.y = self->at.y
			};
		}
		self->justCornered = 0;

		self->at.x += self->x_increment;
		self->d += 2 * (self->abs_slope.x - self->abs_slope.y);
	} else {
		self->d += 2 * self->abs_slope.x;
	}

	self->at.y += self->y_increment;
	return self->at;
}

static inline short Chalk_Rat_pixelsPerPin(const struct Chalk_Rat *self)
/*
	returns the number of pixels that occur between each pin (integer-aligned point on the line)
	in a line of the given abs_slope, plus '1' to include the pin.

	The below code is for non-cornered Bresenham's Line Algorithm.
	~~~
	return (self->abs_slope.x > self->abs_slope.y)? self->abs_slope.x : self->abs_slope.y;
	~~~
	
	If I use something that fills in 1 corner always,
	it will instead be abs_slope.x + abs_slope.y
*/
{
	return self->abs_slope.x + self->abs_slope.y;
}
static inline short Chalk_Rat_pixelsPerPin_cardinal(const struct Chalk_Rat *self)
/*
	cardinal fills in corners, so the pixels per pin are different.
*/
{
	return self->abs_slope.x + self->abs_slope.y;
}


#endif
