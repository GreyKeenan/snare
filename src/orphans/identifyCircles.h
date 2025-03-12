#ifndef ORPHANS_identifyCircles
#define ORPHANS_identifyCircles


static inline /*heap*/ struct gu_echo *Orphans_identifyCircles(
	unsigned int beach_update, // the index to search for new circle events around

	const struct Dot * /*nonull*/ sites,

	/*heap*/ struct Orphans_sand * /*nonull*/ beach[static 1],
	unsigned int beach_length[static 1],
	unsigned int beach_allocation[static 1],

	/*heap*/ struct Dot * /*nonull*/ circles[static 1],
	unsigned int circles_length[static 1],
	unsigned int circles_allocation[static 1],
)
{
	(void)beach_update;
	(void)sites;
	(void)beach;
	(void)beach_length;
	(void)beach_allocation;
	(void)circles;
	(void)circles_length;
	(void)circles_allocation;

	/*heap*/ struct gu_echo *echo = NULL;
	int e = 0;

	// ==========

	return echo;
}


#endif
