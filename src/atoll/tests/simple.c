#include "../treasure.h"

#include "../diagram.h"
#include "../coast.h"

//#include "../debug_display.c"
#include "../debug_paint.c"
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


#define test(s, ...) (test)((s), sizeof(s)/sizeof(*(s)), __VA_ARGS__)
int (test)(struct atoll_point * /*nonull*/ sites, unsigned int length, double scale, double offset)
{

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	gu_sneeze("//////////////////////////////////////////////////\n\n");

	gu_sneeze("sites:\n");;
	gu_qsort(sites, length, sort);
	for (unsigned int i = 0; i < length; ++i) {
		gu_sneeze("\t[%2u]: (%d, %d)\n", i, sites[i].x, sites[i].y);
	}

	struct atoll_diagram d = {0};
	e = atoll_diagram_init(&d, sites, length, atoll_COPYSITES);
	if (e) {
		gu_sneeze("unable to init diagram: %d\n", e);
		goto fin;
	}

	struct atoll_coast c = {0};
	e = atoll_coast_init(&c, length);
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


	#ifdef DEBUGSTEP
	gu_sneeze("DONE!\n");
	atoll_DEBUG_paint(&d, NULL, scale, offset);
	#else
	atoll_DEBUG_initSDL();
	atoll_DEBUG_paint(&d, NULL, scale, offset);
	atoll_DEBUG_endSDL();
	#endif


	fin:
	atoll_diagram_reset(&d);
	atoll_coast_reset(&c);
	return e;
}




int main(int argc, char **argv)
{
	// http://www.raymondhill.net/voronoi/rhill-voronoi.html

	struct atoll_point s_d[] = {
		(struct atoll_point) {250, 250},
		(struct atoll_point) {0,0},
		(struct atoll_point) {500,0},
		(struct atoll_point) {0,500},
		(struct atoll_point) {500,500}
	};
	struct atoll_point s_9[] = {
		// 0,0 50,0 50,50 0,50 0,25 25,0 50,25, 25,50 30,20
		// 125,125 375,125 375,375 125,375 125,250 250,125 375,250 250,375 275,225
		(struct atoll_point) {300, 200},
		(struct atoll_point) {250,500},
		(struct atoll_point) {500,250},
		(struct atoll_point) {250,0},
		(struct atoll_point) {0,250},
		(struct atoll_point) {0,0},
		(struct atoll_point) {500,0},
		(struct atoll_point) {0,500},
		(struct atoll_point) {500,500}
	};
	struct atoll_point s_4[] = {
		// 0,0 50,0 50,50 0,50 0,25 25,0 50,25, 25,50 30,20
		// 200,200 250,200 250,250 200,250 200,225 225,200 250,225, 225,250 230,220
		(struct atoll_point) {123,50},
		(struct atoll_point) {400,83},
		(struct atoll_point) {415,292},
		(struct atoll_point) {224,347}
	};


	#ifdef DEBUGSTEP
	int e = atoll_DEBUG_initSDL();
	if (e) {
		gu_sneeze("unable to init SDL: %d\n", e);
		goto fin;
	}
	#endif


	if (argc < 2) {
		test(s_9, 0.5, 50);
		goto fin;
	}

	for (int i = 0; argv[1][i] != '\0'; ++i) {
		gu_sneeze("\nsites[%c]\n", argv[1][i]);
		switch (argv[1][i]) {
			case 'd':
				test(s_d, 0.5, 125);
				break;
			case '9':
				test(s_9, 0.5, 125);
				break;
			case '4':
				test(s_4, 0.5, 125);
				break;
			default:
				break;
		}
	}


	fin:

	#ifdef DEBUGSTEP
	atoll_DEBUG_endSDL();
	#endif

	return 0;
}
