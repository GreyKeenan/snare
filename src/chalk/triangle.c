#include "./triangle.h"

static inline int Chalk_cross_2d(const struct Chalk_Point a, const struct Chalk_Point b)
{
	return a.x * b.y - b.x * a.y;
}

static inline int Chalk_lines_intersect(
	const struct Chalk_Point a1,
	struct Chalk_Point a2,
	const struct Chalk_Point b1,
	struct Chalk_Point b2
)
/* https://stackoverflow.com/a/565282 */
{
	a2.x -= a1.x;
	a2.y -= a1.y;
	b2.x -= b1.x;
	b2.y -= b1.y;

	struct Chalk_Point b1_minus_a1 = (struct Chalk_Point) {
		.x = b1.x - a1.x,
		.y = b1.y - a1.y
	};

	double a_magnitude = Chalk_cross_2d(b1_minus_a1, b2) / Chalk_cross_2d(a2, b2);
	double b_magnitude = Chalk_cross_2d(b1_minus_a1, a2) / Chalk_cross_2d(a2, b2);
	
	if (Chalk_cross_2d(b2, a2) == 0) {
		if (Chalk_cross_2d(b1_minus_a1, a2)) {

			if (

			return COLLINEAR; //TODO
		}
		return PARALLEL;
	}

	if (1) {
		return INTERSECTING;
	}

	return NON_INTERSECTING;
}

int Chalk_brute_triangulate(const struct Chalk_Point *points, unsigned int point_count, struct Chalk_Point **triangles_destination, unsigned int *triangles_count)
{
	return 1;
}


int Chalk_nodivision_linecollision(

