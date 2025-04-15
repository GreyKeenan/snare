
#include "../math.h"

#include "gu/gu.h"

#include <math.h>


int test(double ax, double ay, double bx, double by, double cx, double cy, double ex, double ey)
{
	struct gumetry_point cc = atoll_circumcenter(
		(struct atoll_point) {ax, ay},
		(struct atoll_point) {bx, by},
		(struct atoll_point) {cx, cy}
	);

	gu_sneeze("(%lf, %lf) =?= (%lf, %lf)\n", cc.x, cc.y, ex, ey);
	return 0;
}


int main(void)
{

	test(7,10, 10,5, 11,10, 9,39/5.0);
	test(5,15, 15,2, 21,11, 345/28.0, 72/7.0);
	test(7,3, 2,2, -4,-3, 267/38,-385/38);

	test(20,-7, 10,-7, 10,1, 15,-3); // 2 points are horizontally aligned, making 0 slope
	test(10,5, 20,5, 30,5, NAN,NAN); // 3 points are horiz aligned, meaning not a triangle
	test(10,6, 10,3, 10,9, NAN,NAN); // 3 points are verti aligned, meaning not a triangle
	test(1,1, 2,2, 3,3, NAN,NAN);    // 3 points colinear, no triangle

}
