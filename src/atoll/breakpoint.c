#include "./breakpoint.h"

#include "gumetry/parabola.h"

#include <math.h>



static inline struct atoll_podouble atoll_breakpoint_horizontals(const double directix, const double y, const double left, const double right);
static inline struct atoll_podouble atoll_breakpoint_verticals(const double directix, const double x, const double left, const double right);

static inline struct atoll_podouble atoll_breakpoint_general(const double directix, const struct atoll_podouble left, const struct atoll_podouble right);


struct atoll_podouble atoll_breakpoint(const double directix, const struct atoll_podouble left, const struct atoll_podouble right)
{
	if (left.y == directix && right.y == directix) return (struct atoll_podouble) {NAN,NAN};

	// one site is on the directix
	if (left.y == directix) {
		return (struct atoll_podouble) {
			.x = left.x,
			.y = gumetry_parabolaV_y(left.x, right, directix)
		};
	}
	if (right.y == directix) {
		return (struct atoll_podouble) {
			.x = right.x,
			.y = gumetry_parabolaV_y(right.x, left, directix)
		};
	}

	if (left.y == right.y) { // the perpendicular line is vertical
		return atoll_breakpoint_horizontals(directix, left.y, left.x, right.x);
	}
	if (left.x == right.x) { // the perpendicular line is horizontal
		return atoll_breakpoint_verticals(directix, left.x, left.y, right.y);
	}

	return atoll_breakpoint_general(directix, left, right);
}

static inline struct atoll_podouble atoll_breakpoint_general(const double directix, const struct atoll_podouble left, const struct atoll_podouble right)
{

	const double m = (left.x - right.x) / (right.y - left.y);

	#define midx ((left.x + right.x) / 2)
	#define midy ((left.y + right.y) / 2)
	#define b (midy - m*midx)

	#define h (left.x)
	#define k ((directix + left.y) / 2)

	const double p = (left.y - directix) / 2;

	const double part_1 = h + 2*m*p;
	const double part_2 = 2*p*sqrt( (h*m + b - k)/p + m*m );

	const double x_sum = part_1 + part_2;
	const double x_diff = part_1 - part_2;

	double x = 0;
	if (left.y > right.y) x = (x_sum > x_diff)? x_sum:x_diff;
	else x = (x_sum < x_diff)? x_sum:x_diff;

	#undef midx
	#undef midy
	#undef b
	#undef h
	#undef k

	return (struct atoll_podouble) {
		.x = x,
		.y = gumetry_parabolaV_y(x, left, directix) // TODO: can solve mx + b instead here
	};
}

// ==========

static inline struct atoll_podouble atoll_breakpoint_horizontals(const double directix, double y, double left, double right)
{
	const double x = (left + right) / 2;
	return (struct atoll_podouble) {
		.x = x,
		.y = gumetry_parabolaV_y(x, (struct gumetry_point){left, y}, directix)
	};
}

// ==========

static inline struct atoll_podouble atoll_breakpoint_verticals(const double directix, double x, double left, double right)
{
		#define h (x)
		#define k (left)
		#define g (right)
		#define h2 (h * 2)
		#define d (directix)

		const double top_2 = sqrt(   h2*h2 - 4*(h*h + (d - g)*(k - d))   );

		// '+' will always result in the higher-x one since sqrt cant give negative ofc
		if (left > right) {
			return (struct atoll_podouble) {
				.y = (k + g) / 2,
				.x = (h2 + top_2) / 2
			};
		}

		return (struct atoll_podouble) {
			.y = (k + g) / 2,
			.x = (h2 - top_2) / 2
		};

		#undef h
		#undef k
		#undef g
		#undef h2
		#undef d
}




// Logic/math behind these functions

