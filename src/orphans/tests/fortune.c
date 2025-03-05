
#include "../fortune.h"
#include "../region.h"

#include "dot/dot.h"
#include "dot/sort.h"

#include "gu/gu.h"
#include "gu/echo.h"

#include <stdlib.h>
#include <stdio.h>

// #include <limits.h>


int main(void)
{

	struct gu_echo *echo = NULL;

	#define LEN 7
	struct Dot arr[LEN] = {
		(struct Dot) {0, 10},
		(struct Dot) {7, 15},
		(struct Dot) {9, 3},
		(struct Dot) {5, 20},
		(struct Dot) {1, 0},
		(struct Dot) {1, 20},
		(struct Dot) {4, 7}
	};

	qsort(arr, LEN, sizeof(*arr), Dot_sort_x_ascending);


	struct Orphans_Region regions[LEN] = {0};

	struct Dot * /*heap*/ edges = NULL;
	unsigned int edges_length = 0;
	unsigned int edges_allocation = 0;

	struct Dot low = {-10, -10};
	struct Dot high = {30, 30};

	echo = Orphans_fortune(
		LEN, arr,
		low, high,
		regions,
		&edges, &edges_length, &edges_allocation
	);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		return 1;
	}
	gu_sneeze("fortune() didn't return an error value\n");

	return 0;
}

