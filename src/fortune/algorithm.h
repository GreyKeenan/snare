#ifndef FORTUNE_algorithm
#define FORTUNE_algorithm

#include "./voronoi.h"
#include "./beach.h"

struct gu_echo;

/*heap*/ struct gu_echo *Fortune_algorithm(struct Fortune_voronoi diagram[static 1], struct Fortune_beach beach[static 1]);
/*
	assumes:
		`Fortune_voronoi` and `Fortune_beach` have each been initialized with their respective functions

	Uses Fortunes Algorithm to construct a Voronoi Diagram at `diagram`.
	The remaining beachline will contain unterminated edges.
	Subsequent functions can handle those edges, whether clipping or removing etc.

	returns NULL on success, or an allocated echo on error.
	`diagram` and `beach` may have been modified.
*/

#endif
