#ifndef GUMETRY_line
#define GUMETRY_line


#include "./point.h"


#define gumetry_INTERSECT 0
#define gumetry_COLLINEAR 1
#define gumetry_PARALLEL 2
#define gumetry_NOINTERSECT 3

#define gumetry_ONLINE 0x00
#define gumetry_LEFT 0x01
#define gumetry_RIGHT 0x02
#define gumetry_ABOVE 0x04
#define gumetry_BELOW 0x08


int gumetry_line_intersection(
	struct gumetry_point out[static 1],
	struct gumetry_point a, struct gumetry_point b,
	struct gumetry_point c, struct gumetry_point d
);
/*
	gives the intersection of a->b & c->d to `out`.
	a != b
	c != d

	returns INTERSECT if a single intersection exists
	returns COLLINEAR or PARALLEL otherwise, respectively
*/

int gumetry_line_side(struct gumetry_point a, struct gumetry_point b, struct gumetry_point p);
/*
	returns a value representing what side of the line(a, b) point `p` lies on
	a != b

	if (ret == 0), then the point is on the line
	if (ret & LEFT), then the point is left of the line
	if (ret & RIGHT), then the point is right of the line
	if (ret & ABOVE), then the point is above the line
	if (ret & BELOW), then the point is below the line
*/

static inline int gumetry_segment_intersection(
	struct gumetry_point out[static 1],
	struct gumetry_point a, struct gumetry_point b,
	struct gumetry_point c, struct gumetry_point d
)
/*
	finds the intersection of two *segments*, if it exists
	a != b
	c != d

	returns 0 if a single intersection exists
	returns NOINTERSECT or PARALLEL/COLLINEAR from _line_intersection().
	Strictly speaking, when NOINTERSECT is returned, the lines may be COLLINEAR or PARALLEL.
*/
{
	if (gumetry_line_side(a,b, c) & gumetry_line_side(a,b, d)) return gumetry_NOINTERSECT;
	if (gumetry_line_side(c,d, a) & gumetry_line_side(c,d, b)) return gumetry_NOINTERSECT;
	return gumetry_line_intersection(out, a,b, c,d);
}


#endif
