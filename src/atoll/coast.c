#include "./coast.h"

#include "./diagram.h"
#include "./breakpoint.h"

#include "gu/gu.h"
#include "gu/order.h"
#include "gu/intlist.h"
#include "gu/echo.h"

#include <math.h>


struct atoll_coast_context {
	const unsigned int *beach;
	unsigned int beach_length;
	const struct atoll_point *sites;
	double d;
	int16_t x;
	int *e;
};


gu_comparer atoll_coast_compare;


int atoll_coast_init(struct atoll_coast self[static 1], unsigned int site_count)
{

	if (site_count == UINT_MAX) return 2;

	*self = (struct atoll_coast){0};

	int e = 0;

	e = gu_intlist_fit(&self->foci, NULL, &self->foci_allocation, site_count + 1);
	if (e) return e + 100;

	e = gu_intlist_fit(&self->breaks, NULL, &self->breaks_allocation, site_count);
	if (e) return e + 200;

	e = gu_intlist_fit(&self->circles, NULL, &self->circles_allocation, site_count + 1);
	if (e) return e + 300;

	return e;

}
void atoll_coast_reset(struct atoll_coast *self)
{
	if (self == NULL) return;

	gu_free(self->foci);
	gu_free(self->breaks);
	gu_free(self->circles);

	*self = (struct atoll_coast){0};
}


/*heap*/ struct gu_echo *atoll_coast_prime(struct atoll_coast coast[static 1], struct atoll_diagram * /*nonull*/ diagram)
{
	unsigned int count_aligned = 1;
	for ( ; count_aligned < diagram->site_count; ++count_aligned) {
		if (diagram->sites[0].y != diagram->sites[count_aligned].y) break;
	}
	
	coast->nextSite += count_aligned;

	int e = 0;

	unsigned int dummy = 0;

	if (count_aligned == 1) {
		e = gu_unstable_intlist_push(&coast->foci, &coast->foci_length, &coast->foci_allocation, &dummy);
		if (e) return gu_echo_new(e, "failed to push() the first foci");
		return NULL;
	}

	unsigned int j = 0;
	for (unsigned int i = 0; i < count_aligned; ++i) {

		j = 0;
		for ( ; j < i + 1; ++j) { //linear search for where in existing beachline to insert the new focus. Slow but this whole thing is a rare case.
			if (j == i) break;
			if (diagram->sites[i].x < diagram->sites[coast->foci[j]].x) break;
		}

		if (j == i) {
			e = gu_unstable_intlist_push(&coast->foci, &coast->foci_length, &coast->foci_allocation, &i);
			if (e) return gu_echo_new(e, "failed to push() foci #%u", i);
			continue;
		}
		
		e = gu_intlist_pry(&coast->foci, &coast->foci_length, &coast->foci_allocation, j, 1);
		if (e) return gu_echo_new(e, "failed to pry() foci #%u", i);

		coast->foci[j] = i;
	}
	for (unsigned int i = 0; i < count_aligned - 1; ++i) {
		e = atoll_diagram_newedge(diagram, coast->foci[i], coast->foci[i + 1]);
		if (e) return gu_echo_new(e, "failed to initialize new half-edges for break #%u", i);

		dummy = i * 2;
		e = gu_unstable_intlist_push(&coast->breaks, &coast->breaks_length, &coast->breaks_allocation, &dummy);
		if (e) return gu_echo_new(e, "failed to push() break #%u", i);
	}

	return NULL;
}


int atoll_coast_compare(const void * /*nonull*/ vctx, const void * /*nonull*/ vfocus)
{
	const struct atoll_coast_context *ctx = vctx;
	const unsigned int *focus = vfocus;

	if (focus == ctx->beach + ctx->beach_length - 1) {
		return -1; // is last element
	}

	const struct atoll_podouble breakpoint = atoll_breakpoint(
		ctx->d,
		ctx->sites[focus[0]],
		ctx->sites[focus[1]]
	);

	if (breakpoint.x != breakpoint.x || breakpoint.x == 1/0.0 || breakpoint.x == -1/0.0) {
		*ctx->e = 1;
		return 0;
	}

	if (ctx->x > breakpoint.x) return 1;
	if (ctx->x < breakpoint.x) return -1;
	return 0;
}


int atoll_coast_arcAtX(const unsigned int * /*nonull*/ foci, unsigned int foci_length, const struct atoll_point * /*nonull*/ sites, double directix, int16_t x, unsigned int arcidx[static 1])
{

	int e = 0;
	struct atoll_coast_context ctx = {
		.beach = foci,
		.beach_length = foci_length,
		.sites = sites,
		.d = directix,
		.x = x,
		.e = &e
	};

	*arcidx = gu_searchbetween(&ctx, foci, foci_length, &atoll_coast_compare);

	return e;
}


void atoll_coast_updateCircles(struct atoll_circle * /*nonull*/ circles, unsigned int circles_length, unsigned int from, int by)
{
	for (unsigned int i = 0; i < circles_length; ++i) {
		if (circles[i].arc < from) continue;
		circles[i].arc += by;
	}
}


void atoll_coast_removeCirclesWithArc(struct atoll_circle * /*nonull*/ circles[static 1], unsigned int circles_length[static 1], unsigned int arc)
{
	for (unsigned int i = 0; i < (*circles_length); ++i) {
		if ((*circles)[i].arc != arc) continue;
		gu_intlist_cut(circles, circles_length, i, 1);
		i -= 1;
	}
}
