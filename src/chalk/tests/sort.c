
#include "../point.h"

#include "../compare_point.h"

#include <stdlib.h>
#include <stdio.h>


int main(void) {

	#define NITEMS (sizeof(arr) / sizeof(*arr))
	struct Chalk_Point arr[] = {
		(struct Chalk_Point) { 1, 10 },
		(struct Chalk_Point) { 2, 7 },
		(struct Chalk_Point) { 3, 12 },
		(struct Chalk_Point) { 4, 8 },
		(struct Chalk_Point) { 5, 11 },
	};

	qsort(arr, NITEMS, sizeof(struct Chalk_Point), Chalk_Point_compL_y);

	for (size_t i = 0; i < NITEMS; ++i) {
		printf("(%d, %d)\n", arr[i].x, arr[i].y);
	}
}
