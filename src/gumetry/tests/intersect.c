
#include "../line.h"

#include "gu/gu.h"


int test(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy)
{
	struct gumetry_point out = {0};

	struct gumetry_point a = {ax, ay};
	struct gumetry_point b = {bx, by};
	struct gumetry_point c = {cx, cy};
	struct gumetry_point d = {dx, dy};

	gu_sneeze("(%lf, %lf)->(%lf, %lf) & (%lf, %lf)->(%lf, %lf)\n\t", ax,ay, bx,by, cx,cy, dx,dy);
	switch (gumetry_line_intersection(out, a, b, c, d)) {
		case gumetry_INTERSECT:
			gu_sneeze("intersect at (%lf, %lf)\n", out[0], out[1]);
			break;
		case gumetry_PARALLEL:
			gu_sneeze("are parallel\n");
			break;
		case gumetry_COLLINEAR:
			gu_sneeze("are collinear\n");
			break;
		default:
			gu_sneeze("UNRECOGNIZED RETURN\n");
			break;
	}

	return 0;
}


int main(void)
{

	test(0,0, 1,1, 5,5, -5,5);
	test(0,0, 1,1, 5,5, -4,-4);
	test(1,0, 10,0, 7,10, 8,10);
	//test(1,1, 1,1, 5,7, 8,13);

}
