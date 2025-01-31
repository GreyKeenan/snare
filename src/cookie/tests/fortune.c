
#include "../fortune.h"
#include "../voronoi.h"

#include "chalk/point.h"
#include "chalk/compare_point.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	#define NITEMS (sizeof(arr) / sizeof(*arr))
	struct Chalk_Point arr[] = {
		(struct Chalk_Point) { 0, 10 },
		(struct Chalk_Point) { 7, 15 },
		(struct Chalk_Point) { 9, 3 },
		(struct Chalk_Point) { 5, 20 },
		(struct Chalk_Point) { 1, 0 },
		(struct Chalk_Point) { 1, 20 },
		(struct Chalk_Point) { 4, 7 },
	};

	qsort(arr, NITEMS, sizeof(*arr), Chalk_Point_compL_x);

	printf("sites, organized by ascending X:\n");
	for (unsigned int i = 0; i < NITEMS; ++i) {
		printf("(%d, %d)\n", arr[i].x, arr[i].y);
	}
	printf("\n");


	#define BORDERLEN 4
	struct Chalk_Point border[BORDERLEN] = {
		(struct Chalk_Point) {0, 0},
		(struct Chalk_Point) {0, 30},
		(struct Chalk_Point) {30, 30},
		(struct Chalk_Point) {30, 0}
	};


	//struct Cookie_Voronoi vd = {0};
	struct Cookie_VoronoiRegion diagram[NITEMS] = {0};

	int e = Cookie_fortune(diagram, arr, NITEMS, border[0], border[2]);
	printf("Cookie_fortune exit status: %d\n", e);
	if (e) {
		goto fin;
	}





	fin:

	return (_Bool)e;
}

