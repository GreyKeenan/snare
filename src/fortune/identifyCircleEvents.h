#ifndef FORTUNE_identifyCircleEvents
#define FORTUNE_identifyCircleEvents

#include "./voronoi.h"
#include "./beach.h"

#include <stdint.h>

/*heap*/ struct gu_echo *Fortune_identifyCircleEvents(
	int16_t directix,
	unsigned int updated_parabola,

	const struct Fortune_voronoi diagram[static 1],
	const struct Fortune_beach beach[static 1],

	struct Fortune_point * /*nonull*/ circles,
	unsigned int * /*nonull*/ circles_length,
	unsigned int * /*nonull*/ circles_allocation
);
/*
	assumes:
		updated_parabola < beach->focuses_length - 1
		updated_parabola != 0

		the beachline is validly constructed

*/

#endif
