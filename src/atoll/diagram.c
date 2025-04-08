#include "./diagram.h"

#include "gu/gu.h"
#include "gu/intlist.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int atoll_diagram_init(
	struct atoll_diagram self[static 1],
	struct atoll_podouble * /*nonull*/ sites,
	unsigned int site_count,
	bool dontCopySites
)
{
	if (self == NULL
		|| sites == NULL
		|| site_count < 2
		|| site_count == UINT_MAX
	) return 2;

	//if (site_count + 1 > SIZE_MAX / sizeof(struct atoll_podouble)) return 3;
	if (sizeof(struct atoll_podouble) > SIZE_MAX / (site_count + 1)) return 3;

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
		self->cells[i] = atoll_INDULL;
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

static inline void atoll_hedge_append( struct atoll_hedge * /*nonull*/ hedges, unsigned int head, unsigned int newtail)
{
	hedges[newtail].next = head;
	hedges[newtail].previous = hedges[head].previous;

	hedges[hedges[head].previous].next = newtail;
	hedges[head].previous = newtail;
}
static inline void atoll_diagram_newhedge(struct atoll_diagram self[static 1], unsigned int cell)
{
	self->hedges[self->hedges_length] = (struct atoll_hedge) {
		.cell = cell,
		.previous = self->hedges_length,
		.next     = self->hedges_length,
		.head = atoll_INDULL,
		.tail = atoll_INDULL
	};
	if (self->cells[cell] == atoll_INDULL) {
		self->cells[cell] = self->hedges_length;
	} else {
		atoll_hedge_append(self->hedges, self->cells[cell], self->hedges_length);
	}
	self->hedges_length += 1;
}
int atoll_diagram_newedge(struct atoll_diagram self[static 1], unsigned int cell_1, unsigned int cell_2)
{
	int e = 0;

	if (self->hedges_length > UINT_MAX - 2) return 100;
	if (self->hedges_length + 2 > self->hedges_allocation) {
		e = gu_intlist_grow(&self->hedges, &self->hedges_allocation);
		if (e) return e;
	}

	atoll_diagram_newhedge(self, cell_1);
	atoll_diagram_newhedge(self, cell_2);

	return 0;
}


int atoll_edge_giveVertex(struct atoll_hedge * /*nonull*/ hedges, unsigned int edge, unsigned int vertidx)
{
	if (hedges[edge].head == atoll_INDULL) hedges[edge].head = vertidx;
	else if (hedges[edge].tail == atoll_INDULL) hedges[edge].tail = vertidx;
	else return 1;

	if (hedges[edge^1].head == atoll_INDULL) hedges[edge^1].head = vertidx;
	else if (hedges[edge^1].tail == atoll_INDULL) hedges[edge^1].tail = vertidx;
	else return 2;

	return 0;
}
