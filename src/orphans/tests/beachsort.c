
#include "../beachline.h"
#include "../sand.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"

#include <stdlib.h>


void printbeach(int directix, const struct Dot * /*nonull*/ sites, const struct Orphans_sand * /*nonull*/ beach, size_t beachlen)
{
	gu_sneeze("beach[%zu]. Breakpoints with directix:%d. \n", beachlen, directix);
	for (size_t i = 0; i < beachlen; ++i) {
		if (i != 0) {
			gu_sneeze("\t(%lf)\n", Orphans_breakpoint_x(directix, sites[beach[i-1].site], sites[beach[i].site]));
		}
		gu_sneeze("\t[%zu]:(%d, %d)\n",
			i, sites[beach[i].site].x, sites[beach[i].site].y);
	}
}


int main(int argc, char **argv)
{

	int keyx = 0;
	if (argc > 1) {
		keyx = atoi(argv[1]);
	}

	#define KEY sites
	struct Dot sites[] = {
		(struct Dot){ keyx , 10 }, // the key

		(struct Dot){ 5 , 1  },
		(struct Dot){ 10, 6  },
		(struct Dot){ 0 , 8  },

	};
	const size_t siteslen = sizeof(sites) / sizeof(*sites);
	(void)siteslen;

	gu_sneeze("key: (%d, %d)\n", KEY->x, KEY->y);

	struct Orphans_sand beach[] = {
		(struct Orphans_sand){ 1, 0 },
		// breakpoint with directix 10: (-6.64237, -2.203026)
		(struct Orphans_sand){ 3, 0 },
		// (3.78523, 5.41802)
		(struct Orphans_sand){ 1, 0 },
		// (5.51472, 5.48528)
		(struct Orphans_sand){ 2, 0 },
		// (22.48528, -11.48528)
		(struct Orphans_sand){ 1, 0 }
	};
	const size_t beachlen = sizeof(beach) / sizeof(*beach);

	printbeach(KEY->y, sites, beach, beachlen);

	unsigned int at = 0;
	/*heap*/ struct gu_echo *echo = Orphans_beachline_searchbetween(&at, sites, KEY, beach, beachlen);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		return 1;
	}

	gu_sneeze("at:%u\n", at);

	return 0;
}

/*
notes


250308
==========

ohhhh.
Because of the way beachline_compare() is written,
it will always find an == match.
When gu_searchbetween() finds an equal match,
it adds 1 to the index to ensure i - 1 <= key.

So, either I need to use a bsearch() function that isnt a between,
like the std,
but it still needs the context.

Or, I can rewrite how beachline_compare() works.

OR, i can always subtract 1 from the return value and be lazy?
I'll probably have to deal with it later though.

update: i added the -1 temproray fix in beachline_searchbetween()

*/
