#ifndef GUMETRY_point
#define GUMETRY_point

struct gumetry_point { double x, y; };

static inline struct gumetry_point gumetry_point_average(const struct gumetry_point * /*nonull*/ points, unsigned int count)
{
	double x = 0;
	double y = 0;
	for (unsigned int i = 0; i < count; ++i) {
		x += points[i].x;
		y += points[i].y;
	}
	return (struct gumetry_point) { x/count, y/count };
}

#endif
