
#include "../breakpoint.h"

#include "gu/gu.h"


typedef double expouble;
#define EXPB "lf"

struct scenario {
	double directix;
	struct atoll_podouble left;
	struct atoll_podouble right;

	expouble expected_x;
	expouble expected_y;
};

static inline struct scenario scen(double d, double lx, double ly, double rx, double ry, expouble ex, expouble ey)
{
	return (struct scenario) {
		.directix = d,
		.left.x  = lx, .left.y  = ly,
		.right.x = rx, .right.y = ry,
		.expected_x = ex, .expected_y = ey
	};
}


int test(struct scenario s) {
	struct atoll_podouble bp = atoll_breakpoint(s.directix, s.left, s.right);

	printf("d:%.1lf l:(%.1lf, %.1lf) r:(%.1lf, %.1lf) exp:(%"EXPB", %"EXPB")"
		"\n""\t""got:(%lf, %lf)"
		"\n",
		s.directix, s.left.x, s.left.y, s.right.x, s.right.y,
		s.expected_x, s.expected_y,
		bp.x, bp.y
	);

	return 0;
}


int main(void)
{
/*
horizontally-aligned case

vertically-aligned cases
	higher left
	higher right

on the directix cases
	left on directix
	right on directix

unaligned cases
	higher left
	higher right
*/


	#define LEN (sizeof(scenes)/sizeof(*scenes))
	struct scenario scenes[] = {
		  scen(10, 5,5, 10,5,  15/2.0, 55/8.0) //horizontally-aligned

		, scen(6, 2,3,2,5, 0.26795,4) //vertically aligned, lower-first
		, scen(6, 2,5,2,3, 3.73205,4) //vertically aligned, higher-first

		, scen(17, 2,17,-2,7, 2,11.2) //left on directix
		, scen(17, 2,7,-2,17, -2,11.2) //right on directix

		// unaligned:
		, scen(10, 3,5,4,4, 5.74597,6.74597)
		, scen(14, -7,-3,11,4, 0.74094,3.73758)
		, scen(-7, -30,-18, 30,-23, -2.2402,-47.50235)
	};

	for (size_t i = 0; i < LEN; ++i) {
		printf("[%2zu] ", i);
		test(scenes[i]);
	}

}
