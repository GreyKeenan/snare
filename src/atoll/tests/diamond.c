#include "../treasure.h"

#include "../diagram.h"
#include "../coast.h"

#include "../debug_display.c"
#include "../debug.c"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/order.h"

#include <stdbool.h>


gu_comparer sort;
int sort(const void *a, const void *b)
{
	return ((struct atoll_point*)a)->y - ((struct atoll_point*)b)->y;
}

int main(void)
{
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	struct atoll_point sites[] = {
		(struct atoll_point) {250, 250},

		(struct atoll_point) {0,0},
		(struct atoll_point) {500,0},
		(struct atoll_point) {0,500},
		(struct atoll_point) {500,500}
	};
	unsigned int sites_length = sizeof(sites) / sizeof(*sites);

	gu_sneeze("sorted sites:\n");
	gu_qsort(sites, sites_length, sort);
	for (unsigned int i = 0; i < sites_length; ++i) {
		gu_sneeze("\t[%2u]: (%d, %d)\n", i, sites[i].x, sites[i].y);
	}


	// ==========

	struct atoll_diagram d = {0};
	e = atoll_diagram_init(&d, sites, sites_length, atoll_COPYSITES);
	if (e) {
		gu_sneeze("unable to init diagram: %d\n", e);
		goto fin;
	}

	struct atoll_coast c = {0};
	e = atoll_coast_init(&c, sites_length);
	if (e) {
		gu_sneeze("unable to init coast: %d\n", e);
		goto fin;
	}


	echo = atoll_treasure(&d, &c);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);

		atoll_DEBUG_diagram_sneeze(&d);
		atoll_DEBUG_coast_sneeze(&c);
		//e = 1;
		//goto fin;
	}


	// ==========


	atoll_DEBUG_diagram_sneeze(&d);
	atoll_DEBUG_coast_sneeze(&c);

	echo = atoll_DEBUG_display(&d, 1);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		e = 1;
		goto fin;
	}


	// ==========


	fin:

	atoll_diagram_reset(&d);
	atoll_coast_reset(&c);

	return (bool)e;
}
