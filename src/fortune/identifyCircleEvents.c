#include "./identifyCircleEvents.h"

#include "gu/echo.h"
#include "gu/list.h"

#include <math.h>

// ==========

/*heap*/ struct gu_echo *Fortune_checkConvergence(
	int16_t directix,
	unsigned int converging_parabola,

	const struct Fortune_voronoi diagram[static 1],
	const struct Fortune_beach beach[static 1],

	struct Fortune_point * /*nonull*/ circles,
	unsigned int * /*nonull*/ circles_length,
	unsigned int * /*nonull*/ circles_allocation
)
{
	if (
		converging_parabola == 0
		|| converging_parabola >= beach->focuses_length - 1 //shouldnt ever be greater
		|| diagram->sites[beach->focuses[converging_parabola]].y >= directix //shouldnt ever be greater
	) {
		return NULL;
	}

	
	const struct Fortune_point focuses[3] = {
		*(diagram->sites[beach->focuses[converging_parabola - 1]]),
		*(diagram->sites[beach->focuses[converging_parabola    ]]),
		*(diagram->sites[beach->focuses[converging_parabola + 1]])
	};
	const double midpoint1[2] = { (f[1].x +(double) f[2].x) / 2, (f[1].y +(double) f[2].y) / 2 };
	const double midpoint2[2] = { (f[3].x +(double) f[2].x) / 2, (f[3].y +(double) f[2].y) / 2 };

	const double m1 = -(midpoint1[0] / midpoint1[1]);
	const double m2 = -(midpoint2[0] / midpoint2[1]);

	const double b1 = midpoint1[1] - m1 * midpoint1[0];
	const double b2 = midpoint2[1] - m2 * midpoint2[0];

	const double circumcenter_x = (b1 - b2) / (m2 - m1);
	const double circumcenter_y = m1 * circumcenter_x + b1;

	const double distance = sqrt(
		  (circumcenter_x - midpoint1[1]) * (circumcenter_x - midpoint1[1])
		+ (circumcenter_y - midpoint1[2]) * (circumcenter_y - midpoint1[2])
	);

	/*
	struct Fortune_convergence convergence = {
		.height = circumcenter_y + distance,
		.circumcenter = (struct Fortune_point){circumcenter_x, circumcenter_y},
	};
	*/

	// Wait... how do I store circle events in a way that I can find the point later?
	/*
		Save the circumcenter,
		and for every beachline focus
		check if 3 consecutive ones converge at the circumcenter.
		That's stupidly slow.

		Have indices to the focuses of the beachline,
		and then linearly update all of the circle-event indices
		each time a focus is added?
		Hm. This is why the examples used a linked list, I suppose.
		Ig this is a temporary solution?
		Besides, do I really want to go back and reimplement everything
		with a linked-list beachline ...?

		store the directix that the circle event was identified for,
		and re-identify it?
		This assumes new focuses haven't disrupted the potential event.
		Also, how would searching through the beachline work when
		its focuses arent necessarily below the directix?

		store the circle event directly with the arc-entry.
		To grab the circle events though,
		would need to have another list of them somehow.
		Maybe have a separate list of circle-directixes,
		then search the beachline linearly for circle-events which have that directix.

		save the circumcenter, and binary search the beachline for breakpoints
		equal to that circumcenter.
		It would have to be approximately equal, because of lost precision.
		Again, assumes the event is valid.
	*/

	return NULL;
}
