#include "./beach.h"

#include "gu/list.h"


int Fortune_beach_init(struct Fortune_beach self[static 1], unsigned int site_count)
{
	int e = 0;

	*self = (struct Fortune_beach){0};

	e = gu_list_fit(&self->parabolas, &self->parabolas_length, &self->parabolas_allocation, site_count);
	if (e) {
		return e + 10;
	}

	e = gu_list_fit(&self->breakpoints, &self->breakpoints_length, &self->breakpoints_allocation, site_count);
	if (e) {

		Fortune_beach_free(self);

		return e + 20;
	}

	return 0;
}
