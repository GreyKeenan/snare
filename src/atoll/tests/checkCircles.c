
#include "../coast.h"
#include "../circle.h"

#include "gu/gu.h"

#include <stdbool.h>
#include <string.h>


struct atoll_circle new(double x, double y, double r) {
	return (struct atoll_circle) {.center.x = x, .center.y = y, .radius = r};
}

int main(void)
{

	int e = 0;

	struct atoll_circle static_circles[] = {
		new(0,0,10),	// should be removed for site (1, 1)
		new(-20,11,7),
		new(5,5,7),	// removed
		new(7,-5,30),	// removed
		new(-50,-50,9)
	};
	unsigned int circles_length = sizeof(static_circles) / sizeof(*static_circles);

	struct atoll_circle *circles = malloc(sizeof(static_circles));
	if (circles == NULL) {
		gu_sneeze("unable to malloc for circles\n");
		e = 1;
		goto fin;
	}
	memcpy(circles, static_circles, sizeof(static_circles));


	struct atoll_point site = { 1, 1 };


	atoll_coast_checkCircles(&circles, &circles_length, site);

	for (unsigned int i = 0; i < circles_length; ++i) {
		gu_sneeze("[%2u]: (%lf, %lf) %lf\n", i, circles[i].center.x, circles[i].center.y, circles[i].radius);
	}




	fin:

	gu_free(circles);

	return (bool)e;
	
}
