#include "./coast.h"

#include "./diagram.h"
#include "./breakpoint.h"

#include "gu/gu.h"
#include "gu/order.h"


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


void atoll_coast_updateCircleIndices(struct atoll_coast self[static 1], unsigned int from, int by)
{
	for (unsigned int i = 0; i < self->circles_length; ++i) {
		if (self->circles[i].closing_arc < from) {
			continue;
		}
		self->circles[i].closing_arc += by;
	}
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
