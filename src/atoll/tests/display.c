#include "../debug_display.c"

#include "../diagram.h"


int main(void)
{

	// phony diagram just for display purposes

	struct atoll_point site = {50, 50};

	struct atoll_hedge h = { .head = 0, .tail = 1 };

	struct atoll_point vertices[2] = {
		(struct atoll_point) {400, 100},
		(struct atoll_point) {100, 400},
	};

	struct atoll_diagram d = {
		.sites = &site, .site_count = 1,
		.hedges = &h, .hedges_length = 1,
		.vertices = vertices
	};


	/*heap*/ struct gu_echo *echo = NULL;

	echo = atoll_DEBUG_display(&d, 1);

	if (echo != NULL) {
		gu_echo_sneeze(echo);
		gu_echo_destroy(echo);
	}

}
