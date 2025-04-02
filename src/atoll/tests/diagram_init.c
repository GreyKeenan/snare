
#include "../diagram.h"

#include "gu/gu.h"


void printDiagram(struct atoll_diagram self[static 1])
{
	gu_sneeze("diagram %p:"
		"\n""\t""sites: %p"
		"\n""\t""site_count: %u"
		"\n""\t""cells: %p"
		"\n""\t"
		"\n""\t""vertices: %p"
		"\n""\t""vertices_length: %u"
		"\n""\t""vertices_allocation: %u"
		"\n""\t"
		"\n""\t""hedges: %p"
		"\n""\t""hedges_length: %u"
		"\n""\t""hedges_allocation: %u"
		"\n",
		(void*)self,
		(void*)self->sites,
		self->site_count,
		(void*)self->cells,
		(void*)self->vertices,
		self->vertices_length,
		self->vertices_allocation,
		(void*)self->hedges,
		self->hedges_length,
		self->hedges_allocation
	);
}


int main(void)
{
	int e = 0;

	#define LEN ( sizeof(sites) / sizeof(*sites) )
	struct atoll_point sites[] = {
		(struct atoll_point) {1, 2},
		(struct atoll_point) {3, 4},
		(struct atoll_point) {5, 6},
		(struct atoll_point) {7, 8}
	};
	gu_sneeze("sites: %p\n", (void*)sites);

	struct atoll_diagram d;
	printDiagram(&d);

	gu_sneeze("\n");
	e = atoll_diagram_init(&d, sites, 0, false);
	gu_sneeze("diagram_init w/ 0: %d\n", e);
	e = atoll_diagram_init(&d, sites, UINT_MAX, false);
	gu_sneeze("diagram_init w/ UINTMAX: %d\n", e);

	/*
	void *blank_sites = malloc(sizeof(struct atoll_point) * UINT_MAX - 1);
	if (blank_sites == NULL) {
		gu_sneeze("\nunable to malloc spaxe for blank sites\n");
	} else {
		e = atoll_diagram_init(&d, blank_sites, UINT_MAX - 1, false);
		gu_sneeze("diagram_init w/ UINTMAX - 1: %d\n", e);
	}
	*/ // not my brightest idea

	gu_sneeze("\n");

	e = atoll_diagram_init(&d, sites, LEN, atoll_DONTCOPYSITES);
	gu_sneeze("digram_init: %d\n", e);
	printDiagram(&d);
	if (e) goto fin;

	for (size_t i = 0; i < LEN + 2; ++i) {
		if (i == LEN + 1) {
			gu_sneeze("All cells were initialized to INDULL.\n");
			break;
		}
		if (d.cells[i] != atoll_INDULL) {
			gu_sneeze("At least cell[%zu] != INDULL.\n", i);
			break;
		}
	}




	fin:
	//atoll_diagram_reset(&d);

	return e;
}
