
#include "../coast.h"
#include "../diagram.h"

#include "gu/gu.h"

#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char **argv)
{

	int16_t directix = 10;
	int16_t x = 7;

	if (argc > 1) {
		if (argv[1][0] == 'b') {
			gu_sneeze("beach: 0 {-6.6} 1 {3.8} 2 {5.5} 3 {22.5} 4\n");
			return 0;
		}

		x = atoi(argv[1]);
	}


	int e = 0;

	#define SITESLEN (sizeof(sites)/sizeof(*sites))
	struct atoll_point sites[] = {
		(struct atoll_point) {5, 1},
		(struct atoll_point) {10, 6},
		(struct atoll_point) {0, 8}
	};
	
	#define FOCILEN (sizeof(foci)/sizeof(*foci))
	unsigned int foci[] = {
		0,
		// breakpoint with directix 10: (-6.64237, -2.203026)
		2,
		// (3.78523, 5.41802)
		0,
		// (5.51472, 5.48528)
		1,
		// (22.48528, -11.48528)
		0
	};

	unsigned int at = 0;
	e = atoll_coast_arcAtX(foci, FOCILEN, sites, directix, x, &at);
	if (e) {
		gu_sneeze("coast_arcAtX() error code: %d\n", e);
	}

	gu_sneeze("%d at: %u\n", x, at);

	

	return (bool)e;
}
