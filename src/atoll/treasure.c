#include "./treasure.h"

#include "./diagram.h"
#include "./coast.h"
#include "./siteEvent.h"
#include "./circleEvent.h"

#include "gu/echo.h"


/*heap*/ struct gu_echo *atoll_treasure(struct atoll_diagram * /*nonull*/ diagram, struct atoll_coast * /*nonull*/ coast)
{
	int e = 0; (void)e;
	/*heap*/ struct gu_echo *echo = NULL;


	echo = atoll_coast_prime(coast, diagram);
	if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to prime the beachline");


	// handle the lesser-y site between coast->circles & diagram->sites[coast->nextSite]
	// if both are empty, end the alg
	// if one is empty, use the other

	while (1) {
		if (coast->nextSite >= diagram->site_count && coast->circles_length == 0) {
			break;
		}

		if (coast->nextSite >= diagram->site_count) {
		} else if (coast->circles_length == 0
			|| diagram->sites[coast->nextSite].y < coast->circles[coast->circles_length - 1].center.y
		) {
			// handle site event
			echo = atoll_siteEvent(diagram, coast, coast->nextSite);
			if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to process site event #%u", coast->nextSite);
			coast->nextSite += 1;
			continue;
		}

		// handle circle event
		coast->circles_length -= 1;
		echo = atoll_circleEvent(diagram, coast, coast->circles[coast->circles_length]);
		if (echo != NULL) return gu_echo_wrap(echo, 0, "failed to process circle event");

	}

	return gu_echo_new(1, "TODO");
}