/*

General Case
==================================================

Points are neither horizontally nor vertically aligned.
We need to find the perpendicular line,
and then the collision between that line and a parabola.

	(x, y) is the target breakpoint
	(d) is the directix
	(l_x, l_y) is the left point
	(r_x, r_y) is the right point

For the line crossing between both focuses:

	focus_line_slope = (l_y - r_y) / (l_x - r_x)

For the midpoint-perpendicular line:

	(m) is the perpednicular slope
	m = -1 / focus_line_slope

A point along the perpendicular slope is:

	(p_x, p_y) is the midpoint between l & r.

	p_x = (l_x + r_x)/2
	p_y = (l_y + r_y)/2

Then, we can solve for the y-intercept.

	(b) is the perpendicular y-intercept

	p_y = (m)p_x + b
	b = p_y - (m)p_x

Then, we take the parabola formula and solve for y,
and then solve for x with both formulas

	y = a(x - h)^2 + k        <- vertex-form parabola

	mx + b = a(x - h)^2 + k

	/       2ah + m +/- root( 4a(hm + b - k) + mm )
	:  x = -----------------------------------------
	\                   2a

	a = 1/(4p)

	/       (2h)/(4p) + m +/- root( (4(hm + b - k))/(4p) + mm )
	:  x = -----------------------------------------------------
	\                   2/(4p)
	/       h/(2p) + m +/- root( (hm + b - k)/p + mm )
	:  x = ------------------------------------------
	\                   1/(2p)

	x = h + 2mp +/- (2p)root( (hm + b - k)/p + mm )

(Remember that `p` is from: `vertex + p = focus`.


Horizontal case
==================================================

Points are horizontally aligned,
so their `x` is just the average x of left/right.
Then, we can solve for y a parabola equation.
This is impler than vertically-aligned,
because there is only 1 y to choose from.

	(x, y) is the target point
	(h, k) is the vertex of one of the parabolas
	(h, b) is one of the sites/focuses
	(f, g) is the other site/focus
	(d) is the directix

	x = (a + f) / 2

	find y

	parabola formula (vertical): (h - k)^2 = 4p(y - k)

'p' is the value that, when added to the vertex, gives the focus.

	k + p = b
	p = b - k
	k = (d + b) / 2
	p = b - (d + b)/2
	p = (b - d)/2

To solve for y, consider a vertex-form parabola equation:

	y = a(x - h)^2 + k

`a` is the same as `1/4p`

	 (x - h)^2
	----------- + k = y
	 4p

	 (x - h)^2
	------------ + k = y
	 4(b - d)/2

	 (x - h)^2
	----------- + k = y
	 2(b - d)

	 (x - h)^2     b + d
	----------- + ------- = y
	 2(b - d)        2

I think that form is preferrable here, but also:

	 (x - h)^2 + bb - dd
	--------------------- = y
	        2(b - d)


Vertic case
==================================================

The perpendicular line is a horizontal line.
We know `outble.y = avg(left.y, right.y)`.
Then, `distance = directix - outble.y`.

That gives us a triangle to solve.
One side is `left -> right`.
The two other sides are both of length `directix - outble.y`.

The triangle is symmetrical,
so we can split it in half to get a right triangle.

Term: `avg(left, right) = midpoint`

The triangle is: `focus->midpoint->outble`.
`focus->midpoint = abs(left.y - right.y)/2`.
`focus->outble = directix - outble.y`.

Then, outble.x is `focus.x +/- length`,
where we solve for the other side of the triangle ofc.

We can use the same criteria as the general case
to decide which solution (+/- length) to use.

	(h, k) = a focus
	(f, g) = the other focus
	d = directix_y

	y = (k + g) / 2
	z = d - y

	(h - x)^2 + (k - y)^2 = z^2
	...
	/      2h +/- sqrt( (2h)^2 - 4(h^2 + (k - y)^2 - z^2) )
	: x = --------------------------------------------------
	\                         2

Then, we can simplify `(k - y)^2 - z^2`,
since y is derived from k and g.

	k - y
	k - (k + g)/2
	(2k - k - g) / 2
	(k - g)/2

	z
	d - y
	d - (k + g)/2

	/   k - g              k + g
	: (-------)^2 - (d -  -------)^2
	\     2                  2
	...
	(d - g)(k - d)

	-> sqrt( (2h)^2 - 4(h^2 + (d - g)(k - d)) )

(I cheated on that one.)

*/
