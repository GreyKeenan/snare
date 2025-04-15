#include "./triangle.h"


struct gumetry_point gumetry_circumcenter(
	struct gumetry_point p0,
	struct gumetry_point p1,
	struct gumetry_point p2
)
{
	if (p1.y - p0.y == 0 && p1.y - p2.y == 0) return (struct gumetry_point) {NAN,NAN};

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


	if (m[0] - m[1] == 0) return (struct gumetry_point) {NAN, NAN};


	int solve = 0;
	if (p0.y == p1.y) {
		x[2] = (p0.x + p1.x) / 2;
		solve = 1;
	} else if (p1.y == p2.y) {
		x[2] = (p1.x + p2.x) / 2;
	} else {
		x[2] = (b[1] - b[0]) / (m[0] - m[1]);
	}

	return (struct gumetry_point) {
		.x = x[2],
		.y = m[solve] * x[2] + b[solve]
	};
}
