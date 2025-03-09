#include "./beachline.h"

#include "./sand.h"

#include "dot/dot.h"

//#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/order.h"

#include <math.h>


/*heap*/ struct gu_echo *Orphans_beachline_searchbetween(unsigned int * /*nonull*/ position, struct Dot * /*nonull*/ sites, unsigned int key, struct Orphans_sand * /*nonull*/ beachline, unsigned int length)
{
	int e = 0;
	void *context[4] = {&e, sites, beachline, &length};

	size_t at = gu_searchbetween_withcontext(context, &key, beachline, length, (gu_comparer_withcontext*)Orphans_beachline_compare);
	if (e) {
		return gu_echo_new(e, "breakpoint calculation resulted in NaN or inf. Failed when checking beachline[%u]:site(%d, %d) to beachline[%u]:site(%d, %d) against key:(%d, %d).",
			at, sites[beachline[at].site].x, sites[beachline[at].site].y,
			at + e, sites[beachline[at + e].site].x, sites[beachline[at + e].site].y,
			sites[key].x, sites[key].y);
	}

	*position = at;

	return NULL;
}

int Orphans_beachline_compare(void * /*nonull*/ context[static 4], const unsigned int * /*nonull*/ key, const struct Orphans_sand * /*nonull*/ b)
{
	/*
		This is going to be a little unintuitive
		because the beachline is sorted by *breakpoint*,
		not by focus/site.
		In other words, its sorted by a value
		calculated between each consecutive 2 elements in the list,
		rather than by a value of the elements.

		For a given 'b', I check its right-breakpoint.
	*/
	int *pe = context[0];
	const struct Dot * const sites = context[1];
	const struct Orphans_sand * const beachline = context[2];
	const unsigned int beachline_length = *(unsigned int *)(context[3]);

	// ==========

	// TODO: is this where I should handle out-of-bounds breakpoints?

	if (b == beachline + beachline_length - 1) { //is last element
		return -1;
	}

	const double breakpoint = Orphans_breakpoint_x(sites[*key].y, sites[b->site], sites[(b + 1)->site]);
	if (breakpoint != breakpoint || breakpoint == 1/0.0 || breakpoint == -1/0.0) { // NaN or infinities
		*pe = 1;
		return 0;
	}

	if (sites[*key].x > breakpoint) {
		return 1;
	}
	if (sites[*key].x < breakpoint) {
		return -1;
	}
	return 0;
}

