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

	#define A (*(struct atoll_point*)a)
	#define B (*(struct atoll_point*)b)

	if (A.y == B.y) return A.x - B.x;
	return A.y - B.y;

	#undef A
	#undef B
}

int main(void)
{
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	// http://www.raymondhill.net/voronoi/rhill-voronoi.html
	// 0,0 50,0 50,50 0,50 0,25 25,0 50,25, 25,50 30,20
		// 200,200 250,200 250,250 200,250 200,225 225,200 250,225, 225,250 230,220
	struct atoll_point sites[] = {

		(struct atoll_point) {123,50},
		(struct atoll_point) {400,83},
		(struct atoll_point) {415,292},
		(struct atoll_point) {224,347},

		(struct atoll_point) {0} // EXTRA
	};
	unsigned int sites_length = -1 + sizeof(sites) / sizeof(*sites);

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


	echo = atoll_DEBUG_display(&d, 0.5, 125);
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
