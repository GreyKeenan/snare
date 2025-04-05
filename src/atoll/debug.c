
#include "./coast.h"
#include "./diagram.h"
#include "./circle.h"

#include "gu/gu.h"

void atoll_DEBUG_hedge_sneeze(const struct atoll_hedge *self)
{
	if (self == NULL) {
		gu_sneeze("hedge: { }\n");
		return;
	}

	gu_sneeze("hedge: %p\n", (void*)self);
	gu_sneeze("{\n");

	gu_sneeze("previous: %u\n", self->previous);
	gu_sneeze("next: %u\n", self->next);
	gu_sneeze("cell: %u\n", self->cell);
	gu_sneeze("head: %u\n", self->head);
	gu_sneeze("tail: %u\n", self->tail);

	gu_sneeze("}\n");
}

void atoll_DEBUG_diagram_sneeze(const struct atoll_diagram *self)
{
	if (self == NULL) {
		gu_sneeze("diagram: { }\n");
		return;
	}

	gu_sneeze("diagram: %p\n", (void*)self);
	gu_sneeze("{\n");

	gu_sneeze("site_count: %u\n", self->site_count);
	gu_sneeze("sites: %p\n", (void*)self->sites);
	if (self->sites != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->site_count; ++i) {
			gu_sneeze("(%u):\t(%d, %d)\n", i, self->sites[i].x, self->sites[i].y);
		}
		gu_sneeze("]\n");
	}
	gu_sneeze("\n");

	gu_sneeze("cells: %p\n", (void*)self->cells);
	if (self->cells != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->site_count + 1; ++i) {
			gu_sneeze("(%u):\t%u\n", i, self->cells[i]);
		}
		gu_sneeze("]\n");
	}
	gu_sneeze("\n");

	gu_sneeze("vertices_length: %u\n", self->vertices_length);
	gu_sneeze("vertices_allocation: %u\n", self->vertices_allocation);
	gu_sneeze("vertices: %p\n", (void*)self->vertices);
	if (self->vertices != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->vertices_length; ++i) {
			gu_sneeze("(%u):\t(%d, %d)\n", i, self->vertices[i].x, self->vertices[i].y);
		}
		gu_sneeze("]\n");
	}
	gu_sneeze("\n");

	gu_sneeze("hedges_length: %u\n", self->hedges_length);
	gu_sneeze("hedges_allocation: %u\n", self->hedges_allocation);
	gu_sneeze("hedges: %p\n", (void*)self->hedges);
	if (self->hedges != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->hedges_length; ++i) {
			gu_sneeze("(%u):\t", i);
			atoll_DEBUG_hedge_sneeze(self->hedges + i);
		}
		gu_sneeze("]\n");
	}
	gu_sneeze("\n");

	gu_sneeze("}\n");
}

void atoll_DEBUG_circle_sneeze(const struct atoll_circle *self)
{
	gu_sneeze("circle: %p\n", (void*)self);
	if (self == NULL) return;

	gu_sneeze("{\n");

	gu_sneeze("center: (%lf, %lf)\n", self->center.x, self->center.y);
	gu_sneeze("radius: %lf\n", self->radius);
	gu_sneeze("arc: %u\n", self->arc);

	gu_sneeze("}\n");
}

void atoll_DEBUG_coast_sneeze(const struct atoll_coast *self)
{
	gu_sneeze("coast: %p\n", (void*)self);
	if (self == NULL) return;
	gu_sneeze("{\n");

	gu_sneeze("foci_length: %u\n", self->foci_length);
	gu_sneeze("foci_allocation: %u\n", self->foci_allocation);
	gu_sneeze("foci: %p\n", (void*)self->foci);
	if (self->foci != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->foci_length; ++i) {
			gu_sneeze("(%u):\t%u\n", i, self->foci[i]);
		}
		gu_sneeze("]\n");
	}
	
	gu_sneeze("breaks_length: %u\n", self->breaks_length);
	gu_sneeze("breaks_allocation: %u\n", self->breaks_allocation);
	gu_sneeze("breaks: %p\n", (void*)self->breaks);
	if (self->breaks != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->breaks_length; ++i) {
			gu_sneeze("(%u):\t%u\n", i, self->breaks[i]);
		}
		gu_sneeze("]\n");
	}

	gu_sneeze("nextSite: %u\n", self->nextSite);

	gu_sneeze("circles_length: %u\n", self->circles_length);
	gu_sneeze("circles_allocation: %u\n", self->circles_allocation);
	gu_sneeze("circles: %p\n", (void*)self->circles);
	if (self->circles != NULL) {
		gu_sneeze("[\n");
		for (unsigned int i = 0; i < self->circles_length; ++i) {
			gu_sneeze("(%u):\t", i);
			atoll_DEBUG_circle_sneeze(self->circles + i);
		}
		gu_sneeze("]\n");
	}

	gu_sneeze("}\n");
}
