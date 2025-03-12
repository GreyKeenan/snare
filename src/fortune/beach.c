#include "./beach.h"

#include "./breakpoint.h"

#include "gu/echo.h"
#include "gu/order.h"
#include "gu/list.h"

// ==========

int Fortune_beach_compare_breakpoints(int e[static 1], const void * /*nonull*/ key[static Fortune_beach_KEYLENGTH], const unsigned int * /*nonull*/ parabola_b);

// ==========

int Fortune_beach_init(struct Fortune_beach self[static 1], unsigned int site_count)
{
	int e = 0;

	*self = (struct Fortune_beach){0};

	e = gu_list_fit(&self->focuses, &self->focuses_length, &self->focuses_allocation, site_count);
	if (e) {
		return e + 10;
	}

	e = gu_list_fit(&self->intersections, &self->intersections_length, &self->intersections_allocation, site_count);
	if (e) {

		Fortune_beach_free(self);

		return e + 20;
	}

	return 0;
}

// ==========

/*heap*/ struct gu_echo *Fortune_beach_parabolaBelowPoint(
	const unsigned int * /*nonull*/ focuses,
	const unsigned int focuses_length,
	const struct Fortune_point * /*nonull*/ sites,
	const struct Fortune_point point[static 1],
	unsigned int returnto[static 1]
)
{
	int e = 0;
	const void * const /*nonull*/ key[Fortune_beach_KEYLENGTH] = { point, focuses, &focuses_length, sites };

	unsigned int at = gu_searchbetween_withcontext(&e, key, focuses, focuses_length, (gu_comparer_withcontext*)Fortune_beach_compare_breakpoints);
	if (e) {
		return gu_echo_new(e, "breakpoint calculation resulted in NaN or inf when checking between focuses[%u]:(%d, %d) & [%u]:(%d, %d) against (%d, %d).",
			at - 1, sites[focuses[at - 1]].x, sites[focuses[at - 1]].y,
			at, sites[focuses[at]].x, sites[focuses[at]].y,
			point->x, point->y
		);
	}

	*returnto = at;

	return NULL;
}

int Fortune_beach_compare_breakpoints(int e[static 1], const void * /*nonull*/ key[static Fortune_beach_KEYLENGTH], const unsigned int * /*nonull*/ parabola_b)
{
	const struct Fortune_point * /*nonull*/ new_site = key[0];
	const unsigned int * /*nonull*/ focuses = key[1];
	const unsigned int focuses_length = *(unsigned int *)(key[2]);
	const struct Fortune_point * /*nonull*/ sites = key[3];

	// ==========

	// TODO: is this where I should handle out-of-bounds breakpoints?

	if (parabola_b == focuses + (focuses_length - 1)) { //is last element
		return -1;
	}

	const double breakpoint = Fortune_breakpoint_x(new_site->y, sites[*parabola_b], sites[*(parabola_b + 1)]);
	if (breakpoint != breakpoint || breakpoint == 1/0.0 || breakpoint == -1/0.0) { // NaN or infinities
		*e = 1;
		return 0;
	}

	if (new_site->x > breakpoint) {
		return 1;
	}
	if (new_site->x < breakpoint) {
		return -1;
	}
	return 0;
}
