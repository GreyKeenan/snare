#include "./algorithm.h"

#include "./siteEvent.h"

#include "./voronoi.h"
#include "./beach.h"

#include "gu/echo.h"
#include "gu/list.h"

#include <stdlib.h>

// ==========

/*heap*/ struct gu_echo *Fortune_algorithm(struct Fortune_voronoi diagram[static 1], struct Fortune_beach beach[static 1])
{

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	/*heap*/ struct Fortune_point *circles = NULL;
	unsigned int circles_length = 0;
	unsigned int circles_allocation = 0;

	// ==========

	e = gu_list_fit(&circles, &circles_length, &circles_allocation, diagram->site_count);
	if (e) {
		return gu_echo_new(e, "unable to fit() for circle event queue. site_count:%u", diagram->site_count);
	}

	// ==========

	unsigned int next_site = 0;
	struct Fortune_point circle_event = {0};
	while (1) {
		if (next_site >= diagram->site_count && circles_length == 0) {
			break;
		}

		if (next_site >= diagram->site_count) {
		} else if (circles_length == 0 || diagram->sites[next_site].y < circles[circles_length - 1].y) {

			//handle site event

			next_site++;
			continue;
		}

		gu_list_pop(&circles, &circles_length, &circle_event);

		// handle edge event

	}

	// ==========

	fin:

	gu_free(circles);

	return echo;
}
