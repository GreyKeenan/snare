#include "./math.h"

#include <math.h>


double atoll_parabola_y(
	double x,
	double h, // vertex.x = focus.x
	double f, // focus.y
	double d  // directixY
)
{ return ((x - h)*(x - h)) / (2*(f - d))  +  (f + d)/2; }

struct atoll_podouble atoll_circumcenter(
	struct atoll_podouble p0,
	struct atoll_podouble p1,
	struct atoll_podouble p2
)
{
	if (p1.y - p0.y == 0 && p1.y - p2.y == 0) return (struct atoll_podouble) {NAN,NAN};

	double x[3] = {0};
	double y[2] = {0};
	double m[2] = {0};
	double b[2] = {0};

	x[0] = (p1.x + p0.x) / 2;
	y[0] = (p1.y + p0.y) / 2;
	m[0] = (p0.x - p1.x)
	/ (p1.y - p0.y);
	b[0] = y[0] - m[0]*x[0];

	x[1] = (p1.x + p2.x) / 2;
	y[1] = (p1.y + p2.y) / 2;
	m[1] = (p2.x - p1.x)
	/ (p1.y - p2.y);
	b[1] = y[1] - m[1]*x[1];


	if (m[0] - m[1] == 0) return (struct atoll_podouble) {NAN, NAN};


	int solve = 0;
	if (p0.y == p1.y) {
		x[2] = (p0.x + p1.x) / 2;
		solve = 1;
	} else if (p1.y == p2.y) {
		x[2] = (p1.x + p2.x) / 2;
	} else {
		x[2] = (b[1] - b[0]) / (m[0] - m[1]);
	}

	return (struct atoll_podouble) {
		.x = x[2],
		.y = m[solve] * x[2] + b[solve]
	};
}
