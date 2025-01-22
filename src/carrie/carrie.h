#ifndef CARRIE_Carrie_H
#define CARRIE_Carrie_H

#include "chalk/point.h"

struct Carrie_SkewGrid {

	unsigned short width, height;
	unsigned char *data;

	unsigned char gap;
	/* distance between each point in the unwarped-grid */

};

static inline int Carrie_SkewGrid_init(struct Carrie_SkewGrid *self, unsigned char *data, unsigned short width, unsigned short height, unsigned char min_cell_girth)
{

	if (data == NULL || ((width | height) == 0)) {
		return 1;
	}

	*self = (struct Carrie_SkewGrid) {
		.width = width,
		.height = height,
		.data = data,
		.gap = Carrie_boint_MAX * 2 + min_cell_girth
	};

	return 0;
}

static inline int Carrie_SkewGrid_index_xy(const struct Carrie_SkewGrid *self, unsigned short x, unsigned short y, struct Chalk_Point *destination)
{
	if (x >= self->width || y >= self->height) {
		return 1;
	}
	if (self == NULL || destination == NULL) {
		return 2;
	}

	unsigned char boint = self->data[x + y * self->width];
	
	destination->x = x * self->gap + Carrie_boint_x(boint);
	destination->y = y * self->gap + Carrie_boint_y(boint);

	return 0;
}
static inline int Carrie_SkewGrid_index_i(const struct Carrie_SkewGrid *self, unsigned int index, struct Chalk_Point *destination)
{
	if (index >= self->width * self->height) {
		return 1;
	}
	if (self == NULL || destination == NULL) {
		return 2;
	}

	destination->x = (index % self->width) * self->gap + Carrie_boint_x(self->data[index]);
	destination->y = (index / self->width) * self->gap + Carrie_boint_y(self->data[index]);

	return 0;
}

#endif
