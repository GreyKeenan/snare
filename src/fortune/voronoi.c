#include "./voronoi.h"

#include "gu/list.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int Fortune_voronoi_init(struct Fortune_voronoi self[static 1], struct Fortune_point * /*nonull*/ sites, unsigned int site_count, _Bool dontCopySites)
{
	if (site_count < 2) {
		return -1;
	}

	int e = 0;

	*self = (struct Fortune_voronoi){
		.site_count = site_count,
		.border = Fortune_INDEX_NULL
	};

	self->cells = malloc(sizeof(*self->cells), site_count);
	if (self->cells == NULL) {
		e = -2;
		goto fin_err;
	}

	if (dontCopySites) {
		self->sites = sites;
	} else {

		self->sites = malloc(sizeof(*self->cells), site_count);
		if (self->sites == NULL) {
			e = -4;
			goto fin_err;
		}

		/*
		// This can be assumed by malloc succeeding
		if (sizeof(*sites) > SIZE_MAX / site_count) {
			e = -3;
			goto fin_err;
		}
		*/

		memcpy(self->sites, sites, sizeof(*sites) * site_count);
	}

	e = gu_fit(&self->vertices, &self->vertices_length, &self->vertices_allocation, site_count);
	if (e) {
		e += 1000;
		goto fin_err;
	}
	e = gu_fit(&self->edges, &self->edges_length, &self->edges_allocation, site_count);
	if (e) {
		e += 2000;
		goto fin_err;
	}
	e = gu_fit(&self->halves, &self->halves_length, &self->halves_allocation, site_count);
	if (e) {
		e += 3000;
		goto fin_err;
	}


	return 0;
	fin_err:

	if (dontCopySites) {
		self->sites == NULL;
	}

	Fortune_voronoi_free(self);

	return e;
}
