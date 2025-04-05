#include "../treasure.h"

#include "../diagram.h"
#include "../coast.h"

#include "gu/gu.h"
#include "gu/echo.h"

#include <stdbool.h>


int main(void)
{
	int e = 0;
	/*heap*/ struct gu_echo *echo = NULL;


	struct atoll_point sites[] = {
		(struct atoll_point) {10, 5},
		//(struct atoll_point) {14, 5},
		//(struct atoll_point) {5, 5},
		(struct atoll_point) {7, 10},
		(struct atoll_point) {11, 10},
		(struct atoll_point) {1, 20}
	};
	unsigned int sites_length = (sizeof(sites)/sizeof(*sites));


	struct atoll_diagram d = {0};
	e = atoll_diagram_init(&d, sites, sites_length, atoll_COPYSITES);
	if (e) {
		gu_sneeze("unable to init diagram: %d\n", e);
		goto fin;
	}

	struct atoll_coast c = {0};
	e = atoll_coast_init(&c, sites_length);
	if (e) {
		gu_sneeze("unable to init coast: %d\n", e);
		goto fin;
	}


	echo = atoll_treasure(&d, &c);
	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
		e = 1;
		goto fin;
	}


	fin:

	atoll_diagram_reset(&d);
	atoll_coast_reset(&c);

	return (bool)e;
}
