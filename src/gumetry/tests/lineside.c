
#include "../line.h"

#include "gu/gu.h"


int test(double l1, double l2, double l3, double l4, double p1, double p2) {
	struct gumetry_point a = {l1, l2};
	struct gumetry_point b = {l3, l4};
	struct gumetry_point p = {p1, p2};

	int n = gumetry_line_side(a, b, p);

	gu_sneeze("(%lf, %lf) is on the (0x%02x) side of (%lf, %lf)->(%lf, %lf)\n",
		p1,p2, n, l1,l2, l3,l4);

	return n;
}


int main(void)
{
	test(0,0, 2,1, 10,10);
	test(0,0, 2,1, 10,-10);
	test(0,0, 1,-1, 10,-10);
}
