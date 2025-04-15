#include "./circle.h"

#include "./coast.h"

#include "gumetry/triangle.h"
#include "gumetry/parabola.h"

#include "gu/gu.h"
#include "gu/order.h"
#include "gu/intlist.h"

#include <math.h>


gu_comparer atoll_circle_compare;
int atoll_circle_compare(const void * /*nonull*/ va, const void * /*nonull*/ vb)
{
	#define A (*(struct atoll_circle*)va)
	#define B (*(struct atoll_circle*)vb)
	if (A.center.y + A.radius > B.center.y + B.radius) return -1;
	if (A.center.y + A.radius < B.center.y + B.radius) return  1;
	#undef A
	#undef B
	return 0;
}


int atoll_circle_identify(struct atoll_coast *coast, struct gumetry_point *sites, unsigned int arc, double directix)
{
	if (coast == NULL || sites == NULL) return 2;

	if (arc == 0 || arc == coast->foci_length - 1) return 0;

	struct atoll_circle newcircle = {0};
	if (atoll_arcIsntConverging(&newcircle, arc, directix,
		sites[coast->foci[arc - 1]],
		sites[coast->foci[arc    ]],
		sites[coast->foci[arc + 1]]
	)) return 0;


	unsigned int at = 0;
	if (coast->circles_length != 0) {
		at = gu_searchbetween(&newcircle, coast->circles, coast->circles_length, &atoll_circle_compare);
	}

	int e = 0;
	if (at == coast->circles_length) {
		e = gu_unstable_intlist_push(&coast->circles, &coast->circles_length, &coast->circles_allocation, &newcircle);
		return e? (e + 100):0;
	}

	e = gu_intlist_pry(&coast->circles, &coast->circles_length, &coast->circles_allocation, at, 1);
	if (e) return e + 200;
	coast->circles[at] = newcircle;
	return e;
}


int atoll_arcIsntConverging(
	struct atoll_circle *destination,
	unsigned int forarc,

	double directix,
	struct gumetry_point a,
	struct gumetry_point b,
	struct gumetry_point c
)
// I *think* this works even if the directix is lower than one of the foci.
// (Which might be important to account for rounding errors.)
{
	if (b.y >= directix || (b.y >= a.y && b.y >= c.y)) return 1;

	struct gumetry_point cc = gumetry_circumcenter(a, b, c);
	if (cc.x != cc.x) return 2;
	if (cc.y < gumetry_parabolaV_y(cc.x, b, directix)) return 3;

	if (destination != NULL) {
		*destination = (struct atoll_circle) {
			.center = cc,
			.radius = sqrt(
				(a.x - cc.x)*(a.x - cc.x)
				+ (a.y - cc.y)*(a.y - cc.y)
			),
			.arc = forarc
		};
	}

	if (a.y > b.y && c.y > b.y) return 0;
	if (a.y > b.y) return (cc.x >= (b.x + a.x)/2)? 0:4;
	/*if (c.y > b.y)*/return (cc.x <= (b.x + c.x)/2)? 0:5;
}

/*
Consider that, for every 3 foci,
there are 2 possible arc configurations (with a fixed arc at the center).

	(a, b, c) & (c, b, a)

The point where arcs potentially converge is just the circumcenter of three foci.
However, these two arc configurations would give the same circumcenter, of course.
So, we have to distinguish between them somehow.

Actually, this can be:

* if `b` is the highest-y or all are even, theres only 1 `abc` arc, and its not closing.
* if `a` and `c` are both higher than `b`, theres only 1 `abc` arc.
* if `a` is higher than `b`, `b`'s arc is the one greater than `breakpoint(a,b)`.
* if `c` is higher than `b`, `b`'s arc is the one less than `breakpoint(b, c)`.

> WAIT!
  I don't need to use the breakpoints above.
  I can just use the midpoints, since they lie on the same perpendicular line.
  That avoids the rounding errors with breakpoints, too.

Thinking about how the perpendiculars become vertical when `y`s are even, this makes sense.
For help visualizing, use <https://www.desmos.com/calculator/fkudi3klvc>.

Of note,
I'm not certain that all of these checks are necessary.
There are a limited number of cases with which this function needs to be called
during proper fortune's algorithm operation.
However, I'm going to try implementing it with this complete logic first.
*/
