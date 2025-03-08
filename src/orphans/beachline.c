#include "./beachline.h"

#include "dot/dot.h"

#include "gu/gu.h"

#include <math.h>

double Orphans_breakpoint_x(const double directix, const struct Dot a, const struct Dot b)
{
	const struct Dot focus1 = (a.y == directix)? b:a;
	const struct Dot focus2 = (a.y == directix)? a:b;

	gu_sneeze("directix:%lf focus1:(%d, %d) focus2(%d, %d)\n", directix, focus1.x, focus1.y, focus2.x, focus2.y);

	if (focus1.y == focus2.y) {
		// the perpendicular line is vertical
		// breakpoint x will be a constant, then.

		gu_sneeze("focus y-es are equal.\n");

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

		gu_sneeze("focus x-es are equal.\n");

		if (focus2.y == directix) {
			gu_sneeze("a focus lies on the directix.\n");
			return focus2.x;
		}

		const double target_y = (focus1.y + (double)focus2.y) / 2;
		const double triangle_c = directix - target_y;
		const double triangle_a = focus1.y - target_y;
		const double triangle_toroot = triangle_c * triangle_c - triangle_a * triangle_a;
		const double triangle_b = sqrt( triangle_c * triangle_c - triangle_a * triangle_a );

		gu_sneeze("target_y:%lf\n", target_y);
		gu_sneeze("(%lf)^2 - (%lf)^2 = (root(%lf) = %lf)\n",
			triangle_c, triangle_a, triangle_toroot, triangle_b);
		gu_sneeze("lower-solution:%lf higher-solution:%lf\n",
			focus1.x - triangle_b, focus1.x + triangle_b);

		//return focus1.x - triangle_b;
		const double triangle_sum_x = focus1.x + triangle_b;
		const double triangle_difference_x = focus1.x - triangle_b;

		if (a.y > b.y) {
			return (triangle_sum_x > triangle_difference_x)? triangle_sum_x:triangle_difference_x;
		}
		return (triangle_sum_x < triangle_difference_x)? triangle_sum_x:triangle_difference_x;
	}

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

	const double perpendicular_x = (a.x + b.x) /(double) 2;
	const double perpendicular_y = (a.y + b.y) /(double) 2;
	const double perpendicular_m = -1 * (a.x - b.x)/(double)(a.y - b.y);
	const double perpendicular_b = perpendicular_y - perpendicular_m * perpendicular_x;

	const double vertex_h = focus1.x;
	const double vertex_k = (directix + (double)focus1.y) / 2;
	const double parabola_p = focus1.y - vertex_k;

	const double top1 = vertex_h / (2 * parabola_p) + perpendicular_m;
	const double toroot = (vertex_h * perpendicular_m + perpendicular_b - vertex_k) / parabola_p + perpendicular_m * perpendicular_m;
	const double top2 = sqrt(toroot);
	const double bottom = 1 / (2 * parabola_p);

	const double difference_x = (top1 - top2) / bottom;
	const double difference_y = perpendicular_m * difference_x + perpendicular_b;

	const double sum_x = (top1 + top2) / bottom;
	const double sum_y = perpendicular_m * sum_x + perpendicular_b;

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


	if (a.y > b.y) {
		return (sum_x > difference_x)? sum_x:difference_x;
	}
	return (sum_x < difference_x)? sum_x:difference_x;
}
