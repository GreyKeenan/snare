#include "./circle.h"

#include "./coast.h"
#include "./math.h"

#include "gu/gu.h"
#include "gu/order.h"
#include "gu/intlist.h"

#include <math.h>


gu_comparer atoll_circle_compare;
int atoll_circle_compare(const void * /*nonull*/ va, const void * /*nonull*/ vb)
{
	return ((struct atoll_circle*)vb)->center.y - ((struct atoll_circle*)va)->center.y; // higher-y first so can pop lowest-y off of the top
}


int atoll_circle_identify(struct atoll_coast * /*nonull*/ coast, struct atoll_point * /*nonull*/ sites, unsigned int arc, double directix)
{
	if (arc == 0 || arc >= coast->foci_length - 1) return 0;
		// the arc is at one of the ends of the beachline, which are never closing


	struct atoll_podouble cc = atoll_circumcenter(
		sites[coast->foci[arc - 1]],
		sites[coast->foci[arc]],
		sites[coast->foci[arc + 1]]
	);
	if (cc.x != cc.x) return 0;
		// The perpendicular lines are parallel.
		// No circumcenter exists, so the arc isnt closing.

	const struct atoll_point middle = sites[coast->foci[arc]];
	if (cc.y < atoll_parabola_y(cc.x, middle.x, middle.y, directix)) return 0;
		// circumcenter is behind the beachline, so the arc isnt closing


	const struct atoll_circle newcircle =  {
		.center = cc,
		.radius = sqrt(
			(middle.x - cc.x)*(middle.x - cc.x)
			+ (middle.y - cc.y)*(middle.y - cc.y)
		),
		.arc = arc
	};

	// add the new circle event to the queue, in the sorted position:

	unsigned int at = 0;
	if (coast->circles_length != 0) {
		at = gu_searchbetween(&newcircle, coast->circles, coast->circles_length, &atoll_circle_compare);
	}

	int e = 0;
	if (at == coast->circles_length) {
		e = gu_unstable_intlist_push(&coast->circles, &coast->circles_length, &coast->circles_allocation, &newcircle);
		if (e) return e + 100;
	} else {
		e = gu_intlist_pry(&coast->circles, &coast->circles_length, &coast->circles_allocation, at, 1);
		if (e) return e + 200;
		coast->circles[at] = newcircle;
	}

	return e;
}

