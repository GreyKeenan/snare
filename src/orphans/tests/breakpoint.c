
#include "../beachline.h"

#include "dot/dot.h"

#include "gu/gu.h"
#include "gu/echo.h"

void test(int16_t l, int16_t ax, int16_t ay, int16_t bx, int16_t by)
{
	struct Dot a = {ax, ay};
	struct Dot b = {bx, by};
	double result = Orphans_breakpoint_x(l, a, b);

	gu_sneeze("breakpoint_x(%d, (%d, %d), (%d, %d)) = %lf\n\n",
		l, a.x, a.y, b.x, b.y, result);
}

int main(void)
{
	test(2, 0,0, 1,0);
	test(2, 1,0, 0,0);
	test(2, 0,0, 0,1);
	test(2, 0,1, 0,0);

	test(10, 5,5, 1,3);

	test(15, 10,0, 0,10);
	test(-1, -10,-5, 0,-10);

	return 0;
}
