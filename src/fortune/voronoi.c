#include "./voronoi.h"

#include "./half.h"
#include "./point.h"

#include "gu/echo.h"
#include "gu/list.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// ==========

int Fortune_voronoi_init(struct Fortune_voronoi self[static 1], struct Fortune_point * /*nonull*/ sites, unsigned int site_count, _Bool dontCopySites)
{
	if (site_count < 2) {
		return -1;
	}
	if (sizeof(*sites) > SIZE_MAX / site_count) {
		return -2; //this would be crazy though
	}

	int e = 0;

	*self = (struct Fortune_voronoi){
		.site_count = site_count,
		.border = Fortune_INULL
	};

	self->cells = malloc(sizeof(*self->cells) * site_count);
	if (self->cells == NULL) {
		e = -3;
		goto fin_err;
	}

	if (dontCopySites) {
		self->sites = sites;
	} else {

		self->sites = malloc(sizeof(*self->cells) * site_count);
		if (self->sites == NULL) {
			e = -4;
			goto fin_err;
		}

		memcpy(self->sites, sites, sizeof(*sites) * site_count);
	}

	e = gu_list_fit(&self->vertices, &self->vertices_length, &self->vertices_allocation, site_count);
	if (e) {
		e += 1000;
		goto fin_err;
	}
	e = gu_list_fit(&self->edges, &self->edges_length, &self->edges_allocation, site_count);
	if (e) {
		e += 2000;
		goto fin_err;
	}
	e = gu_list_fit(&self->halves, &self->halves_length, &self->halves_allocation, site_count);
	if (e) {
		e += 3000;
		goto fin_err;
	}


	return 0;
	fin_err:

	if (dontCopySites) {
		self->sites = NULL;
	}

	Fortune_voronoi_free(self);

	return e;
}

// ==========

/*heap*/ struct gu_echo *Fortune_voronoi_initializeEdge(struct Fortune_voronoi self[static 1])
{
	int e = 0;

	struct Fortune_point dummy_point = {0};

	e = gu_list_push(&self->vertices, &self->vertices_length, &self->vertices_allocation, &dummy_point);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 vertices");
	}

	e = gu_list_push(&self->vertices, &self->vertices_length, &self->vertices_allocation, &dummy_point);
	if (e) {
		return gu_echo_new(e, "failed to push() 2/2 vertices");
	}

	struct Fortune_edge dummy_edge = {
		.head = self->vertices_length - 2,
		.tail = self->vertices_length - 1
	};

	e = gu_list_push(&self->edges, &self->edges_length, &self->edges_allocation, &dummy_edge);
	if (e) {
		return gu_echo_new(e, "failed to push() new edge");
	}

	struct Fortune_half dummy_half = {
		.cell = Fortune_INULL,
		.previous = self->halves_length, //pointing to itself initially makes later-appending easier
		.next = self->halves_length,
		.edge = self->edges_length - 1
	};

	e = gu_list_push(&self->halves, &self->halves_length, &self->halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 halves");
	}

	e = gu_list_push(&self->halves, &self->halves_length, &self->halves_allocation, &dummy_half);
	if (e) {
		return gu_echo_new(e, "failed to push() 1/2 halves");
	}


	return NULL;
}
