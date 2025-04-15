#include "../treasure.h"

#include "../diagram.h"
#include "../coast.h"

#include "../debug_paint.c"

#include "gumetry/cvpoly.h"

#include "gu/gu.h"
#include "gu/echo.h"
#include "gu/random.h"
#include "gu/order.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>


#define TEST_SCALE ((double)20)


gu_comparer sort;
int sort(const void *a, const void *b)
{
	#define A (*(struct gumetry_point*)a)
	#define B (*(struct gumetry_point*)b)
	if (B.y > A.y) return -1;
	if (A.y > B.y) return 1;
	return 0;
	#undef A
	#undef B
}


int main(int argc, char **argv)
{
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	uint64_t seed = 0;
	if (argc > 1) {
		seed = atoll(argv[1]);
	} else {
		time_t thetime = time(NULL);
		seed = thetime;
	}

	gu_sneeze("\nseed: %"PRIu64"\n", seed);
	uint64_t rstate[2] = {0};
	gu_xorshiftr128plus_seed(rstate, seed);


	#define VLEN 4
	struct gumetry_point vertices[VLEN] = {
		(struct gumetry_point) {1, 1},
		(struct gumetry_point) {20, 1},
		(struct gumetry_point) {20, 20},
		(struct gumetry_point) {1, 20}
	};

	#define POINTS 15
	struct gumetry_point sites[POINTS] = {0};
	unsigned int sites_length = POINTS;

	e = gumetry_cvpoly_rpoints(vertices, VLEN, sites, POINTS, rstate, gu_xorshiftr128plus_anonymous);
	if (e) {
		gu_sneeze("failed to generate random points\n");
		goto fin;
	}

	// ----------

	gu_sneeze("\npoints (*%lf):\n", TEST_SCALE);
	for (unsigned int i = 0; i < POINTS; ++i) {
		gu_sneeze("(%lf, %lf) ", sites[i].x * TEST_SCALE, sites[i].y * TEST_SCALE);
	}

	gu_sneeze("\nsorted:\n");
	gu_qsort(sites, sites_length, sort);
	for (unsigned int i = 0; i < sites_length; ++i) {
		gu_sneeze("[%2u]: (%lf, %lf)\n", i, sites[i].x, sites[i].y);
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

		//atoll_DEBUG_diagram_sneeze(&d);
		//atoll_DEBUG_coast_sneeze(&c);
		e = 1;
		goto fin;
	}


	// ==========



	e = atoll_DEBUG_initSDL();
	if (e) gu_sneeze("unable to init SDL\n");
	e = 0;

	atoll_DEBUG_setscale(TEST_SCALE, 0);
	atoll_DEBUG_paint(&d, &c);

	atoll_DEBUG_endSDL();


	// ==========


	fin:

	atoll_diagram_reset(&d);
	atoll_coast_reset(&c);

	return (bool)e;
}
