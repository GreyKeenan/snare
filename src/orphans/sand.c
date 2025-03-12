#include "./sand.h"


#include "dot/dot.h"


int Orphans_sand_sort_sitex_ascending(const struct Dot * /*nonull*/ sites, unsigned int * /*nonull*/ a, unsigned int * /*nonull*/ b)
{
	if (sites[*a].x < sites[*b].x) {
		return -1;
	}
	if (sites[*a].x > sites[*b].x) {
		return 1;
	}
	return 0;
}
