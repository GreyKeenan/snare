
#include "../dot.h"
#include "../sort.h"

#include "gu/gu.h"

#include <stdlib.h>


int main(void) {

	#define NITEMS (sizeof(arr) / sizeof(*arr))
	struct Dot arr[] = {
		(struct Dot) { 1, 10 },
		(struct Dot) { 2, 7 },
		(struct Dot) { 3, 12 },
		(struct Dot) { 4, 8 },
		(struct Dot) { 5, 11 },
	};

	qsort(arr, NITEMS, sizeof(struct Dot), Dot_sort_x_ascending);

	gu_sneeze("ascending x\n");
	for (size_t i = 0; i < NITEMS; ++i) {
		gu_sneeze("(%d, %d)\n", arr[i].x, arr[i].y);
	}

	qsort(arr, NITEMS, sizeof(struct Dot), Dot_sort_x_descending);

	gu_sneeze("descending x\n");
	for (size_t i = 0; i < NITEMS; ++i) {
		gu_sneeze("(%d, %d)\n", arr[i].x, arr[i].y);
	}

	qsort(arr, NITEMS, sizeof(struct Dot), Dot_sort_y_ascending);

	gu_sneeze("ascending y\n");
	for (size_t i = 0; i < NITEMS; ++i) {
		gu_sneeze("(%d, %d)\n", arr[i].x, arr[i].y);
	}

	qsort(arr, NITEMS, sizeof(struct Dot), Dot_sort_y_descending);

	gu_sneeze("descending y\n");
	for (size_t i = 0; i < NITEMS; ++i) {
		gu_sneeze("(%d, %d)\n", arr[i].x, arr[i].y);
	}
}
