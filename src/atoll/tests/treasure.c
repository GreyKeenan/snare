#include "../treasure.h"

#include "../diagram.h"
#include "../coast.h"

//#include "../debug_display.c"
#include "../debug_paint.c"
#include "../debug.c"

#include "gumetry/cvpoly.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/random.h"
#include "gu/order.h"

#include <stdbool.h>
#include <time.h>


gu_comparer sort;
int sort(const void *a, const void *b)
{
	return ((struct atoll_point*)a)->y - ((struct atoll_point*)b)->y;
}


int main(void)
{
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;


	#define VLEN 4
	double vertices[VLEN * 2] = {
		1, 1,
		20, 1,
		20, 20,
		1, 20
	};

	#define POINTS 15
	double points[POINTS * 2] = {0};

	time_t thetime = time(NULL);
	uint64_t rstate[2] = {0};
	gu_xorshiftr128plus_seed(rstate, thetime);

	e = gumetry_cvpoly_rpoints(vertices, VLEN, points, POINTS, rstate, gu_xorshiftr128plus_anonymous);
	if (e) {
		gu_sneeze("failed to generate random points\n");
		goto fin;
	}

	// ----------

	struct atoll_point sites[POINTS] = {0};
	unsigned int sites_length = POINTS;

	gu_sneeze("\npoints:\n");
	for (unsigned int i = 0; i < POINTS; ++i) {
		sites[i].x = points[i * 2] * 10; //hm, I regret not using doubles for everything
		sites[i].y = points[i*2 + 1] * 10;
		gu_sneeze("(%d, %d) ", sites[i].x, sites[i].y);
	}

	gu_sneeze("\nsorted:\n");
	gu_qsort(sites, sites_length, sort);
	for (unsigned int i = 0; i < sites_length; ++i) {
		gu_sneeze("[%2u]: (%d, %d)\n", i, sites[i].x, sites[i].y);
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



	/*
	echo = atoll_DEBUG_display(&d, 2, 0);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		e = 1;
		goto fin;
	}
	// */

	//*
	e = atoll_DEBUG_initSDL();
	if (e) gu_sneeze("unable to init SDL\n");
	e = 0;

	atoll_DEBUG_setscale(2, 0);
	atoll_DEBUG_paint(&d, &c);

	atoll_DEBUG_endSDL();
	// */


	// ==========


	fin:

	atoll_diagram_reset(&d);
	atoll_coast_reset(&c);

	return (bool)e;
}
