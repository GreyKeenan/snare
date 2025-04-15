#include "./line.h"


int gumetry_line_intersection(
	struct gumetry_point out[static 1],
	struct gumetry_point a, struct gumetry_point b,
	struct gumetry_point c, struct gumetry_point d
)
{
	if (a.x == b.x && c.x == d.x) return (a.x == c.x)? gumetry_COLLINEAR:gumetry_PARALLEL;
	// both are vertical

	double m[2] = {0};
	double t[2] = {0};

	m[0] = (a.y - b.y) / (a.x - b.x);
	t[0] = a.y - m[0]*a.x;

	m[1] = (c.y - d.y) / (c.x - d.x);
	t[1] = c.y - m[1]*c.x;

	if (m[0] == m[1]) return (t[0] == t[1])? gumetry_COLLINEAR:gumetry_PARALLEL;
	// parallel

	int s = 0;
	if (a.x == b.x) {
		out->x = a.x;
		s = 1;
	} else if (c.x == d.x) out->x = c.x;
	else out->x = (t[0] - t[1]) / (m[1] - m[0]);

	out->y = m[s]*out->x + t[s];

	return gumetry_INTERSECT;
}

int gumetry_line_side(struct gumetry_point a, struct gumetry_point b, struct gumetry_point p)
{
	if (a.x == b.x) {
		if (p.x == a.x) return gumetry_ONLINE;
		return (p.x > a.x)? gumetry_RIGHT:gumetry_LEFT;
	}
	if (a.y == b.y) {
		if (p.y == a.y) return gumetry_ONLINE;
		return (p.y > a.y)? gumetry_ABOVE:gumetry_BELOW;
	}

	const double m = (a.y - b.y) / (a.x - b.x);
	const double t = a.y - m*a.x;

	int side = 0;

	const double y = m*p.x + t;
	if (p.y == y) return gumetry_ONLINE;
	else side |= (p.y > y)? gumetry_ABOVE:gumetry_BELOW;

	const double x = (p.y - t) / m;
	if (p.x == x) return gumetry_ONLINE;
	else side |= (p.x > x)? gumetry_RIGHT:gumetry_LEFT;

	return side;
}
