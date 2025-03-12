
#include "../beach.h"

#include "../breakpoint.h"

#include "gu/gu.h"
#include "gu/echo.h"

#include <stdlib.h>


void printbeach(int directix, const struct Fortune_point * /*nonull*/ sites, const unsigned int *focuses, size_t focuses_len)
{
	gu_sneeze("beach-focuses[%zu]. Breakpoints with directix:%d. \n", focuses_len, directix);
	for (size_t i = 0; i < focuses_len; ++i) {
		if (i != 0) {
			gu_sneeze("\t(%lf)\n", Fortune_breakpoint_x(directix, sites[focuses[i-1]], sites[focuses[i]]));
		}
		gu_sneeze("\t[%zu]:(%d, %d)\n",
			i, sites[focuses[i]].x, sites[focuses[i]].y);
	}
}


int main(int argc, char **argv)
{

	int keyx = 0;
	if (argc > 1) {
		keyx = atoi(argv[1]);
	}

	#define KEY sites
	struct Fortune_point sites[] = {
		(struct Fortune_point){ keyx , 10 }, // the key

		(struct Fortune_point){ 5 , 1  },
		(struct Fortune_point){ 10, 6  },
		(struct Fortune_point){ 0 , 8  },

	};
	const size_t siteslen = sizeof(sites) / sizeof(*sites);
	(void)siteslen;

	gu_sneeze("key: (%d, %d)\n", KEY->x, KEY->y);

	#define LEN 5
	unsigned int focuses[LEN] = {
		1,
		// breakpoint with directix 10: (-6.64237, -2.203026)
		3,
		// (3.78523, 5.41802)
		1,
		// (5.51472, 5.48528)
		2,
		// (22.48528, -11.48528)
		1
	};
	const size_t length = sizeof(focuses) / sizeof(*focuses);

	printbeach(KEY->y, sites, focuses, length);

	unsigned int at = 0;
	/*heap*/ struct gu_echo *echo = Fortune_beach_parabolaBelowPoint(focuses, length, sites, KEY, &at);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		return 1;
	}

	gu_sneeze("at:%u\n", at);

	return 0;
}
