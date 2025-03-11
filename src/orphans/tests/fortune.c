
#include "../fortune.h"
#include "../half.h"

#include "dot/dot.h"
#include "dot/sort.h"

#include "gu/gu.h"
#include "gu/echo.h"

#include <stdlib.h>
#include <stdio.h>

// #include <limits.h>


int main(void)
{

	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;

	#define LEN 7
	struct Dot sites[LEN] = {
		(struct Dot) {0, 10},
		(struct Dot) {7, 15},
		(struct Dot) {9, 3},
		(struct Dot) {5, 20},
		(struct Dot) {1, 0},
		(struct Dot) {1, 20},
		(struct Dot) {4, 7}
	};
	qsort(sites, LEN, sizeof(*sites), Orphans_sortforme);

	unsigned int cells[LEN] = {0};

	/*heap*/ struct Orphans_half *halves = NULL;
	unsigned int halves_length = 0;
	unsigned int halves_allocation = 0;

	/*heap*/ struct Orphans_edge *edges = NULL;
	unsigned int edges_length = 0;
	unsigned int edges_allocation = 0;

	/*heap*/ struct Dot *vertices = NULL;
	unsigned int vertices_length = 0;
	unsigned int vertices_allocation = 0;

	echo = Orphans_fortune(
		sites, LEN,
		NULL, 0,
		cells,
		&halves, &halves_length, &halves_allocation,
		&edges, &edges_length, &edges_allocation,
		&vertices, &vertices_length, &vertices_allocation
	);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		e = 1;
		goto fin;
	}
	gu_sneeze("fortune() didn't return an error value\n");


	fin:

	gu_free(halves);
	gu_free(edges);
	gu_free(vertices);

	return e;
}

