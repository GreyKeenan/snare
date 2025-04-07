
#include "../circle.h"

#include "gu/gu.h"




#define FORARC 531


int test(
	double directix,
	int16_t ax, int16_t ay,
	int16_t bx, int16_t by,
	int16_t cx, int16_t cy,
	bool expected,
	double ccx, double ccy
)
{
	struct atoll_circle circ = {0};
	int out = atoll_arcIsntConverging(
		&circ, FORARC,
		directix,
		(struct atoll_point) {ax, ay},
		(struct atoll_point) {bx, by},
		(struct atoll_point) {cx, cy}
	);

	gu_sneeze("return:%d expected:%d\n", out, expected);
	gu_sneeze("circumcenter:(%.30lf, %.30lf)\n", circ.center.x, circ.center.y);
	gu_sneeze("expected    :(%.30lf, %.30lf)\n", ccx, ccy);
	gu_sneeze("\n");

	return 0;
}

int main(void)
{

	test(15, -10,6, -6,7, -5,15,
		false, -573/62.0,711/62.0);

	// directix cases
	test(9, 1,8, 1,9, 1,7,
		true, 0,0);
	test(9, 1,9, 2,8, 3,9,
		false, 2,9);
	test(9, 0,9, 2,5, 4,7,
		false, 5/3.0,22/3.0);

	// vertically aligned
	test(50, 10,10, 10,30, 10,40,
		true, 0,0);
	// horizontally aligned
	test(10, 5,5, 10,5, 20,5,
		true, 0,0);
	test(27.8, 1,0, 9,0, 26,21,
		false, 5,20.61905);
	// otherwise colinear
	test(32, 1,0, 4,5, 7,10,
		true, 0,0);

	// duplicate foci
	test(14.3, 19,-6, 9,8, 19,-6,
		true, 0,0);
	test(14.3, 19,-6, 9,8, 19,-6,
		true, 0,0);

	
	// wow, this is some complete coverage if I've ever seen it :/



	// exactly equal
	test(250, 250,250, 0,0, 500,0,
		false, 250,0);

}

/*

special cases:

~~[abc] for a and c~~

...abc... where a, b, or c are on the directix
...abc... where a, b, and c are colinear

...aba...
	For this to happen, b.y must be greater than a.y

*/