double Orphans_breakpoint_x(const double directix, const struct Dot a, const struct Dot b)
{
	const struct Dot focus1 = (a.y == directix)? b:a;
	const struct Dot focus2 = (a.y == directix)? a:b;

	//gu_sneeze("directix:%lf focus1:(%d, %d) focus2(%d, %d)\n", directix, focus1.x, focus1.y, focus2.x, focus2.y);

	if (focus1.y == focus2.y) {
		// the perpendicular line is vertical
		// breakpoint x will be a constant, then.

		//gu_sneeze("focus y-es are equal.\n");

		return (focus1.x + (double)focus2.x) / 2;
	}
	if (focus1.x == focus2.x) {
		/*
		The perpendicular line is horizontal.
		Breakpoint y is a constant.
		However, we dont need to use it to solve for 'x' in the parabola.
		In this case, we instead can form a triangle, since we know target.y.
		`focus1`, `focus2`, and the target are the vertices.
		
		target.y = avg(focus1.y, focus2.y)
		c = target.y - focusE.y
		a = directix - target.y
		c^2 - a^2 = b^2
			c >= a is necessary
			c > a will always be true (rounding errors?)
			because focusE.y < directix
		target.x = focusE.x +/- b

		Additionally, we have to handle the case where
		one of the focuses has a y == directix.

		Finally, which of the 2 collisions is correct, behaviorally?
			I'll default to the lowest-x? This may change. (250307)
		*/

		//gu_sneeze("focus x-es are equal.\n");

		if (focus2.y == directix) {
			//gu_sneeze("a focus lies on the directix.\n");
			return focus2.x;
		}

		const double target_y = (focus1.y + (double)focus2.y) / 2;
		const double triangle_c = directix - target_y;
		const double triangle_a = focus1.y - target_y;
		//const double triangle_toroot = triangle_c * triangle_c - triangle_a * triangle_a;
		const double triangle_b = sqrt( triangle_c * triangle_c - triangle_a * triangle_a );

		/*
		gu_sneeze("target_y:%lf\n", target_y);
		gu_sneeze("(%lf)^2 - (%lf)^2 = (root(%lf) = %lf)\n",
			triangle_c, triangle_a, triangle_toroot, triangle_b);
		gu_sneeze("lower-solution:%lf higher-solution:%lf\n",
			focus1.x - triangle_b, focus1.x + triangle_b);
		*/

		const double triangle_sum_x = focus1.x + triangle_b;
		const double triangle_difference_x = focus1.x - triangle_b;

		if (a.y > b.y) {
			return (triangle_sum_x > triangle_difference_x)? triangle_sum_x:triangle_difference_x;
		}
		return (triangle_sum_x < triangle_difference_x)? triangle_sum_x:triangle_difference_x;
	}

		// wait, is this even possible?

	/*
	TODO: is it possible for the perpendicular line
	to have < 2 intersections?
	What about with rounding errors?
	*/
	/*
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
	*/

	const double perpendicular_x = (a.x + b.x) /(double) 2; //TODO why did I use 'a' and 'b' here
	const double perpendicular_y = (a.y + b.y) /(double) 2;
	const double perpendicular_m = -1 * (a.x - b.x)/(double)(a.y - b.y);
	const double perpendicular_b = perpendicular_y - perpendicular_m * perpendicular_x;

	const double vertex_h = focus1.x;
	const double vertex_k = (directix + (double)focus1.y) / 2;
	const double parabola_p = focus1.y - vertex_k;

	const double top1 = vertex_h / (2 * parabola_p) + perpendicular_m;
	//const double toroot = (vertex_h * perpendicular_m + perpendicular_b - vertex_k) / parabola_p + perpendicular_m * perpendicular_m;
	const double top2 = sqrt( (vertex_h * perpendicular_m + perpendicular_b - vertex_k) / parabola_p + perpendicular_m * perpendicular_m );
	const double bottom = 1 / (2 * parabola_p);

	const double difference_x = (top1 - top2) / bottom;
	//const double difference_y = perpendicular_m * difference_x + perpendicular_b;

	const double sum_x = (top1 + top2) / bottom;
	//const double sum_y = perpendicular_m * sum_x + perpendicular_b;

	/*
	gu_sneeze("neither x nor y were equal.\n");
	gu_sneeze("perpendicular: %lf = %lf(%lf) + %lf)\n", perpendicular_y, perpendicular_m, perpendicular_x, perpendicular_b);
	gu_sneeze("parabola: (x - %lf)^2 = 4(%lf)(y - %lf)\n", vertex_h, parabola_p, vertex_k);
	gu_sneeze("other parabola: (x - %d)^2 = 4(%lf)(y - %lf)\n", focus2.x, (focus2.y - (double)directix) / 2, (directix + (double)focus2.y) / 2);
	gu_sneeze(
		"\n""/	     %lf +/- (root(%lf) = %lf)"
		"\n"":	x = ---------------------------------"
		"\n""\\	     %lf"
		"\n", top1, toroot, top2, bottom
	);
	gu_sneeze("difference:(%lf, %lf)\nsum:(%lf, %lf)\n", difference_x, difference_y, sum_x, sum_y);
	*/


	if (a.y > b.y) {
		return (sum_x > difference_x)? sum_x:difference_x;
	}
	return (sum_x < difference_x)? sum_x:difference_x;
	/*
	Consider a beachline containing the sites {a, b, a}.
	This function could be expected to return
	the leftmost solution when called for (beachline[0], beachline[1]),
	but also the rightmost solution when called for (beachline[1], beachline[2]).
	So, either the selection process needs to be left to the caller,
	or ... I guess the order of sites given to function matters?

	1. identify sites as highest vs lowest
	1. if the highest site is given first,
	  take its rightmost collision
	1. if the highest site is given second,
	  take its leftmost collision.

	This logic applies to equal x-es too.
	Equal height is already a special case.
	*/
}
