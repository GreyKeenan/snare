#include "./diagram.h"

#include "./hedge.h"

#include "gu/gu.h"
#include "gu/intlist.h"
#include "gu/echo.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int atoll_diagram_init(
	struct atoll_diagram self[static 1],
	struct gumetry_point * /*nonull*/ sites,
	unsigned int site_count,
	bool dontCopySites
)
{
	if (self == NULL
		|| sites == NULL
		|| site_count < 2
		|| site_count == UINT_MAX
	) return 2;

	//if (site_count + 1 > SIZE_MAX / sizeof(struct gumetry_point)) return 3;
	if (sizeof(struct gumetry_point) > SIZE_MAX / (site_count + 1)) return 3;

	*self = (struct atoll_diagram) {
		.site_count = site_count
	};

	if (dontCopySites) {
		self->sites = sites;
	} else {
		self->sites = malloc(sizeof(*self->sites) * site_count);
		if (self->sites == NULL) return 4;
		memcpy(self->sites, sites, sizeof(*sites) * site_count);
	}

	int e = 0;

	self->cells = malloc(sizeof(*self->cells) * (site_count + 1));
	if (self->cells == NULL) {
		e = 5;
		goto fin_err;
	}
	for (unsigned int i = 0; i < site_count + 1; ++i) {
		self->cells[i] = atoll_NADA;
	}

	#define START (site_count + 1)
	e = gu_intlist_fit(&self->vertices, NULL, &self->vertices_allocation, START);
	if (e) {
		e += 100;
		goto fin_err;
	}
	e = gu_intlist_fit(&self->hedges, NULL, &self->hedges_allocation, START);
	if (e) {
		e += 200;
		goto fin_err;
	}

	return e;
	fin_err:
	if (dontCopySites) self->sites = NULL;
	atoll_diagram_reset(self);
	return e;
}

void atoll_diagram_reset(struct atoll_diagram *self)
{
	if (self == NULL) return;

	gu_free(self->sites);
	gu_free(self->cells);
	gu_free(self->vertices);
	gu_free(self->hedges);

	*self = (struct atoll_diagram){0};
}


int atoll_diagram_addPolygon(
	struct atoll_diagram self[static 1],
	const struct gumetry_point * /*nonull*/ polygon,
	unsigned int polygon_length,
	unsigned int outside, unsigned int inside
)
{
	int e = 0;

	const unsigned int first_new_vertex = self->vertices_length;
	for (unsigned int i = 0; i < polygon_length; ++i) {
		e = gu_unstable_intlist_push(
			&self->vertices,
			&self->vertices_length,
			&self->vertices_allocation,
			polygon + i
		);
		if (e) return 100 + e;
	}

	for (unsigned int i = 0; i < polygon_length; ++i) {
		e = atoll_edge_create(
			&self->hedges,
			&self->hedges_length,
			&self->hedges_allocation,

			first_new_vertex + i,
			first_new_vertex - 1 + (i? i:polygon_length),
			outside, inside
		);
		if (e) return 200 + e;

		if (i == 0) self->cells[self->site_count] = self->hedges_length;
		else {
			e = atoll_hedge_join(self->hedges, self->hedges_length - 4, self->hedges_length - 2, 1);
			if (e) return 300 + e;
		}
	}

	return 0;
}
